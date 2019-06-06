#ifndef MAP_H
#define MAP_H

#include <basic/preprocesor.h>
#include <stdint.h>


namespace logic
{
	class Map
	{
	private:
		static const uint16_t _expectedWidth;
		static const uint16_t _expectedHeight;

		char **_data;

		uint16_t _width;
		uint16_t _height;

		bool _loaded;

		// Wykrywa rozmiar mapy na podstawie odczytanych danych oraz ich dlugosci.
		bool detectSize(const uint8_t *data, uint32_t dataLength);

		// Wydobywa wlasniwe dane mapy.
		void extractData(const uint8_t *data);

	public:
		Map();
		~Map();

		// zwraca informacje o tym czy mapa jest wczytana.
		//
		bool isLoaded();

		// Wczytuje mape z pliku. W przypadku proby ponownego wczytania mapy nalezy wykonac najpierw metode destroy().
		//
		bool load(const char *mapPath);

		// Niszczy wczytana mape.
		//
		void destroy();

		// Zwraca wskaznik do odczytanych danych mapy.
		//
		char *__*__getData();

		// Zwraca szerokosc mapy.
		//
		uint16_t getWidth();

		// Zwraca wysokosc mapy.
		//
		uint16_t getHeight();
	};
}

#endif // MAP_H
