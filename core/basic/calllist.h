#ifndef CALLLIST_H
#define CALLLIST_H

#include "cleaner.h"

#include <stddef.h>
#include <stdint.h>


namespace core { namespace basic
{
// HEADER

	template<class TCallArg, class TFunArg>
	class CallList
	{
	public:
		struct Item
		{
			void (*fun)(TCallArg *, TFunArg *);
			TFunArg *__funArg;
		};

		struct Container
		{
			Item item;
			Container *__prev;
			Container *next;
		};

		struct Intermediary
		{
			Container *__container;
			uint32_t counter;
		};

	private:
		Container *_first;
		Container *__last;

	public:
		class Indicator
		{
		private:
			Intermediary *_intermediary;

			friend class CallList;

		private:
			Indicator(Container *__container);

		public:
			Indicator();
			Indicator(const Indicator &indicator);
			~Indicator();
		};

	public:
		CallList();
		~CallList();

		// Dodaje funkcje do listy.
		//
		Indicator add(void (*fun)(TCallArg *, TFunArg *), TFunArg *__funArg = NULL);

		// Usuwa wskazana funkcje.
		//
		bool remove(const Indicator &indicator);

		// Usuwa wszystkie funkcje.
		//
		void clear();

		// Wykonuje funkcje znajdujace sie na liscie.
		//
		void call(TCallArg *__callArg = NULL);
	};

// BODY

	template<class TCallArg, class TFunArg>
	CallList<TCallArg, TFunArg>::Indicator::Indicator(Container *__container)
	{
		this->_intermediary = new Intermediary();

		this->_intermediary->__container = __container;
		this->_intermediary->counter = 1;
	}

	template<class TCallArg, class TFunArg>
	CallList<TCallArg, TFunArg>::Indicator::Indicator()
	{
		this->_intermediary = NULL;
	}

	template<class TCallArg, class TFunArg>
	CallList<TCallArg, TFunArg>::Indicator::Indicator(const Indicator &indicator)
	{
		this->_intermediary = indicator._intermediary;
		this->_intermediary->counter += 1;
	}

	template<class TCallArg, class TFunArg>
	CallList<TCallArg, TFunArg>::Indicator::~Indicator()
	{
		if(this->_intermediary->counter > 1)
			this->_intermediary->counter -= 1;

		else
			Cleaner::deleteObject(this->_intermediary);
	}

	template<class TCallArg, class TFunArg>
	CallList<TCallArg, TFunArg>::CallList()
	{
		this->_first = NULL;
		this->__last = NULL;
	}

	template<class TCallArg, class TFunArg>
	CallList<TCallArg, TFunArg>::~CallList()
	{
		this->clear();
	}

	template<class TCallArg, class TFunArg>
	typename CallList<TCallArg, TFunArg>::Indicator CallList<TCallArg, TFunArg>::add(void (*fun)(TCallArg *, TFunArg *), TFunArg *__funArg)
	{
		Container *container = new Container();

		container->item.fun = fun;
		container->item.__funArg = __funArg;

		container->__prev = this->__last;
		container->next = NULL;

		if(this->_first == NULL)
			this->_first = container;

		else
			this->__last->next = container;

		this->__last = container;

		return Indicator(container);
	}

	template<class TCallArg, class TFunArg>
	bool CallList<TCallArg, TFunArg>::remove(const Indicator &indicator)
	{
		Intermediary *__intermediary = indicator._intermediary;

		if(__intermediary == NULL)
			return false;

		Container *&container = __intermediary->__container; // celowe pobranie wskaznika do usuniecia obiektu

		if(container == NULL)
			return false;

		if(container->__prev != NULL)
			container->__prev->next = container->next;

		if(container->next != NULL)
			container->next->__prev = container->__prev;

		Cleaner::deleteObject(container);

		return true;
	}

	template<class TCallArg, class TFunArg>
	void CallList<TCallArg, TFunArg>::clear()
	{
		while(true)
		{
			Container *container = this->_first;

			if(container == NULL)
				break;

			this->_first = this->_first->next;
			Cleaner::deleteObject(container);
		}

		this->__last = NULL;
	}

	template<class TCallArg, class TFunArg>
	void CallList<TCallArg, TFunArg>::call(TCallArg *__callArg)
	{
		Container *__container = this->_first;

		while(__container != NULL)
		{
			Item &item = __container->item;
			item.fun(__callArg, item.__funArg);

			__container = __container->next;
		}
	}
}}

#endif // CALLLIST_H
