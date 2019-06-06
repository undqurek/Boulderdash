#include "consolemenu.h"

#include "intermediary/thread.h"

#include <stdlib.h>
#include <cstdio>
#include <iostream>

#if SYSTEM == WINDOWS
#   include <conio.h>
#endif // WINDOWS


namespace core { namespace console
{
    using namespace core::basic;
    using namespace core::intermediary;

    void ConsoleMenu::setDefaultColors()
	{
		this->_operations.setBackColor(this->_defaultBackColor);
		this->_operations.setFontColor(this->_defaultFontColor);
	}

	void ConsoleMenu::setSelectedColors()
	{
		this->_operations.setBackColor(this->_selectedBackColor);
		this->_operations.setFontColor(this->_selectedFontColor);
	}

	void ConsoleMenu::showItem(uint16_t x, uint16_t y,
		List<char *>::Iterator &iterator,
		uint16_t number)
	{
		this->setSelectedColors();
		this->_operations.setPosition(x, y);

		const char *text = iterator.__getItem();
		std::cout << " " << number << ". " << text << " ";

		iterator.goNext();
	}

	void ConsoleMenu::showItems(uint16_t x, uint16_t y,
		List<char *>::Iterator &iterator,
		uint16_t startIndex, uint16_t indexLimit)
	{
		this->setDefaultColors();

		for(uint16_t i = startIndex; i < indexLimit; ++i, ++y)
		{
			this->_operations.setPosition(x, y);

			const char *text = iterator.__getItem();
			std::cout << " " << (i + 1) << ". " << text << " ";

			iterator.goNext();
		}
	}

	ConsoleMenu::ConsoleMenu()
    {
		this->_defaultBackColor = ConsoleOperations::BC_Black;
		this->_defaultFontColor = ConsoleOperations::FC_White;
		this->_selectedBackColor = ConsoleOperations::BC_White;
		this->_selectedFontColor = ConsoleOperations::FC_Green;
	}

	void ConsoleMenu::setDefaultBackColor(ConsoleOperations::BackColor color)
	{
		this->_defaultBackColor = color;
	}

	void ConsoleMenu::setDefaultFontColor(ConsoleOperations::FontColor color)
	{
		this->_defaultFontColor = color;
	}

	void ConsoleMenu::setSelectedBackColor(ConsoleOperations::BackColor color)
	{
		this->_selectedBackColor = color;
	}

	void ConsoleMenu::setSelectedFontColor(ConsoleOperations::FontColor color)
	{
		this->_selectedFontColor = color;
	}

	void ConsoleMenu::print(uint16_t x, uint16_t y, List<char *> *list, uint16_t position)
    {
		uint16_t count = list->getSize();

		if(count == 0)
			return;

		List<char *>::Iterator iterator = list->getBegin();

		if(position > 0)
		{
			if(position > count)
				position = count;

			uint16_t index = position - 1;

			if(position > 1)
				this->showItems(x, y, iterator, 0, index);

			this->showItem(x, y + index, iterator, position);
		}

		this->showItems(x, y + position, iterator, position, list->getSize());
    }

	uint16_t ConsoleMenu::run(uint16_t x, uint16_t y, List<char *> *list, uint16_t position)
    {
		uint16_t size = list->getSize();
		this->print(x, y, list, position);

        while(true)
        {
			if(this->_operations.checkKey())
			{
				uint16_t key = this->_operations.getKey();

				if(key >= '1' && key <= '9')
				{
					position = key - '1' + 1;

					if(position > size)
						continue;

					this->print(x, y, list, position);
				}
				else
				{
					switch(key)
					{
					case ConsoleOperations::K_Up:
						if(position > 1)
						{
							--position;
							this->print(x, y, list, position);
						}

						break;

					case ConsoleOperations::K_Down:
						if(position < size)
						{
							++position;
							this->print(x, y, list, position);
						}

						break;

					case ConsoleOperations::K_Enter:
						return position;

					case ConsoleOperations::K_Escape:
						return 0xFFFF;
					}
				}
			}
			else
				Thread<void>::sleepMicroseconds(50);
		}
	}
}}
