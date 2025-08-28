#ifndef PAIR_H
#define PAIR_H

// CTAD demo here
template <typename T = int, typename U = int> // default int
struct Pair
{
    T first{0};
    U second{0};
};

// deduction guide to help compiler how to duduce the template arguments
// needed in C++17 Only
template <typename T, typename U>
Pair(T, U)->Pair<T, U>;

template <typename T, typename U>
constexpr auto max(const Pair<T,U>& p)
{
    return p.first > p.second ? p.first : p.second;
}

template <typename T>
constexpr void print(const T& p) 
{
    std::cout << '[' << p.first << ", " << p.second << "]\n";
}


#endif
