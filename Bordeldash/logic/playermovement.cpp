#include "playermovement.h"

namespace logic
{
	const Vector2D<int16_t> PlayerMovement::_charsMap[4] = { { 0, -1 }, { 0, +1 }, { -1, 0 }, { +1, 0 } };

	char PlayerMovement::checkPosition(const Vector2D<int16_t> &direction)
	{
		uint16_t x = this->_playerPosition.x + direction.x;
		uint16_t y = this->_playerPosition.y + direction.y;

		char value = this->__mapData[y][x];

		return (value == this->_spaceChar || value == this->_diamondChar || value == this->_groundChar);
	}

	PlayerMovement::PlayerMovement(Map *__map,
		Vector2D<uint16_t> &playerPosition,
		char playerChar,
		char diamondChar,
		char groundChar,
		char spaceChar)
	{
		this->__mapData = __map->__getData();

		this->_mapWidth = __map->getWidth();
		this->_mapHeight = __map->getHeight();

		this->_playerPosition = playerPosition;

		this->_playerChar = playerChar;
		this->_diamondChar = diamondChar;
		this->_groundChar = groundChar;
		this->_spaceChar = spaceChar;
	}

	bool PlayerMovement::isCorrect()
	{
		return (this->__mapData[this->_playerPosition.y][this->_playerPosition.x] == this->_playerChar);
	}

	bool PlayerMovement::move(MovementDirection direction)
	{
		if(direction < 0 || direction > 3)
			return false;

		const Vector2D<int16_t> &tmp = _charsMap[direction];

		if(this->checkPosition(tmp))
		{
			this->__mapData[this->_playerPosition.y][this->_playerPosition.x] = this->_spaceChar;

			this->_playerPosition.x += tmp.x;
			this->_playerPosition.y += tmp.y;

			this->__mapData[this->_playerPosition.y][this->_playerPosition.x] = this->_playerChar;

			return true;
		}

		return false;
	}

	Vector2D<uint16_t> PlayerMovement::getPlayerPosition()
	{
		return this->_playerPosition;
	}

	char PlayerMovement::getPlayerChar()
	{
		return this->_playerChar;
	}
}
