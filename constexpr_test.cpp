#include <iostream>

// CE - Costant Expression, CEV - Constant Expression Variable

int five() { return 5; }
constexpr float six() { return 6.0; }

int main()
{
    constexpr double gravity{9.8}; // double is fine
    constexpr int sum{7 + 8}; // Can be evaluated during compile-time
    constexpr int something{sum};

    std::cout << "Your age: ";
    int age{};
    std::cin >> age;

    const int myAge_0{age}; // This can be evaluated during the runtime
    constexpr int myAge{age}; // age is not a constant expression which can't be initialized by a CEV
    constexpr int f{five()}; // The return of the function is not a constant expression too
    constexpr int g{six()}; // This is fine

    return EXIT_SUCCESS;
}
