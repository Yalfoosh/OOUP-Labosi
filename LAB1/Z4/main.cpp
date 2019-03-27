#include <iostream>

//region Classes

class Base
{
    public:
        //if in doubt, google "pure virtual"
        virtual void set(int x) = 0;
        virtual int get() = 0;
};

class CoolClass: public Base
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
        void set(int x) { x_ = x; };
        int get() { return x_; };

    private:
        int x_;
};

//endregion

int main()
{
    PlainOldClass poc;
    Base* pb = new CoolClass;

    poc.set(42);
    pb->set(42);
}

//region Questions

/*
 *
 * Q1 - linije 153 i 156.
 *
 *
 * Q2 - poc se inicijalizira guranjem na stog dok pb poziva potprogram konstruktora koji će mu vratiti pokazivače.
 *
 *
 * Q3 - linija 298 - piše samo da zauzima 32 bita.
 *
 *
 * Q4 - linija 109 - pozove se konstruktor Base, inciijalizira se virtualna tablica, adresa se vraća posmaknuta za 12
 *      bitova na stog.
 *
 *
 * Q5 - PlainOldClass::set() stavi argument iz funkcije tamo gdje pokazuje pokazivač na _x
 *
 *      Base::set() dohvati adresu CoolClass, preko koje dođe do adrese virtualne tablice, preko koje dođe do adrese
 *      settera od CoolClass, pa pozove što se nalazi na toj memorijskoj lokaciji.
 *
 *
 * Q6 - Linija 122.
 *
 */

//endregion