#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef char const* (*char_function)();
typedef struct
{
    char_function* functions;
} Animal;

typedef Animal* (*animal_function)(char const*);
typedef Animal (*animal_function2)(char const*);

const char* str_concatenate(const char* string, const char* suffix)
{
    char* to_return = malloc(strlen(string) + strlen(suffix) + 1);

    strcpy(to_return, string), strcat(to_return, suffix);
    return (const char*)to_return;
}

void* myfactory(char const* libname, char const* ctorarg)
{
	HINSTANCE library = LoadLibrary(TEXT(str_concatenate(str_concatenate("./", libname), ".dll")));

	if (library != NULL)
	{
        animal_function factory_function;

        factory_function = (animal_function) GetProcAddress(library, "create");
        return factory_function(ctorarg);
	}

	FreeLibrary(library);

	return NULL;
}
