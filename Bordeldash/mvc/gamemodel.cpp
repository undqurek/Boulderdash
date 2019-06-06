#include "gamemodel.h"

#include <stddef.h>


namespace mvc
{
	GameView *GameModel::__getView()
	{
		return this->__view;
	}

	bool GameModel::runBefore()
	{
		return (this->__view != NULL);
	}

	bool GameModel::run()
	{
		return (this->__view != NULL);
	}

	bool GameModel::runAfter()
	{
		return (this->__view != NULL);
	}

	GameModel::GameModel()
	{

	}
}
