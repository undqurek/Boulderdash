#include "random.h"

#include <stdlib.h>
#include <time.h>


// 14:29:10  08.07.2012
namespace core { namespace intermediary
{
	Random::Random()
	{
		::srand(::time(NULL));
	}

	double Random::next(double min, double max)
	{
        double nominal = (double)::rand() / (double)RAND_MAX; // losujemy wartosc z przedialu <0, 1>
        double value = (nominal * (max - min)) + min; // dopasowujemy wartosc do przedzialu <min, max>

        return value;
    }

	int32_t Random::next(int32_t min, int32_t max)
	{
        double nominal = (double)::rand() / (double)RAND_MAX; // losujemy wartosc z przedialu <0, 1>
        int32_t value = (int32_t)(nominal * (max - min) + 0.5) + min; // dopasowujemy wartosc do przedzialu <min, max>

        return value;
	}
}}
