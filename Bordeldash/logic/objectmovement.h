#ifndef OBJECTMOVEMENT_H
#define OBJECTMOVEMENT_H

#include "types.h"
#include "map.h"

#include <basic/preprocesor.h>
#include <stdint.h>


namespace logic
{
	// Symuluje upadek obieku.
	class ObjectMovement
	{
	private:
		char *__*__mapData;

		uint16_t _mapWidth;
		uint16_t _mapHeight;

		int8_t _direction; // informuje o tym jak dany obket ma upadac bazujac na ostatnim upadku
		Vector2D<uint16_t> _objectPosition;

		char _objectChar;
		char _spaceChar;

	public:
		ObjectMovement(Map *__mapData,
			Vector2D<uint16_t> &objectPosition,
			char objectChar = 'o',
			char spaceChar = ' ');

		// Aktualizaje pozcyje obketu.
		//
		bool move();

		// Zwraca pozycje potwora.
		//
		Vector2D<uint16_t> getObjectPosition();

		// Zwraca znak opisujacy obiekt.
		//
		char getObjectChar();
	};
}

#endif // OBJECTMOVEMENT_H
