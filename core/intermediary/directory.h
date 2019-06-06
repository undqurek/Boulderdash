#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "global.h"

#include "basic/list.h"

#include <stdint.h>
#include <dirent.h>


namespace core { namespace intermediary
{
	class Directory
	{
	private:
		::DIR *_dir; // uchwyt do katalogu

	public:
		enum ItemType
		{
			IT_Undefined	= 0,
			IT_Directory	= 1 << 1,
			IT_File			= 1 << 2,
			IT_Error		= 1 << 3
		};

	public:
		Directory();
		~Directory();

		// Otwiera katalog.
		//
		bool open(const char *path);

		// Zamyka katalog.
		//
		bool close();

		// Zwraca informacje o tym czy katalog jest otwarty.
		//
		bool isOpened();

		// Ustawia wskanik odczytywanych nazw na okreslona nazwe.
		//
		bool seek(uint32_t offset);

		// Zwraca aktualna pozycje wskanika odczytywanych nazw.
		//
		uint32_t tell();

		// Odczytuje aktualna nazwe.
		//
		char *read();

		// Zwraca informacje o typie obiektu.
		//
		static ItemType getType(const char *path);

		// Zwraca liste nazw elementow znajdujacych sie we wskazanym katalogu.
		//
		// return	: jesli nie powiedzie sie otwieranie katalogu tozwracany jest NULL
		static basic::List<char *> *getItems(const char *path, ItemType flags = IT_Undefined);

		// Usuwa z pamieci itemy.
		//
		static void deleteItems(basic::List<char *> *&items);
	};
}}

#endif // DIRECTORY_H
