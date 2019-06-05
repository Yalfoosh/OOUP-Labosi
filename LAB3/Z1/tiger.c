#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char const* (*char_function)();

typedef struct
{
    char_function* functions;
	char const* name;
} Tiger;

typedef struct
{
    char_function* functions;
} Animal;


char const* getTigerName(void* tiger){ return ((Tiger* ) tiger)->name; }
char const* tigerMenu(void) { return "meso"; }
char const* tigerGreet(void) { return "Ror!"; }

char_function tiger_functions[3] =
{
    (char_function) getTigerName,
    (char_function) tigerGreet,
    (char_function) tigerMenu
};

void constructTiger(Tiger* tiger, char const* name)
{
    (*tiger).name = name;
    (*tiger).functions = tiger_functions;
}

void* create(char const* name)
{
    Tiger* tiger = malloc(sizeof(Tiger));
    constructTiger(tiger, name);

    return tiger;
}