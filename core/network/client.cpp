#include "client.h"

#include "basic/cleaner.h"
#include "basic/string.h"
#include "networkutils.h"

#include <string>
#include <iostream>
#include <sstream>


namespace core { namespace network
{
    Client::Client(bool blocking)
        : Socket()
    {
#if SYSTEM == WINDOWS
        ::WSADATA wsaData = { 0 };

        // inicjacja Winsock DLL dla procesu jesli nie zostala jeszcze zainicjowana
        ::WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif // WINDOWS

        this->_blocking = blocking;
        this->_port = 0;
    }

    Client::~Client()
    {
        this->Socket::~Socket();

#if SYSTEM == WINDOWS
        // sprzata po socket'ach
        ::WSACleanup();
#endif // WINDOWS
    }

    bool Client::connect(uint32_t ipv4, uint16_t port)
    {
        if(this->isOpen())
            return false;

#if SYSTEM == LINUX
        // Otwieramy socket przekazujac parametry:
        // address family: AF_INET <=> IP v4
        // type: SOCK_STREAM <=> strumien danych
        // protocol: 0 <=> TCP/IP
        this->_descriptor = ::socket(AF_INET, SOCK_STREAM, 0);

        // jesli nie udalo sie utworzyc socketa
        if(this->_descriptor == -1)
            return false;

        //TODO: operacje nieblokujace (fcntl() i O_NONBLOCK)
//        if(this->_blocking == false)
//        {
//            u_long mode =  1; // argument mowiacy o trybie nie blokujacym

//            // ustawia tryb nieblokujacy
//            if(::ioctl(this->_descriptor, FIONBIO, &mode) == -1)
//            {
//                ::close(this->_descriptor);
//                this->_descriptor = -1;

//                return false;
//            }
//        }

        struct ::sockaddr_in address; // struktura reprezentujaca adres
        ::bzero(&address, sizeof(address));

        address.sin_family = AF_INET; // rodzina adresow IP v4
        address.sin_addr.s_addr = ipv4;
        address.sin_port = ::htons(port);

        // nawiazujemy polaczenie i sprawdzamy czy powiodla sie operacja
        if(::connect(this->_descriptor, (::sockaddr *)&address, sizeof(address)) == -1)
        {
            ::close(this->_descriptor);
            this->_descriptor = -1;

            return false;
        }

        //TODO: poprawic
        this->Socket::_ip = ::inet_ntoa(*(struct in_addr *)&ipv4);
#endif // LINUX

#if SYSTEM == WINDOWS
        // Otwieramy socket przekazujac parametry:
        // address family: AF_INET <=> IP v4
        // type: SOCK_STREAM <=> strumien danych
        // protocol: IPPROTO_TCP <=> TCP/IP
        this->_descriptor = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        // jesli nie udalo sie utworzyc socketa
        if(this->_descriptor == INVALID_SOCKET)
            return false;

        //TODO: operacje nieblokujace (fcntl() i O_NONBLOCK)
//        if(this->_blocking == false)
//        {
//            u_long mode = 1; // argument mowiacy o trybie nie blokujacym

//            // ustawia tryb nieblokujacy
//            if(::ioctlsocket(this->_descriptor, FIONBIO, &mode) == SOCKET_ERROR)
//            {
//                ::closesocket(this->_descriptor);
//                this->_descriptor = INVALID_SOCKET;

//                return false;
//            }
//        }

        struct ::sockaddr_in address; // struktura reprezentujaca adres
        ::ZeroMemory(&address, sizeof(struct ::sockaddr_in));

        address.sin_family = AF_INET; // rodzina adresow IP v4
        address.sin_addr.s_addr = ipv4;
        address.sin_port = ::htons(port);

        // nawiazujemy polaczenie i sprawdzamy czy powiodla sie operacja
        if(::connect(this->_descriptor, (::sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
        {
            ::closesocket(this->_descriptor);
            this->_descriptor = INVALID_SOCKET;

            return false;
        }

        //TODO: poprawic
        this->Socket::_ip = ::inet_ntoa(*(struct in_addr *)&ipv4);
#endif // WINDOWS

        this->_port = port;

        return true;
    }

    bool Client::connect(const char *ipv4, uint16_t port)
    {
        uint32_t tmp = ::inet_addr(ipv4);

        return this->connect(tmp, port);
    }

    bool Client::close()
    {
        if(this->Socket::close())
        {
            this->_port = 0;
            return true;
        }

        return false;
    }

//    uint32_t Client::createIPv4Address(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
//    {
//        union
//        {
//            uint32_t ip;
//            uint8_t parts[4];
//        };

//        parts[0] = a;
//        parts[1] = b;
//        parts[2] = c;
//        parts[3] = d;

//        return ip;
//    }

//    uint32_t Client::createIPv4Address(const char *address)
//    {
//        union
//        {
//            uint32_t ip;
//            uint8_t parts[4];
//        };

//        std::istringstream stream(std::string(address));

////        stream >> parts[0];
////        stream >> parts[1];
////        stream >> parts[2];
////        stream >> parts[3];

//        return ip;
//    }
}}
