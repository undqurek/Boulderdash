#ifndef TIMER_H
#define TIMER_H

#include "global.h"
#include "basic/preprocesor.h"

#if SYSTEM == WINDOWS
	#include <Windows.h>
#endif


// 14:29:10  08.07.2012
namespace core { namespace intermediary
{
    class CORE_DECLARATION StopWatch
	{
	private:

#if SYSTEM == WINDOWS
		LARGE_INTEGER _frequency; // czestotliwosc wykorzysytywana przy obliczaniu czasu pomiaru

		LARGE_INTEGER _start; // czas rozpoczecia pomairu
		LARGE_INTEGER _end; // czas zakonczenia pomiaru
#endif // WINDOWS

#if SYSTEM == LINUX
		double _start; // czas rozpoczecia pomairu
#endif // LINUX

		double _time; // ostatni czas pomiaru
		bool _started; // informuje o tym czy aktualnie odmiarzany jest czas

	public:
		StopWatch();

		// Ropocztyna pomiar.
		//
		bool start();

		// Konczy pomiar.
		//
		bool stop();

		// Zwraca zmierzony czas.
		//
		double getTime();
	};
}}

#endif
