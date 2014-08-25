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
        File: MySQL Handle Manager (Source File)

        Description: Contains the class definitions for HandleManager.h (see documentation of that file for more information).
*/

#include "mysql-handle-manager.h"
#include <SDK.h>
#include "clog.h"

// Static variables
std::map<unsigned int, MySQLHandle*> HandleManager::Handles;

int HandleManager::AddHandle(MySQLHandle* handle)
{
	if(handle == NULL)
		return false;

	unsigned int availableId = 0;

	for (unsigned int i = 1; i <= MAX_MYSQL_HANDLES; ++i)
	{
		if (Handles[i] == NULL)
		{
			availableId = i;
			break;
		}
	}

	if (availableId == 0)
		return 0;

	handle->handleId = availableId;
	Handles[availableId] = handle;
	return availableId;
}

MySQLHandle* HandleManager::GetHandle(unsigned int id)
{
	return Handles[id];
}

void HandleManager::RemoveHandle(unsigned int id)
{
	if (Handles[id] != NULL)
	{
		MySQLHandle* handle = Handles[id];
		Handles.erase(id);
		handle->closeConnection();
		delete handle;

		cLog::PrintFormat("Handle %i connection closed.", id);
	}
}
