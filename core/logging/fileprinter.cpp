#include "fileprinter.h"

#include "basic/string.h"


namespace core { namespace logging
{
	FilePrinter::FilePrinter(const char *filePath)
	{
		this->_filePath = filePath;
	}

	FilePrinter::~FilePrinter()
	{
		this->close();
	}

	bool FilePrinter::open()
	{
		return this->_file.open(this->_filePath, intermediary::File::FM_Create);
	}

	bool FilePrinter::close()
	{
		return this->_file.close();
	}

	bool FilePrinter::isOpened()
	{
		return this->_file.isOpened();
	}

	bool FilePrinter::flush()
	{
		return this->_file.flush();
	}

	bool FilePrinter::write(const char *text)
	{
		if(this->_file.isOpened())
		{
			uint32_t length = basic::String::checkLength(text);

            if(length == 0)
                return true;

			return this->_file.write((uint8_t*)text, length);
		}

		return false;
	}

	bool FilePrinter::writeLine(const char *text)
	{
		if(this->_file.isOpened())
		{
			uint32_t length = basic::String::checkLength(text);

            if(length == 0)
                return true;

			return this->_file.write((uint8_t*)text, length) && this->_file.write((uint8_t*)"\n", 1);
		}

		return false;
	}
}}
