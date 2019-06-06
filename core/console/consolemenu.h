#ifndef CONSOLEMENU_H
#define CONSOLEMENU_H

#include "basic/list.h"
#include "consoleoperations.h"


namespace core { namespace console
{
	class ConsoleMenu
    {
    private:
		ConsoleOperations _operations;

		ConsoleOperations::BackColor _defaultBackColor;
		ConsoleOperations::FontColor _defaultFontColor;
		ConsoleOperations::BackColor _selectedBackColor;
		ConsoleOperations::FontColor _selectedFontColor;

		void setDefaultColors();
		void setSelectedColors();

		void showItem(uint16_t x, uint16_t y,
			basic::List<char *>::Iterator &iterator,
			uint16_t number);

		void showItems(uint16_t x, uint16_t y,
			basic::List<char *>::Iterator &iterator,
			uint16_t startIndex, uint16_t indexLimit);

    public:
		ConsoleMenu();

		void setDefaultBackColor(ConsoleOperations::BackColor color);
		void setDefaultFontColor(ConsoleOperations::FontColor color);
		void setSelectedBackColor(ConsoleOperations::BackColor color);
		void setSelectedFontColor(ConsoleOperations::FontColor color);

		// Wypisuje na ekranie konsoli menu.
		//
		// x		: o'owa pozycja menu
		// y		: y'owa pozycja menu
		// list		: [wymagany] lista opcji w menu
		// position	: zaznaczona pozycja w menu (numerowanie od 1, w przypadku 0 brak zaznaczenia)
		void print(uint16_t x, uint16_t y, basic::List<char *> *list, uint16_t position);

		// Uruchamia na ekranie konsoli interatktywne menu.
		//
		// x		: o'owa pozycja menu
		// y		: y'owa pozycja menu
		// list		: [wymagany] lista opcji w menu
		// position	: zaznaczona pozycja w menu (numerowanie od 1, w przypadku 0 brak zaznaczenia)
		//
		// return	: zwraca watrosc reprezentujaca zaznaczony numer (wartosc z przedzilu <0, 0xFFFE>) w przypadku nacisniecia klawisza ENTER lub 0xFFFF w przypadku nacisniecia klasza ESCAPE
		uint16_t run(uint16_t x, uint16_t y, basic::List<char *> *list, uint16_t position);
    };
}}

#endif // CONSOLEMENU_H
