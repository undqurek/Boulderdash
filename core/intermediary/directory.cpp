#include "directory.h"

#include "basic/cleaner.h"
#include "basic/string.h"

#include <sys/stat.h>


using namespace core::basic;

namespace core { namespace intermediary
{
	void deleteCString(char *cString)
	{
		Cleaner::deleteArray(cString);
	}

	Directory::Directory()
	{
		this->_dir = NULL;
	}

	Directory::~Directory()
	{
		this->close();
	}

	bool Directory::open(const char *path)
	{
		if(path == NULL)
			return false;

		if(this->_dir == NULL) // sprawdzamy czy jakis folder nie jest obecnie otwarty
		{
			this->_dir = ::opendir(path);

			if(this->_dir == NULL)
				return false;

			return true;
		}

		return false;
	}

	bool Directory::close()
	{
		if(this->_dir == NULL)
			return false;

		if(::closedir(this->_dir) == 0)
		{
			this->_dir = NULL;
			return true;
		}

		return false;
	}

	bool Directory::isOpened()
	{
		return (this->_dir != NULL);
	}

	bool Directory::seek(uint32_t offset)
	{
		if(this->_dir == NULL)
			return false;

		::seekdir(this->_dir, offset);

		return true;
	}

	uint32_t Directory::tell()
	{
		if(this->_dir == NULL)
			return false;

		return ::telldir(this->_dir);
	}

	char *Directory::read()
	{
		if(this->_dir == NULL)
			return NULL;

		struct ::dirent *item = ::readdir(this->_dir); // obiektu tego nie nalezy usuwac gdyz jest on sam usuwany

		if(item == NULL)
			return NULL;

#ifdef SYSTEM == LINUX
        return String::copyCString(item->d_name, item->d_reclen);
#endif // LINUX

#if SYSTEM == WINDOWS
		return String::copyCString(item->d_name, item->d_namlen);
#endif // WINDOWS
	}

	Directory::ItemType Directory::getType(const char *path)
	{
		struct stat informations;

		if(::stat(path, &informations) == 0)
		{
			if(informations.st_mode & S_IFDIR)
				return IT_Directory;

			if(informations.st_mode & S_IFREG)
				return IT_File;

			return IT_Undefined;
		}
		else
			return IT_Error;
	}

	List<char *> *Directory::getItems(const char *path, ItemType flags)
	{
		Directory directory;

		if(directory.open(path))
		{
			directory.seek(2); // pomijamy nazwy '.' i '..'
			List<char *> *filesNames = new List<char *>();

			if(flags == IT_Undefined)
			{
				while(true)
				{
					char *itemName = directory.read();

					if(itemName == NULL)
						break;

					filesNames->pushBack(itemName);
				}
			}
			else
			{
				while(true)
				{
					char *itemName = directory.read();

					if(itemName == NULL)
						break;

					char *itemPath = String::concatenate(path, itemName);
					ItemType type = getType(itemPath);

					Cleaner::deleteArray(itemPath);

					if(type & flags) // dodawane do listy sa tylko obiekty odpowiedniego typu
						filesNames->pushBack(itemName);
				}
			}

			return filesNames;
		}

		return NULL;
	}

	void Directory::deleteItems(List<char *> *&items)
	{
		items->clear(deleteCString);
		Cleaner::deleteObject(items);
	}
}}
