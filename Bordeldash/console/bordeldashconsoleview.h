#ifndef BordeldashCONSOLEVIEW_H
#define BordeldashCONSOLEVIEW_H

#include "logic/Bordeldashview.h"

#include <console/consolemenu.h>
#include <stdint.h>


using namespace core::console;

namespace console
{
	class BordeldashConsoleView
		: public logic::BordeldashView
	{
	private:
		uint16_t _logoLeft;
		uint16_t _logoTop;

		uint16_t _menuLeft;
		uint16_t _menuTop;

		const char *__mapsDirectory;
		const char *__savesDirectory;

		core::console::ConsoleOperations _operations;
		core::console::ConsoleMenu _menu;

		void printFrame();
		void printLogo();

		void setMainMenuMode();
		void setSinglepalyerMenuMode();
		void setMultipalyerMenuMode();
		void setEditorMenuMode();

		void setSingleplayerGameMode(const char *menuTitle, const char *directoryPath);
		void setMultipalyerGameMode();
		void setMapEditorMode();

		bool setMapLoadMode(const char *title, const char *directory);

	public:
		BordeldashConsoleView();

		// Uruchamia logike widoku.
		//
		bool run();

		// Wyswietla mape.
		//
		void showMap(const char *__*__map, uint16_t width, uint16_t height);

		// Aktualizuje pozycje playera.
		//
		void setPlayer(logic::Vector2D<uint16_t> &oldPosition, logic::Vector2D<uint16_t> &newPosition);

		// Aktualizuje pozycje potwora.
		//
		void setMonster(logic::Vector2D<uint16_t> &oldPosition, logic::Vector2D<uint16_t> &newPosition);

		// Aktualizuje pozycje kamienia.
		//
		void setStone(logic::Vector2D<uint16_t> &oldPosition, logic::Vector2D<uint16_t> &newPosition);

		// Aktualizuje pozycje diamentu.
		//
		void setDiamond(logic::Vector2D<uint16_t> &oldPosition, logic::Vector2D<uint16_t> &newPosition);

		// Aktualizauje widok.
		//
		void update();
	};
}

#endif // BordeldashCONSOLEVIEW_H
