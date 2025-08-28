#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <string>
#include "diy.h"
#include "pair.h"
#include <utility>
#include <vector>
#include <list>
#include <span>
#include <unordered_map>
#include <unordered_set>

void doNothing(int &) {}
void print(double);

void printInt(int64_t x)
{
    std::cout << x << std::endl;
}
constexpr int add(int x, int y)
{
    return x + y;
}
consteval int add_eval(int x, int y)
{
    return x + y;
}
constexpr double division(double x, double y)
{
    return x / y;
}

constexpr bool isEven(std::int64_t number) // check whether the number is a Even
{
    return (number % 2 == 0) ? true : false;
    // return (number & 1) ? false : true;
}

void print(double x)
{
    std::cout << std::setprecision(12);
    std::cout << x << std::endl;
}

[[maybe_unused]] int g_x{1}; // global variable x

void static_test()
{
    for (int i = 0; i < 15; ++i)
    {
        [[maybe_unused]] static const int expensive{899};
        static int s_value{0}; // scope of static will not change, but the duration will
        s_value++;
        std::cout << "s:" << s_value << '\n';
    } // s_value will not be destroied here
    // the value will keep until the program ends
}

struct Foo
{
    std::pair<int, int> p1{1, 3}; // good
    // std::pair p2{1, 3}; // CTAD can't be used here, aka CATD doesn't work with non-static member initialization
};

template <typename T, typename U>
using Point = Pair<T, U>; // using Alias templates

template <typename T, typename U>
void print(const Point<T, U> &p) // needs specify the typename of (Alias) Class template when it is a Parameter
{
    std::cout << "First: " << p.first << ", " << "Second: " << p.second << '\n';
}

int return_c1() { return 1; }
int return_1()  { return 1; }

// unsigned index if we want size_type as the type of index
template <typename T>
void printArray(const std::vector<T> &arr)
{
    // typename keyword prefix required for dependent type, index's type is dependent type (traversal)
    for (typename std::vector<T>::size_type index{0}; index < arr.size(); ++index)
        std::cout << arr[index] << ' ';

    std::cout << '\n';
}

template <typename T>
void printArrayReverse(const std::vector<T> &arr)
{
    for (auto index{std::ssize(arr) - 1}; index >= 0; --index) // use signed int for loop is better than unsigned int
    {
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';
    }
    std::cout << '\n';
}

// we use this function when our index is an signed int.
template <typename T>
constexpr std::size_t toUZ(T value) // UZ is the suffix for literals of std::size_t
{
    assert((std::is_integral<T>() || std::is_enum<T>()) && "Only support Int and Enumerators for Trans.");
    return static_cast<std::size_t>(value);
}

// Signed Index
// using Index = int; // for some mid/small array
using Index = std::ptrdiff_t; // bigger than before, size_t's signed version (Recommended)

template <typename T>
class SignedArrayView
{
public:
    using Index = std::ptrdiff_t;

    SignedArrayView(T &arr)
        : m_array{arr}
    {
    }

    constexpr auto &operator[](Index index) { return m_array[static_cast<typename T::size_type>(index)]; }             // modify available (for non-const obj)
    constexpr const auto &operator[](Index index) const { return m_array[static_cast<typename T::size_type>(index)]; } // read only (for const obj)
    constexpr auto ssize() const { return static_cast<Index>(m_array.size()); }                                        // convert size_t(unsigned) to Index(signed), custom ssize()

private:
    T &m_array; // don't make a copy of an array
};

// template <typename T>
void spanPrint(std::span<int> span)
{
    for(auto ele:span)
        std::cout << ele * 2 << ' ';
    std::cout << '\n';
}

