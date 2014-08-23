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
    File: Functions.cpp
    Description: -
*/

#include "functions.h"

#include <CReturnValue.h>

#include "mysql-handle-manager.h"
#include "mysql-handle.h"

#include "clog.h"

SDK::ScriptArgument* plugin_mysql_debug(SDK::ScriptArguments* pArugments)
{
	bool debug=pArugments->GetBool(0);
	if(debug!=cLog::isOpen())
	{
		if(debug)
		cLog::Initialise();
		else
		cLog::Close();
	}
	return new CReturnValue();
}

SDK::ScriptArgument* plugin_mysql_connect(SDK::ScriptArguments* pArugments)
{
	const char* host = pArugments->GetString(0);
	const char* username = pArugments->GetString(1);
	const char* password = pArugments->GetString(2);
	const char* database = pArugments->GetString(3);
	int port = 3306;
	if(pArugments->Count() == 5)
	{
		port = pArugments->GetInteger(4);
	}
	
	MySQLHandle* handle = new MySQLHandle(host, username, password, database, port);

	if(!handle->isValid())
	{
		cLog::PrintFormatConsole("Error: mysql.connect(%s, %s, %s, %s) on port %i failed!", host, username, password, database, port);
		delete handle;
		return new CReturnValue(0);
	}

	int id = HandleManager::AddHandle(handle);

	if(id == 0)
	{
		cLog::Print("Error: Can not create anymore handles, limit reached.", true);
		delete handle;
		return new CReturnValue(0);
	}
	cLog::PrintFormat("MySQL Connection successful on Handle %i.", id);
	return new CReturnValue(id);
}

SDK::ScriptArgument* plugin_mysql_close(SDK::ScriptArguments* pArugments)
{
	int id = pArugments->GetInteger(0);

	HandleManager::RemoveHandle(id);
	return new CReturnValue(id);
}

SDK::ScriptArgument* plugin_mysql_errno(SDK::ScriptArguments* pArugments)
{
	int id = pArugments->GetInteger(0);

	MySQLHandle* handle = HandleManager::GetHandle(id);

	if(handle == NULL)
	{
		return new CReturnValue(1);
	}
	return new CReturnValue(handle->getLastError());
}

SDK::ScriptArgument* plugin_mysql_ping(SDK::ScriptArguments* pArugments)
{
	int id = pArugments->GetInteger(0);

	MySQLHandle* handle = HandleManager::GetHandle(id);

	if(handle == NULL)
	{
		return new CReturnValue(-1);
	}
	return new CReturnValue(handle->ping());
}

SDK::ScriptArgument* plugin_mysql_query(SDK::ScriptArguments* pArugments)
{
	int id = pArugments->GetInteger(0);
	const char* query = pArugments->GetString(1);

	MySQLHandle* handle = HandleManager::GetHandle(id);
	
	if (handle == NULL)
	{
		return new CReturnValue(false);
	}
	return new CReturnValue(handle->executeQuery(query));
}

SDK::ScriptArgument* plugin_mysql_store_result(SDK::ScriptArguments* pArugments)
{
	int id = pArugments->GetInteger(0);

	MySQLHandle* handle = HandleManager::GetHandle(id);

	if(handle == NULL)
	{
		return new CReturnValue(false);
	}
	return new CReturnValue(handle->storeResult());
}

SDK::ScriptArgument* plugin_mysql_free_result(SDK::ScriptArguments* pArugments)
{
	int id = pArugments->GetInteger(0);

	MySQLHandle* handle = HandleManager::GetHandle(id);

	if(handle == NULL)
	{
		return new CReturnValue(false);
	}
	return new CReturnValue(handle->freeResult());
}

SDK::ScriptArgument* plugin_mysql_num_rows(SDK::ScriptArguments* pArugments)
{
	int id = pArugments->GetInteger(0);

	MySQLHandle* handle = HandleManager::GetHandle(id);
	if(handle == NULL)
	{
		return new CReturnValue(-1);
	}
	return new CReturnValue(handle->getResultRowCount());
}

SDK::ScriptArgument* plugin_mysql_num_fields(SDK::ScriptArguments* pArugments)
{
	int id = pArugments->GetInteger(0);

	MySQLHandle* handle = HandleManager::GetHandle(id);

	if(handle == NULL)
	{
		return new CReturnValue(-1);
	}
	return new CReturnValue(handle->getResultFieldCount());
}

SDK::ScriptArgument* plugin_mysql_fetch_row(SDK::ScriptArguments* pArugments)
{
	int id = pArugments->GetInteger(0);
	
	MySQLHandle* handle = HandleManager::GetHandle(id);

	if(handle == NULL)
	{
		return new CReturnValue(-1);
	}
	return new CReturnValue(handle->fetchResultRow());
}

SDK::ScriptArgument* plugin_mysql_fetch_row_assoc(SDK::ScriptArguments* pArugments)
{
	int id = pArugments->GetInteger(0);
	
	MySQLHandle* handle = HandleManager::GetHandle(id);

	if (handle == NULL)
	{
		return new CReturnValue(-1);
	}
	return new CReturnValue(handle->fetchResultRowAssoc());
}

SDK::ScriptArgument* plugin_mysql_fetch_field_row(SDK::ScriptArguments* pArugments)
{
	int id = pArugments->GetInteger(0);
	int fieldIndex = pArugments->GetInteger(1);

	MySQLHandle* handle = HandleManager::GetHandle(id);

	if(handle == NULL)
	{
		return new CReturnValue(0);
	}

	const char* data = handle->fetchFieldFromRow(static_cast<unsigned int>(fieldIndex));

	if (data == NULL)
	{
		return new CReturnValue(0);
	}
	return new CReturnValue(data);
}

SDK::ScriptArgument* plugin_mysql_escape_string(SDK::ScriptArguments* pArugments)
{
	int id = pArugments->GetInteger(0);
	const char* string = pArugments->GetString(1);

	MySQLHandle* handle = HandleManager::GetHandle(id);

	if(handle == NULL)
	{
		return new CReturnValue(0);
	}

	char* escaped = new char[strlen(string)*2+1];
	mysql_real_escape_string(handle->getConnection(), escaped, string, strlen(string));
	return new CReturnValue(escaped);
}
