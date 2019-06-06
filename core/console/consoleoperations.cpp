#include "consoleoperations.h"

#if SYSTEM == LINUX
#	include <sys/types.h>
#	include <iostream>
#	include <termios.h>
#	include <cstdio>
#endif

#if SYSTEM == WINDOWS
#	include <iostream>
#	include <conio.h>
#endif


namespace core { namespace console
{
//    bool kbhit2()
//    {
//        struct timeval tv;
//        fd_set read_fd;

//        tv.tv_sec = 0;
//        tv.tv_usec = 0;
//        FD_ZERO(&read_fd);
//        FD_SET(0, &read_fd);

//        if(select(1, &read_fd, NULL, NULL, &tv) == -1)
//        {
//            return false;
//        }

//        if(FD_ISSET(0, &read_fd))
//        {
//            return true;
//        }

//        return false;
//    }

	ConsoleOperations::ConsoleOperations()
    {
#if SYSTEM == WINDOWS
		this->__hOutput = ::GetStdHandle(STD_OUTPUT_HANDLE); // pobieramy wskaznik do istniejacego obiektu

		this->_fontColor = FC_White;
		this->_backColor = BC_Black;
#endif
    }

	ConsoleOperations::~ConsoleOperations()
    {

    }

	bool ConsoleOperations::setPosition(uint16_t x, uint16_t y)
    {
#if SYSTEM == LINUX
		std::cout << "\E[" << y << ";" << x << "H";
#endif

#if SYSTEM == WINDOWS
		::COORD coord = {x, y};
		::SetConsoleCursorPosition(this->__hOutput, coord);
#endif
    }

	void ConsoleOperations::setFontColor(FontColor color)
    {
#if SYSTEM == LINUX
        std::cout << "\E[3" << color << "m";
#endif

#if SYSTEM == WINDOWS
		this->_fontColor = color;
		::SetConsoleTextAttribute(this->__hOutput, this->_fontColor | this->_backColor);
#endif
    }

	void ConsoleOperations::setBackColor(BackColor color)
    {
#if SYSTEM == LINUX
        std::cout << "\E[4" << color << "m";
#endif

#if SYSTEM == WINDOWS
		this->_backColor = color;
		::SetConsoleTextAttribute(this->__hOutput, this->_fontColor | this->_backColor);
#endif
	}

	bool ConsoleOperations::checkKey()
	{
#if SYSTEM == WINDOWS
		return (::kbhit() > 0);
#endif
	}

	ConsoleOperations::Key ConsoleOperations::getKey()
	{
#if SYSTEM == WINDOWS
		uint16_t key = (uint16_t)::getch();

		if(key == 0xE0)
			key |= (uint16_t)::getch() << 8;

		return (Key)key;
#endif
	}

	bool ConsoleOperations::getCString(char *buffer, uint16_t length)
	{
		uint16_t limit = length - 1;
		uint16_t index = 0;

		while(true)
		{
			if(this->checkKey())
			{
				char key = this->getKey();

				switch(key)
				{
					case 8: // BACKSPACE
						if(index > 0)
						{
							buffer[index] = 0;
							std::cout << "\b \b";

							index -= 1;
						}

						break;

					default:
						if(index < limit && key > 31 && key < 127) // wypisywane sa tylko wybrane znaki ASCII
						{
							buffer[index] = key;
							std::cout << key;

							index += 1;
						}

						break;

				case 13: // ENTER
					buffer[index] = '\0';
					return true;

				case 27: // ESCAPE
					return false;

				}
			}
		}

	}

	void ConsoleOperations::pause()
    {
#if SYSTEM == LINUX
        std::cout << "read -p “$*”";
#endif
    }

	void ConsoleOperations::clearScreen()
    {
#if SYSTEM == LINUX
        std::cout << "\E[2J";
#endif
    }

	void ConsoleOperations::clearScreen(uint16_t x, uint16_t y, uint16_t width, uint16_t heigth, char value)
    {
		for(uint16_t i = 0; i < heigth; i++)
        {
			this->setPosition(x, y + i);

			for(uint16_t j = 0; j < width; j++)
				std::cout << value;
		}
	}

//	void ConsoleOperations::resetColors()
//	{
//#if SYSTEM == LINUX
//		std::cout << "\E[0m";
//#endif

//#if SYSTEM == WINDOWS
//		this->_fontColor = FC_White;
//		this->_backColor = BC_Black;

//		::SetConsoleTextAttribute(this->_hOutput, this->_fontColor | this->_backColor);
//#endif
//	}

//    char& Operations::getChar()
//    {
//        // przechowuje ustawienia
//        struct termios term;

//        // pobieramy ustawienia
//        tcgetattr(STDIN_FILENO, &term);

//        // konfigurujemy nowe parametry - wylaczamy wypisywanie znakow w konsoli
//        term.c_lflag &= ~(ICANON | ECHO);

//        // ustawiamy nowe parametry
//        tcsetattr(STDIN_FILENO, TCSANOW, &term);

//        // odczytujemy wartosc wcisnietego klawisza
//        char ch = ::getchar();

//        // konfigurujemy domyslne dane
//        term.c_lflag &= (ICANON | ECHO);

//        // przywracamy domyslne dane
//        tcsetattr(STDIN_FILENO, TCSANOW, &term);

//        return ch;
//    }
}}
