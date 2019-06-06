#include "gameview.h"

#include <stddef.h>


namespace mvc
{
	GameModel *GameView::__getModel()
	{
		return this->__model;
	}

	bool GameView::runBefore()
	{
		return (this->__model != NULL);
	}

	bool GameView::run()
	{
		return (this->__model != NULL);
	}

	bool GameView::runAfter()
	{
		return (this->__model != NULL);
	}

	GameView::GameView()
	{

	}
}
