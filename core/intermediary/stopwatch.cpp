#include "stopwatch.h"

#if SYSTEM == LINUX
	#include "time.h"
#endif // LINUX


// 14:29:10  08.07.2012
namespace core { namespace intermediary
{
	StopWatch::StopWatch()
	{
#if SYSTEM == WINDOWS
		::QueryPerformanceFrequency(&this->_frequency); // odczytujemy czestotliwosc za pomoca ktorej bedziemy pozniej obliczac czas pomiaru
#endif // WINDOWS

		this->_time = 0;
		this->_started = false;
	}

	bool StopWatch::start()
	{
		if(this->_started)
			return false;

#if SYSTEM == WINDOWS
		::QueryPerformanceCounter(&this->_start);
#endif // WINDOWS

#if SYSTEM == LINUX
		this->_start = Time::getTotalMicroseconds();
#endif // LINUX

		this->_started = true;

		return true;
	}

	bool StopWatch::stop()
	{
		if(this->_started)
		{
#if SYSTEM == WINDOWS
			::QueryPerformanceCounter(&this->_end);

			double difference = this->_end.QuadPart - this->_start.QuadPart;
			this->_time = 1000.0 * difference / this->_frequency.QuadPart;
#endif // WINDOWS

#if SYSTEM == LINUX
			this->_time = Time::getTotalMicroseconds() - this->_start;
#endif // LINUX

			this->_started = false;
		}

		return false;
	}

	double StopWatch::getTime()
	{
		return this->_time;
	}
}}
