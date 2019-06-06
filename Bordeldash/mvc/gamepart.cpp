#include "gamepart.h"

namespace mvc
{
	GamePart::GamePart(GameModel *_model, GameView *_view)
	{
		this->_model = _model;
		this->_view = _view;

		_model->__view = _view;
		_view->__model = _model;
	}

	bool GamePart::runBefore()
	{
		return this->_model->runBefore() && this->_view->runBefore();
	}

	bool GamePart::run()
	{
		return this->_model->run() && this->_view->run();
	}

	bool GamePart::runAfter()
	{
		return this->_model->runAfter() && this->_view->runAfter();
	}
}
