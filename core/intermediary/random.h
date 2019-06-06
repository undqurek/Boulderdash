#ifndef RANDOM_H
#define RANDOM_H

#include "global.h"

#include <stdint.h>


// 14:29:10  08.07.2012
namespace core { namespace intermediary
{
    class CORE_DECLARATION Random
	{
	public:
		Random();

		// Losuje losowa liczbe dodatnia
		//
		// min	: minimalna dodatnia wartosc
		// max	: maksymalna dodatnia wartosc
		double next(double min, double max);

		// Losuje losowa liczbe dodatnia
		//
		// min	: minimalna dodatnia wartosc
		// max	: maksymalna dodatnia wartosc
		int32_t next(int32_t min, int32_t max);
	};
}}

#endif // RANDOM_H
