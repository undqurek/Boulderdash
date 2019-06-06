#include "gamecontroller.h"

#include <basic/cleaner.h>


using namespace	core::basic;

namespace mvc
{
	GameController::GameController(GamePart **_parts, uint32_t partsCount)
	{
		this->_parts = _parts;
		this->_partsCount = partsCount;
	}

	GameController::~GameController()
	{
		Cleaner::deleteArrayWithObjects(this->_parts, this->_partsCount);
	}

	bool GameController::run()
	{
		for(uint32_t i = 0; i < this->_partsCount; ++i)
		{
			if(this->_parts[i]->runBefore() == false)
				return false;
		}

		for(uint32_t i = 0; i < this->_partsCount; ++i)
		{
			if(this->_parts[i]->run() == false)
				return false;
		}

		for(uint32_t i = 0; i < this->_partsCount; ++i)
		{
			if(this->_parts[i]->runAfter() == false)
				return false;
		}

		return true;
	}
}
