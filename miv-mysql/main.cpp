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
	File: Main File

	Description: This file contains the entry point for the MIV-MySQL module. It will initialise the module,
	register the 'mysql' class and the required functions.
*/

#include <SDK.h>
#include <Platform.h>

#include "functions.h"
#include "clog.h"

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID reserved)
{
	if(fdwReason == DLL_PROCESS_ATTACH)
	{
		printf("\n**** Loading MySQL Plugin.\n");
	}
	else if(fdwReason == DLL_PROCESS_DETACH)
	{
		printf("\n**** Unloading MySQL Plugin.\n");
	}
	return true;
}

EXPORT bool InitializeModule(SDK::ModuleData* data)
{
	SDK::ScriptClass* mysql = data->CreateClass("mysql");
	
	mysql->AddStaticFunction("debug", (fnScriptFunction)plugin_mysql_debug, "b");
	mysql->AddStaticFunction("connect", (fnScriptFunction)plugin_mysql_connect, "ssss");
	mysql->AddStaticFunction("close", (fnScriptFunction)plugin_mysql_close, "i");
	mysql->AddStaticFunction("errno", (fnScriptFunction)plugin_mysql_errno, "i");
	mysql->AddStaticFunction("ping", (fnScriptFunction)plugin_mysql_ping, "i");
	mysql->AddStaticFunction("query", (fnScriptFunction)plugin_mysql_query, "is");
	mysql->AddStaticFunction("store_result", (fnScriptFunction)plugin_mysql_store_result, "i");
	mysql->AddStaticFunction("free_result", (fnScriptFunction)plugin_mysql_free_result, "i");
	mysql->AddStaticFunction("num_rows", (fnScriptFunction)plugin_mysql_num_rows, "i");
	mysql->AddStaticFunction("num_fields", (fnScriptFunction)plugin_mysql_num_fields, "i");
	mysql->AddStaticFunction("fetch_row", (fnScriptFunction)plugin_mysql_fetch_row, "i");
	mysql->AddStaticFunction("fetch_row_assoc", (fnScriptFunction)plugin_mysql_fetch_row, "i");
	mysql->AddStaticFunction("fetch_field_row", (fnScriptFunction)plugin_mysql_fetch_field_row, "ii");
	mysql->AddStaticFunction("escape_string", (fnScriptFunction)plugin_mysql_escape_string, "is");
	return true;
}

EXPORT unsigned int GetSDKVersion()
{
	return SDK_VERSION;
}
