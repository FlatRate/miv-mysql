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
    File: cLog.cpp
    Description: Contains the function definitions for cLog.h.
*/

#include "clog.h"
#include <time.h>
#include <stdarg.h>

FILE* cLog::File = NULL;

void cLog::Initialise()
{
	if(File)
	{
		return;
	}
	File = fopen("mysql_debug.log", "w");
}

void cLog::Close()
{
	if(File)
	{
		fclose(File);
	}
}

void cLog::Print(const char* string, bool logConsole)
{
	char tbuf[11];
	time_t t = time(NULL);
	tm* lt = localtime(&t);

	sprintf(tbuf, "%02d:%02d:%02d", lt->tm_hour, lt->tm_min, lt->tm_sec);

	if(File)
	{
		fprintf(File, "[%s] %s\n", tbuf, string);
		fflush(File);
	}
	if(logConsole)
	{
		printf("[MySQL] %s\n", string);
	}
}

void cLog::PrintFormat(const char* string, ...)
{
	char buf[512];

	va_list args;
	va_start(args, string);
	vsnprintf(buf, sizeof(buf), string, args);
	va_end(args);

	cLog::Print(buf, false);
}

void cLog::PrintFormatConsole(const char* string, ...)
{
	char buf[512];

	va_list args;
	va_start(args, string);
	vsnprintf(buf, sizeof(buf), string, args);
	va_end(args);

	cLog::Print(buf, true);
}