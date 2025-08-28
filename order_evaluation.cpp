#include <iostream>

int printValue(int a, int b, int c)
{
    return a + (b * c);
}

int getValue()
{
    std::cout << "Please enter an Integer: ";
    int temp{};
    std::cin >> temp;
    return temp;
}

int main()
{
    // ambiguous order
    // the order of evaluation of the arguments is R->L (GCC)
    std::cout << "Start:\n" << printValue(getValue(), getValue(), getValue()) << std::endl;
    // clang's order is L->R

    // fixed
    // do not depend on operand(or argument) evaluation order! 
    int a{getValue()}; // 1
    int b{getValue()}; // 2
    int c{getValue()}; // 3

    printValue(a, b, c); // 7

    return 0;
}
