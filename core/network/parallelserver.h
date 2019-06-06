#ifndef PARALLELSERVER_H
#define PARALLELSERVER_H

#include "global.h"
#include "basic/cleaner.h"
#include "intermediary/thread.h"
#include "server.h"


namespace core { namespace network
{
    class ParallelServer;

    class ClientContener
    {
    private:
        volatile bool &_lopped;

        Socket *_socket;
        intermediary::Thread<ClientContener> *_thread;

        friend class ParallelServer;

        ClientContener(volatile bool &lopped, Socket *_socket, intermediary::Thread<ClientContener> *_thread);

    public:
        virtual ~ClientContener();

        // Zwraca informacje o tym czy petle powinny byc podtrzymywane.
        //
        bool isLopped() volatile;

        // Zwraca wskaznik do socketa.
        //
        Socket *__getSocket();
    };

    class CORE_DECLARATION ParallelServer
    {
    private:
        network::Server _serwer;

        volatile uint32_t _clientsCount;

        volatile bool _threadsLopped; // informacja o tym czy watki maja byc podtrzymywane
        intermediary::Thread<ParallelServer> _acceptingThread; // laczy klientow

        struct Tmp
        {
            ParallelServer *__server;
            ClientContener *contener;
        };

        // Wykonuje glowna logike nasluchujaca i laczaca klientow.
        //
        static void *listenClients(ParallelServer *__this);

        // Wykonuje logike klienta.
        //
        static void *runClient(Tmp *contener);

    public:
        ParallelServer();
        ~ParallelServer();

        // Zwraca numer portu na ktorym uruchomiono serwer.
        //
        uint16_t getPort();

        // Uruchamia serwer pod wskazanym portem.
        //
        bool run(uint32_t connectionsLimit, uint16_t port);

        // Zatrzymuje serwer.
        //
        bool stop();

        // Sprawdza czy serwer jest uruchomiony.
        //
        bool isRun();

        // Wykonuje logike klienta.
        //
        void *(*funRunClient)(ClientContener *__contener);
    };
}}

#endif // PARALLELSERVER_H
