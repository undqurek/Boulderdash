#ifndef SAFEPOINTER_H
#define SAFEPOINTER_H

#include "cleaner.h"
#include <stdint.h>


namespace core { namespace basic
{
// HEADER

	template<class TPointer>
	class SafePointer
	{
	private:
		TPointer *_pointer;

		uint32_t *_counter; // ilosc uzyc
		void (*_funDelete)(TPointer *&); // funkcja usuwajaca obiekt

	public:
		SafePointer(TPointer *_pointer, void (*funDelete)(TPointer *&));
		SafePointer(SafePointer &pointer);
		~SafePointer();

		// Zwraca wskaznik do przechowywanego obiektu.
		//
		TPointer *__getPointer();

		// Zwraca ilosc uzyc.
		//
		uint32_t getCounter();
	};

// BODY

	template<class TPointer>
	SafePointer<TPointer>::SafePointer(TPointer *_pointer, void (*funDelete)(TPointer *&))
	{
		this->_pointer = _pointer;

		this->_counter = new uint32_t(1);
		this->_funDelete = funDelete;
	}

	template<class TPointer>
	SafePointer<TPointer>::SafePointer(SafePointer &pointer)
	{
		this->_pointer = pointer._pointer;

		this->_counter = pointer._counter;
		this->_funDelete = pointer._funDelete;

		*this->_counter += 1;
	}

	template<class TPointer>
	SafePointer<TPointer>::~SafePointer()
	{
		if(this->_counter == NULL)
			return;

		if(*this->_counter > 1)
			*this->_counter -= 1;

		else
		{
			Cleaner::deleteObject(this->_counter);
			this->_funDelete(this->_pointer);
		}
	}

	template<class TPointer>
	TPointer *SafePointer<TPointer>::__getPointer()
	{
		return this->_pointer;
	}

	template<class TPointer>
	uint32_t SafePointer<TPointer>::getCounter()
	{
		if(this->_counter == NULL)
			return 0;

		return *this->_counter;
	}
}}

#endif // SAFEPOINTER_H
