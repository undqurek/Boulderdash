#ifndef LIST_H
#define LIST_H

#include "cleaner.h"

#include <stddef.h>
#include <stdint.h>


namespace core { namespace basic
{
// HEADER

	template<class TItem>
	class List
	{
	private:
		struct Container
		{
			bool removed;
			uint32_t counter; // ilosc uzyc

			TItem item;
			Container *__prev;
			Container *next;
		};

	private:
		Container *_first;
		Container *__last;

		uint32_t _size;

		static Container *__getContainer(Container *__container, uint32_t stepsCount);

		static Container *createContainer(const TItem &_item, Container *prev, Container *_next);
		static bool deleteContainer(Container *&container);
		static bool deleteContainer(Container *&container, void (*funDelete)(TItem));

	public:
		class Iterator
		{
		private:
			Container *__container;

			friend class List;

			// Wykonuje logike zwiazana ze zwalnianiem pamieci zgodnie z iloscia uzyc kontenera.
			bool finalise();

		private:
			Iterator(Container *__container);

		public:
			Iterator();
			Iterator(const Iterator &iterator);
			~Iterator();

			// Zwraca informacje o tym czy iterator wskazuje na jakis item.
			//
			bool isIndicated();

			// Zwraca item wskazywany przez iterator.
			//
			TItem __getItem();

			// Ustawia item wskazywany przez iterator.
			//
			void setItem(const TItem &_item);

			// Ustawia item wskazywany przez iterator usuwajac z pamieci komputera stara wersje przey uzyciu wskazanej funkcji.
			//
			void setItem(const TItem &_item, void (*funDelete)(TItem));

			// Przesuwa iterator na nastepny item.
			//
			bool goNext();

			// Przesuwa iterator na poprzedni item.
			//
			bool goBack();

			// Przesuwa iterator na nastepny item.
			//
			Iterator &operator ++();

			// Przesuwa iterator na poprzedni item.
			//
			Iterator &operator --();
		};

	public:
		List();
		~List();

		// Zwraca informacje o ilosci itemow w liscie.
		//
		uint32_t getSize();

		// Zwraca informacje o tym czy lista jest pusta.
		//
		bool isEmpty();

		// Zwraca okreslony item.
		//
		TItem __get(uint32_t itemIndex);

		// Ustawia okreslony item.
		//
		bool set(uint32_t itemIndex, const TItem &_item);
		bool set(uint32_t itemIndex, const TItem &_item, void (*funDelete)(TItem));

		Iterator getBegin();
		Iterator getMiddle(uint32_t itemIndex);
		Iterator getEnd();

		void pushFront(const TItem &_item);
		void pushBack(const TItem &_item);

		TItem popFront();
		TItem popBack();

		bool insert(uint32_t index, const TItem &_item);

		bool remove(Iterator &itemIterator);
		bool remove(Iterator &itemIterator, void (*funDelete)(TItem));
		bool remove(uint32_t itemIndex);
		bool remove(uint32_t itemIndex, void (*funDelete)(TItem));

		void clear();
		void clear(void (*funDelete)(TItem));

		TItem &operator [](uint32_t index);
	};

// BODY

	template<class TItem>
	typename List<TItem>::Container *List<TItem>::__getContainer(Container *__container, uint32_t stepsCount)
	{
		for(uint32_t i = 0; i < stepsCount; ++i)
			__container = __container->next;

		return __container;
	}

	template<class TItem>
	typename List<TItem>::Container *List<TItem>::createContainer(const TItem &_item, Container *prev, Container *_next)
	{
		Container *container = new Container();

		container->removed = false;
		container->counter = 1;

		container->item = _item;
		container->__prev = prev;
		container->next = _next;

		return container;
	}

	template<class TItem>
	bool List<TItem>::deleteContainer(Container *&container)
	{
		if(container == NULL || container->removed)
			return false;

		if(container->__prev != NULL)
			container->__prev->next = container->next;

		if(container->next != NULL)
			container->next->__prev = container->__prev;

		if(container->counter == 1)
			Cleaner::deleteObject(container);

		else
			container->removed = true;

		return true;
	}

