#ifndef GAMEPART_H
#define GAMEPART_H

#include "gamemodel.h"
#include "gameview.h"


namespace mvc
{
	class GamePart
	{
	private:
		GameModel *_model;
		GameView *_view;

	public:
		GamePart(GameModel *_model, GameView *_view);

		bool runBefore();
		bool run();
		bool runAfter();
	};
}

#endif // GAMEPART_H
