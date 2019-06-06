#ifndef SOCKET_H
#define SOCKET_H

#include <stdint.h>

#include "global.h"
#include "basic/preprocesor.h"

#if SYSTEM == LINUX
#   include <stdlib.h>
#   include <stdio.h>
#   include <unistd.h>
#   include <string.h>
#   include <sys/socket.h>
#   include <sys/ioctl.h>
#   include <arpa/inet.h>
#   include <netdb.h>
//#   include "basic/helpers.h"
#endif

#if SYSTEM == WINDOWS
#   include <winsock2.h>
#   include <ws2tcpip.h>
#endif


namespace core { namespace network
{
    class Client;
	class Server;

    class CORE_DECLARATION Socket
    {
    private:
#if SYSTEM == LINUX
        int _descriptor;
#endif // LINUX

#if SYSTEM == WINDOWS
        ::SOCKET _descriptor;
#endif // WINDOWS

        int32_t _readBytes; // ilosc odczytanych byte'ow
        int32_t _writtenBytes; // ilosc zapisanych byte'ow

        char *_ip;

        friend class Client;
		friend class Server;

        Socket();

#if SYSTEM == LINUX
        Socket(int desriptor, char *_ip);
#endif // LINUX

#if SYSTEM == WINDOWS
        Socket(::SOCKET desriptor, char *_ip);
#endif // WINDOWS

	public:
        enum Type
        {
            T_IPv4,
            T_IPv6
        };

        enum Protocol
        {
            P_TCP,
            P_UDP
        };

    public:
        virtual ~Socket();

        // Zwraca adres IP v4 z ktorym nawiazano polaczenie.
        //
        const char *__getIP();

        //TODO: set send timeout
        //TODO: set recive timeout
        //TODO: commect timeout
        //TODO: accept timout

        // Zamyka polaczenie.
        //
        virtual bool close();

        // Zwraca informacje czy socket jest otwarty.
        //
        bool isOpen();

        // Odczytuje odebrane dane.
        //
        bool read(const uint8_t *buffer, uint32_t length);

        // Wysyla dane.
        //
        bool write(const uint8_t *buffer, uint32_t length);

        // Odczytuje pojedynczy byte.
        //
        bool readByte(uint8_t &outValue);

        // Zwraca informacje o ilosci dostepnych byte'ow do odczytania.
        //
        uint32_t available();

        // Czeka na dotarcie okreslonej ilosci byte'ow.
        //
        bool wait(int bytesCount);
    };
}}

#endif // SOCKET_H
