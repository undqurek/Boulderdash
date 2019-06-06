#include "unittest.h"

#include "cleaner.h"
#include "logging/consoleprinter.h"


namespace core { namespace basic
{
	UnitTest::UnitTest()
	{
		this->_printer = NULL;
	}

	UnitTest::~UnitTest()
	{
		Cleaner::deleteObject(_printer);
	}

	template <class TArg>
	bool UnitTest::assertEquals(TArg expected, TArg actual)
	{
		return assertEquals(expected, actual, "UnitTest: Incorrect value.");
	}

	template <class TArg>
	bool UnitTest::assertEquals(TArg expected, TArg actual, const char *message)
	{
		if(this->_printer == NULL)
			this->_printer = new logging::ConsolePrinter();

		if(expected = actual)
			return true;

		this->_printer->writeLine(message);
		return false;
	}

	bool UnitTest::setPrinter(logging::Printer *_printer)
	{
		Cleaner::deleteObject(this->_printer);
		this->_printer = _printer;
	}

	bool UnitTest::open()
	{
		if(this->_printer == NULL)
			this->_printer = new logging::ConsolePrinter();

		return this->_printer->open();
	}

	bool UnitTest::close()
	{
		if(this->_printer == NULL)
			this->_printer = new logging::ConsolePrinter();

		return this->_printer->close();
	}

	bool UnitTest::isOpened()
	{
		if(this->_printer == NULL)
			this->_printer = new logging::ConsolePrinter();

		return this->_printer->isOpened();
	}

	bool UnitTest::assertTrue(bool actual)
	{
		return this->assertEquals<bool>(true, actual);
	}

	bool UnitTest::assertTrue(bool actual, const char *message)
	{
		return this->assertEquals<bool>(true, actual, message);
	}

	bool UnitTest::assertFalse(bool actual)
	{
		return this->assertEquals<bool>(false, actual);
	}

	bool UnitTest::assertFalse(bool actual, const char *message)
	{
		return this->assertEquals<bool>(false, actual, message);
	}

	bool UnitTest::assertEquals(bool expected, bool actual)
	{
		return this->assertEquals<bool>(expected, actual);
	}

	bool UnitTest::assertEquals(bool expected, bool actual, const char *message)
	{
		return this->assertEquals<bool>(expected, actual, message);
	}

	bool UnitTest::assertEquals(uint8_t expected, uint8_t actual)
	{
		return this->assertEquals<uint8_t>(expected, actual);
	}

	bool UnitTest::assertEquals(uint8_t expected, uint8_t actual, const char *message)
	{
		return this->assertEquals<uint8_t>(expected, actual, message);
	}

	bool UnitTest::assertEquals(uint16_t expected, uint16_t actual)
	{
		return this->assertEquals<uint16_t>(expected, actual);
	}

	bool UnitTest::assertEquals(uint16_t expected, uint16_t actual, const char *message)
	{
		return this->assertEquals<uint16_t>(expected, actual, message);
	}

	bool UnitTest::assertEquals(uint32_t expected, uint32_t actual)
	{
		return this->assertEquals<uint32_t>(expected, actual);
	}

	bool UnitTest::assertEquals(uint32_t expected, uint32_t actual, const char *message)
	{
		return this->assertEquals<uint32_t>(expected, actual, message);
	}

	bool UnitTest::assertEquals(uint64_t expected, uint64_t actual)
	{
		return this->assertEquals<uint64_t>(expected, actual);
	}

	bool UnitTest::assertEquals(uint64_t expected, uint64_t actual, const char *message)
	{
		return this->assertEquals<uint64_t>(expected, actual, message);
	}

	bool UnitTest::assertEquals(const char *expected, const char *actual)
	{
		return this->assertEquals(expected, actual, "UnitTest: Incorrect c-string value.");
	}

	bool UnitTest::assertEquals(const char *expected, const char *actual, const char *message)
	{
		while(true)
		{
			if(*expected == '\0')
			{
				if(*actual == '\0')
					return true;

				this->_printer->writeLine(message);
				return false;
			}

			if(*actual == '\0')
			{
				this->_printer->writeLine(message);
				return false;
			}

			if(*expected == *actual)
				continue;

			this->_printer->writeLine(message);
			return false;
		}
	}
}}
