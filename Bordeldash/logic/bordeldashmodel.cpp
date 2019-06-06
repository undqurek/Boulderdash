#include "Bordeldashmodel.h"

#include "Bordeldashview.h"

#include <basic/cleaner.h>
#include <intermediary/thread.h>


using namespace	core::basic;
using namespace	core::intermediary;

namespace logic
{
	static void deleteMonster(MonsterMovement *monster)
	{
		Cleaner::deleteObject(monster);
	}

	static void deleteObject(ObjectMovement *object)
	{
		Cleaner::deleteObject(object);
	}

	bool BordeldashModel::detectPlayer()
	{
		Cleaner::deleteObject(this->_playerMovement);

		const char *__*__mapData = (const char *__*__)this->_map.__getData();

		uint16_t mapWidth = this->_map.getWidth();
		uint16_t mapHeight = this->_map.getHeight();

		bool detected = false;
		Vector2D<uint16_t> position;

		for(uint16_t y = 0; y < mapHeight; ++y)
		{
			const char *__row = __mapData[y];

			for(uint16_t x = 0; x < mapWidth; ++x)
			{
				if(__row[x] == 'A')
				{
					if(detected)
						return false;

					else
					{
						position.x = x;
						position.y = y;

						detected = true;
					}
				}
			}
		}

		this->_playerMovement = new PlayerMovement(&this->_map, position, 'A', '?', '#', ' ');

		return detected;
	}

	void BordeldashModel::detectMonsters()
	{
		this->_monstersMovements.clear(&deleteMonster);

		const char *__*__mapData = (const char *__*__)this->_map.__getData();

		uint16_t mapWidth = this->_map.getWidth();
		uint16_t mapHeight = this->_map.getHeight();

		Monster monster;

		Vector2D<uint16_t> &position = monster.position;
		Vector2D<uint16_t> &direction = monster.direction;

		for(uint16_t y = 0; y < mapHeight; ++y)
		{
			const char *__row = __mapData[y];

			for(uint16_t x = 0; x < mapWidth; ++x)
			{
				if(__row[x] == '@')
				{
					position.x = x;
					position.y = y;
					direction.x = 1;
					direction.y = 0;

					this->_monstersMovements.pushBack(new MonsterMovement(&this->_map, monster, '@', 'A', ' '));
				}
			}
		}
	}

	void BordeldashModel::detectObjects(List<ObjectMovement *> &refObjects, const char objectChar)
	{
		refObjects.clear(&deleteObject);

		const char *__*__mapData = (const char *__*__)this->_map.__getData();

		uint16_t mapWidth = this->_map.getWidth();
		uint16_t mapHeight = this->_map.getHeight();

		Vector2D<uint16_t> position;

		for(uint16_t y = 0; y < mapHeight; ++y)
		{
			const char *__row = __mapData[y];

			for(uint16_t x = 0; x < mapWidth; ++x)
			{
				if(__row[x] == objectChar)
				{
					position.x = x;
					position.y = y;

					refObjects.pushBack(new ObjectMovement(&this->_map, position, objectChar, ' '));
				}
			}
		}
	}

	BordeldashModel::BordeldashModel()
	{
		this->_looped = false;
		this->_playerMovement = NULL;
	}

	BordeldashModel::~BordeldashModel()
	{
		this->_monstersMovements.clear(&deleteMonster);
		this->_stonesMovements.clear(&deleteObject);
		this->_diamondsMovements.clear(&deleteObject);

		Cleaner::deleteObject(this->_playerMovement);
	}

	bool BordeldashModel::loadMap(const char *mapPath)
	{
		this->_map.destroy();

		if(this->_map.load(mapPath))
		{
			if(this->detectPlayer())
			{
				this->detectMonsters();
				this->detectObjects(this->_stonesMovements, 'o');
				this->detectObjects(this->_diamondsMovements, '?');

				return true;
			}
			else
				this->_map.destroy();
		}

		return false;
	}

	bool BordeldashModel::makeLogic()
	{
		BordeldashView *__view = (BordeldashView *__)this->__getView();

		if(__view == NULL)
			return false;

		__view->showMap((const char *__*__)this->_map.__getData(), this->_map.getWidth(), this->_map.getHeight());

		uint32_t counter = 0; // odlaicza iteracje w trakcie ktorych potwory, kamienie i diamenty nie poruszaja sie
		this->_looped = true;

		while(this->_looped)
		{
			if(this->_playerDirection.isSetted())
			{
				Vector2D<uint16_t> oldPosition = this->_playerMovement->getPlayerPosition();

				if(this->_playerMovement->move(this->_playerDirection.get()))
				{
					Vector2D<uint16_t> newPosition = this->_playerMovement->getPlayerPosition();
					__view->setPlayer(oldPosition, newPosition);
				}
			}

			if(counter < 10)
				counter += 1;

			else
			{
				for(List<MonsterMovement *>::Iterator i = this->_monstersMovements.getBegin(); i.isIndicated(); ++i)
				{
					this->_monstersMovements.remove(1);
					continue;

					MonsterMovement *__monster = i.__getItem();
					Vector2D<uint16_t> oldPosition = __monster->getMonsterPosition();

					if(__monster->move())
					{
						Vector2D<uint16_t> newPosition = __monster->getMonsterPosition();
						__view->setMonster(oldPosition, newPosition);
					}
				}

				for(List<ObjectMovement *>::Iterator i = this->_stonesMovements.getBegin(); i.isIndicated(); ++i)
				{
					ObjectMovement *__stone = i.__getItem();
					Vector2D<uint16_t> oldPosition = __stone->getObjectPosition();

					if(__stone->move())
					{
						Vector2D<uint16_t> newPosition = __stone->getObjectPosition();
						__view->setStone(oldPosition, newPosition);
					}
				}

				for(List<ObjectMovement *>::Iterator i = this->_diamondsMovements.getBegin(); i.isIndicated(); ++i)
				{
					ObjectMovement *__diamond = i.__getItem();
					Vector2D<uint16_t> oldPosition = __diamond->getObjectPosition();

					if(__diamond->move())
					{
						Vector2D<uint16_t> newPosition = __diamond->getObjectPosition();
						__view->setDiamond(oldPosition, newPosition);
					}
				}

				counter = 0;
			}

			__view->update();

			Thread<void>::sleepMilliseconds(10);
		}
	}

	bool BordeldashModel::postBreakLogic()
	{
		this->_looped = false;
	}

	bool BordeldashModel::movePlayer(PlayerMovement::MovementDirection direction)
	{
		return this->_playerDirection.set(direction);
	}
}
