#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myfactory.h"

typedef char const* (*char_function)();

typedef struct
{
    char_function* functions;
} Animal;


void animalPrintGreeting(Animal* animal)
{
    char const* name = animal->functions[0](animal);
    printf("%s pozdravlja: %s\n", name, animal->functions[1]());
}

void animalPrintMenu(Animal* animal)
{
    char const* name = (*animal).functions[0](animal);
    printf("%s voli %s.\n", name, (*animal).functions[2]());
}


int main(void)
{
    Animal* p1 = (Animal*) myfactory("parrot", "Duga");
    Animal* p2 = (Animal*) myfactory("tiger", "Zebra");
    /*
    Animal* p3 = (Animal*) myfactory("parrot", "Duga stack");
    Animal* p4 = (Animal*) myfactory("tiger", "Zebra stack");
    Animal p5 = *p3;
    Animal p6 = *p4;
     */

    if (!(p1 && p2))
    {
        printf("Creation of plug-in objects failed.\n");
        exit(1);
    }

    animalPrintGreeting(p1), animalPrintGreeting(p2);
    animalPrintMenu(p1), animalPrintMenu(p2);

    free(p1), free(p2);

    /*
    animalPrintGreeting(&p5), animalPrintGreeting(&p6);
    animalPrintMenu(&p5), animalPrintMenu(&p6);
     */

    getchar();

    return 0;
}