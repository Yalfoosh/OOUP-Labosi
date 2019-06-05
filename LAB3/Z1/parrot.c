#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char const* (*char_function)();

typedef struct
{
	char_function* functions;
} Animal;

typedef struct
{
	char_function* functions;
	char const* name;
} Parrot;



char const* getParrotName(void* parrot) { return ((Parrot*) parrot)->name; }
char const* parrotMenu(void) { return "ljude"; }
char const* parrotGreet(void) { return "Poyy."; }

char_function parrot_functions[3] =
{
	(char_function) getParrotName,
	(char_function) parrotGreet,
	(char_function) parrotMenu
};


void constructParrot(Parrot* parrot, char const* name)
{
	(*parrot).name = name;
	parrot->functions = parrot_functions;
}

void* create(char const* name)
{
	Parrot* parrot = malloc(sizeof(Parrot));
	constructParrot(parrot, name);
	return parrot;
}