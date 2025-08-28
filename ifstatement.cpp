#include <iostream>

int main()
{
    constexpr int x{3};
    //std::cout << (x < 0) ? "Negative" : "Non-negative";   // Output 0, because the precedence of "<<" is higher than "?"
    std::cout << ((x < 0) ? "Negative" : "Non-negative") << '\n'; // Output Correct

    std::cout << (true ? 1 : 2) << '\n'; // Both operand 1 and operand 2 are SAME TYPE, all fine
    std::cout << (false ? 1 : 2.2) << '\n'; // Compiler converts (int) 1 to a (double) 1.0
    //std::cout << (false ? -1 : 2u) << '\n'; // Compiler converts (signed int) -1 to (unsigned int) 4294967295
    //std::cout << (false ? 5 : "What's this?") << '\n'; // Compiler can't convert
    std::cout << ((x != 2) ? std::to_string(x) : std::string{"x is 2"}) << '\n'; // explicitly convert the types to match

    return EXIT_SUCCESS;
}
