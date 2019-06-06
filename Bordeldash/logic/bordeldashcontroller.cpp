#include "Bordeldashcontroller.h"

#include "Bordeldashmodel.h"
#include "console/Bordeldashconsoleview.h"

#include <basic/cleaner.h>


using namespace core::basic;
using namespace	mvc;
using namespace console;

namespace logic
{
	BordeldashController::BordeldashController()
	{
		this->_started = false;

		GameModel *part_model = new BordeldashModel();
		GameView *part_view = new BordeldashConsoleView();

		GamePart **controller_parts = new GamePart*[1];
		controller_parts[0] = new GamePart(part_model, part_view);

		this->_controller = new GameController(controller_parts, 1);
	}

	BordeldashController::~BordeldashController()
	{
		Cleaner::deleteObject(this->_controller);
	}

	bool BordeldashController::isStarted()
	{
		return this->_started;
	}

	bool BordeldashController::run()
	{
		if(this->_started)
			return false;

		if(this->_controller->run())
		{
			this->_started = true;

			return true;
		}

		return false;
	}
}
