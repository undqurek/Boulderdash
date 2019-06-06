#ifndef BINARYREADER_H
#define BINARYREADER_H

#include "global.h"
#include "basic/memory.h"

#include <stdint.h>
#include <stddef.h>


namespace core { namespace basic
{
    class CORE_DECLARATION BinaryReader
	{
	private:

        uint32_t _offset; // okresla pozycje odczytywanych danych

        uint8_t *__data; // wskaznik do danych
        uint32_t _dataLength; // dlugosc obszaru danych

        template<typename T> inline bool read(T &outValue); // uniwersalna funkcja odczytujaca

	public:
		// Tworzy obiekt
		//
		// __data		: [wymagany] blok danych z ktorego odczytywane sa dane
		// dataLength	: rozmair bloku danych
        BinaryReader(uint8_t *__data, uint32_t dataLength) throw (const char *);

		// Zwraca pozycje odczytywanych danych
		//
		uint32_t getOffset();

		// Przeskakuje okreslona ilosc byte'ow
		//
		bool jump(uint32_t count);

		// Zwraca wskaznik obcy powiazany z pozycja odczytywanych danych
		//
		// return	: w przypadku przekroczonego zakresu zwraca NULL
        uint8_t *__getPointer();

        bool read(uint8_t &outValue);
        bool read(uint16_t &outValue);
        bool read(uint32_t &outValue);
        bool read(uint64_t &outValue);

        bool read(int8_t &outValue);
        bool read(int16_t &outValue);
        bool read(int32_t &outValue);
        bool read(int64_t &outValue);

        bool read(float &outValue);
        bool read(double &outValue);

        uint32_t read(uint8_t *data, uint32_t dataLength);
	};
}}

#endif // BINARYREADER_H
