#ifndef PRINTER_H
#define PRINTER_H

#include "global.h"


namespace core { namespace logging
{
    class CORE_DECLARATION Printer
	{
	public:
		virtual bool open() = 0;
		virtual bool close() = 0;
		virtual bool isOpened() = 0;

		virtual bool flush() = 0;

		virtual bool write(const char *text) = 0;
		virtual bool writeLine(const char *text) = 0;
	};
}}

#endif // PRINTER_H
