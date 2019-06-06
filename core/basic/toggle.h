#ifndef TOGGLE_H
#define TOGGLE_H

#include <stddef.h>


namespace core { namespace basic
{
// HEAD

	template<class T>
	class Toggle
	{
	protected:
		bool _setted;
		T _object;

	public:
		Toggle();
		virtual ~Toggle();

		// Zwraca informacje o tym czy obiekt jest ustawiony;
		//
		bool isSetted();

		// Ustawia obiekt.
		//
		virtual bool set(T _object) = 0;

		// Zwraca ustawiony obiekt.
		//
		T get();

		// Resetuje stan.
		//
		bool reset();

		// Resetuje stan wykonujac logike funkcji usuwajacej obiekt znajdujacy sie wewnatrz.
		//
		bool reset(void (*funDelete)(T));
	};

	//
	template<class T>
	class FirstToggle
		: public Toggle<T>
	{
	public:
		~FirstToggle();

		// Ustawia obiekt.
		//
		bool set(T _object);
	};

	template<class T>
	class LastToggle
		: public Toggle<T>
	{
	public:
		~LastToggle();

		// Ustawia obiekt.
		//
		bool set(T _object);

		// Ustawia obiekt usuwajac poprzednia wersje.
		//
		bool set(T _object, void (*funDelete)(T));
	};


// BODY

	template<class T>
	Toggle<T>::Toggle()
	{
		this->_setted = false;
	}

	template<class T>
	Toggle<T>::~Toggle()
	{
		this->reset();
	}

	template<class T>
	bool Toggle<T>::isSetted()
	{
		return this->_setted;
	}

	template<class T>
	T Toggle<T>::get()
	{
		if(this->_setted)
		{
			this->_setted = false;

			return this->_object;
		}
		else
			return (T)NULL;
	}

	template<class T>
	bool Toggle<T>::reset()
	{
		this->_setted = false;

		return true;
	}

	template<class T>
	bool Toggle<T>::reset(void (*funDelete)(T))
	{
		if(this->_setted)
		{
			funDelete(this->_object);
			this->_setted = false;

			return true;
		}

		return false;
	}

	template<class T>
	FirstToggle<T>::~FirstToggle()
	{
		this->Toggle<T>::~Toggle();
	}

	template<class T>
	bool FirstToggle<T>::set(T _object)
	{
		if(this->_setted)
			return false;

		this->_object = _object;
		this->_setted = true;

		return true;
	}

	template<class T>
	LastToggle<T>::~LastToggle()
	{
		this->Toggle<T>::~Toggle();
	}

	template<class T>
	bool LastToggle<T>::set(T _object)
	{
		this->_object = _object;
		this->_setted = true;

		return true;
	}

	template<class T>
	bool LastToggle<T>::set(T _object, void (*funDelete)(T))
	{
		if(this->_setted)
			funDelete(this->_object);

		this->_object = _object;
		this->_setted = true;

		return true;
	}
}}

#endif // TOGGLE_H
