#include <iostream>
#include <cstdlib>
#include <cassert>

// #define NDEBUG //deactivate DEBUG mode
// automating the test functions

constexpr bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

int testVowel()
{
#ifdef NDEBUG

    std::cerr << "Test run with NDEBUG defined";
    std::abort();

#endif

    assert(isLowerVowel('a'));
    assert(isLowerVowel('e'));
    assert(isLowerVowel('i'));
    assert(isLowerVowel('o'));
    assert(isLowerVowel('u'));
    assert(!isLowerVowel('q'));
    assert(!isLowerVowel('j'));
    assert(!isLowerVowel('k'));

    return 0;
}
int testPrecision()
{
#ifdef NDEBUG
std::cerr << "Test run with NDEBUG defined";
std::abort();
#endif

    double one{0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1};
    assert(one == 1 && "NOT EQUAL!");
    return 0;
}



int main()
{
    testVowel();
    testPrecision();
    // if we reachd here, all tests have passed
    std::cout<<"Success!\n";

    return 0;
}
