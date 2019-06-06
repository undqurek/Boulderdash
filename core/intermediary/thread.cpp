#include "thread.h"


namespace core { namespace intermediary
{
#if SYSTEM == WINDOWS
    DWORD WINAPI thread_fun(LPVOID __arg)
    {
        Thread<void> *__self = (Thread<void>*)__arg;

        if(__self->funRun == NULL)
        {
            __self->_threadId = 0;
            __self->_hThread = NULL;

            //TODO: dorobic porawne zwracanie wartosci
            return 0;
        }

        void *result = __self->funRun(__self->__arg);

        __self->_threadId = 0;
        __self->_hThread = NULL;

        //TODO: dorobic zwracanie wartosci
        return 0;
    }
#endif // WINDOWS
}}
