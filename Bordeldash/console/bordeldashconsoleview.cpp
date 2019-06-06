#include "Bordeldashconsoleview.h"

#include "logic/Bordeldashmodel.h"

#include <basic/list.h>
#include <basic/string.h>
#include <intermediary/directory.h>
#include <iostream>


using namespace core::basic;
using namespace core::intermediary;
using namespace logic;

namespace console
{
	void BordeldashConsoleView::printFrame()
	{
		this->_operations.setPosition(0, 0);

		std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

		for(uint16_t i = 0; i < 23; ++i)
			std::cout << "+                                                                              +";

		std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

		this->_operations.setPosition(0, 0);
	}

	void BordeldashConsoleView::printLogo()
	{
		const char *__logo[7][1] = {
			{ "     ____    ______ ____   ____   _____ __     ____   _____  ____  __  __" },
			{ "    / _  |  /  _  // __ | / __ | / ___// /    / __ | / __  // ___// / / /" },
			{ "   / /_/ / / / / // /_/ // / / // /__ / /    / / / // /_/ // /_  / /_/ / " },
			{ "  / _   / / / / //   __// / / // ___// /    / / / // __  //__  // __  /  " },
			{ " / /_/ | / /_/ // /\\ \\ / /_/ // /__ / /__  / /_/ // / / / __/ // / / /   " },
			{ "/_____/ /_____//_/ /_//_____//____//____/ /_____//_/ /_//____//_/ /_/    " },
			{ "                                                                     v2.0" },
		};

		for(uint16_t i = 0; i < 7; ++i)
		{
			this->_operations.setPosition(this->_logoLeft, this->_logoTop + i);
			std::cout << __logo[i][0];
		}
	}

	void BordeldashConsoleView::setMainMenuMode()
	{
		List<char *__> list;

		list.pushBack("SINGLEPAYER GAME");
		list.pushBack("MULTIPAYER GAME");
		list.pushBack("MAP EDITOR");
		list.pushBack("EXIT");

		uint16_t position = 1;

		while(true)
		{
			this->_operations.setPosition(this->_menuLeft, this->_menuTop);
			std::cout << "---=[ MAIN MENU ]=---";

			position = this->_menu.run(this->_menuLeft, this->_menuTop + 1, &list, position);
			this->_operations.clearScreen(this->_menuLeft, this->_menuTop, 28, 5);

			switch(position)
			{
			case 1: // SINGLEPAYER GAME
				this->setSinglepalyerMenuMode();
				break;

			case 2: // MULTIPAYER GAME
				this->setMultipalyerMenuMode();
				break;

			case 3: // MAP EDITOR
				this->setEditorMenuMode();
				break;

			case 4: // EXIT
				return;

			case 0xFFFF: // ESCAPE KEY
				return;
			}
		}
	}

	void BordeldashConsoleView::setSinglepalyerMenuMode()
	{
		List<char *__> list;

		list.pushBack("NEW GAME");
		list.pushBack("LOAD GAME");
		list.pushBack("BACK");

		uint16_t position = 1;

		while(true)
		{
			this->_operations.setPosition(this->_menuLeft, this->_menuTop);
			std::cout << "---=[ SINGLEPAYER GAME ]=---";

			position = this->_menu.run(this->_menuLeft, this->_menuTop + 1, &list, position);
			this->_operations.clearScreen(1, 1, 78, 23);

			switch(position)
			{
			case 1: // NEW GAME
				this->setSingleplayerGameMode("Maps:", this->__mapsDirectory);
				break;

			case 2: // LOAD GAME
				this->setSingleplayerGameMode("Saves:", this->__savesDirectory);
				break;

			case 3: // BACK
				return;

			case 0xFFFF: // ESCAPE KEY
				return;
			}
		}
	}

	void BordeldashConsoleView::setMultipalyerMenuMode()
	{
		List<char *__> list;

		list.pushBack("CREATE GAME");
		list.pushBack("JOIN GAME");
		list.pushBack("BACK");

		uint16_t position = 1;

		while(true)
		{
			this->_operations.setPosition(this->_menuLeft, this->_menuTop);
			std::cout << "---=[ MULTIPAYER GAME ]=---";

			position = this->_menu.run(this->_menuLeft, this->_menuTop + 1, &list, position);
			this->_operations.clearScreen(1, 1, 78, 23);

			switch(position)
			{
			case 1: // CREATE GAME
				this->setMultipalyerGameMode();
				break;

			case 2: // JOIN GAME
				//TODO: dorobic

				break;

			case 3: // BACK
				return;

			case 0xFFFF: // ESCAPE KEY
				return;
			}
		}
	}

	void BordeldashConsoleView::setEditorMenuMode()
	{
		List<char *__> list;

		list.pushBack("NEW MAP");
		list.pushBack("LOAD MAP");
		list.pushBack("BACK");

		uint16_t position = 1;

		while(true)
		{
			this->_operations.setPosition(this->_menuLeft, this->_menuTop);
			std::cout << "---=[ MAP EDITOR ]=---";

			position = this->_menu.run(this->_menuLeft, this->_menuTop + 1, &list, position);
			this->_operations.clearScreen(this->_menuLeft, this->_menuTop, 22, 4);

			switch(position)
			{
			case 1: // NEW GAME
				//TODO: dorobic

				break;

			case 2: // LOAD GAME
				this->setMapEditorMode();
				break;

			case 3: // BACK
				return;

			case 0xFFFF: // ESCAPE KEY
				return;
			}
		}
	}

