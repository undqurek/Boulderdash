#ifndef CHECKINGCSTRINGLENGTH_H
#define CHECKINGCSTRINGLENGTH_H

#include "logging/consoleprinter.h"
#include "basic/string.h"


namespace core { namespace unittests { namespace basic_string
{
	class CheckingCStringLength
	{
	private:
		static logging::ConsolePrinter _printer;

		static void assertCStringLength(const char *cstring,
			uint32_t expectedLength,
			bool maxLengthUsed = false,
			uint32_t maxLength = 0xFFFFFFFF)
		{
			uint32_t cstringLength = maxLengthUsed ? basic::String::checkLength(cstring, maxLength) : basic::String::checkLength(cstring);

			if(cstringLength == expectedLength) return;

			if(*cstring == '\0')
				_printer.writeLine("uinttest::basic_string : Incorrect empty c-string length.");

			else
			{
				_printer.write("uinttest::basic_string : Incorrect cstring length for: ");
				_printer.writeLine(cstring);
			}

			throw "Error!"; // przerywamy wyknywanie aplikacji
		}

	public:
		static void assert()
		{
			_printer.open();

			assertCStringLength(NULL, 0);
			assertCStringLength("", 0);
			assertCStringLength("1", 1);
			assertCStringLength("12", 2);
			assertCStringLength("123", 3);
			assertCStringLength("1234", 4);
			assertCStringLength("jakis mega dlugi testowy tekst", 30);

			assertCStringLength(NULL, 0, true, 0);
			assertCStringLength(NULL, 0, true, 1);
			assertCStringLength(NULL, 0, true, 2);

			assertCStringLength("", 0, true, 0);
			assertCStringLength("", 0, true, 1);
			assertCStringLength("", 0, true, 2);
			assertCStringLength("", 0, true, 3);
			assertCStringLength("", 0, true, 4);

			assertCStringLength("1", 0, true, 0);
			assertCStringLength("1", 1, true, 1);
			assertCStringLength("1", 1, true, 2);
			assertCStringLength("1", 1, true, 3);
			assertCStringLength("1", 1, true, 4);

			assertCStringLength("12345678", 0, true, 0);
			assertCStringLength("12345678", 1, true, 1);
			assertCStringLength("12345678", 2, true, 2);
			assertCStringLength("12345678", 3, true, 3);
			assertCStringLength("12345678", 4, true, 4);
			assertCStringLength("12345678", 7, true, 7);
			assertCStringLength("12345678", 8, true, 8);
			assertCStringLength("12345678", 8, true, 9);

			assertCStringLength("jakis mega dlugi testowy tekst", 0, true, 0);
			assertCStringLength("jakis mega dlugi testowy tekst", 1, true, 1);
			assertCStringLength("jakis mega dlugi testowy tekst", 2, true, 2);
			assertCStringLength("jakis mega dlugi testowy tekst", 3, true, 3);
			assertCStringLength("jakis mega dlugi testowy tekst", 4, true, 4);
			assertCStringLength("jakis mega dlugi testowy tekst", 30, true, 30);
			assertCStringLength("jakis mega dlugi testowy tekst", 30, true, 40);
			assertCStringLength("jakis mega dlugi testowy tekst", 30, true, 10000);

			_printer.close();
		}
	};

	logging::ConsolePrinter CheckingCStringLength::_printer = logging::ConsolePrinter();
}}}

#endif // CHECKINGCSTRINGLENGTH_H
