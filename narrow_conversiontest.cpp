#include "diy.h"
#include <iomanip> // std::setprecision()

int main()
{
    float x{5.2f}; // double2float okay
    int y{5.0}; // double2int error (absolute error)
    int here{1}; // int2int okay
    long long we{1000000000000000LL}; // int2int, error, too big to conversion
    int where{we}; // (longlong2int), too big to conversion
    double there{here}; // int2float (narrow conversion), constexpr can be excluded

    // constexpr works almost all the time
    [[maybe_unused]] unsigned int u{5};
    [[maybe_unused]] unsigned int k{-5};// signed2unsigned, error, because the value has `-`
    [[maybe_unused]] float f{1.5};

    constexpr int n{5};
    [[maybe_unused]] double d{n};
    [[maybe_unused]] short s{5};
    [[maybe_unused]] float small{1.23456789};// conversion success with precision loss

    std::cout << std::setprecision(3);
    std::cout <<"x is "<< x;

    return 0;
}
