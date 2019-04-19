#include <iostream>
#include <string.h>

//region Provided Code

class B
{
    public:
    virtual int prva() = 0;
    virtual int druga() = 0;
};

class D: public B
{
    public:
    virtual int prva() { return 0; }
    virtual int druga() { return 42; }
};

//endregion

//region Type Definitions & Global Variables

typedef int (*int_function)();
int NUMBER_OF_FUNCTIONS = 2;

//endregion

void indirectVirtualCalls(B* b_instance_pointer)
{
    auto functions = *((int_function**) b_instance_pointer);

    for(int i = 0; i < NUMBER_OF_FUNCTIONS; ++i)
        printf("%d\n", (*functions[i])());
}

int main()
{
    D b;
    indirectVirtualCalls(&b);

    return 0;
}