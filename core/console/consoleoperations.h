#ifndef CONSOLEOPERATIONS_H
#define CONSOLEOPERATIONS_H

#include "basic/preprocesor.h"
#include <stdint.h>

#if SYSTEM == WINDOWS
#	include <windows.h>
#endif


namespace core { namespace console
{
	//bool kbhit2();

	class ConsoleOperations
    {
    private:

#if SYSTEM == WINDOWS
		::HANDLE __hOutput; // obiektu tego nie nalezy zwalniac

		::WORD _fontColor;
		::WORD _backColor;
#endif

	public:

		enum FontColor
		{
#if SYSTEM == LINUX
			FC_Black = 0,
			FC_Red = 1,
			FC_Green = 2,
			FC_Yellow = 3,
			FC_Blue = 4,
			FC_Magenta = 5,
			FC_Cyan = 6,
			FC_White = 7
#endif

#if SYSTEM == WINDOWS
//			FC_Red = FOREGROUND_RED,
//			FC_Green = FOREGROUND_GREEN,
//			FC_Blue = FOREGROUND_BLUE,
//			FC_Intensity = FOREGROUND_INTENSITY

			FC_Black = 0,
			FC_Red = FOREGROUND_RED,
			FC_Green = FOREGROUND_GREEN,
			FC_Yellow = FOREGROUND_RED | FOREGROUND_GREEN,
			FC_Blue = FOREGROUND_BLUE,
			FC_Magenta = FOREGROUND_RED | FOREGROUND_BLUE,
			FC_Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
			FC_White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#endif
		};

		enum BackColor
		{
#if SYSTEM == LINUX
			BC_Black = 0,
			BC_Red = 1,
			BC_Green = 2,
			BC_Yellow = 3,
			BC_Blue = 4,
			BC_Magenta = 5,
			BC_Cyan = 6,
			BC_White = 7
#endif

#if SYSTEM == WINDOWS
//			BC_Red = BACKGROUND_RED,
//			BC_Blue = BACKGROUND_BLUE,
//			BC_Green = BACKGROUND_GREEN,
//			BC_Intensity = BACKGROUND_INTENSITY

			BC_Black = 0,
			BC_Red = BACKGROUND_RED,
			BC_Green = BACKGROUND_GREEN,
			BC_Yellow = BACKGROUND_RED | BACKGROUND_GREEN,
			BC_Blue = BACKGROUND_BLUE,
			BC_Magenta = BACKGROUND_RED | BACKGROUND_BLUE,
			BC_Cyan = BACKGROUND_GREEN | BACKGROUND_BLUE,
			BC_White = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
#endif
		};

		enum Key
		{
#if SYSTEM == LINUX
            //TODO: zweryfikowac kody
            K_Enter = 0x0D, //10,
            K_Escape = 0x1B,

            K_Up = 0x48E0,
            K_Down = 0x50E0,
            K_Left = 0x4BE0,
            K_Right = 0x4DE0
#endif

#if SYSTEM == WINDOWS
			K_Enter = 0x0D, //10,
			K_Escape = 0x1B,

			K_Up = 0x48E0,
			K_Down = 0x50E0,
			K_Left = 0x4BE0,
			K_Right = 0x4DE0
#endif
		};

    public:
		ConsoleOperations();
		~ConsoleOperations();

		bool setPosition(uint16_t x, uint16_t y);
		void setFontColor(FontColor color);
		void setBackColor(BackColor color);

		// Sprawdza czy wcisnieto jakis klawisz.
		//
		bool checkKey();

		// Pobiera z bufora kod wcisnietego klawisza.
		//
		Key getKey();

		// Pobiera ciag znakow i zapisuje go do buffer'a.
		//
		// return	: zwraca false jesl operacja sie nie powiedzie lub nacisniety zostanie klawisz ESCAPE
		bool getCString(char *buffer, uint16_t length);

        void pause();
        void clearScreen();
		void clearScreen(uint16_t x, uint16_t y, uint16_t width, uint16_t heigth, char value = ' ');
    };
}}

#endif // CONSOLEOPERATIONS_H
