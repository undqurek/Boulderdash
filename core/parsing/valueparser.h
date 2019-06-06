#ifndef VALUEPARSER_H
#define VALUEPARSER_H

#include "global.h"

#include <stdint.h>


namespace core { namespace parsing
{
    class CORE_DECLARATION ValueParser
    {
    private:
        ValueParser();

    public:
		// Parsuje ciag liczb jako calkowita liczbe dodania. np. "2321424" => 2321424
		//
		static bool parseUInt32(const char *&pointer, const char *&end, uint32_t &outValue);

        // Parsuje ciag liczb jako int. np. "-23" => -23
        //
		static bool parseInt32(const char *&pointer, const char *&end, int32_t &outValue);

		// Parsuje ciag liczb jako czesc dziesietna dodania. np. "2321424" => 0.2321424f
		//
		static bool parseAsUDecimal(const char *&pointer, const char *&end, double &outValue);

		// Parsuje ciag liczb jako double. np. "-23.123" => -23.123f
		//
		static bool parseDouble(const char *&pointer, const char *&end, double &outValue);
	};
}}

#endif // VALUEPARSER_H
