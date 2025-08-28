#include "diy.h"
#include <iostream>
#include <array>
#include <vector>
#include <functional> // reference_warpper
struct House
{
    double area_squaremeters{};
    int bed_room{};
    int living_room{};
};
template <typename T>
void printVector(const std::vector<T>& vec)
{
    for(const auto& ele:vec)
        std::cout << ele << ' ';
    std::cout << '\n';
}

int main()
{
    std::array<House, 3> house_inf{};
    house_inf[0] = {99.8, 2, 1};
    house_inf[1] = {110.2, 3, 1};
    house_inf[2] = {127.3, 3, 2};
    for(const auto& house:house_inf)
    {
        std::cout << "The area of the house: " << house.area_squaremeters << " m^2"
                  << "\nGets " << house.bed_room << " bedroom(s) and " << house.living_room << " living-room(s).\n";
    }

    [[maybe_unused]] std::array house_temp{House{101, 2, 1}, House{95, 2, 1}}; // deduction (use this)
    [[maybe_unused]] std::array<House, 2> house_new{House{99, 2, 1}, {77, 2, 3}}; // declaration is needed at the first element place.
    [[maybe_unused]] std::array<House, 2> house_temp2{{{101, 2, 1}, {95, 2, 1}}}; // The first {} for initializing the array object, the second for initializing elements(c-style array) (or use this)
    [[maybe_unused]] constexpr std::array elision_brace{1, 2, 3, 4}; // the second {} has been elision because those elements can be put into Cstyle array naturally

    int a{1};
    int b{2};
    int c{3};
    int &x{a};
    int &y{b};
    x = c;

    std::vector v1{a, b}; // can hold type of value
    std::vector v2{&a, &b}; // or a pointer
    printVector(v1);
    printVector(v2);

    [[maybe_unused]] std::array a1{&a, &b}; // set of pointers
    // std::vector<int &> v3{x, y}; // error
    [[maybe_unused]] std::array v3{x, y}; // array<int,2>

    std::array<std::reference_wrapper<int>, 3> arr_ref{a, b, c}; // int->int& (all the elements are reference of int) A set of reference of variables
    arr_ref[0].get() = 7; // modify `a` (get() for modifying the referenced obj)
    std::cout << arr_ref[0] << ' ' << a << '\n';

    int test{1};
    std::reference_wrapper<int> test_ref{test};
    std::reference_wrapper x1{test};
    auto t_ref{std::ref(test)}; // create a reference warpper of test in short cut (recommended)
    auto t_cref{std::cref(test)}; // const reference (recommended)
    t_ref.get() = 8; // use get() here for modifying the object
    // t_cref.get() = 9;
    auto x_ref{std::reference_wrapper{test}};

    return 0;
}
