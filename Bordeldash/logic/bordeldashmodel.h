#ifndef BordeldashMODEL_H
#define BordeldashMODEL_H

#include "mvc/gamemodel.h"
#include "types.h"
#include "map.h"
#include "playermovement.h"
#include "monstermovement.h"
#include "objectmovement.h"

#include <basic/list.h>
#include <basic/toggle.h>
#include <intermediary/thread.h>


namespace logic
{
	class BordeldashModel
		: public mvc::GameModel
	{
	private:
		bool _looped;

		core::basic::LastToggle<PlayerMovement::MovementDirection> _playerDirection;

		Map _map;

		PlayerMovement *_playerMovement;
		core::basic::List<MonsterMovement *> _monstersMovements;
		core::basic::List<ObjectMovement *> _stonesMovements;
		core::basic::List<ObjectMovement *> _diamondsMovements;

		bool detectPlayer();
		void detectMonsters();
		void detectObjects(core::basic::List<ObjectMovement *> &refObjects, const char objectChar);

	public:
		BordeldashModel();
		~BordeldashModel();

		// Wczytuje mape.
		//
		bool loadMap(const char *mapPath);

		// Uruchamia logike gry.
		//
		bool makeLogic();

		// Przerywa logike gry.
		//
		bool postBreakLogic();

		// Porusza graczem.
		//
		bool movePlayer(PlayerMovement::MovementDirection direction);
	};
}

#endif // BordeldashMODEL_H
