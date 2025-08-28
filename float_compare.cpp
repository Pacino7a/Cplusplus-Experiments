#include <iostream>
#include <cmath>
#include <algorithm>

// replacement of std::abs() for constexpr before C++23
template <typename T>
constexpr T constAbs(T x) // can be called like a normal function, but can handle different kinds of value
{
    return (x < 0) ? -x : x;
}
//std::cout << constAbs(-5) << std::endl; --> 5
//std::cout << constAbs(-3.14) << std::endl; --> 3.14
//std::cout << constAbs(-100L) << std::endl; --> 100

constexpr bool approximatelyEqualRel(double a, double b, double relEpsilon, double absEpsilon)
{
    // abs distance
    if(std::abs(a - b) <= absEpsilon) // fix the problem of close to 0
        return true;
    //std::abs() is not a constexpr until C++23
    
    // adaptive distance for approximation,
    // which is controlled by scale relEpsilon (e.g. 2% of Maximum Magnitude -- 2% Error)
    // but when a and b is very close to 0, 
    // the error that the algorithm can tolerate will be very very small
    // the output of relative error will be invalid probably
    // so we need absEpsilon to handle this
    return (std::abs(a - b)) <= (std::max(std::abs(a), std::abs(b)) * relEpsilon); 

}

int main()
{
    constexpr double relEpsilon{1e-8};
    constexpr double absEpsilon{1e-12};
    constexpr double a{0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1};

    // std::cout << "Please enter 1 double (Space to Seperate each one): ";
    // double A{};
    // double B{};
    // std::cin >> A;
    // std::cin >> B;
    // if (approximatelyEqualRel(A, B, relEpsilon, absEpsilon))
    //     std::cout << "EQUAL!";
    // else
    //     std::cout << "NOT EQUAL!";

    // if (approximatelyEqualRel(1.0, a, relEpsilon, absEpsilon))
    //     std::cout << "EQUAL!";
    // else
    //     std::cout << "NOT EQUAL!";
    // std::cout << '\n';
    // if (approximatelyEqualRel(0.0, a-1.0, relEpsilon, absEpsilon))
    //     std::cout << "EQUAL!";
    // else
    //     std::cout << "NOT EQUAL!";

    std::cout << std::boolalpha;
    constexpr bool same{approximatelyEqualRel(0.0, a - 1.0, relEpsilon, absEpsilon)};
    std::cout << same << '\n';

    return 0;
}
