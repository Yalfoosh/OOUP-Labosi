#include <stdio.h>
#include <stdlib.h>

//region Definitions

#define DOG_GREET "vau!"
#define DOG_MENU "kuhanu govedinu"
#define CAT_GREET "mijau!"
#define CAT_MENU "konzerviranu tunjevinu"

#define DEFAULT_DOG_NAME "Doggo"
#define DEFAULT_CAT_NAME "Catto"
#define DEFAULT_NAME "Missingno"

//endregion

//region Type Definitions

typedef char const* (*PTRFUN)();

typedef struct
{
    char* name;
    PTRFUN* functions;
} Animal;

typedef enum
{
    None = 0,
    Dog = 1,
    Cat = 2
} AnimalType;

//endregion

// region Function Prototypes

void AnimalDecorator(Animal *, char *, AnimalType);
void animalPrintGreeting(Animal*);
void animalPrintMenu(Animal*);

char const* dogGreet();
char const* dogMenu();
Animal* createDog(char*);

char const* catGreet();
char const* catMenu();
Animal* createCat(char*);

//endregion

//region Animals

void animalPrintGreeting(Animal* animalInstance)
{ printf("%s pozdravlja: %s\n", (*animalInstance).name, animalInstance->functions[0]()); }

void animalPrintMenu(Animal* animalInstance)
{ printf("%s voli: %s\n", (*animalInstance).name, animalInstance->functions[1]()); }

//region Dogs

PTRFUN dogFunctions[2];
char const* dogGreet() { return DOG_GREET; }
char const* dogMenu() { return DOG_MENU; }

Animal* createDog(char* name)
{
    Animal* dog = malloc(sizeof(Animal));
    AnimalDecorator(dog, name, Dog);
    return dog;
}

Animal createDogStack(char* name)
{
    Animal dog;
    dog.name = name;
    dog.functions = dogFunctions;

    return dog;
}

//endregion

//region Cats

PTRFUN catFunctions[2];
char const* catGreet() { return CAT_GREET; }
char const* catMenu(){ return CAT_MENU; }

Animal* createCat(char* name)
{
    Animal* cat = malloc(sizeof(Animal));
    AnimalDecorator(cat, name, Cat);
    return cat;
}

Animal createCatStack(char* name)
{
    Animal cat;
    cat.name = name;
    cat.functions = catFunctions;

    return cat;
}

//endregion

void AnimalDecorator(Animal *animalInstance, char *name, AnimalType type)
{
    (*animalInstance).name = name;

    switch(type)
    {
        case Dog:
            (*animalInstance).functions = dogFunctions;
            break;
        case Cat:
            (*animalInstance).functions = catFunctions;
            break;
        default:
            exit(-1);
    }
}

//endregion

//region Functions

void run()
{
    Animal* p1 = createDog("Hamlet");
    Animal* p2 = createCat("Ofelija");
    Animal* p3 = createDog("Polonije");

    animalPrintGreeting(p1);
    animalPrintGreeting(p2);
    animalPrintGreeting(p3);

    animalPrintMenu(p1);
    animalPrintMenu(p2);
    animalPrintMenu(p3);

    free(p1);
    free(p2);
    free(p3);
}

void run_stack()
{
    Animal p1 = createDogStack("Hamlet");
    Animal p2 = createCatStack("Ofelija");
    Animal p3 = createDogStack("Polonije");

    animalPrintGreeting(&p1);
    animalPrintGreeting(&p2);
    animalPrintGreeting(&p3);

    animalPrintMenu(&p1);
    animalPrintMenu(&p2);
    animalPrintMenu(&p3);

    //Nije potrebno free-ati p1, p2 i p3 jer zbog RAIIja se sve oslobađa kad p1, p2 i p3 izađu iz vidokruga.
}

Animal** createAnimals(AnimalType type, int n)
{
    if(n < 0)
        n = -n;
    else if(n == 0)
        n = 1;

    Animal** animals = (Animal**)malloc(n * sizeof(Animal*));

    for(int i = 0; i < n; ++i)
    {
        animals[i] = (Animal*)malloc(sizeof(Animal));
        AnimalDecorator(animals[i],
                        type == Dog ? DEFAULT_DOG_NAME
                                    : type == Cat ? DEFAULT_CAT_NAME
                                                  : DEFAULT_NAME,
                        type);
    }

    return animals;
}

//endregion

int main()
{
    dogFunctions[0] = &dogGreet;
    dogFunctions[1] = &dogMenu;
    catFunctions[0] = &catGreet;
    catFunctions[1] = &catMenu;

    int dogs_to_run = 20;

    printf("Running heap allocated...\n");
    run();

    printf("\nRunning stack allocated...\n");
    run_stack();

    printf("\nInitializing %d dogs...\n", dogs_to_run);
    Animal** dogs = createAnimals(Dog, dogs_to_run);

    for(int i = 0; i < dogs_to_run; ++i)
        printf("[%d] I have a dog named %s.\n", i + 1, dogs[i]->name);

    return 0;
}

//region Questions

/*
 *
 * Vaše rješenje mora biti takvo da memorijsko zauzeće za svaki primjerak "razreda" (psa, mačke) ne ovisi o broju
 * virtualnih metoda. Drugim riječima, dodavanje nove virtualne metode ne smije kod svakog primjerka psa i mačke
 * povećati memorijsko zauzeće.
 *
 * ---------------------------------------------------------------------------------------------------------------------
 *
 * Tako i je jer svaki primjerak klasa psa i mačke prima pokazivač na tablicu, što je konstantno veličine 4B ili 8B.
 *
 */

/*
 * Pokažite da je konkretne objekte moguće kreirati i na gomili i na stogu (detalji). Memorijski prostor na stogu
 * zauzmite lokalnom varijablom, a za zauzimanje memorije na gomili pozovite malloc.
 *
 * ---------------------------------------------------------------------------------------------------------------------
 *
 * Dokazano u run_stack().
 *
 */

/*
 *
 * Napišite funkciju za stvaranje n pasa, gdje je n argument funkcije (npr. za potrebe vuče saonica). Pokažite kako
 * bismo to ostvarili jednim pozivom funkcije malloc i potrebnim brojem poziva funkcije constructDog.
 *
 * ---------------------------------------------------------------------------------------------------------------------
 *
 * Ostvareno u createAnimals(); ne koristi se createDog već je pruženo generičko rješenje (ali sve je analogno).
 *
 */

/*
 *
 * Nakon rješavanja zadatka, uspostavite vezu s terminologijom iz objektno orijentiranih jezika.
 * Koji elementi vašeg rješenja bi korespondirali s podatkovnim članovima objekta, metodama, virtualnim metodama,
 * konstruktorima, te virtualnim tablicama?
 *
 * ---------------------------------------------------------------------------------------------------------------------
 *
 * Objekti su pokazivači na generičku klasu.
 * Metode su reference na funkcije u tablicama dogFunctions i catFunctions.
 * Virtualne metode su animalPrintGreeting() i animalPrintMenu() jer se one ponašaju ovisno o implementaciji za klasu.
 * Konstruktori su teoretski createDog() i createCat().
 * Virtualne tablice su dogFunctions i catFunctions.
 *
 */

//endregion