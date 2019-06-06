#ifndef CHECKINGRUN_H
#define CHECKINGRUN_H

#include "console/consolemenu.h"


namespace core { namespace unittests { namespace console_consolemenu
{
	class CheckingRun
	{
	private:
		//static logging::ConsolePrinter _printer;

	public:
		static void assert()
		{
			//_printer.open();

			basic::List<const char*> list;

			list.pushBack("PALY GAME");
			list.pushBack("MAP EDITOR");
			list.pushBack("EXIT");

			core::console::ConsoleMenu menu;

			menu.setDefaultFontColor(core::console::ConsoleOperations::FC_Yellow);
			menu.setDefaultBackColor(core::console::ConsoleOperations::BC_Blue);

			menu.run(0, 0, &list, 1);

			//_printer.close();
		}
	};

	//logging::ConsolePrinter CheckingRun::_printer = logging::ConsolePrinter();
}}}

#endif // CHECKINGRUN_H
