// This module focus on the overloading of the function whose parameters' type is class type
// aka Class Templates
#include <iostream>
#include <string>

// general template of a function overloading
template<typename T>
constexpr T max(T a, T b)
{
    return a > b ? a : b;
}

// general template of a struct overloading
template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T, typename U> // recommend, more gerneral
struct Pair_D
{
    T first{};
    U second{};
};

struct Point
{
    int first{0};
    int second{0};
};


// instantiation (e.g. Pair<int> below)------------------
// template<> (tells the compiler this is a template type with no template parameter)
// struct Pair<int>
// {
//    int first{};
//    int second{};
// };
// -------------------------------------------------------------

// ERROR!-------------------------------
// struct Pair
// {
//     int first{0};
//     int second{0};
// };
// struct Pair  // Redefined here is not be Allowed
// {
//     double first{0.0};
//     double second{0.0};
// };
// ------------------------------------------

// ----------Too Complex!----------------------
// constexpr int max(Pair<int>& p)
// {
//     return p.first > p.second ? p.first : p.second;
// }

// constexpr double max(Pair<double>&p) // overloaded function differs only by return type is (insufficient)
// {                                   // it must differ by the type of parameters and return value.
//     return p.first > p.second ? p.first : p.second;
// }

// Simpler
template <typename T>
constexpr T max(const Pair<T>& p)
{
    return p.first > p.second ? p.first : p.second;
}

// Good, but constrianed
// template <typename T, typename U>
// constexpr void print(const Pair_D<T,U>& p) // only match for (Pair_D) type, which is a limitation for this function
// {
//     std::cout << '[' << p.first << ", " << p.second << ']' << '\n';
// }

// more GERNERAL function template, we can print any type who contains first and second as its member
template <typename T>
constexpr void print(const T& p) // T can match any type as long as T gets two members.
{
    std::cout << '[' << p.first << ", " << p.second << ']' << '\n';
}

// or use standard lib's std::pair for printing Pair
template <typename T, typename U>
constexpr void print(const std::pair<T,U>& p)
{
    std::cout << '[' << p.first << ", " << p.second << ']' << '\n';
}

int main()
{
    constexpr Pair<int> pair_1{5, 6}; // we can specify the typename for instantiation 
    std::cout <<"The biggest number between "<<pair_1.first<<" and "<<pair_1.second<<" is "<< max(pair_1) << '\n';

    Pair<double> pair_2{8.8, 7.2};
    std::cout <<"The biggest number between "<<pair_2.first<<" and "<<pair_2.second<<" is "<< max(pair_2) << '\n';

    // typename T and typename U can be the same.
    [[maybe_unused]] Pair_D pair_0{1, 1}; // or just make the complier to figure it out
    print(Pair_D{1, 2.2}); // ref needs be const for passing in a temporary variable, or you can pass it by value
    print(Pair_D{1, 1});
    Pair_D pair_3{1, 2.2};
    print(pair_3); // can be used for Pair<T> or Pair_D<T, U>
    print(pair_1); // 
    print(Point{1, 1});

    std::pair<int,double> pair_std{1, 2.2}; // standard-lib

    return 0;
}
