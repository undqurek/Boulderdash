#ifndef UNITTEST_H
#define UNITTEST_H

#include "global.h"

#include <logging/printer.h>
#include <stdint.h>


namespace core { namespace basic
{
	class CORE_DECLARATION UnitTest
	{
	private:
		logging::Printer *_printer;

		template <class TArg>
		bool assertEquals(TArg expected, TArg actual);

		template <class TArg>
		bool assertEquals(TArg expected, TArg actual, const char *message);

	public:
		UnitTest();
		~UnitTest();

		bool setPrinter(logging::Printer *_printer);

		bool open();
		bool close();
		bool isOpened();

		bool assertTrue(bool actual);
		bool assertTrue(bool actual, const char *message);

		bool assertFalse(bool actual);
		bool assertFalse(bool actual, const char *message);

		bool assertEquals(bool expected, bool actual);
		bool assertEquals(bool expected, bool actual, const char *message);

		bool assertEquals(uint8_t expected, uint8_t actual);
		bool assertEquals(uint8_t expected, uint8_t actual, const char *message);

		bool assertEquals(uint16_t expected, uint16_t actual);
		bool assertEquals(uint16_t expected, uint16_t actual, const char *message);

		bool assertEquals(uint32_t expected, uint32_t actual);
		bool assertEquals(uint32_t expected, uint32_t actual, const char *message);

		bool assertEquals(uint64_t expected, uint64_t actual);
		bool assertEquals(uint64_t expected, uint64_t actual, const char *message);

		bool assertEquals(const char *expected, const char *actual);
		bool assertEquals(const char *expected, const char *actual, const char *message);
	}
	UnitTestInstance;
}}

#endif // UNITTEST_H
