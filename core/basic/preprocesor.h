#ifndef PREPROCESOR_H
#define PREPROCESOR_H


#define LINUX 1
#define WINDOWS 2

#define SYSTEM WINDOWS
//#define SYSTEM LINUX


#define DECLARATION_EXPORT __declspec(dllexport)
#define DECLARATION_IMPORT __declspec(dllimport)


#define _in_ // argument wejsciowy
#define _out_ // argument wyjsciowy
#define _mod_ // argument modyfikowant
#define __ // wykorzystywany jest do zaznaczanie ze elementy nie powinny byc usuwane w miejscu wskazanym przez define'a


// Zwraca nazwe zmiennej podanej w parametrze
//
#define STRINGIFY(x) #x

// Zamienia liczby na c-string'i - CIALO MAKRA JEST HACK'iem !!!
//
#define TOSTRING(x) STRINGIFY(x)

// Tworzy komunikat poszerzony o informacje (sciezke do pliku i numer lini) mowiaca o polozeniu komunikatu w kodzie zrodlowym
//
#define CREATE_ERROR_MESSAGE(message)\
	("file: " __FILE__ " line: " TOSTRING(__LINE__) " error: " message)



#define ARGUMENT_CHECK_POINTER(pointer)\
	if(pointer == NULL)\
        throw #pointer " is not defined.";

#define ARGUMENT_CHECK_ELEMENTS_MIN_LIMIT(argument, limit)\
	if(argument <= limit)\
        throw #argument " must be greater than " #limit ".";

#define ARGUMENT_CHECK_ELEMENTS_MIN_COUNT(argument, count)\
	if(argument < count)\
        throw #argument " must be greater or equal than " #count ".";

#endif // PREPROCESOR_H
