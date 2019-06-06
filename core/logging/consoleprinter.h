#ifndef CONSOLEPRINTER_H
#define CONSOLEPRINTER_H

#include "global.h"
#include "printer.h"


namespace core { namespace logging
{
    class CORE_DECLARATION ConsolePrinter
        : public Printer
	{
	private:
		bool _opened;

	public:
		ConsolePrinter();
		~ConsolePrinter();

		bool open();
		bool close();
		bool isOpened();

		bool flush();

		bool write(const char *text);
		bool writeLine(const char *text);
	};
}}

#endif // CONSOLEPRINTER_H
