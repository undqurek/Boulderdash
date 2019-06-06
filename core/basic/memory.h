#ifndef MEMORY_H
#define MEMORY_H

#include "global.h"

#include <stddef.h>
#include <stdint.h>
//#include <stdio.h>


// 16:51:54  22.01.2012
namespace core { namespace basic
{
    class CORE_DECLARATION Memory
    {
    private:
        Memory();

    public:

        // Porownuje dwa bloki danych
        //
        static bool compare(const uint8_t *expected, const uint8_t *actual, size_t length);

        // Przekopiowuje dane
        //
        static void copy(const uint8_t *src, uint8_t *dest, size_t length);
    };
}}

#endif // MEMORY_H
