#include <iostream>

//region Classes

class CoolClass
{
    public:
        virtual void set(int x) { x_ = x; };
        virtual int get() { return x_; };

    private:
        int x_;
};

class PlainOldClass
{
    public:
        void set(int x){ x_ = x; };
        int get(){ return x_; };

    private:
        int x_;
};

//endregion

int main()
{
    printf("Size of CoolClass: %d B\n", (int)sizeof(CoolClass));
    printf("Size of PlainOldClass: %d B\n", (int)sizeof(PlainOldClass));

    return 0;
}

//region Questions

/*
 *
 * Ispitajte memorijske zahtjeve objekata dvaju tipova (pomoć: ispiši sizeof(PlainOldClass) i sizeof(CoolClass)).
 * Objasnite dobivenu razliku. Ako dobijete rezultate koje ne možete objasniti, pročitajte kada i zašto prevoditelj
 * nadopunjava objekte (engl. padding).
 *
 * ---------------------------------------------------------------------------------------------------------------------
 *
 * Veličina CoolClass je 16 B jer ima dodatnih 8 B za virtualnu tablicu. Obje klase imaju 1 privatni int koji zauzima
 * 4 B prostora. CoolClassa se nadopunjuje s 12 B na 16 B jer smo na x64 arhitekturi, pa kompajler gleda da zauzeće
 * memorije (u bitovima) bude višekratnik broja 64, tj 8 B.
 */

//endregion