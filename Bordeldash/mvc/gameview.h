#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "gamemodel.h"


namespace mvc
{
	class GameView
	{
	private:
		GameModel *__model;

		friend class GamePart;

	protected:
		GameModel *__getModel();

		virtual bool runBefore();
		virtual bool run();
		virtual bool runAfter();

	public:
		GameView();
	};
}

#endif // GAMEVIEW_H
