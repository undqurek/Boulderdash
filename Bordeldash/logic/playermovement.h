#ifndef PAYERMOVEMENT_H
#define PAYERMOVEMENT_H

#include "types.h"
#include "map.h"

#include <basic/preprocesor.h>


namespace logic
{
	class PlayerMovement
	{
	private:
		char *__*__mapData;

		uint16_t _mapWidth;
		uint16_t _mapHeight;

		Vector2D<uint16_t> _playerPosition;

		char _playerChar;
		char _diamondChar;
		char _groundChar;
		char _spaceChar;

		const static Vector2D<int16_t> _charsMap[4]; // przechowuje wektory kierunku

		char checkPosition(const Vector2D<int16_t> &direction);

	public:
		enum MovementDirection
		{
			MD_Up = 0,
			MD_Down = 1,
			MD_Left = 2,
			MD_Right = 3
		};

	public:
		PlayerMovement(Map *__mapData,
			Vector2D<uint16_t> &playerPosition,
			char playerChar = 'A',
			char diamondChar = '?',
			char groundChar = '#',
			char spaceChar = ' ');

		// Zwraca informacje o tym czy gracz jest poprawny (czy nie zostal skuty przez potwora).
		//
		bool isCorrect();

		// Porusza graczem
		//
		bool move(MovementDirection direction);

		// Zwraca pozycje gracza.
		//
		Vector2D<uint16_t> getPlayerPosition();

		// Zwraca znak opisujacy gracza.
		//
		char getPlayerChar();
	};
}

#endif // PAYERMOVEMENT_H
