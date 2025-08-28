#include "diy.h"

void print(int x) { std::cout << "you just input " << x << '\n'; }

// manually
// void print(bool) = delete; // we can delete the meaningless functions (forbid to use)
// void print(char) = delete;

// automatically
template <typename T> // deleting all non-matching overloads
void print(T x) = delete;

// template function, which can be used at once
template <typename T>
T add_tep(T x, T y) { return x + y; }

template <typename T, typename U> // we can use auto to deduce the type of the result which is came form two 
auto get_min(T x, U y) { return (x < y) ? x : y; }   // different type input

// short cut
auto bigger_new_way(auto x, auto y) { return (x > y) ? x : y; } // New way (compare with Line 17~18)

// auto test(int, int); // this is a bad forward declaration, we do not need this
auto test(double, double) -> int; // tail for deduction

int add(int x = 1, int y = 2); // set default value in declaration

template<int N>
void print_N()
{
    for (int i = 0; i < N; ++i)
    {
        std::cout << "Template_with_non-type paras:"
                  << i + 1 << '\n';
    }
}

double getSqrt_Ori(double x)
{
    // static_assert(x > 0 && "Your input must be a Positive number!"); // Fail to assert during compiling
    assert(x > 0 && "Your input must be a Positive number!"); // but run-time
    if (x >= 0)
        return std::sqrt(x);
    return 0.0;
}

template<double N> // you can use static_assert here, because the non-type template parameter is a constexpr
double getSqrt()
{
    static_assert(N > 0 && "Your input must be a Positive number!");
    if constexpr (N >= 0)
        return std::sqrt(N);

    return 0.0;
}

int main()
{
    std::cout << "default: " << add() << '\n';
    std::cout << "test: " << test(3,1.5) << '\n';
    std::cout << "Bigger: " << bigger_new_way(2, 3.6) << '\n';
    std::cout << "Template_add: " << add_tep<double>(1.3, 2.2) << '\n'; // we can use <actual_type> to set the type of template parameters
                                                                        // aka. instantiate the function for a specific typename (Specification)
    std::cout << "Template_add: " << add_tep(1.3, 2.2) << '\n'; // template argument deduction (RECOMMENDED)
    std::cout << "Template_getminimum: " << get_min(2.2, 3) << '\n';

    print_N<8>(); // <non-type template parameters> (NOT the parameters inside!)
                //int/enumeration type/std::nullptr/float/object's ref/function's ref/member func's ref/literals

    std::cout << getSqrt<0.25>() << '\n';
    // std::cout << getSqrt<-0.25>() << '\n'; // this will get an error while compiling the program
    std::cout << getSqrt_Ori(0.25) << '\n';
    std::cout << getSqrt_Ori(-0.25) << '\n';

    return 0;
}

auto test(double x,double y) -> int
{
    return x * y;
}

int add(int x, int y)
{
    return x + y;
}
