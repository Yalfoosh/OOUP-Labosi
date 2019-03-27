#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//region Type Definitions

struct UnaryFunction;

typedef double (*functionPointerDouble)(struct UnaryFunction*, double);

typedef struct UnaryFunction
{
    functionPointerDouble* table;

    int lowerBound;
    int upperBound;
} UnaryFunction;

typedef struct
{
    functionPointerDouble* table;

    int lowerBound;
    int upperBound;
} Square;

typedef struct
{
    functionPointerDouble* table;

    int lowerBound;
    int upperBound;
    double a;
    double b;
} Linear;

//endregion

//region Function Prototypes

void constructUnaryFunction(UnaryFunction*, int, int);
void tabulate(UnaryFunction*);
static bool same_functions_for_ints(UnaryFunction*, UnaryFunction*, double);

void constructSquare(Square*, int, int);
Square* createSquare(int, int);
double squareValueAt(Square*, double);
double squareNegativeValueAt(Square*, double);

void constructLinear(Linear*, int, int, double, double);
Linear* createLinear(int, int, int, int);
double linearValueAt(Linear*, double);
double linearNegativeValueAt(Linear*, double);

//endregion

//region Classes

//region Unary Function

functionPointerDouble unaryFunctionTable[2] = { (functionPointerDouble) NULL,
                                                (functionPointerDouble) NULL };

void constructUnaryFunction(UnaryFunction *unaryFunctionInstance, int lowerBound, int upperBound)
{
    unaryFunctionInstance->lowerBound = lowerBound;
    unaryFunctionInstance->upperBound = upperBound;

    unaryFunctionInstance->table = unaryFunctionTable;
}

void tabulate(UnaryFunction* unaryFunctionInstance)
{
    for(int x = unaryFunctionInstance->lowerBound; x <= unaryFunctionInstance->upperBound; ++x)
        printf("f(%d)=%lf\n", x, (unaryFunctionInstance->table)[0](unaryFunctionInstance, x));
}

static bool same_functions_for_ints(UnaryFunction* function_1, UnaryFunction* function_2, double tolerance)
{
    if(function_1->lowerBound != function_2->lowerBound || function_1->upperBound != function_2->upperBound )
        return false;

    double difference;

    for(int x = function_1->lowerBound; x <= function_1->lowerBound; ++x)
    {
        difference = function_1->table[0](function_1, x)
                     - function_2->table[0](function_2, x);

        if(difference < 0)
        {
            if(difference < tolerance)
                return false;
        }
        else if(difference > tolerance)
            return false;
    }
    return true;
}

//endregion

//region Square

double squareValueAt(Square* squareInstance, double x) { return x*x; }
double squareNegativeValueAt(Square* squareInstance, double x) { return -squareValueAt(squareInstance, x); }
functionPointerDouble squareTable[2] = { (functionPointerDouble) squareValueAt,
                                         (functionPointerDouble) squareNegativeValueAt };

void constructSquare(Square* squareInstance, int lowerBound, int upperBound)
{
    constructUnaryFunction((UnaryFunction*) squareInstance, lowerBound, upperBound);
    squareInstance->table = squareTable;
}

Square* createSquare(int lowerBound, int upperBound)
{
    Square* squareInstance = malloc(sizeof(Square));
    constructSquare(squareInstance, lowerBound, upperBound);

    return squareInstance;
}

//endregion

//region Linear

double linearValueAt(Linear* linearInstance, double x) { return (linearInstance->a) * (x) + (linearInstance->b); }
double linearNegativeValueAt(Linear* linearInstance, double x) { return -linearValueAt(linearInstance, x); }

functionPointerDouble linearTable[2] = { (functionPointerDouble) linearValueAt,
                                         (functionPointerDouble) linearNegativeValueAt };

void constructLinear(Linear* linearInstance, int lowerBound, int upperBound, double aRatio, double bRatio)
{
    constructUnaryFunction((UnaryFunction*) linearInstance, lowerBound, upperBound);

    linearInstance->a = aRatio;
    linearInstance->b = bRatio;

    linearInstance->table = linearTable;
}

Linear* createLinear(int lowerBound, int upperBound, int aRatio, int bRatio)
{
    Linear* linearInstance = malloc(sizeof(Linear));
    constructLinear(linearInstance, lowerBound, upperBound, aRatio, bRatio);

    return linearInstance;
}

//endregion

//endregion

int main()
{
    UnaryFunction *f1, *f2;

    f1 = (UnaryFunction*) createSquare(-2, 2);
    tabulate(f1);

    f2 = (UnaryFunction*) createLinear(-2, 2, 5, -2);
    tabulate(f2);

    printf("f1==f2: %s\n", same_functions_for_ints(f1, f2, 1E-6) ? "DA" : "NE");
    printf("neg_val f2(1) = %lf\n", f2->table[1](f2, 1.0));

    free(f1);
    free(f2);

    return 0;
}