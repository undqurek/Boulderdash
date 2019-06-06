#ifndef BINARYWRITER_H
#define BINARYWRITER_H

#include "global.h"
#include "basic/preprocesor.h"
#include "memory.h"
#include "cleaner.h"

#include <stddef.h>
#include <stdint.h>


// 17:33:38  04.12.2011
namespace core { namespace basic
{
	// Zapisuje dane do pamieci tymczasowej (RAM)
    class CORE_DECLARATION BinaryWriter
	{
	private:
        static const uint32_t _sectorLength = 256; // rozmiar pojedynczego sektora przechowujacego dane

		// struktura pomocnicza przechowujaca dane
		struct Sector
		{
            uint8_t data[BinaryWriter::_sectorLength]; // tablica z danymi
            Sector* __next; // wskaznik obcy do nastepnej struktury

			Sector();
			~Sector();
		};


        Sector* _firstSector; // pierwszy sektor kolejki
        Sector* __lastSector; // ostatni sektor kolejki

        uint32_t _lastSectorOffset; // ilosc zapisanych danych w ostatnim sektorze - opisuje pozycje od ktorej nastepuje dopisywanie danych do sektora podczas operacji zapisu

//		// ilosc utworzonych sektorow
//		uint32_t _sectorsCount;

        uint32_t _dataLength; // calkowity rozmiar zapisanych danych

        // uniwersalna funkcja zapisujaca
		template<typename T>
		inline void write(register T &value);

	public:
		BinaryWriter();
		~BinaryWriter();

		// Zwraca informacje o ilosci zapisanych danych
		//
		// return	: ilosc zapisanych danych
		uint32_t getSize();

		// Czysci zapisane dane
		//
		void clear();

		void write(uint8_t data);
		void write(uint16_t data);
		void write(uint32_t data);
		void write(uint64_t data);

		void write(int8_t data);
		void write(int16_t data);
		void write(int32_t data);
		void write(int64_t data);

		void write(float data);
		void write(double data);

        void write(uint8_t *data, uint32_t dataLength) throw (const char *);

		// Zapisuje dane w postaci tablicy typu uint8_t.
		//
		// return		: zwraca wskaznik do do utworzonej tablicy lub NULL jesli nie sapisano zadnych danych
        uint8_t *toArray();

		// Zapisuje dane w postaci tablicy typu uint8_t.
		//
		// data		: [wymagany] tablica do ktorej zapisywane sa dane
		//
        // return   : zwraca wskaznik do data
        uint8_t *toArray(uint8_t *&data) throw (const char *);

		// Zapisuje dane w postaci tablicy typu uint8_t usuwajac w trakcie operacji zapisane sektory.
		// Jest ona przydatna w przypadku gdy po zapisaniu danych do obiektu nie beda juz ponownie potrzebne lub obiekt zostanie zaraz zniszczony (przyspieszy to zwalnianie pamieci).
		//
		// return		: zwraca wskaznik do do utworzonej tablicy lub NULL jesli nie sapisano zadnych danych
        uint8_t *pullOutData();

		// Zapisuje dane w postaci tablicy typu uint8_t usuwajac z wrakcie operacji zapisane sektory.
		// Jest ona przydatna w przypadku gdy po zapisaniu danych do obiektu nie beda juz ponownie potrzebne lub obiekt zostanie zaraz zniszczony (przyspieszy to zwalnianie pamieci).
		//
        // data     : [wymagany] tablica do ktorej zapisywane sa dane
		//
        // return   : zwraca wskaznik do data
        uint8_t *pullOutData(uint8_t *&data) throw (const char *);
	};
}}

#endif // BINARYWRITER_H
