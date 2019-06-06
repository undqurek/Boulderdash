#include "binaryreader.h"


namespace core { namespace basic
{
    template<typename T> inline bool BinaryReader::read(T &outValue)
	{
        uint8_t size = sizeof(T);

		// sprawdzamy czy nie zostal przekroczony zakres
		if(this->_offset + size > this->_dataLength)
		{
			// w przypadku przekroczenia zakresu danych zwracamy 0
			outValue = 0;

			return false;
		}

		// zwracamy odczytana wartosc
		outValue = *((T*)(this->__data + this->_offset));

		// aktualizujemy pozyjce odczytywanych danych
		this->_offset += size;

		return true;
	}

	BinaryReader::BinaryReader(uint8_t* __data, uint32_t dataLength) throw (const char*)
	{
		// sprawdzamy czy zdefiniowano parametr __data
		if(__data == NULL)
            throw "<__data> is not defined.";

		this->_offset = 0;

		this->__data = __data;
		this->_dataLength = dataLength;
	}

	uint32_t BinaryReader::getOffset()
	{
		return this->_offset;
	}

	bool BinaryReader::jump(uint32_t count)
	{
		// sprawdzamy czy operacja jest mozliwa - nie dojdzie do przekroczenia obszaru danych
		if(this->_offset + count < this->_dataLength)
		{
			// aktualizujemy pozycje odczytywanych danych
			this->_offset += count;

			return true;
		}

		return false;
	}

    uint8_t *BinaryReader::__getPointer()
	{
		// sprawdzamy czy zakres odczytywanych danych nie zostal przekroczony
		if(this->_offset < this->_dataLength)
			return this->__data + this->_offset;

		return NULL;
	}

    bool BinaryReader::read(uint8_t &outValue)
	{
		return this->read<uint8_t>(outValue);
	}

    bool BinaryReader::read(uint16_t &outValue)
	{
		return this->read<uint16_t>(outValue);
	}

    bool BinaryReader::read(uint32_t &outValue)
	{
		return this->read<uint32_t>(outValue);
	}

    bool BinaryReader::read(uint64_t &outValue)
	{
		return this->read<uint64_t>(outValue);
	}

    bool BinaryReader::read(int8_t &outValue)
	{
		return this->read<int8_t>(outValue);
	}

    bool BinaryReader::read(int16_t &outValue)
	{
		return this->read<int16_t>(outValue);
	}

    bool BinaryReader::read(int32_t &outValue)
	{
		return this->read<int32_t>(outValue);
	}

    bool BinaryReader::read(int64_t &outValue)
	{
		return this->read<int64_t>(outValue);
	}

    bool BinaryReader::read(float &outValue)
	{
		return this->read<float>(outValue);
	}

    bool BinaryReader::read(double &outValue)
	{
		return this->read<double>(outValue);
	}

    uint32_t BinaryReader::read(uint8_t *data, uint32_t dataLength)
	{
		// sprawdzamy czy operacja jest mozliwa - nie dojdzie do przekroczenia obszaru danych
		if(this->_offset < this->_dataLength)
		{
			// oblczamy dostepa ilosc danych
			uint32_t available = this->_dataLength - this->_offset;

			// jesli dostepnych danych jest wiecej od danych do odczytania
			if(available > dataLength)
			{
				// kopiujemy dostepny obszar danych
				basic::Memory::copy(this->__data + this->_offset, data, dataLength);

				// aktualizujemy pozycje odczytywanych danych
				this->_offset += dataLength;

				return dataLength;
			}
			else
			{
				// kopiujemy dostepny obszar danych
				basic::Memory::copy(this->__data + this->_offset, data, available);

				// aktualizujemy pozycje odczytywanych danych
				this->_offset += available;

				return available;
			}
		}

		return 0;
	}
}}
