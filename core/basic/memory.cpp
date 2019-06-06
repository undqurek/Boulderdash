#include "memory.h"


// 16:51:54  22.01.2012
namespace core { namespace basic
{
	Memory::Memory()
	{

	}

    bool Memory::compare(const uint8_t *expected, const uint8_t *actual, size_t length)
	{
        const uint8_t *endExpected = expected + length;

        for(; expected < endExpected; ++expected, ++actual)
		{
            if(*expected != *actual)
				return false;
		}

		return true;
	}

    void Memory::copy(const uint8_t *src, uint8_t *dest, size_t length)
	{
        const uint8_t *srcEnd = src + length;

        //TODO: zaktualizowac logike kopiujaca

        // kopiujemy dane po byte'cie
        for(; src < srcEnd; ++src, ++dest)
			*dest = *src;
	}
}}
