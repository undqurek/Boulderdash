//#include "parallelserver.h"


//namespace core { namespace core { namespace network
//{
//    using namespace basic;
//    using namespace intermediary;

//    ClientContener::ClientContener(volatile bool &lopped, Socket *_socket, intermediary::Thread<ClientContener> *_thread)
//        : _lopped(lopped)
//    {
//        this->_socket = _socket;
//        this->_thread = _thread;
//    }

//    ClientContener::~ClientContener()
//    {
//        basic::Cleaner::deleteObject(this->_socket);
//        basic::Cleaner::deleteObject(this->_thread);
//    }

//    bool ClientContener::isLopped() volatile
//    {
//        return this->_lopped;
//    }

//    Socket *ClientContener::__getSocket()
//    {
//        return this->_socket;
//    }

//    void *ParallelServer::listenClients(ParallelServer *__this)
//    {
//        //void *(*funRun)(TArg *__arg) = __this;

//        while(__this->_threadsLopped)
//        {
//            Socket *clinet = __this->_serwer.accept(); // oczekiwanie na polaczenie sie klienta

//            // jesli nie powiodlo sie laczenie klienta
//            if(clinet == NULL)
//                continue;

//            Thread<ClientContener> *clinetThread = new Thread<ClientContener>();
//            clinetThread->funRun = runClient;

//            Tmp *tmp = new Tmp();

//            tmp->__server = __this;
//            tmp->contener = new ClientContener(__this->_threadsLopped, clinet, clinetThread);

//            if(clinetThread->start(tmp))
//                ++__this->_clientsCount;

//            else
//                Cleaner::deleteObject(tmp);
//        }

//        //TODO: zrobic to innaczej
//        while(__this->_clientsCount > 0)
//            Thread<void>::sleepMicroseconds(100);

//        return NULL;
//    }

//    void *ParallelServer::runClient(Tmp *tmp)
//    {
//        void *(*funRunClient)(ClientContener *) = tmp->__server->funRunClient;

//        if(funRunClient == NULL)
//        {
//            Cleaner::deleteObject(tmp->contener);
//            Cleaner::deleteObject(tmp);

//            return NULL;
//        }

//        void *result = funRunClient(tmp->contener);
//        Cleaner::deleteObject(tmp);

//        return result;
//    }

//    ParallelServer::ParallelServer()
//    {
//        this->_threadsLopped = false;
//        this->_clientsCount = 0;

//        this->_acceptingThread.funRun = listenClients;
//    }

//    ParallelServer::~ParallelServer()
//    {
//        this->stop();
//    }

//    uint16_t ParallelServer::getPort()
//    {
//        return this->_serwer.getPort();
//    }

//    bool ParallelServer::run(uint32_t connectionsLimit, uint16_t port)
//    {
//        if(connectionsLimit == 0)
//            return false;

//        if(this->_serwer.run(connectionsLimit, port))
//        {
//            this->_threadsLopped = true; // ustawiamy wartosc potrzymujaca watek
//            this->_clientsCount = 0;

//            //this->_clientsThreads = new Thread<ParallelServer>[connectionsLimit];

//            if(this->_acceptingThread.start(this))
//                return true;

//            this->_serwer.stop();
//        }

//        return false;
//    }

//    bool ParallelServer::stop()
//    {
//        if(this->isRun())
//        {
//            this->_threadsLopped = false; // ustawiamy wartosc potrzymujaca watek
//            this->_acceptingThread.join();

//            return this->_serwer.stop();
//        }

//        return false;
//    }

//    bool ParallelServer::isRun()
//    {
//        return this->_serwer.isRun();
//    }
//}}}
