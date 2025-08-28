#include "diy.h"
#include <array>
#include <vector>

template <typename T, std::size_t N>
struct array; // This is what std::array's definition looks like

// when you want pass an array, you need pass what the type of its element is and the number of its element at where the parameter was defined
void printAfixedArray(const std::array<int,8>& arr) // this function is very boring that you can use this only when you get an array with 8 int elements
{ // more horrible thing is that we can't use CTAD here :(
    std::cout << "The length of this array is " << arr.size() << '\n';
    for(auto ele:arr)
        std::cout << ele << ' ';
    std::cout << '\n';
}

// with a template we can pass an array with flexiable length and various type (CAUTION: Length's type can only be sizet)
// C++20 and beyond can use auto to replace non-type template parameter's type
template <typename T, auto Length> // without this non-type template parameter, array's length is not a constexpr 
void printArray_BP(const std::array<T, Length> &arr)
{
    static_assert(Length != 0 && "The length of array should be greater than or equal to Zero.\n");
    constexpr auto len{std::size(arr)};
    std::cout << "The length of This array is " << len << "\nThe elements follows: (";
    bool first{true};
    for(const auto& elem:arr)
    {
        if(first)
        {
            std::cout << elem;
            first = false;
        }
        else
            std::cout << ", " << elem;
    }
    std::cout << ")\n";
}

template <typename T, auto N>
std::array<T,N> getArray() // will make a copy of the array and all its elements And we must explicitly supply the template arguments
{
    std::array<T,N> arr{};
    for (typename std::array<T,N>::size_type index{0}; index<N; ++index)
    {
        T value{};
        for (;;)
        {
            std::cout << "Please enter a value: ";
            std::cin >> value;
            if(!std::cin)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                continue;
            }
            break;
        }
        arr[index] = value;
    }
    return arr; // return by value (maybe expensive)
}

// By out-parameter
template <typename T, auto N>
void getArray_OutPara(std::array<T,N>& arr) //
{
    for (typename std::array<T,N>::size_type index{0}; index<N; ++index)
    {
        T value{};
        for (;;)
        {
            std::cout << "Please enter a value: ";
            std::cin >> value;
            if(!std::cin)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                continue;
            }
            break;
        }
        arr[index] = value;
    }
}
int main()
{
    [[maybe_unused]] std::array array_1{1}; // CTAD <int,1>  (Best Practice)
    [[maybe_unused]] std::array<double, 2> array_2{}; // list initializer - value initialization for all elements in the array

    // Right Value
    [[maybe_unused]] const std::vector vec{1, 2, 3};
    
    [[maybe_unused]] const std::array array_3{1, 2, 3};
    [[maybe_unused]] constexpr std::array array_4{1, 2, 3, 4, 5}; // define array as constexpr whenever possible. If you don't need `constexpr`, use vector instead.
    // constexpr std::array_5<int> array_5{1, 2, 3, 4, 5}; // CTAD not work here (omit array's length)
    [[maybe_unused]] constexpr auto array_5{std::to_array<int>({1, 2, 3, 4, 5})}; // But we can do that by using std::to_array(). (it is possible to omit the array length of a std::array)
    // std::to_array is more expensive than common initialization and should be avoided when the array will be created many times
    [[maybe_unused]] constexpr auto array_6{std::to_array<short>({1, 2, 3, 4, 5})}; // should only be used in cases where the type can’t be effectively determined from the initializers
    
    // all you need is using std::array like these, constexpr is necessary if you choose to use array
    [[maybe_unused]] constexpr std::array best_practice{1, 2, 3, 4, 5, 6}; // <<------ 1
    [[maybe_unused]] constexpr auto best_practice_2{std::to_array<short>({1, 2, 3, 4, 5, 6})}; // <<------ 2

    // the length of array is std::size_t too, so the type of length must be a constexpr or a size_t
    [[maybe_unused]] constexpr auto x{1};
    [[maybe_unused]] constexpr auto x_t{1UZ}; // <---- This is a std::size_t, suffix for deduction
    // std::array's size_type is always std::size_t

    // get the length of array
    std::cout << "Array_4's Length is:" << array_4.size() << "or" << std::size(array_4) << "or" << std::ssize(array_4) << '\n';
    // the length of an array is always a constexpr whether it is a constexpr
    [[maybe_unused]] constexpr auto length_unc{std::size(array_1)};
    [[maybe_unused]] constexpr auto length_cons{std::size(array_4)};
    
    // when you want to index an array, you need use `[]` or `at()` too (same with vector)
    [[maybe_unused]] auto value1 = array_4[1]; // constexpr -> std::size_t (not narrowing conversion)
    int a{1};
    int b{a};
    [[maybe_unused]] auto value2 = array_4[b]; // non-constexpr may causes narrowing conversion
    // at() will check your index while runtime
    [[maybe_unused]]  constexpr auto value3 = std::get<3>(array_4);  // check the bound while compiling time (The index must be a constexpr)

    constexpr std::array array_i{1, 2, 3, 4};
    constexpr std::array array_d{1.2, 2.2, 3.2, 4.2};
    constexpr std::array array_char{'h', 'e', 'l', 'l', 'o'};
    // constexpr std::array<int,0> array_empty{}; // we can create an empty array
    printArray_BP(array_i);
    printArray_BP(array_d);
    printArray_BP(array_char);
    // printArray_BP(array_empty); // static assert abort

    std::array arrayfromuser{getArray<double, 3>()}; // return by value
    printArray_BP(arrayfromuser);
    std::array<int, 5> arrayfromuser_2{};
    printArray_BP(arrayfromuser_2);
    getArray_OutPara(arrayfromuser_2); // return by out-parameter (reference)
    printArray_BP(arrayfromuser_2);

    return 0;
}



