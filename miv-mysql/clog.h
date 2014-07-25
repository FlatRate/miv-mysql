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
    File: Log.h
    Description: -
*/

#include <stdio.h>

#pragma once
class cLog
{
	public:
		static void Initialise();
		static void Close();

		static void Print(const char* string, bool logConsole);
		static void PrintFormat(const char* string, ...);
		static void PrintFormatConsole(const char* string, ...);

	private:
		static FILE* File;
};