#include "valueparser.h"

namespace core { namespace parsing
{
	ValueParser::ValueParser()
	{
	}

	bool ValueParser::parseUInt32(const char *&pointer, const char *&end, uint32_t &outValue)
	{
        // sprawdzamy zakres, oraz czy znak jest ktoras z cyfr
        if(pointer < end && *pointer >= '0' && *pointer <= '9')
		{
            uint32_t value = *pointer - 48; // obliczamy wartosc liczbowa znaku
			++pointer;

            // sprawdzamy zakres, oraz czy znak jest ktoras z cyfr
            while(pointer < end && *pointer >= '0' && *pointer <= '9')
			{
                value = value * 10 + (*pointer - 48); // obliczamy wartosc liczbowa i aktualizujemy wartosc ktora zwrocimy
                ++pointer;
			}

            outValue = value;
			return true;
		}

		outValue = 0;
		return false;
	}

	bool ValueParser::parseInt32(const char *&pointer, const char *&end, int32_t &outValue)
    {
        if(pointer < end)
        {
            bool minus = false; // informuje o tym czy wykryto znak minus na poczatku liczby

            // sprawdzamy czy na poczatku znajduje sie aznak minus
            if(*pointer == '-')
            {
                minus = true;
                ++pointer;
            }

            uint32_t value = 0;

            // parsujemy czesc calkowita
            if(parseUInt32(pointer, end, value) == false)
            {
                outValue = 0;
                return false;
            }

            outValue = minus ? -value : value;
            return true;
        }

		outValue = 0;
		return false;
    }

	bool ValueParser::parseAsUDecimal(const char *&pointer, const char *&end, double &outValue)
	{
        // sprawdzamy zakres, oraz czy znak jest ktoras z cyfr
        if(pointer < end && *pointer >= '0' && *pointer <= '9')
		{
            int value = *pointer - 48; // obliczamy wartosc liczbowa znaku
            double tmp = 0.1; // aktualizujemy mnoznik pomocniczy

			++pointer;

            // sprawdzamy zakres, oraz czy znak jest ktoras z cyfr
            while(pointer < end && *pointer >= '0' && *pointer <= '9')
			{
                value = value * 10 + *pointer - 48; // obliczamy wartosc liczbowa i aktualizujemy wartosc ktora zwrocimy
                tmp *= 0.1; // aktualizujemy mnoznik pomocniczy

				++pointer;
			}

            outValue = value * tmp;
			return true;
		}

		outValue = 0;
		return false;
	}

	bool ValueParser::parseDouble(const char *&pointer, const char *&end, double &outValue)
	{
        if(pointer < end)
		{
            bool minus = false; // informuje o tym czy wykryto znak minus na poczatku liczby

			// sprawdzamy czy na poczatku znajduje sie aznak minus
			if(*pointer == '-')
			{
                minus = true;
                ++pointer;
			}

			uint32_t total = 0; // czesc dziesietna liczby

			// parsujemy czesc calkowita
            if(parseUInt32(pointer, end, total) == false)
			{
                outValue = 0;
				return false;
			}

            double value = total; // aktualizujemy wartosc ktora zwrocimy

            if(pointer < end)
			{
                // sprawdzamy czy wykryto znak oddzielajacy czesc dziesietna od calkowitej
				if(*pointer == '.')
				{
                    double decimal = 0.0; // czesc dziesietna liczby
                    ++pointer;

                    // parsujemy czesc dziesietna
                    if(parseAsUDecimal(pointer, end, decimal) == false)
					{
                        outValue = 0;
						return false;
					}

                    value += decimal; // aktualizujemy wartosc ktora zwrocimy
				}
			}

            outValue = minus ? -value : value;
			return true;
		}

		outValue = 0;
		return false;
	}
}}
