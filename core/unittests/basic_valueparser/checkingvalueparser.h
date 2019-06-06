#ifndef CHECKINGVALUEPARSER_H
#define CHECKINGVALUEPARSER_H

#include "logging/consoleprinter.h"
#include "basic/valueparser.h"


namespace core { namespace unittests { namespace basic_valueparser
{
    class CheckingValueParser
	{
	private:
		static logging::ConsolePrinter _printer;

	public:
		static void assert()
		{
			_printer.open();

            //basic::ValueParser::parseInt32()

			_printer.close();
		}
	};

	logging::ConsolePrinter CheckingCStringLength::_printer = logging::ConsolePrinter();
}}}

#endif // CHECKINGVALUEPARSER_H
