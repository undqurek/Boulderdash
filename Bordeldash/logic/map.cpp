#include "map.h"

#include <basic/cleaner.h>
#include <basic/memory.h>
#include <intermediary/file.h>
#include <parsing/parserutils.h>
#include <stddef.h>


using namespace	core::basic;
using namespace	core::intermediary;
using namespace core::parsing;

namespace logic
{
	const uint16_t Map::_expectedWidth = 80;
	const uint16_t Map::_expectedHeight = 19;

	bool Map::detectSize(const uint8_t *data, uint32_t dataLength)
	{
		const char *__pointer = (char*)data;
		const char *__end = __pointer + dataLength;

		const char *__lineBegin = __pointer;
		ParserUtils::findEndLine(__pointer, __end); // przesuwamy pointer na koniec lini lub pliku jesli brak konca lini

		if(__pointer == __lineBegin) // wymagane jest aby mapa zawierala przynajmniej jedna niepusta linie
			return false;

		this->_width = __pointer - __lineBegin; // obliczony rozmiar pierwszej lini jest szerokoscia mapy
		this->_height = 1;

		if(ParserUtils::skipEndLine(__pointer, __end)) // jesli uda sie pominac znak konca lini to prawdopodobnie istnieje kolejna linia
		{
			__lineBegin = __pointer;

			while(ParserUtils::findEndLine(__pointer, __end)) // dopuki udaje sie odnalesc znak konca lini to mamy pewnosc ze istnieje jakas kolejna linia
			{
				if(__pointer - __lineBegin != this->_width) // sprawdzamy czy rozmiar lini zgadza sie z rozmiarem pierwszej lini
					return false;

				this->_height += 1;

				if(ParserUtils::skipEndLine(__pointer, __end)) // jesli uda sie pominac znak konca lini to prawdopodobnie istnieje kolejna linia
					__lineBegin = __pointer;

				else
					return false;
			}

			if(__pointer == __lineBegin) // jesli wskaznik pokrywa sie ze znakiem poczatku lini to znaczy ze nie istnieje zadna linia konczaca plik (ostatnia linia jest pusta lub jej brak)
				return true;

			if(__pointer - __lineBegin != this->_width) // sprawdzamy czy rozmiar lini konczacej zgadza sie z rozmiarem pierwszej lini
				return false;

			this->_height += 1;
		}

		return true;
	}

	void Map::extractData(const uint8_t *data)
	{
		this->_data = new char*[this->_height];

		for(uint16_t y = 0; y < this->_height; ++y)
		{
			this->_data[y] = new char[this->_width];
			Memory::copy(data, (uint8_t *)this->_data[y], this->_width);

			data += this->_width;

			if(*data == '\r')
				data += 1;

			if(*data == '\n')
				data += 1;
		}
	}

	Map::Map()
	{
		this->_data = NULL;

		this->_width = 0;
		this->_height = 0;

		this->_loaded = false;
	}

	Map::~Map()
	{
		this->destroy();
	}

	bool Map::isLoaded()
	{
		return this->_loaded;
	}

	bool Map::load(const char *mapPath)
	{
		if(this->_loaded)
			return false;

		uint8_t *data;
		uint32_t dataLength;

		if(File::readBytes(mapPath, data, dataLength, 100 * 1024 * 1024) == dataLength
		   && this->detectSize(data, dataLength)
		   && this->_width == this->_expectedWidth
		   && this->_height == this->_expectedHeight)
		{
			this->extractData(data);
			Cleaner::deleteArray(data);

			this->_loaded = true;

			return true;
		}

		Cleaner::deleteArray(data);

		return false;
	}

	void Map::destroy()
	{
		if(this->_loaded)
		{
			Cleaner::deleteArray2D(this->_data, this->_height);

			this->_width = 0;
			this->_height = 0;

			this->_loaded = false;
		}
	}

	char *__*Map::__getData()
	{
		return this->_data;
	}

	uint16_t Map::getWidth()
	{
		return this->_width;
	}

	uint16_t Map::getHeight()
	{
		return this->_height;
	}
}
