#include "monstermovement.h"

namespace logic
{
	void MonsterMovement::rotateLeft()
	{
		uint16_t tmp = this->_monster.direction.x;
		this->_monster.direction.x = this->_monster.direction.y;
		this->_monster.direction.y = -tmp;
	}

	void MonsterMovement::rotateRight()
	{
		uint16_t tmp = this->_monster.direction.x;
		this->_monster.direction.x = -this->_monster.direction.y;
		this->_monster.direction.y = tmp;
	}

	bool MonsterMovement::checkRightWall()
	{
		uint16_t wallX = this->_monster.position.x - this->_monster.direction.y;
		uint16_t wallY = this->_monster.position.y + this->_monster.direction.x;

		//char value = this->__mapData[this->_mapWidth * wallY + wallX];
		char value = this->__mapData[wallY][wallX];

		if(value == this->_spaceChar || value == this->_playerChar)
			return false;

		return true;
	}

	bool MonsterMovement::checkBeforeWall()
	{
		uint16_t wallX = this->_monster.position.x + this->_monster.direction.x;
		uint16_t wallY = this->_monster.position.y + this->_monster.direction.y;

		//char value = this->__mapData[this->_mapWidth * wallY + wallX];
		char value = this->__mapData[wallY][wallX];

		if(value == this->_spaceChar || value == this->_playerChar)
			return false;

		return true;
	}

	bool MonsterMovement::checkCornerWall()
	{
		uint16_t wallX = this->_monster.position.x - this->_monster.direction.y - this->_monster.direction.x;
		uint16_t wallY = this->_monster.position.y + this->_monster.direction.x - this->_monster.direction.y;

		if(this->__mapData[wallY][wallX] == this->_spaceChar)
			return false;

//		if(this->__mapData[this->_mapWidth * wallY + wallX] == this->_spaceChar)
//			return false;

		return true;
	}

	bool MonsterMovement::rotateMonster()
	{
		if(this->checkBeforeWall()) // jesli przed potworem jest sciana to obracamy potowra w lewo
		{
			this->rotateLeft();

			if(this->checkBeforeWall()) // jesli po obrocie w lewo przed potworem jest nadal sciana
			{
				this->rotateLeft();

				return this->checkBeforeWall(); // jesli po obrocie w lewo przed potworem jest nadal sciana
			}
		}

		return false;
	}

	MonsterMovement::MonsterMovement(Map *__map,
		Monster &monster,
		char monsterChar,
		char playerChar,
		char spaceChar)
	{
		this->__mapData = __map->__getData();
		this->_mapWidth = __map->getWidth();
		this->_mapHeight = __map->getHeight();

		this->_monster = monster;

		this->_monsterChar = monsterChar;
		this->_playerChar = playerChar;;
		this->_spaceChar = spaceChar;
	}

	bool MonsterMovement::move()
	{
		// pozycja potwora na mapie przed aktualizacja pozycji
		//uint16_t index = this->_mapWidth *  this->_monster.position.y +  this->_monster.position.x;
		Vector2D<uint16_t> oldPosition = this->_monster.position;

		if(this->checkRightWall()) // jesli po prawej stronie potwora jest siciana
		{
			if(this->rotateMonster())  // wykonijemy ewentualne oborty i sprawdzamy czy przed potowrem jest sciana
				return false;
		}
		else // jesli potwor nie ma siany po swojej prawej stronie
		{
			if(this->checkCornerWall()) // jesli potowr znalazl sie na rogu
				this->rotateRight();

			else // jesli potwor nie jest na rogu
			{
				if(this->rotateMonster()) // wykonijemy ewentualne oborty i sprawdzamy czy przed potowrem jest sciana
					this->rotateLeft();
			}
		}

		this->_monster.position.x += this->_monster.direction.x;
		this->_monster.position.y += this->_monster.direction.y;

		//this->__mapData[index] = this->_spaceChar;
		this->__mapData[oldPosition.y][oldPosition.x] = this->_spaceChar;
		//this->__mapData[this->_mapWidth * this->_monster.position.y +  this->_monster.position.x] = this->_monsterChar;
		this->__mapData[this->_monster.position.y][this->_monster.position.x] = this->_monsterChar;

		return true;
	}

	Vector2D<uint16_t> MonsterMovement::getMonsterPosition()
	{
		return this->_monster.position;
	}

	char MonsterMovement::getMonsterChar()
	{
		return this->_monsterChar;
	}
}
