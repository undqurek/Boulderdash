#ifndef NETWORKUTILS_H
#define NETWORKUTILS_H

#include <stdint.h>

#include "global.h"
#include "basic/preprocesor.h"


namespace core { namespace network
{
	class CORE_DECLARATION NetworkUtils
    {
    private:
		NetworkUtils();

    public:
        // Pobiera adres hosta.
        //
        // host     : [wymagany] host urzadzenia
        //
        // return   : adres IP lub NULL w przypadku braku
        static uint32_t getHostIPv4(const char *host);

        static char *createIPv4CString(uint32_t ip);

    };
}}

#endif // NETWORKUTILS_H
