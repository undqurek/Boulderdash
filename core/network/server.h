#ifndef SERVER_H
#define SERVER_H

#include <stdint.h>

#include "global.h"
#include "basic/preprocesor.h"
#include "socket.h"


namespace core { namespace network
{
    class CORE_DECLARATION Server
    {
    private:

#if SYSTEM == LINUX
        int _descriptor;
#endif // LINUX

#if SYSTEM == WINDOWS
        ::SOCKET _descriptor; // identyfikator soketu
#endif // WINDOWS

        //struct ::timeval _acceptanceTimeout; // czas oczekiwania na pojawienie się klienta podcza wykonywania metody accept

        bool _blocking; // blokujace sockety
        uint32_t _limit; // limit polaczen
        uint16_t _port;

    public:
        Server(bool blocking = true);
        virtual ~Server();

        // Zwraca limit polaczen do uruchomionego serwera.
        //
        uint32_t getLimit();

        // Zwraca numer portu na ktorym uruchomiono serwer.
        //
        uint16_t getPort();

//        // Zwraca czas oczekiwania na pojawienie sie klienta podcza wykonywania metody accept.
//        //
//        uint32_t getAcceptanceTimeout();

//        // Ustawia czas oczekiwania na pojawienie sie klienta podcza wykonywania metody accept.
//        //
//        void setAcceptanceTimeout(uint32_t microseconds);

        // Uruchamia serwer pod wskazanym portem.
        //
        bool run(uint32_t limit, uint16_t port);

        // Zatrzymuje serwer. Wymagane jest aby najpierw zakonczyc wszystkie polaczenia w klientami.
        //
        bool stop();

        // Sprawdza czy serwer jest uruchomiony.
        //
        bool isRun();

        // Czeka na polaczenie sie klienta i zwraca socket za pomoca, ktorego mozna komunikawac sie z klientem.
        //
        Socket *accept();
    };
}}

#endif // SERVER_H
