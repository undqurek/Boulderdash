#include "time.h"

#if SYSTEM == LINUX
#   include <sys/time.h>
#   include <time.h>
#   include <sys/types.h>
#endif


// 14:29:10  08.07.2012
namespace core { namespace intermediary
{
	Time::Time()
	{

	}

	double Time::getTotalMicroseconds()
	{
#if SYSTEM == LINUX
		timeval tv;

        ::gettimeofday(&tv, NULL);
        double us = tv.tv_sec * 1000000.0 + tv.tv_usec * 0.001; // obliczamy czas w mikrosekundach

		return us;
#endif // LINUX

#if SYSTEM == WINDOWS
		return 0.0;
#endif // WINDOWS
	}
}}
