#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "gamepart.h"

#include <stdint.h>


namespace mvc
{
	class GameController
	{
	private:
		GamePart **_parts;
		uint32_t _partsCount;

	public:
		GameController(GamePart **_parts, uint32_t partsCount);
		~GameController();

		bool run();
	};
}

#endif // GAMECONTROLLER_H
