/*
    This file is part of the open source MIV-MySQL project.

    MIV-MySQL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MIV-MySQL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MIV-MySQL source code. If not, see <http://www.gnu.org/licenses/>.
*/

/*
        File: MySQL Handler (Source File)

        Description: Contains the class definitions for MySQL-Handle.h (see documentation of that file for more information).
*/

#include "mysql-handle.h"
#include "cLog.h"

MySQLHandle::MySQLHandle(const char* host, const char* username, const char* password, const char* database, int port)
{
	connection = mysql_init(NULL);
	storedResult = NULL;
	storedRow = NULL;

	if (connection != NULL)
	{
		connection = mysql_real_connect(connection, host, username, password, database, port, NULL, NULL);
	}
	else
	{
		cLog::Print("ERROR: mysql_init() returned NULL on new MySQL handle", false);
	}
}

MySQLHandle::~MySQLHandle() { }

const bool MySQLHandle::isValid()
{
	return (connection != NULL); // true if connection is not NULL
}

MYSQL* MySQLHandle::getConnection()
{
	return connection;
}

void MySQLHandle::closeConnection()
{
	if (connection != NULL)
	{
		mysql_close(connection);
		if (storedResult != NULL) freeResult();
	}
}

unsigned int MySQLHandle::getLastError()
{
	if (connection == NULL)
	{
		return 0;
	}
	return mysql_errno(connection);
}

int MySQLHandle::ping()
{
	if (connection == NULL)
	{
		return -1;
	}
	return mysql_ping(connection);
}

bool MySQLHandle::executeQuery(const char* query)
{
	if (connection == NULL)
	{
		cLog::PrintFormatConsole("(%i) ERROR: mysql_query() - Connection was NULL", handleId);
		return false;
	}

	if (mysql_query(connection, query) != 0)
	{
		cLog::PrintFormatConsole("(%i) ERROR: Query - %s", handleId, query);
		cLog::PrintFormatConsole("(%i) ERROR: %s", handleId, mysql_error(connection));
		return false;
	}
	cLog::PrintFormat("(%i) Query: %s", handleId, query);
	return true;
}

bool MySQLHandle::storeResult()
{
	if (connection == NULL)
	{
		return false;
	}

	storedResult = mysql_store_result(connection);

	if (storedResult == NULL)
	{
		return false;
	}

	cLog::PrintFormat("(%i) Stored result.", handleId);
	return true;
}

bool MySQLHandle::freeResult()
{
	if (connection == NULL || storedResult == NULL)
	{
		cLog::PrintFormatConsole("(%i) ERROR: mysql_free_result() - Connection or result was NULL", handleId);
		return false;
	}

	mysql_free_result(storedResult);
	storedResult = NULL;
	storedRow = NULL;

	cLog::PrintFormat("(%i) Freed result.", handleId);
	return true;
}

int MySQLHandle::getResultRowCount()
{
	if (connection == NULL || storedResult == NULL)
	{
		cLog::PrintFormatConsole("(%i) ERROR: mysql_num_rows() - Connection or result was NULL", handleId);
		return -1;
	}

	return static_cast<int>(mysql_num_rows(storedResult));
}

int MySQLHandle::getResultFieldCount()
{
	if (connection == NULL || storedResult == NULL)
	{
		cLog::PrintFormatConsole("(%i) ERROR: mysql_num_fields() - Connection or result was NULL", handleId);
		return -1;
	}
	return static_cast<int>(mysql_num_fields(storedResult));
}

int MySQLHandle::getQueryAffectedRows()
{
	if (connection == NULL)
	{
		cLog::PrintFormatConsole("(%i) ERROR: mysql_affected_rows() - Connection was NULL", handleId);
		return -1;
	}

	return static_cast<int>(mysql_affected_rows(connection));
}

bool MySQLHandle::fetchResultRow()
{
	if (connection == NULL || storedResult == NULL)
	{
		cLog::PrintFormatConsole("(%i) ERROR: mysql_fetch_result() - Connection or result was NULL", handleId);
		return false;
	}

	storedRow = mysql_fetch_row(storedResult);

	if(storedRow == NULL) return false;
	else return true;
}

const char* MySQLHandle::fetchFieldFromRow(unsigned int fieldIndex)
{
	if (connection == NULL || storedResult == NULL || storedRow == NULL)
	{
		cLog::PrintFormatConsole("(%i) ERROR: mysql_fetch_field_row() - Connection, result or row was NULL", handleId);
		return NULL;
	}
	if (fieldIndex >= mysql_num_fields(storedResult) || fieldIndex < 0)
	{
		cLog::PrintFormatConsole("(%i) ERROR: mysql_fetch_field_row() - Field index too high, can't be above %i.", handleId, mysql_num_fields(storedResult) -1);
		return NULL;
	}
	return storedRow[fieldIndex];
}