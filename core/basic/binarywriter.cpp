#include "binarywriter.h"


// 17:32:55  04.12.2011
namespace core { namespace basic
{
	BinaryWriter::Sector::Sector()
	{
		this->__next = NULL;
	}

	BinaryWriter::Sector::~Sector()
	{
		this->__next = NULL;
	}

	template<typename T>
	void BinaryWriter::write(register T &value)
	{
        register uint8_t size = sizeof(T);

		// sprawdzamy zapisywane dane nie przekrocza dostepnego miejsca
		if(this->_lastSectorOffset + size > _sectorLength)
		{
			// zapisujemy pojedynczo kazdy byte
			for(register uint8_t i = 0; i < size; ++i)
			{
				// sprawdzamy czy istnieje jakies wolne miejsce w ostatnim sektorze
				if(this->_lastSectorOffset < _sectorLength)
				{
                    *(this->__lastSector->data + this->_lastSectorOffset) = *(((uint8_t*)&value) + i); // zapisujemy dane
                    ++this->_lastSectorOffset; // aktualizujemy informacje o ilosci danych zapisanych w sektorze
				}
				else
				{
                    Sector* sector = new Sector(); // tworzymy nowy sektor

                    *(sector->data) = *(((uint8_t*)&value) + i); // zapisujemy dane
                    this->_lastSectorOffset = 1; // ustawiamy informacje o ilosci danych zapisanych w ostatnim sektorze

					// sprawdzamy czy utworzony sektor nie jest pierwszym sektorem
					if(this->_firstSector == NULL)
                        this->_firstSector = sector; // zapisujemy wskaznik do piwerwszego sektora

					// sprawdzamy czy przypisano wskaznik do ostatniego sektora
					if(this->__lastSector == NULL)
                        this->__lastSector = sector; // przypisujemy wskaznik do ostatniego sektora

					else
					{
                        this->__lastSector->__next = sector; // ustawiamy dla poprzedniego sektora wskaznik wskazujacy na nastepny sektor na aktualny sektor
                        this->__lastSector = sector; // ustawiamy wskaznik wskazujacy na ostatni sektor na aktualny sektor
					}

//					// aktualizujemy informacje o ilosci utworzonych sektorow
//					++this->_sectorsCount;
				}
			}
		}
        else // jesli jest na tyle dostepnego miejsca to zapisujemy dane w calosci
		{
            *((T*)(this->__lastSector->data + this->_lastSectorOffset)) = value; // zapisujemy dane
            this->_lastSectorOffset += size; // aktualizujemy informacje o ilosci danych zapisanych w sektorze
		}


        this->_dataLength += size; // aktuazlizujemy informacje o ilosci zapisanych danych
	}

	BinaryWriter::BinaryWriter()
	{
		this->_firstSector = NULL;
		this->__lastSector = NULL;

		this->_lastSectorOffset = _sectorLength;
//		this->_sectorsCount = 0;
		this->_dataLength = 0;
	}

	BinaryWriter::~BinaryWriter()
	{
		this->clear();
	}

	uint32_t BinaryWriter::getSize()
	{
		return this->_dataLength;
	}

	void BinaryWriter::clear()
	{
        // jesli istnieja jakies zapisane dane
		if(this->_dataLength > 0)
		{
            Sector* sector = this->_firstSector;

			// dopuki istnieje jakis sektor
			while(sector != NULL)
			{
                Sector* tmp = sector->__next;
                delete sector;
                sector = tmp;
			}

			// zerujemy wskaniki do sektorow
			this->_firstSector = NULL;
			this->__lastSector = NULL;

			// ustawiamy wartosci domyslne parametrom
			this->_lastSectorOffset = _sectorLength;
//			this->_sectorsCount = 0;
			this->_dataLength = 0;
		}
	}

	void BinaryWriter::write(uint8_t data)
	{
        this->write<uint8_t>(data);
	}

	void BinaryWriter::write(uint16_t data)
	{
		this->write<uint16_t>(data);
	}

	void BinaryWriter::write(uint32_t data)
	{
		this->write<uint32_t>(data);
	}

	void BinaryWriter::write(uint64_t data)
	{
		this->write<uint64_t>(data);
	}

	void BinaryWriter::write(int8_t data)
	{
		this->write<int8_t>(data);
	}

	void BinaryWriter::write(int16_t data)
	{
		this->write<int16_t>(data);
	}

	void BinaryWriter::write(int32_t data)
	{
		this->write<int32_t>(data);
	}

	void BinaryWriter::write(int64_t data)
	{
		this->write<int64_t>(data);
	}

	void BinaryWriter::write(float data)
	{
		this->write<float>(data);
	}

	void BinaryWriter::write(double data)
	{
		this->write<double>(data);
	}

