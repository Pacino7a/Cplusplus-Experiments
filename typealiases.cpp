#include "diy.h"

typedef int Mytype_int_32; // typedef
using Myint_32 = int; // type aliases (Recommended)
// the methods above, do the same thing

using PrintError = int;
PrintError printDataO();

using myFunc = int(*)(int, char); // aliases for a function (pointer)
typedef int(*myFunct)(int, char); // complex

int example(int x, char i)
{
    return x + i;
}

void callTheResult(myFunc func)
{
    int result{func(10,'A')};
    std::cout << result << '\n';
}

using Mycal = int(*)(int, int); // switch the function flexiably

class Calculator{
    public:

        Mycal operation;
        // list initialization
        Calculator(Mycal op) : operation(op){} 
        // initialize (operation),
        // make it points to where (op) is pointing
        // set calculate mode

        // what this class can do
        int compute(int a, int b)
        {
            return operation(a, b);
        }
};

int add(int a, int b)
{
    return a + b;
}

int multipy(int a, int b)
{
    return a * b;
}

int main()
{
    myFunc func = example;
    std::int32_t hel{1};
    std::int8_t wor{2};
    std::cout << func(hel, wor) << '\n';
    callTheResult(func);

    // initialize the entities of (class)calculator
    Calculator caladd(add); // set calculate mode
    Calculator calmulti(multipy);

    std::cout << "Add: " << caladd.compute(5, 2) << '\n';
    std::cout << "Multipy: " << calmulti.compute(5, 2) << '\n';

    return 0;
}
