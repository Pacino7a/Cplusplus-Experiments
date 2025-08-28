#include <iostream>

constexpr void doNothing(int) {}
void print(int);
constexpr int add(int x, int y)
{
    return x + y;
}
consteval int add_eval(int x, int y)
{
    return x + y;
}

int main()
{
    // All of them are the caller of the constexpr function
    // and there are 4 levels of evaluating
    constexpr int always{add(5,1)}; // always evaluate during compile time - Level 4
    doNothing(add(5, 1));

    int probably{add(5, 2)};        // probably, (Level 3), because there is no require (constexpr)
    print(add(2, 3));               // probably Compile-time

    
    int x{2};
    int y{4};
    constexpr int validation{x};
    print(add(x, y)); // possibly, but mostly Runtime, Level 2 - No require and no constexpr as parameters
    constexpr int check{add(x, y)}; // check primarily , But C++ has no mechanism to do this.
    
    // std::is_constant_evaluated
    if consteval{};// replacement, they are the same.
    // Does not actually make a distinction between "Compile time" and "Runtime",
    // Because there are level 3 and level 2.
    // For example:
    // when the context is required evaulate during compile-time it gets TRUE
    // But the compiler can also evaluate the constant expression during compile-time (level 3)
    // even there is no any constexpr prefix require
    // In this case, it gets FALSE

    int unknown_during_compiling{};
    std::cin >> unknown_during_compiling;
    print(add(unknown_during_compiling, 3)); // never, not possible to evaluate during the compile-time - Level 1

    print(add_eval(2, 3)); // Fine - consteval only accepts constexpr
    print(add_eval(x, y)); // Error

    return 0;
    // the topic says constexpr should be there whether the function is required but needed,
    // and constexpr is implicit inline function
    // but it also said you shouldn't convert all functions to the inline functions
}

void print(int x)
{
    std::cout << x << std::endl;
}
