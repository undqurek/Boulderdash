#ifndef FILEPRINTER_H
#define FILEPRINTER_H

#include "printer.h"
#include "intermediary/file.h"


namespace core { namespace logging
{
    class CORE_DECLARATION FilePrinter
        : public Printer
	{
	private:
		const char *_filePath;
		intermediary::File _file;

	public:
		FilePrinter(const char *filePath);
		~FilePrinter();

		bool open();
		bool close();
		bool isOpened();

		bool flush();

		bool write(const char *text);
		bool writeLine(const char *text);
	};
}}

#endif // FILEPRINTER_H