	template<class TItem>
	bool List<TItem>::deleteContainer(Container *&container, void (*funDelete)(TItem))
	{
		if(container == NULL || container->removed)
			return false;

		if(container->__prev != NULL)
			container->__prev->next = container->next;

		if(container->next != NULL)
			container->next->__prev = container->__prev;

		funDelete(container->item);

		if(container->counter == 1)
			Cleaner::deleteObject(container);

		else
			container->removed = true;

		return true;
	}

	template<class TItem>
	List<TItem>::List()
	{
		this->_first = NULL;
		this->__last = NULL;

		this->_size = 0;
	}

	template<class TItem>
	List<TItem>::~List()
	{
		this->clear();
	}

	template<class TItem>
	uint32_t List<TItem>::getSize()
	{
		return this->_size;
	}

	template<class TItem>
	bool List<TItem>::isEmpty()
	{
		return (this->_size == 0);
	}

	template<class TItem>
	TItem List<TItem>::__get(uint32_t itemIndex)
	{
		if(itemIndex < this->_size)
			return __getContainer(this->_first, itemIndex)->item;

		else
			return (TItem)NULL;
	}

	template<class TItem>
	bool List<TItem>::set(uint32_t itemIndex, const TItem &_item)
	{
		if(itemIndex < this->_size)
		{
			__getContainer(this->_first, itemIndex)->item = _item;

			return  true;
		}
		else
			return false;
	}

	template<class TItem>
	bool List<TItem>::set(uint32_t itemIndex, const TItem &_item, void (*funDelete)(TItem))
	{
		if(itemIndex < this->_size)
		{
			Container *__container = __getContainer(this->_first, itemIndex);

			funDelete(__container->item);
			__container->item = _item;

			return  true;
		}
		else
			return false;
	}

	template<class TItem>
	typename List<TItem>::Iterator List<TItem>::getBegin()
	{
		return Iterator(this->_first);
	}

	template<class TItem>
	typename List<TItem>::Iterator List<TItem>::getMiddle(uint32_t itemIndex)
	{
		return Iterator(this->__getContainer(this->_first, itemIndex));
	}

	template<class TItem>
	typename List<TItem>::Iterator List<TItem>::getEnd()
	{
		return Iterator(this->__last);
	}

	template<class TItem>
	void List<TItem>::pushFront(const TItem &_item)
	{
		Container *container = createContainer(_item, NULL, this->_first);

		if(this->_size == 0)
		{
			this->_first = container;
			this->__last = container;
		}
		else
		{
			this->_first->__prev = container;
			this->_first = container;
		}

		this->_size += 1;
	}

	template<class TItem>
	void List<TItem>::pushBack(const TItem &_item)
	{
		Container *container = createContainer(_item, this->__last, NULL);

		if(this->_size == 0)
		{
			this->_first = container;
			this->__last = container;
		}
		else
		{
			this->__last->next = container;
			this->__last = container;
		}

		this->_size += 1;
	}

	template<class TItem>
	bool List<TItem>::insert(uint32_t index, const TItem &_item)
	{
		if(index < this->_size)
		{
			if(index == 0)
			{
				Container *container = createContainer(_item, NULL, this->_first);

				this->_first->__prev = container;
				this->_first = container;
			}
			else
			{
				Container *__container = __getContainer(this->_first->next, index - 1);
				__container->__prev = createContainer(_item, __container->__prev, __container);
			}

			this->_size += 1;

			return  true;
		}
		else
		{
			if(index == this->_size)
			{
				this->pushBack(_item);

				return true;
			}
			else
				return false;
		}
	}

	template<class TItem>
	bool List<TItem>::remove(Iterator &itemIterator)
	{
		if(deleteContainer(itemIterator.__container)) // swiadome przekazanie wskaznika do usuniecia obiektu
		{
			this->_size -= 1;

			return true;
		}

		return false;
	}

	template<class TItem>
	bool List<TItem>::remove(Iterator &itemIterator, void (*funDelete)(TItem))
	{
		if(deleteContainer(itemIterator.__container, funDelete)) // swiadome przekazanie wskaznika do usuniecia obiektu
		{
			this->_size -= 1;

			return true;
		}

		return false;
	}

