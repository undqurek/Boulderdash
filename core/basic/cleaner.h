#ifndef CLEANER_H
#define CLEANER_H

#include "global.h"

#include <stddef.h>
#include <stdint.h>
#include <vector>


namespace core { namespace basic
{
	// Usuwa obiekty
	//
    class CORE_DECLARATION Cleaner
	{
	public:
		template<class T> inline static void deleteArray(T *&array)
		{
			if(array != NULL)
			{
				delete [] array;
				array = NULL;
			}
		}

		template<class T> inline static void deleteObject(T *&object)
		{
			if(object != NULL)
			{
				delete object;
				object = NULL;
			}
		}

		template<class T> inline static void deleteArray2D(T **&array, uint32_t arrayLength)
		{
			if(array != NULL)
			{
				for(uint32_t i = 0; i < arrayLength; ++i)
				{
					delete [] array[i];
				}

				delete [] array;
				array = NULL;
			}
		}

		template<typename T> inline static void deleteArrayWithObjects(T **&array, uint32_t arrayLength)
		{
			if(array != NULL)
			{
				for(uint32_t i = 0; i < arrayLength; ++i)
				{
					delete array[i];
				}

				delete [] array;
				array = NULL;
			}
		}

		template<typename T> inline static void clearVector(std::vector<T*> vec)
		{
//			for(std::vector<T*>::iterator i = vec.begin(); i != vec.end(); ++i)
//			{
//				delete (T*)*i;
//			}
		}

		template<typename T> inline static void deleteVector(std::vector<T*>* vector)
		{
			if(vector != NULL)
			{

//				for(std::vector<T*>::iterator i = vector.begin(); i != vector.end(); ++i)
//				{
//					delete (T*)*i;
//				}

//				delete vector;
//				vector = NULL;
			}
		}
	};
}}

#endif // CLEANER_H
