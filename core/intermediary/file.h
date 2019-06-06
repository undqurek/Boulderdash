#ifndef FILE_H
#define FILE_H

#include "global.h"

#include <stdint.h>
#include <stdio.h>


// 14:29:10  08.07.2012
namespace core { namespace intermediary
{
    class CORE_DECLARATION File
	{
	private:
		::FILE *_file; // uchwyt do pliku
		static const uint32_t _readStep = 2048; // ilosc odczytywanych danych na krok

	public:
		// tryb otwarcia pliku
        enum FileMode
		{
	//		FM_Read = 'r',
	//		FM_ReadWrite = ('+' << 8) | 'r',
	//		FM_Rewrite = 'w',
	//		FM_Create = ('+' << 8) | 'w',
	//		FM_Append = 'a',
	//		FM_ReadAppend = ('+' << 8) | 'a',

            //TODO: make it better

			FM_Read = (uint32_t)'r',
			FM_ReadWrite = (uint32_t)'+r',
			FM_Rewrite = (uint32_t)'w',
            FM_Create = (uint32_t)'+w',
			FM_Append = (uint32_t)'a',
			FM_ReadAppend = (uint32_t)'+a',

			FM_ReadBinary = (uint32_t)'br',
			FM_ReadWriteBinary = (uint32_t)'b+r',
			FM_RewriteBinary = (uint32_t)'bw',
			FM_CreateBinary = (uint32_t)'b+w',
			FM_AppendBinary = (uint32_t)'ba',
			FM_ReadAppendBinary = (uint32_t)'b+a'
		};

		// typ przesuniecia
		enum FileSeek
		{
			FS_Set = SEEK_SET,
			FS_Current = SEEK_CUR,
			FS_End = SEEK_END
		};

	public:
		File();
		~File();

        bool open(const char *path, FileMode mode);
		bool close();
		bool isOpened();

		// Ustawia wskaznik odczytu/zapisu
		//
		bool seek(uint32_t offset, FileSeek origin);

		// Zwraca pozycje wskaznika odczytu/zapisu
		//
		uint32_t tell();

		// Zwraca rozmair pliku
		//
		uint32_t getSize();

		// Odczytuje dane z pliku.
		//
		uint32_t read(uint8_t *buffer, uint32_t length);

		// Zapisuje dane do pliku
		//
		uint32_t write(uint8_t *buffer, uint32_t length);

		// Wysyla zapisuje zawartosc bufforow w pliku.
		//
		bool flush();

		// Wczytuje byte'y z wskazanego pliku
		//
		// filePath			: [wymagany] sciezka do pliku
		// outData			: zwracany wskaznik do tablicy zawierajacej odczytane dane lub NULL w przypadku bledu otwarcia pliku
		// outDataLength	: zwraca inflarmacje o rozmiarze tablicy zawierajacej odczytane dane lub 0 w przypadku bledu otwarcia pliku
		// maxDataLength	: maksymalny rozmiar odczytywanych danych, jesli 0xFFFFFFFF to brak ograniczenia dla ilosci odczytywanych danych
		//
		// return			: zwraca ilosc odczytanych danych (jest on mniejszy badz rowny outDataLength)
		static uint32_t readBytes(const char *filePath,
            uint8_t *&outData,
			uint32_t &outDataLength,
			uint32_t maxDataLength = 0xFFFFFFFF);

		// Tworzy plik i zapisuje byte'y do niego.
		//
		// return	: zwraca ilosc zapisanych danych
		static uint32_t writeBytes(const char *filePath,
			uint8_t *data,
			uint32_t dataLength);
	};
}}

#endif // FILE_H