	void BordeldashConsoleView::setSingleplayerGameMode(const char *menuTitle, const char *directoryPath)
	{
		if(this->setMapLoadMode(menuTitle, directoryPath))
		{
			BordeldashModel *__model = (BordeldashModel *__)this->__getModel();
			__model->makeLogic();
		}
	}

	void BordeldashConsoleView::setMultipalyerGameMode()
	{
		if(this->setMapLoadMode("Maps:", this->__mapsDirectory))
		{
			BordeldashModel *__model = (BordeldashModel *__)this->__getModel();
			__model->makeLogic();
		}
	}

	void BordeldashConsoleView::setMapEditorMode()
	{
		if(this->setMapLoadMode("Maps:", this->__mapsDirectory))
		{
			BordeldashModel *__model = (BordeldashModel *__)this->__getModel();

			//__model->
		}
	}

	bool BordeldashConsoleView::setMapLoadMode(const char *title, const char *directory)
	{
		this->_operations.setPosition(3, 2);
		std::cout << title;

		List<char *> *filesNames = Directory::getItems(directory, Directory::IT_File);

		if(filesNames == NULL)
		{
			this->_operations.setPosition(3, 22);
			std::cout << "Error: Missing '" << directory << "' directory!";

			this->_operations.getKey();

			this->_operations.setPosition(3, 22);
			std::cout << "                                               ";

			return false;
		}

		if(filesNames->getSize() == 0)
		{
			Directory::deleteItems(filesNames);

			this->_operations.setPosition(3, 22);
			std::cout << "Error: Missing files!";

			this->_operations.getKey();

			this->_operations.setPosition(3, 22);
			std::cout << "                     ";

			return false;
		}

		uint16_t position = 1;
		BordeldashModel *__model = (BordeldashModel *__)this->__getModel();

		while(true)
		{
			position = this->_menu.run(2, 4, filesNames, position);
			this->_operations.clearScreen(1, 1, 78, 23);

			if(position == 0xFFFF)
			{
				Directory::deleteItems(filesNames);

				return false;
			}

			char *__mapName = filesNames->__get(position - 1);
			char *mapPath = String::concatenate(directory, __mapName);

			if(__model->loadMap(mapPath))
			{
				Cleaner::deleteArray(mapPath);
				Directory::deleteItems(filesNames);

				return true;
			}
			else
			{
				Cleaner::deleteArray(mapPath);

				this->_operations.setPosition(3, 22);
				std::cout << "Error: Incorrect file type!";

				this->_operations.getKey();

				this->_operations.setPosition(3, 22);
				std::cout << "                           ";
			}
		}
	}

	BordeldashConsoleView::BordeldashConsoleView()
	{
		this->_logoLeft = 3;
		this->_logoTop = 3;

		this->_menuLeft = 4;
		this->_menuTop = 18;

		this->__mapsDirectory = "maps/";
		this->__savesDirectory = "saves/";
	}

	bool BordeldashConsoleView::run()
	{
		if(this->BordeldashView::run())
		{
			this->printFrame();
			this->printLogo();

			this->setMainMenuMode();

			return true;
		}

		return false;
	}

	void BordeldashConsoleView::showMap(const char *__*__map, uint16_t width, uint16_t height)
	{
		for(uint16_t y = 0; y < height; ++y)
		{
            const char *__row = __map[y];

			for(uint16_t x = 0; x < width; ++x)
            {
                this->_operations.setPosition(x, y);

                std::cout << __row[x];
            }
		}

		std::cout.flush();
	}

	void BordeldashConsoleView::setPlayer(logic::Vector2D<uint16_t> &oldPosition, logic::Vector2D<uint16_t> &newPosition)
	{
		this->_operations.setPosition(oldPosition.x, oldPosition.y);
		std::cout << " ";

		this->_operations.setPosition(newPosition.x, newPosition.y);
		std::cout << "A";
	}

	void BordeldashConsoleView::setMonster(Vector2D<uint16_t> &oldPosition, Vector2D<uint16_t> &newPosition)
	{
		this->_operations.setPosition(oldPosition.x, oldPosition.y);
		std::cout << " ";

		this->_operations.setPosition(newPosition.x, newPosition.y);
		std::cout << "@";
	}

	void BordeldashConsoleView::setStone(Vector2D<uint16_t> &oldPosition, Vector2D<uint16_t> &newPosition)
	{
		this->_operations.setPosition(oldPosition.x, oldPosition.y);
		std::cout << " ";

		this->_operations.setPosition(newPosition.x, newPosition.y);
		std::cout << "o";
	}

	void BordeldashConsoleView::setDiamond(Vector2D<uint16_t> &oldPosition, Vector2D<uint16_t> &newPosition)
	{
		this->_operations.setPosition(oldPosition.x, oldPosition.y);
		std::cout << " ";

		this->_operations.setPosition(newPosition.x, newPosition.y);
		std::cout << "?";
	}

	void BordeldashConsoleView::update()
	{
		if(this->_operations.checkKey())
		{
			BordeldashModel *__model = (BordeldashModel *__)this->__getModel();
			uint16_t key = this->_operations.getKey();

			if(key & 0xE0)
			{
				switch(key)
				{
				case ConsoleOperations::K_Up:
					__model->movePlayer(PlayerMovement::MD_Up);
					break;

				case ConsoleOperations::K_Down:
					__model->movePlayer(PlayerMovement::MD_Down);
					break;

				case ConsoleOperations::K_Left:
					__model->movePlayer(PlayerMovement::MD_Left);
					break;

				case ConsoleOperations::K_Right:
					__model->movePlayer(PlayerMovement::MD_Right);
					break;
				}
			}
			else
			{
				if(key == ConsoleOperations::K_Escape)
					__model->postBreakLogic();
			}
		}
	}
}
