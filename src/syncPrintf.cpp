#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>
#include "declare.h"

int syncPrintf(const char *format, ...)
{
	int res;
	va_list args;
	lock();
		va_start(args, format);
	res = vprintf(format, args);
	va_end(args);
	unlock();
		return res;
}
