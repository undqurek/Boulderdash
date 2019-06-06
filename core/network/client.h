#ifndef CLIENT_H
#define CLIENT_H

#include <stdint.h>

#include "global.h"
#include "socket.h"


namespace core { namespace network
{
    class CORE_DECLARATION Client
        : public Socket
    {
    private:
        bool _blocking; // blokujace sockety
        uint16_t _port;

    public:
        Client(bool _blocking = true);
        virtual ~Client();

        // Nawiazuje polaczenie ze wskazanym adresem.
        //
        bool connect(uint32_t ipv4, uint16_t port);

        bool connect(const char *ipv4, uint16_t port);

        // Zamyka polaczenie.
        //
        bool close();

//        static uint32_t createIPv4Address(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
//        static uint32_t createIPv4Address(const char *address);
    };
}}

#endif // CLIENT_H
