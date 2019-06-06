#ifndef TIME_H
#define TIME_H

#include "global.h"
#include "basic/preprocesor.h"


// 14:29:10  08.07.2012
namespace core { namespace intermediary
{
    class CORE_DECLARATION Time
	{
	public:
		Time();

		static double getTotalMicroseconds();
	};
}}

#endif // TIME_H
