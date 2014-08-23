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
    File: Functions.h
    Description: Declares all of the functions that will be registered within MultiV.
*/

#pragma once
#include <SDK.h>

SDK::ScriptArgument* plugin_mysql_debug(SDK::ScriptArguments* pArugments);
SDK::ScriptArgument* plugin_mysql_connect(SDK::ScriptArguments* pArugments);
SDK::ScriptArgument* plugin_mysql_close(SDK::ScriptArguments* pArugments);
SDK::ScriptArgument* plugin_mysql_errno(SDK::ScriptArguments* pArugments);
SDK::ScriptArgument* plugin_mysql_ping(SDK::ScriptArguments* pArugments);
SDK::ScriptArgument* plugin_mysql_query(SDK::ScriptArguments* pArugments);
SDK::ScriptArgument* plugin_mysql_store_result(SDK::ScriptArguments* pArugments);
SDK::ScriptArgument* plugin_mysql_free_result(SDK::ScriptArguments* pArugments);
SDK::ScriptArgument* plugin_mysql_num_rows(SDK::ScriptArguments* pArugments);
SDK::ScriptArgument* plugin_mysql_num_fields(SDK::ScriptArguments* pArugments);
SDK::ScriptArgument* plugin_mysql_fetch_row(SDK::ScriptArguments* pArugments);
SDK::ScriptArgument* plugin_mysql_fetch_row_assoc(SDK::ScriptArguments* pArugments);
SDK::ScriptArgument* plugin_mysql_fetch_field_row(SDK::ScriptArguments* pArugments);
SDK::ScriptArgument* plugin_mysql_escape_string(SDK::ScriptArguments* pArugments);