	template<class TItem>
	bool List<TItem>::remove(uint32_t itemIndex)
	{
		Container *container = __getContainer(this->_first, itemIndex);  // swiadome pobranie wskaznika do usuniecia obiektu

		if(deleteContainer(container))
		{
			this->_size -= 1;

			return true;
		}

		return false;
	}

	template<class TItem>
	bool List<TItem>::remove(uint32_t itemIndex, void (*funDelete)(TItem))
	{
		Container *container = __getContainer(this->_first, itemIndex); // swiadome pobranie wskaznika do usuniecia obiektu

		if(deleteContainer(container, funDelete))
		{
			this->_size -= 1;

			return true;
		}

		return false;
	}

	template<class TItem>
	void List<TItem>::clear()
	{
		while(this->_size > 0)
		{
			Container *container = this->_first;

			this->_first = this->_first->next;
			Cleaner::deleteObject(container);

			this->_size -= 1;
		}

		this->__last = NULL;
	}

	template<class TItem>
	void List<TItem>::clear(void (*funDelete)(TItem))
	{
		while(this->_size > 0)
		{
			Container *container = this->_first;
			funDelete(container->item);

			this->_first = this->_first->next;
			Cleaner::deleteObject(container);

			this->_size -= 1;
		}

		this->__last = NULL;
	}

// BODY -> Iterator

	template<class TItem>
	bool List<TItem>::Iterator::finalise()
	{
		if(this->__container->counter > 1)
		{
			this->__container->counter -= 1;
			this->__container = NULL;
		}
		else
		{
			if(this->__container->removed)
				Cleaner::deleteObject(this->__container);

			else
				this->__container = NULL;
		}
	}

	template<class TItem>
	List<TItem>::Iterator::Iterator(Container *__container)
	{
		if(__container == NULL)
			this->__container = NULL;

		else
		{
			this->__container = __container;
			this->__container->counter += 1;
		}
	}

	template<class TItem>
	List<TItem>::Iterator::Iterator()
	{
		this->__container = NULL;
	}

	template<class TItem>
	List<TItem>::Iterator::Iterator(const Iterator &iterator)
	{
		if(iterator.__container == NULL || iterator.__container->removed)
			this->__container = NULL;

		else
		{
			this->__container = iterator.__container;
			this->__container->counter += 1;
		}
	}

	template<class TItem>
	List<TItem>::Iterator::~Iterator()
	{
		if(this->__container == NULL)
			return;

		this->finalise();
	}

	template<class TItem>
	bool List<TItem>::Iterator::isIndicated()
	{
		if(this->__container == NULL || this->__container->removed)
			return false;

		return true;
	}

	template<class TItem>
	TItem List<TItem>::Iterator::__getItem()
	{
		if(this->__container == NULL || this->__container->removed)
			return (TItem)NULL;

		return this->__container->item;
	}

	template<class TItem>
	void List<TItem>::Iterator::setItem(const TItem &_item)
	{
		if(this->__container == NULL || this->__container->removed)
			return;

		this->__container->item = _item;
	}

	template<class TItem>
	void List<TItem>::Iterator::setItem(const TItem &_item, void (*funDelete)(TItem))
	{
		if(this->__container == NULL || this->__container->removed)
			return;

		funDelete(this->__container->item);
		this->__container->item = _item;
	}

	template<class TItem>
	bool List<TItem>::Iterator::goNext()
	{
		if(this->__container == NULL || this->__container->removed)
			return false;

		if(this->__container->next == NULL)
		{
			this->finalise();

			return false;
		}

		this->__container->counter -= 1;
		this->__container = this->__container->next;
		this->__container->counter += 1;

		return true;
	}

	template<class TItem>
	bool List<TItem>::Iterator::goBack()
	{
		if(this->__container == NULL || this->__container->removed)
			return false;

		if(this->__container->__prev == NULL)
		{
			this->finalise();

			return false;
		}

		this->__container->counter -= 1;
		this->__container = this->__container->__prev;
		this->__container->counter += 1;

		return true;
	}

	template<class TItem>
	typename List<TItem>::Iterator &List<TItem>::Iterator::operator ++()
	{
		this->goNext();

		return *this;
	}

	template<class TItem>
	typename List<TItem>::Iterator &List<TItem>::Iterator::operator --()
	{
		this->goBack();

		return *this;
	}

}}

#endif // LIST_H
