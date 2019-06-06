#ifndef UI_H
#define UI_H

#include "types.h"

#include <stdint.h>


namespace logic
{
	class UI
	{
	public:
		virtual void start() = 0;

		virtual void setMonster(Vector2D &oldPosition, Vector2D &newPosition) = 0;
		virtual void setStone(Vector2D &oldPosition, Vector2D &newPosition) = 0;
		virtual void setDiamond(Vector2D &oldPosition, Vector2D &newPosition) = 0;

		virtual void update() = 0;
	};
}

#endif // UI_H
