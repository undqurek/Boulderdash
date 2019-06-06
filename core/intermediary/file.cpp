#include "file.h"


// 14:29:10  08.07.2012
namespace core { namespace intermediary
{
	File::File()
	{
		this->_file = NULL;
	}

	File::~File()
	{
		this->close();
	}

	bool File::open(const char* path, FileMode mode)
	{
        if(path == NULL)
            return false;

		if(this->_file == NULL) // sprawdzamy czy jakis plik nie jest obecnie otwarty
		{
			this->_file = ::fopen(path, (const char*)&mode);

			if(this->_file == NULL)
				return false;

			return true;
		}

		return false;
	}

	bool File::close()
	{
        if(this->_file == NULL)
            return false;

        if(::fclose(this->_file) == 0)
        {
			this->_file = NULL;
            return true;
        }

        return false;
	}

	bool File::isOpened()
	{
		return (this->_file != NULL);
	}

	bool File::seek(uint32_t offset, FileSeek origin)
	{
        if(this->_file == NULL)
            return false;

		return ::fseek(this->_file, offset, origin) == 0; // ustawienie polozenia wskaznika odczytu/zapisu
	}

	uint32_t File::tell()
	{
		if(this->_file == NULL)
			return 0;

		return ::ftell(this->_file); // pobranie wskaznika odczytu/zapisu
	}

	uint32_t File::getSize()
	{
        if(this->_file == NULL)
            return 0;

		uint32_t current = ::ftell(this->_file); // aktualne polozenie wskaznika odczytu/zapisu
		::fseek(this->_file, 0, SEEK_END); // przesuniecie wskaznik na koniec

		uint32_t size = ::ftell(this->_file); // odczytanie polozenia wskaznika - rowne jest ono rozmiarowi pliku
		::fseek(this->_file, current, SEEK_SET); // ustawiaenie poczatkowego polozenia wskaznika

		return size;
	}

	uint32_t File::read(uint8_t* buffer, uint32_t length)
	{
        if(buffer == NULL || this->_file == NULL)
            return 0;

		if(length > _readStep) // jesli blok danych jest wiekszy od rozmairu dla pojedynczego kroku
		{
			uint32_t read = 0; // ilosc odczytanych byte'ow
			uint32_t total = _readStep * (length / _readStep); // czesc calkowita danych do odczytania

			while(read < total) // odczytujemy dane nalezace do czesci calkowitej
			{
				uint32_t tmp = ::fread(buffer + read, 1, _readStep, this->_file); // odczytujemy porcje danych
                read += tmp; // aktualziualizujemy ilosc odczytanych byte'ow

				if(tmp != _readStep) // sprawdzamy czy powiodla sie operacja odczytywania
					return read;
			}

			if(read < length) // odczytujemy pozostale dane
			{
				uint32_t tmp = ::fread(buffer + read, 1, length - total, this->_file); // odczytujemy pozostale dane
                read += tmp; // aktualziualizujemy ilosc odczytanych byte'ow
			}

			return read;
		}
		else
            return ::fread(buffer, 1, length, this->_file); // odczytujemy zadany blok danych
	}

	uint32_t File::write(uint8_t *buffer, uint32_t length)
	{
        if(buffer == NULL || this->_file == NULL)
            return 0;

		//TODO: dorobic zapisywanie porcjami

		return ::fwrite(buffer, 1, length, this->_file); // zapisujemy dane do pliku
	}

	bool File::flush()
	{
        if(this->_file == NULL)
            return false;

		//TODO: dorobic weryfikowanie zapisanych danych na podstawie zwroconej wartosci

		::fflush(this->_file);

		return true;
	}

	uint32_t File::readBytes(const char *filePath,
		uint8_t *&outData,
		uint32_t &outDataLength,
		uint32_t maxDataLength)
	{
		File file;

		if(file.open(filePath, FM_ReadBinary))
		{
			uint32_t fileLength = file.getSize();

			if(maxDataLength != 0xFFFFFFFF && fileLength > maxDataLength)
				fileLength = maxDataLength;

			uint8_t* data = new uint8_t[fileLength];
			uint32_t readDataLength = file.read(data, fileLength); // odczytujemy dane i ustawiamy informacje o ilosci odczytanych danych

			file.close();

            outData = data;
			outDataLength = fileLength;

			return readDataLength;
		}

        outData = NULL;
		outDataLength = 0;

		return 0;
	}

	uint32_t File::writeBytes(const char* filePath, uint8_t* data, uint32_t dataLength)
	{
		File file;

		if(file.open(filePath, FM_CreateBinary))
		{
			uint32_t wroteDataLength = file.write(data, dataLength); // zapisujemy dane i ustawiamy informacje o ilosci zapisanych danych
			file.close();

			return wroteDataLength;
		}

		return 0;
	}
}}
