#pragma once
#include <cstdarg>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <cstdio>

static void Log(const char* const formatString, ...)
{
	va_list argumentList;
	va_start(argumentList, formatString);
	{
		static char buffer[4096];
		va_list tempList;
		memset(buffer, 0, sizeof(buffer));
#if (defined _MSC_VER) // Pre VS2013
		tempList = argumentList;
#else
		va_copy(tempList, argumentList);
#endif
		vsnprintf(buffer, 4095, formatString, argumentList);
		vprintf(formatString, tempList);
		printf("\n");
	}
	va_end(argumentList);
}
