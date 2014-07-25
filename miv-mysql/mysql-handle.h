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
        File: MySQL-Handle.h
        Description: Describes a single MySQL handle. Wrapper class for things like the
        pointer to an instance of MYSQL, cached data and what not. Most functions registered to MultIV will require at least one active MySQL handle.

        The MySQLHandle class also wraps a lot of calls to the libmysql API, simplifying some things.
*/

#pragma once
#include <my_global.h>
#include <mysql.h>

class MySQLHandle
{
public:
        MySQLHandle(const char* host, const char* username, const char* password, const char* database, int port = 3306);
        ~MySQLHandle();

        /*
                Returns true if the MySQLHandle is valid and can perform operations.
        */
        const bool isValid();


        /*
                Returns the handle's pointer to an instance of MYSQL. Where possible,
                class functions should be used over directly calling libmysql functions.
        */
        MYSQL* getConnection();

        /*
                This is the safe way of closing the MySQL handle. It is much preferred
                to simply freeing the object.
        */
        void closeConnection();

        /*
                Returns the error code for the most recently invoked function that can
                succeed or fail. If it returns 0, no error occurred.
        */
        unsigned int getLastError();

        /*
                Returns 0 if connection is still active, non-zero on error.
        */
        int ping();

        /*
                Attempts to execute a query on the MySQL handle.
                Returns true on success.
        */
        bool executeQuery(const char* query);

        /*
                Attempts to store the result from the most recently executed query.
                Returns true on success.
        */
        bool storeResult();

        /*
                Frees the currently stored result.
                Returns true if a result was freed.
        */
        bool freeResult();

        /*
                Returns the amount of rows from the stored result, if one is available.
                Returns -1 on any error.
        */
        int getResultRowCount();

        /*
                Returns the amount of fields for each row of the stored result, if one is available.
                Returns -1 on any error.
        */
        int getResultFieldCount();

        /*
                Returns the amount of affected rows by the last query.
                Returns -1 on any error.
        */
        int getQueryAffectedRows();

        /*
                Returns true if a row was successfully fetched from the stored result set.
                Returns false when there are no more rows to retrieve.
        */
        bool fetchResultRow();

        /*
                Returns the data from the currently stored row at the specified field index, if one
                is available. Otherwise returns NULL.
        */
        const char* fetchFieldFromRow(unsigned int fieldIndex);

private:
        friend class HandleManager;

        MYSQL* connection;
        MYSQL_RES* storedResult;
        MYSQL_ROW storedRow;
        int handleId;
};