#include "string.h"

#include "memory.h"
#include <stddef.h>

#include "cleaner.h"


namespace core { namespace basic
{
	String::String()
	{
		this->_length = 0;
		this->_cString = NULL;
	}

    String::String(const char *cString)
	{
		this->_length = checkLength(cString);
		this->_cString = copyCString(cString, this->_length);
	}

	String::String(const char *_cString, uint32_t cStringLength)
	{
		this->_cString = _cString;
		this->_length = cStringLength;
	}

	uint32_t String::getLength()
	{
		return this->_length;
	}

	const char *String::__getCString()
	{
		return this->_cString;
	}

	void String::empty()
	{
		this->_length = 0;
		Cleaner::deleteArray(this->_cString);
	}

    uint32_t String::checkLength(const char *cString, uint32_t maxLength)
	{
        if(cString == NULL || maxLength == 0 ||  *cString == '\0')
            return 0;

		uint32_t length = 0;

		while(true)
		{
            if(++length == maxLength || cString[length] == '\0') return length;
            if(++length == maxLength || cString[length] == '\0') return length;
            if(++length == maxLength || cString[length] == '\0') return length;
            if(++length == maxLength || cString[length] == '\0') return length;
            if(++length == maxLength || cString[length] == '\0') return length;
            if(++length == maxLength || cString[length] == '\0') return length;
            if(++length == maxLength || cString[length] == '\0') return length;
            if(++length == maxLength || cString[length] == '\0') return length;
		}

        return length;
    }

    char *String::copyCString(const char *cString, uint32_t length)
    {
        if(cString == NULL)
            return NULL;

        char *result = new char[length + 1];
        Memory::copy((const uint8_t *)cString, (uint8_t *)result, length);
        result[length] = '\0';

		return result;
	}

	char *String::concatenate(const char *firstCString, const char *secondCString)
	{
		uint32_t firstLength = checkLength(firstCString);
		uint32_t secondSecond = checkLength(secondCString);

		uint32_t resultLength = firstLength + secondSecond;
		char *result = new char[resultLength + 1];

		Memory::copy((uint8_t *)firstCString, (uint8_t *)result, firstLength);
		Memory::copy((uint8_t *)secondCString,(uint8_t *)(result + firstLength), secondSecond);

		result[resultLength] = '\0';

		return result;
	}
}}
