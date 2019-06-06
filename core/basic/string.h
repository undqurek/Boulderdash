#ifndef STRING_H
#define STRING_H

#include "global.h"
#include <stdint.h>


namespace core { namespace basic
{
    class CORE_DECLARATION String
	{
	private:
		const char *_cString;
		uint32_t _length;

	public:
		String();
        String(const char *cString);
		String(const char *_cString, uint32_t cStringLength);

		// Zwraca dlugosc string'a.
		//
		uint32_t getLength();

		// Zwraca c-stringa reprezentujacego stringa.
		//
		const char *__getCString();

		// Czysci stringa.
		//
		void empty();

        // Sprawdza i zwraca dlugosc podanego c-string'a.
        //
        static uint32_t checkLength(const char *cString, uint32_t maxLength = 0xFFFFFFFF);

        // Kopiuje podanego c-string'a do zwracanej tablicy.
        //
        static char *copyCString(const char *cString, uint32_t length);

		// Laczy ze soba dwa c-string'i.
		//
		static char *concatenate(const char *firstCString, const char *secondCString);
	};
}}

#endif // STRING_H
