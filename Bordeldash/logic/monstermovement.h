#ifndef MONSTERMOVEMENT_H
#define MONSTERMOVEMENT_H

#include "types.h"
#include "map.h"

#include <basic/preprocesor.h>
#include <stdint.h>


namespace logic
{
	struct Monster
	{
		Vector2D<uint16_t> position;
		Vector2D<uint16_t> direction;
	};

	class MonsterMovement
	{
	private:
		char *__*__mapData;

		uint16_t _mapWidth;
		uint16_t _mapHeight;

		Monster _monster;

		char _monsterChar;
		char _playerChar;
		char _spaceChar;

		// Obraca potowra w lewo.
		void rotateLeft();

		// Obraca potwora w prawo.
		void rotateRight();

		// Sprawdza czy potwor ma sciane poswojej prawej sronie.
		bool checkRightWall();

		// Sprawdza czy przed potworem jest sciana.
		bool checkBeforeWall();

		// Sprawdza czy za potworem po prawej stronie jest naronik.
		bool checkCornerWall();

		// Wykonije maksymalnie dwa oborty w prawo jesli jest to konieczne i sprawdzamy czy przed potowrem jest sciana.
		bool rotateMonster();

	public:
		MonsterMovement(Map *__mapData,
			Monster &monster,
			char monsterChar = '@',
			char playerChar = 'A',
			char spaceChar = ' ');

		// Aktualizaje pozcyje potowra.
		//
		bool move();

		// Zwraca pozycje potwora.
		//
		Vector2D<uint16_t> getMonsterPosition();

		// Zwraca znak opisujacy potwora.
		//
		char getMonsterChar();
	};
}

#endif // MONSTERMOVEMENT_H
