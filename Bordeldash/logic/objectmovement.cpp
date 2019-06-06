#include "objectmovement.h"


namespace logic
{
	ObjectMovement::ObjectMovement(Map *__map,
		Vector2D<uint16_t> &objectPosition,
		char objectChar,
		char spaceChar)
	{
		this->__mapData = __map->__getData();
		this->_mapWidth = __map->getWidth();
		this->_mapHeight = __map->getHeight();

		this->_direction = -1; // domyslnie obkety upadaja najpierw na lewo
		this->_objectPosition = objectPosition;

		this->_objectChar = objectChar;
		this->_spaceChar = spaceChar;
	}

	bool ObjectMovement::move()
	{
		//char *__row = this->__mapData + this->_objectPosition.y * this->_mapWidth;
		char *__row = this->__mapData[this->_objectPosition.y];
		char *__nextRow = this->__mapData[this->_objectPosition.y + 1];

		uint32_t offset = this->_objectPosition.x; // przesuniecie obketu w poziomie

		if(__nextRow[offset] == this->_spaceChar) // upadek obketu w dol
		{
			__row[offset] = this->_spaceChar;
			__nextRow[offset] = this->_objectChar;

			this->_objectPosition.y += 1;

			return true;
		}

		if(__nextRow[offset] == this->_objectChar) // upadek obketu na lewo lub prawo
		{
			offset = this->_objectPosition.x + this->_direction; // obliczamy na ktora pozycje x'owa przesunie sie obket

			if(__row[offset] == this->_spaceChar) // sprawdzamy pierwsza mozliwosc przesuniecia zgodnie z kierunkiem
			{
				if(__nextRow[offset] == this->_spaceChar) // jesli obket moze upasc
				{
					__row[this->_objectPosition.x] = this->_spaceChar;
					__row[offset] = this->_objectChar;

					this->_objectPosition.x = offset;

					return true;
				}
			}

			offset = this->_objectPosition.x - this->_direction; // obliczamy na ktora pozycje x'owa przesunie sie obket

			if(__row[offset] == this->_spaceChar) // sprawdzamy druga mozliwosc przesuniecia zgodnie z kierunkiem
			{
				if(__nextRow[offset] == this->_spaceChar)
				{
					__row[this->_objectPosition.x] = this->_spaceChar;
					__row[offset] = this->_objectChar;

					this->_direction = -this->_direction; // zmieniamy kierunek upadku na przeciwny aby zachodzil on od razu dla pierwszego warunku
					this->_objectPosition.x = offset;

					return true;
				}
			}
		}

		return false;
	}

	Vector2D<uint16_t> ObjectMovement::getObjectPosition()
	{
		return this->_objectPosition;
	}

	char ObjectMovement::getObjectChar()
	{
		return this->_objectChar;
	}
}
