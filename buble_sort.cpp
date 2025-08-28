#include "diy.h"
#include <utility>

// Bubble_sort
int main()
{
    int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    constexpr int length{static_cast<int>(std::size(array))};
    std::cout << "Original: ";
    for(const auto& num:array)
        std::cout << num << ' ';
    std::cout << '\n';
    for (int sorted{0};sorted < length - 1;++sorted) // sorted from 0 so we need length - 1 ( 0~7 if length == 9, aka Up to 8 iterations)
    {
        bool swapped{false};
        // Notice the bubbleIndex to prevent it from going out of bound
        // Max of currentIndex == 7 (< length(9) - 1 - sorted(0)) and bubbleIndex == 8
        for (int currentIndex{0}, bubbleIndex{1}; currentIndex < length - 1 - sorted ; ++currentIndex,++bubbleIndex)
        { 
            if(array[currentIndex] > array[bubbleIndex]) // Ascending(>) and Descending(<) (focus on the second operand)
            {
                std::swap(array[currentIndex], array[bubbleIndex]);
                swapped = true;
            }
        }

        if(!swapped) // if we haven't swapped, we're done early. Quit
        {
            std::cout << "Early Termination on iteration " << ++sorted <<'\n'; // increase 1 because we initialized sorted from 0, but this is #Iteration
            break;
        }
    }
    std::cout << "Sorted: ";
    for(const auto& num:array)
        std::cout << num << ' ';
    std::cout << '\n';


    return 0;
}
