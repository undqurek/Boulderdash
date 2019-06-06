#include "consoleprinter.h"

#include <iostream>


namespace core { namespace logging
{
	ConsolePrinter::ConsolePrinter()
	{
		this->_opened = false;
	}

	ConsolePrinter::~ConsolePrinter()
	{
		this->close();
	}

	bool ConsolePrinter::open()
	{
        if(this->_opened)
            return false;

		this->_opened = true;
		return true;
	}

	bool ConsolePrinter::close()
	{
		if(this->_opened)
		{
			this->flush();
			this->_opened = false;

			return true;
		}

		return false;
	}

	bool ConsolePrinter::isOpened()
	{
		return this->_opened;
	}

	bool ConsolePrinter::flush()
	{
		if(this->_opened)
		{
			std::cout.flush();
			return true;
		}

		return false;
	}

	bool ConsolePrinter::write(const char *text)
	{
		if(this->_opened)
		{
			std::cout << text;
			return true;
		}

		return false;
	}

	bool ConsolePrinter::writeLine(const char *text)
	{
		if(this->_opened)
		{
			std::cout << text << "\n";
			return true;
		}

		return false;
	}
}}
