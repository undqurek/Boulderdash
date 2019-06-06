#ifndef THREAD_H
#define THREAD_H

#include "global.h"
#include "basic/preprocesor.h"

#include <stdint.h>

#if SYSTEM == LINUX
#   include <pthread.h>
#   include <stddef.h>
#endif // LINUX

#if SYSTEM == WINDOWS
#   include <Windows.h>
#endif // WINDOWS


namespace core { namespace intermediary
{
// HEADER

#if SYSTEM == WINDOWS
    DWORD WINAPI CORE_DECLARATION thread_fun(LPVOID __arg); // funkcja posrednia wykonywana przez watek
#endif // WINDOWS

	template<class TArg>
    class Thread
	{
	private:

#if SYSTEM == LINUX
		pthread_t _thread; // identyfikator watku
		static void *thread_fun(void *__arg); // funkcja posrednia wykonywana przez watek
#endif // LINUX

#if SYSTEM == WINDOWS
		DWORD _threadId; // identyfikator watku
		HANDLE _hThread; // uchwyt watku

		friend DWORD WINAPI thread_fun(LPVOID __arg);
#endif // WINDOWS

	TArg *__arg; // wskazuje na argument przekazywany z zewnatrz do watku

	public:
		Thread();
		~Thread();

		// Uruchamia watek.
		//
		bool start(TArg *__arg = NULL);

		// Przerywa watek.
		//
		bool abort();

		// Sprawdza czy watek zostal uruchomiony.
		//
		bool isStarted();

        // Czeka na zakonczenie watku.
        //
        void join();

		// Logika wykonywana przez watek.
		//
		void *(*funRun)(TArg *__arg);

		// Usypia watek w ktorym wykonano metode na okreslona ilosc mikrosekund.
		//
		static void sleepMicroseconds(uint32_t microseconds);

		// Usypia watek w ktorym wykonano metode na okreslona ilosc milisekund.
		//
		static void sleepMilliseconds(uint32_t milliseconds);
	};

// BODY

#if SYSTEM == LINUX
    template<class TArg>
    void* Thread<TArg>::thread_fun(void *__arg)
    {
        Thread<TArg> *__self = (Thread<TArg>*)__arg;

        if(__self->funRun == NULL)
        {
            __self->_thread = 0;

            return NULL;
        }

        void *result = __self->funRun(__self->__arg);
        __self->_thread = 0;

        return result;
    }
#endif // LINUX

    template<class TArg>
    Thread<TArg>::Thread()
    {
#if SYSTEM == LINUX
        this->_thread = 0;
#endif // LINUX

#if SYSTEM == WINDOWS
        this->_threadId = 0;
        this->_hThread = NULL;
#endif // WINDOWS
    }

    template<class TArg>
    Thread<TArg>::~Thread()
    {
        this->abort();
    }

    template<class TArg>
    bool Thread<TArg>::start(TArg *__arg)
    {
        if(this->funRun == NULL)
            return false;

        this->__arg = __arg;

#if SYSTEM == LINUX
        // jesli watek zostal juz uruchomiony
        if(this->_thread != 0) return false;

        // tworzymy i sprawdzamy czy powiodlo sie uruchamianie watku
        if(::pthread_create(&this->_thread, NULL, thread_fun, this) == 0) return true;
#endif // LINUX

#if SYSTEM == WINDOWS
        // jesli watek zostal juz uruchomiony
        if(this->_hThread != NULL)
            return false;

        this->_hThread = ::CreateThread(NULL, 0, &thread_fun, this, 0, &this->_threadId);

        // sprawdzamy czy powiodlo sie uruchamianie watku
        if(this->_hThread != NULL)
            return true;
#endif // WINDOWS

        return false;
    }

    template<class TArg>
    bool Thread<TArg>::abort()
    {
#if SYSTEM == LINUX
        if(this->_thread == 0)
            return false;

        ::pthread_cancel(this->_thread);
        this->_thread = 0;
#endif // LINUX

#if SYSTEM == WINDOWS
        if(this->_hThread == 0)
            return false;

        ::TerminateThread(this->_hThread, 0);
        ::CloseHandle(this->_hThread);

        this->_threadId = 0;
        this->_hThread = NULL;
#endif // WINDOWS

        return true;
    }

    template<class TArg>
    bool Thread<TArg>::isStarted()
    {
#if SYSTEM == LINUX
        return this->_thread != 0;
#endif // LINUX

#if SYSTEM == WINDOWS
        return this->_hThread != NULL;
#endif // WINDOWS
    }

    template<class TArg>
    void Thread<TArg>::join()
    {
        if(this->isStarted())
        {
#if SYSTEM == WINDOWS
            ::WaitForSingleObject(this->_hThread, INFINITE);
#endif // WINDOWS
        }
    }

    template<class TArg>
	void Thread<TArg>::sleepMicroseconds(uint32_t microseconds)
    {
#if SYSTEM == LINUX
        struct ::timespec req = { 0 }, rem = { 0 };

        time_t seconds = (time_t)(microseconds / 1000000);
        microseconds = microseconds - (seconds * 1000000L);

        req.tv_sec = seconds;
        req.tv_nsec = microseconds * 1000L;

        ::nanosleep(&req, &rem);
#endif // LINUX

#if SYSTEM == WINDOWS
		//TODO: znalesc odpowiednia funkcje
		::Sleep(microseconds);
#endif // WINDOWS
	}

	template<class TArg>
	void Thread<TArg>::sleepMilliseconds(uint32_t milliseconds)
	{
#if SYSTEM == LINUX
		//TODO: dorobic
#endif // LINUX

#if SYSTEM == WINDOWS
		::Sleep(milliseconds);
#endif // WINDOWS
	}
}}

#endif // THREAD_H
