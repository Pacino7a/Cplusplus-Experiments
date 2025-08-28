#include "diy.h"

void doubleNumber(int& num)
{
    num *= 2;
}

constexpr int arr_c[]{1, 2, 3, 4, 5};

int main()
{
    std::array arr{1, 2, 3, 4, 5};
    
    std::for_each(arr.begin(), arr.end(), doubleNumber); // arr[begin]~arr[end-1] is valiad, aka [first, last)
    std::ranges::for_each(arr, doubleNumber); // don't need begin and end anymore by using <ranges>
    for(auto i:arr)
        std::cout << i << ' ';
    std::cout << '\n';

    auto len{std::size(arr_c)};
    auto ptr_start{arr_c};
    auto ptr_end{arr_c + len}; // <-- This is out of the bound (array.end() is same with this)
    std::cout << *ptr_start << ' ' << *(arr.end()-1) << ' ' << *(ptr_end-1) << '\n';

    return 0;
}
