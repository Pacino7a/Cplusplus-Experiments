#include "diy.h"
#include <utility>

// selection sort
int main()
{
    int array[]{ 30, 50, 20, 10, 40 };
    std::cout << "Original: ";
    for(const auto& num:array)
        std::cout << num << ' ';
    std::cout << '\n';
    constexpr int length{static_cast<int>(std::size(array))};

    for (int startIndex{0}; startIndex < length - 1; ++startIndex)
    {
        int smallest{startIndex};
        for (int currentIndex{startIndex + 1}; currentIndex < length;++currentIndex)
        {
            if(array[currentIndex] < array[smallest])
                smallest = currentIndex;
        }
        std::swap(array[startIndex], array[smallest]);
    }
    std::cout << "Sorted: ";
    for(const auto& num:array)
        std::cout << num << ' ';
    std::cout << '\n';
    
    return 0;
}
