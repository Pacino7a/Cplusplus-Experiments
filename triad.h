#ifndef TRIAD_H
#define TRIAD_H

template <typename T>
struct Triad
{
    T first{};
    T second{};
    T third{};
};

// deduction guide for Traid (C++17)
// if you define this
// the compiler will use this guide with the Highest Priority
template <typename T>
Triad(T, T, T) -> Triad<T>;

template <typename T>
void printTriad(Triad<T>& triad) // we can change `triad<T>` to T for all kinds of class type which contain three Same type of members
{
    std::cout << '[' << triad.first << ", " << triad.second << ", " << triad.third << ']' << '\n';
}


#endif
