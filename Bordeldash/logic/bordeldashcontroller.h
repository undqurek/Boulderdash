#ifndef BordeldashCONTROLLER_H
#define BordeldashCONTROLLER_H

#include "mvc/gamecontroller.h"


namespace logic
{
	class BordeldashController
	{
	private:
		bool _started;
		mvc::GameController *_controller;

	public:
		BordeldashController();
		~BordeldashController();

		// Zwraca informacje o tym czy gra jest uruchomiona.
		//
		bool isStarted();

		// uruchamia logike.
		//
		bool run();
	};
}

#endif // BordeldashCONTROLLER_H
