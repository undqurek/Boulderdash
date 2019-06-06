#ifndef CHECKINGRUN_H
#define CHECKINGRUN_H

#include "intermediary/thread.h"
#include "logging/consoleprinter.h"
#include "network/parallelserver.h"


namespace core { namespace unittests { namespace network_parallelserver
{
    class CheckingRun
    {
    private:
        static logging::ConsolePrinter _printer;

    public:
        static void assert()
        {
            _printer.open();

            network::ParallelServer server;

            if(server.run(1, 27015))
            {
                _printer.writeLine("Server run success.");

                while(server.isRun())
                    intermediary::Thread<void>::sleepMicroseconds(100);
            }
            else
                _printer.writeLine("Server run failed.");

            _printer.close();
        }
    };

    logging::ConsolePrinter CheckingRun::_printer = logging::ConsolePrinter();
}}}

#endif // CHECKINGRUN_H
