#ifndef BordeldashVIEW_H
#define BordeldashVIEW_H

#include "mvc/gameview.h"
#include "types.h"

#include <basic/preprocesor.h>


namespace logic
{
	class BordeldashView
		: public mvc::GameView
	{
	public:
		// Wyswietla mape.
		//
		virtual void showMap(const char *__*__map, uint16_t width, uint16_t height) = 0;

		// Aktualizuje pozycje playera.
		//
		virtual void setPlayer(Vector2D<uint16_t> &oldPosition, Vector2D<uint16_t> &newPosition) = 0;

		// Aktualizuje pozycje potwora.
		//
		virtual void setMonster(Vector2D<uint16_t> &oldPosition, Vector2D<uint16_t> &newPosition) = 0;

		// Aktualizuje pozycje kamienia.
		//
		virtual void setStone(Vector2D<uint16_t> &oldPosition, Vector2D<uint16_t> &newPosition) = 0;

		// Aktualizuje pozycje diamentu.
		//
		virtual void setDiamond(Vector2D<uint16_t> &oldPosition, Vector2D<uint16_t> &newPosition) = 0;

		// Aktualizauje widok.
		//
		virtual void update() = 0;
	};
}

#endif // BordeldashVIEW_H