    void BinaryWriter::write(uint8_t *data, uint32_t dataLength) throw (const char *)
	{
		if(data == NULL)
			throw "data is not defined.";

		// kopiujemy dane partiami dopuki sa dostepne
		for(uint32_t copied = 0, left = dataLength; copied < dataLength;)
		{
			// sprawdzamy czy jest dostepne jakies miejsce
			if(this->_lastSectorOffset < _sectorLength)
			{
                uint32_t available = _sectorLength - this->_lastSectorOffset; // obliczamy ilosc dostepnego miejsca w ostatnim sektorze

				// sprawdzamy czy ilosc danych do skopiowania przekracza  dostepne miejsce w ostatnim sektorze
				if(left > available)
				{
                    basic::Memory::copy(data + copied, this->__lastSector->data + this->_lastSectorOffset, available); // kopiujemy dane do sektora

                    copied += available; // aktualizujemy informacje o ilosc skopiowanych danych
                    left -= available; // aktualizujemy informacje o ilosci danych ktore nalezy jeszcze skopiowac
                    this->_lastSectorOffset += available; // akzualizujemy informacje o ilosci zapisanych danych w ostatnim sektorze
				}
				else
				{
                    basic::Memory::copy(data + copied, this->__lastSector->data + this->_lastSectorOffset, left); // kopiujemy dane do sektora

                    copied += left; // aktualizujemy informacje o ilosc skopiowanych danych
                    this->_lastSectorOffset += left; // akzualizujemy informacje o ilosci zapisanych danych w ostatnim sektorze
				}
			}
			else
			{
                Sector* sector = new Sector();

				// sprawdzamy czy ilosc danych do przekopiowania jest wieksza od rozmiaru utworzonego sektora
				if(left > _sectorLength)
				{
                    basic::Memory::copy(data + copied, sector->data, _sectorLength); // kopiujemy dane do sektora

                    copied += _sectorLength; // aktualizujemy informacje o ilosc skopiowanych danych
                    left -= _sectorLength; // aktualizujemy informacje o ilosci danych ktore nalezy jeszcze skopiowac
                    this->_lastSectorOffset = _sectorLength; // zapisujemy wartosc mowiaca o tym ze nie ma juz miejsca w ostatnim sektorze
				}
				else
				{

                    basic::Memory::copy(data + copied, sector->data, left); // kopiujemy dane do sektora

                    copied += left; // aktualizujemy informacje o ilosc skopiowanych danych
                    this->_lastSectorOffset = left; // akzualizujemy informacje o ilosci zapisanych danych w ostatnim sektorze
				}

				// sprawdzamy czy utworzony sektor nie jest pierwszym sektorem
				if(this->_firstSector == NULL)
                    this->_firstSector = sector;

				// sprawdzamy czy przypisano wskaznik do ostatniego sektora
				if(this->__lastSector == NULL)
					this->__lastSector = sector;

				else
				{
                    this->__lastSector->__next = sector; // ustawiamy dla poprzedniego sektora wskaznik wskazujacy na nastepny sektor na aktualny sektor
                    this->__lastSector = sector; // ustawiamy wskaznik wskazujacy na ostatni sektor na aktualny sektor
				}

//				// aktualizujemy informacje o ilosci utworzonych sektorow
//				++this->_sectorsCount;
			}
		}

        this->_dataLength += dataLength; // aktualzujemy informacje o calkowitym rozmiarze zapisanych danych
	}


    uint8_t *BinaryWriter::toArray()
	{
		// sprawdzamy czy zapisano jakies dane
		if(this->_dataLength > 0)
		{
            uint8_t *data = new uint8_t[this->_dataLength];
            this->toArray(data); // zapisujemy dane w tablicy

			return data;
		}

		return NULL;
	}

    uint8_t *BinaryWriter::toArray(uint8_t *&data) throw (const char *)
	{
		if(data == NULL)
			throw "data is not defined.";

        Sector* __sector = this->_firstSector;

		// jesli istnieja jakies sektory
		if(__sector != NULL)
		{
            uint32_t offset = 0; // zmienna pomocnicza przechowujaca ilosc zapisanych danych
            Sector *__nextSector = NULL;

			// dopuki istnieje nastepny sektor
			while((__nextSector = __sector->__next) != NULL)
			{
                basic::Memory::copy(__sector->data, data + offset, _sectorLength);

                __sector = __nextSector; // nastepny sektor staje sie aktualnym sektorem
                offset += _sectorLength; // aktualizujemy ilosc zapisanych danych
			}

            basic::Memory::copy(__sector->data, data + offset, this->_lastSectorOffset); // kopiujemy dane ostatniego sektora
		}

		return data;
	}

    uint8_t *BinaryWriter::pullOutData()
	{
		// sprawdzamy czy zapisano jakies dane
		if(this->_dataLength > 0)
		{
            uint8_t* data = new uint8_t[this->_dataLength];
            this->pullOutData(data); // zapisujemy dane w tablicy

			return data;
		}

		return NULL;
	}

    uint8_t *BinaryWriter::pullOutData(uint8_t *&data) throw (const char *)
	{
		if(data == NULL)
			throw "data is not defined.";

        Sector* sector = this->_firstSector;

		// jesli istnieja jakies sektory
		if(sector != NULL)
		{
            uint32_t offset = 0; // zmienna pomocnicza przechowujaca ilosc zapisanych danych
            Sector* __nextSector = NULL;

			// dopuki istnieje nastepny sektor
			while((__nextSector = sector->__next) != NULL)
			{
                basic::Memory::copy(sector->data, data + offset, _sectorLength);
                delete sector;

                sector = __nextSector; // nastepny sektor staje sie aktualnym sektorem
                offset += _sectorLength; // aktualizujemy ilosc zapisanych danych
			}

            basic::Memory::copy(sector->data, data + offset, this->_lastSectorOffset); // kopiujemy dane ostatniego sektora
			delete sector;

			// zerujemy wskaniki do sektorow
			this->_firstSector = NULL;
			this->__lastSector = NULL;

			// ustawiamy wartosci domyslne parametrom
			this->_lastSectorOffset = _sectorLength;
//			this->_sectorsCount = 0;
			this->_dataLength = 0;
		}

		return data;
	}
}}
