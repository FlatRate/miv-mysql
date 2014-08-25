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
    
    Special Thanks to Alex Rathbone for some of the source code written in this module.
*/

/*
        File: MySQL-Handle-Manager.h
        Description: Contains a class with static methods that allows the managing of numerous MySQL handles.
*/

#pragma once
#include "mysql-handle.h"
#include <map>

#define MAX_MYSQL_HANDLES 10

class HandleManager
{
public:
        static int AddHandle(MySQLHandle* handle);
        static MySQLHandle* GetHandle(unsigned int id);
        static void RemoveHandle(unsigned int id);
        static unsigned int Count();

private:
        static std::map<unsigned int, MySQLHandle*> Handles;
};
