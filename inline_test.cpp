// DON'T USE "inline" Prefix for optimization
// it works in other way
#include <iostream>

// As an optimization method
// "inline" is very old-school
// In modern C++
// your compiler knows whether the function needs `inline` keyword for performance efficient
// and it will do it for you automatically
// So it will ignore or devalue any your "inline" for optimization
// Last but not Least
// Do NOT use the "inline" keyword to request inline expansion manually!

// In modern C++
// inline means you can define this stuff in many different places
// and it would NOT violate ODR (One Definition Rule)
// you can define each inline fuction into a header file for convenience
// In other case, you shouldn't define any thing prefix of inline
// Unless you have a specific, compelling reason to do so

inline void doNothing(){} // bad for optimization
inline int min(int, int); // bad for optimization

int main()
{
    doNothing();
    std::cout << min(5, 8) << '\n';
    std::cout << min(8, 7) << '\n';
    return EXIT_SUCCESS;
}


inline int min(int x, int y)
{
    return (x < y) ? x : y;
}
