#include "diy.h"

template<int N> // N is a constexpr int, but if you enter a double, it will not be converted to constexpr int
constexpr int factorial()
{
    static_assert(N >= 0 && "The factorial's input must be Non-Negative!");
    int result{1};
    for (int i{2}; i <= N; ++i)
    {
        result *= i;
    }

    return result;
}

template <typename T>
T multi(T x, auto y) { return x * y; }

template <typename T, typename U>
auto sub(T x, U y) { return x - y; }

constexpr int foo(int);

constexpr int goo(int c)
{
    return foo(c);
}

constexpr int foo(int b)
{
    return b;
}

int main()
{
    static_assert(factorial<0>() == 1);
    static_assert(factorial<3>() == 6);
    static_assert(factorial<5>() == 120);

    // factorial<-3>();  // compile error

    std::cout << "Multipy: " << multi(2, 3) << '\n';
    std::cout << "Multipy: " << multi(1.2, 3) << '\n';

    std::cout << "Substract: " << sub(3, 2) << '\n';
    std::cout << "Substract: " << sub(3.5, 2) << '\n';
    std::cout << "Substract: " << sub(4, 1.5) << '\n';

    constexpr int a{goo(5)};
    std::cout << a;

    return 0;
}

