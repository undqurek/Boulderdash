#include "parserutils.h"


namespace core { namespace parsing
{
	ParserUtils::ParserUtils()
	{
	}

	uint32_t ParserUtils::checkCharsCount(const char *data, uint32_t dataLength, char expectedChar)
	{
		uint32_t count = 0;

		for(uint32_t i = 0; i < dataLength; ++i)
		{
			if(data[i] == expectedChar) // jesli wykryto oczekiwany znak
				++count;
		}

		return count;
	}

	bool ParserUtils::checkLineCharsCount(const char *pointer, const char *end, char expectedChar, uint32_t &outCount)
	{
		if(expectedChar == '\r' || expectedChar == '\n') // jesli poszukiwany znak jest znakiem konca lini
			return 0;

		uint32_t count = 0; // ilosc wystapien znaku

		while(pointer < end)
		{
			if(*pointer == expectedChar) // jesli wykryto oczekiwany znak
				++count;

			else
			{
				if(*pointer == '\r' || *pointer == '\n') // jesli wykryto koniec lini
				{
					outCount = count;

					return true;
				}
			}

			++pointer;
		}

		outCount = count;

		return false;
	}

	bool ParserUtils::findChar(const char *&pointer, const char *end, char expectedChar)
	{
		while(pointer < end)
		{
			if(*pointer == expectedChar) // jesli wykryto oczekiwany znak
				return true;

			++pointer;
		}

		return false;
	}

	bool ParserUtils::findEndLine(const char *&pointer, const char *end)
	{
		while(pointer < end)
		{
			if(*pointer == '\r' || *pointer == '\n') // jesli wykryto znak konca lini
				return true;

			++pointer;
		}

		return false;
	}

	bool ParserUtils::skipChars(const char *&pointer, const char *end, char skippedChar)
	{
		while(pointer < end)
		{
			if(*pointer == skippedChar) // jesli wykryto oczekiwany znak
				++pointer;

			else
				return true;
		}

		return false;
	}

	bool ParserUtils::skipEndLine(const char *&pointer, const char *end)
	{
		if(pointer < end)
		{
			if(*pointer == '\n')
			{
				++pointer;
				return true;
			}

			if(*pointer != '\r')
				return false;

			++pointer;

			if(pointer < end && *pointer == '\n')
			{
				++pointer;
				return true;
			}
		}

		return false;
	}

	bool ParserUtils::skipEmptyLines(const char *&pointer, const char *end)
	{
		while(pointer < end)
		{
			if(*pointer == '\r' || *pointer == '\n') // jesli wykryto znak konca lini lub znak przejscia do nowej lini
				++pointer;

			else
				return true;
		}

		return false;
	}
}}