int main()
{
    // print(add(2, 3)); // Compile-time
    // print(add(x, y)); // Runtime

    // print(add_eval(2, 3)); // Fine
    // print(add_eval(x, y)); // Error

    // print(division(x, y)); // infinite
    // print(3^4); // 011 XOR 100 == 111 (7)
    // print(pow(1.3, 4.0)); // 3 ^ 4, not precise (rounding errors)
    // printInt(powint(70, 12)); // overflowed warning
    // printInt(powint(9223372036854773000, 1)); // base will be overflowed
    // printInt(powint(-2, 3));
    // printInt(pow(-2, 6));

    // std::cout << "Please enter an Integer: ";
    // int64_t number{};
    // std::cin >> number;
    // std::string_view check{(isEven(number)) ? " is an Even" : " is an odd"};
    // std::cout << number << check << '\n';

    // double dou{65};
    // long h{65};
    // int l{h};
    // int8_t i{65};
    // char c{i};

    // std::cout << c << '\n';

    // int there{0};
    // int here{1};
    // std::cout << std::boolalpha;
    // {
    //     int here{0};
    //     std::cout << "Is here? " << static_cast<bool>(here) << '\n';
    // }

    // std::cout << "Is here? " << static_cast<bool>(here) << '\n';

    // std::cout << (-2) * (-2) << '\n';

    // static_test();
    // static_test();

    // using namespace std;
    // cout << "hello world" << '\n';
    // int temp{};
    // cin >> temp;
    // cout << temp << '\n';

    // int i{0};
    // do
    // {
    //     std::cout << i << '\n';

    // } while (++i<5);

    // std::cout << "Please enter a number: " << '\n';
    // int x{};
    // std::cin >> x;

    // if(x>=0)
    // {
    //     if(x<21)
    //     std::cout << x << " is between 0 and 20.\n";
    //     else
    //     std::cout << x << " is greater than 20.\n";
    // }
    // else
    //     std::cout << x << " is negative.\n";

    // if(x<0)
    //     std::cout << x << " is negative.\n";
    // else if(x<21)
    //     std::cout << x << " is between 0 abd 20.\n";
    // else
    //     std::cout << x << " is greater than 20.\n";

    // constexpr double gravity{9.8};
    // // constexpr if
    // if constexpr(gravity==9.8) // evaluate in compile-time
    //     std::cout << "You are on the earth!\n";
    // else
    //     std::cout << "You must be an alien.\n";

    // constexpr int jump{2};
    // switch (jump)
    // {
    // case 1:
    //     std::cout << "One.\n";
    //     break;

    // default:
    //     break;
    // }

    // switch (jump)
    // {
    // case 1:
    //     //int here{1}; // initialization is not allowed here, but definition is fine
    //     int here; // share
    //     here = 0; // assign is allowed, but this statment will not share
    //     break;
    // case 2:
    //     std::cout<<std::boolalpha;
    //     std::cout << "here?" << static_cast<bool>(here);
    //     break;
    // case 3:
    // case 4:
    // case 5:
    // // std::cout is the first statement after all of these case labels
    // // case is not a statement, but just a label.
    //     std::cout << jump << " is a number.\n";
    //     break;

    // default:
    //     break;
    // }

    // goto
    // tryAgain:
    //     std::cout << "Please enter an Integer:\n";
    //     int temp{};
    //     std::cin >> temp;
    //     if(temp<0)
    //         goto tryAgain; // get back to the label
    // std::cout << "The valiad number is: " << temp << '\n';

    // int kay{};
    // for (int temp = -5;temp<0;)
    // {
    //     std::cout << "Please enter an Integer:\n";
    //     std::cin >> temp;
    //     kay = temp;
    // }
    // std::cout << "The valiad number is: " << kay << '\n';

    // Point<int, int> vertex_0{1, 2}; // before C++20
    // Point vertex_1{1.5, 1.3}; // using Point to replace Pair (Alias template deduction)
    // print(vertex_1);

    // Pair pair_1{1, 2.2}; // Okay in (C++20), Error in (C++17)
    // Pair pair_2; // default template arguments type (int)
    // print(pair_1);
    // std::cout << max(pair_1) << '\n';

    // std::pair<int, int> pair_s{1, 1}; // specific
    // std::pair pair_d{1, 1}; // deduced
    // std::pair pair_f{1.3f, 1.4f}; // we can use literals suffixes to change the duduced type
    // std::pair pair_u{1u, 2u};

    // std::string sayhello{"helloworld"};
    // std::cout << sayhello << '\n';
    // cutString(sayhello,static_cast<size_t>(5), static_cast<size_t>(5));
    // std::cout << sayhello << '\n';

    // std::string saw{"I saw a red car yesterday."};
    // std::cout << saw << '\n';
    // saw.replace(8, 3, "blue"); // you can check the CPPREFERENCE for more information
    // std::cout << saw << '\n';

    // std::vector arr{ 9, 7, 5, 3, 1 };

    // // printArray(arr);
    // // printArrayReverse(arr);
    // // auto length{static_cast<Index>(arr.size())};
    // auto length{std::ssize(arr)};
    // for (auto i{length - 1}; i >= 0; --i) // Index --> auto because we got std::ssize() C++23
    // {
    //     std::cout << i << ',' << arr[toUZ(i)] << '\n'; // Index (std::ptrdiff_t) works fine here
    // }

    // SignedArrayView arr_v{arr};
    // const SignedArrayView arr_v_const{arr};
    // arr_v[0] = 0;
    // //arr_v_const[0] = 0; // can't modify this
    // for (auto i{arr_v.ssize() - 1}; i >= 0; --i)
    // {
    //     std::cout << i << ',' << arr_v[i] << '\n'; // we don't need to use toUZ() anymore
    // }
    // std::cout << arr[0]; // change took place in Original Array

    // std::cout << "Double :" << -7.04<< ", Int: " << static_cast<int>(-7.04) << '\n';

    // int a{1}; // ori
    // int &b{a}; // ref
    // auto c{b}; // copy
    // c = 7; // assign the copy
    // b = 2; // you want modify a you can only modify itself or its reference directly
    // std::cout << a << ',' << b << ',' << c << '\n';
    // std::string hello{"hello "};
    // std::string world{"world"};
    // std::cout << hello + world << '\n';

    // std::vector a{1, 2, 3, 4, 5, 6, 7, 8};
    // spanPrint(a);
    // for(auto ele:a)
    //     std::cout << ele << ' ';
    // std::cout << '\n';

    // std::vector<int> temporay{1, 2, 3};
    // std::list temporay_list{1, 2, 3};
    // std::unordered_set set{1, 2, 3};
    // set.erase(1);

    // std::vector<int> k{};
    // k.emplace_back(1);
    // for(const auto ele:k)
    //     std::cout << ele << ' ';

    std::vector temp{1,2,3};
    for(auto num:temp)
        std::cout << num << ' ';
    std::cout << '\n';
    std::make_heap(temp.begin(), temp.end());
    for(auto num:temp)
        std::cout << num << ' ';
    std::cout << '\n';

    std::cout << &temp << ", " << &temp[0] << '\n';
    std::cout << 0x84c0 << '\n';
    std::string number{1};
    std::cout << number << '\n';
    return 0;
}
