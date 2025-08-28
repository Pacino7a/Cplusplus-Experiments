//Constant Expression (Needs No one to Rely on)

#include <iostream>

int getNumber() { return 1; };

int main()
{
    char a{'q'}; 
    // although 'q' is a const expression,
    // variable a is not a constant expression because of the type
    const int b{0}; // yes
    const double c{5.0}; // Non-constant expression because of the type (const int and its variant only)
    const int d{a * 2}; // No, because of a
    double e{c + 1.0}; // No, because c is not a ce and the type limitations
    const int f{b * 2}; // yes
    const int g{getNumber()}; // No, because the return value is not sure to the compiler
    const int h{}; // although this is a value-initializer , h will get 0. So this a constant-expression

    // std::cin & std::cout are not constant expressions,
    // because they depend on the user's input

    //never
    int x = 10;
    int y{x + 5}; // <<
    //possibly
    int x = 10;
    int y{10 + 5}; // <<
    //likely
    constexpr int x{10};
    int y{x + 5}; // <<
    //always
    constexpr int k{10};
    constexpr int y{k + 5}; // << constexpr is a request for compiler evaluating
}
