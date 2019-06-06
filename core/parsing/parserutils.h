#ifndef PARSERUTILS_H
#define PARSERUTILS_H

#include "global.h"
#include <stdint.h>


namespace core { namespace parsing
{
	class CORE_DECLARATION ParserUtils
	{
	private:
		ParserUtils();

	public:
		static uint32_t checkCharsCount(const char *data, uint32_t dataLength, char expectedChar);

		// Liczy ilosc wystapien znaku w lini.
		//
		// return	: zwraca true jesli podczas zliczania znakow nie zostanie przekroczony zakres
		static bool checkLineCharsCount(const char *pointer, const char *end, char expectedChar, uint32_t &outCount);

		// Przechodzi do oczekiwanego znaku.
		//
		// return	: zwraca true jesli podczas szukania znaku nie zostanie przekroczony zakres
		static bool findChar(const char *&pointer, const char *end, char expectedChar);

		// Odnajduje znak konca lini.
		//
		static bool findEndLine(const char *&pointer, const char *end);

		// Pomija okreslone znaki
		//
		// return	: zwraca true jesli podczas przechodzenia przez znaki nie zostanie przekroczony zakres
		static bool skipChars(const char *&pointer, const char *end, char skippedChar);

		// Pomija znak lub znaki zwiazane z koncem lini.
		//
		static bool skipEndLine(const char *&pointer, const char *end);

		// Pomija puste linie.
		//
		// return	: zwraca true jesli podczas przechodzenia przez puste linie nie zostanie przekroczony zakres
		static bool skipEmptyLines(const char *&pointer, const char *end);
	};
}}

#endif // PARSERUTILS_H
