#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H
#include <vector>
void insertionSort(std::vector<int>& arr, std::size_t lo, std::size_t hi) 
{
    for (std::size_t i = lo + 1; i <= hi; ++i)
    {
        int key = arr[i]; // pop-out
        std::size_t j = i; // blank
        while (j > lo && arr[j - 1] > key) // when lo == 0, j >= lo will cause trouble
        {
            arr[j] = arr[j - 1]; // if the element before the blank is greater, move it to the right
            --j; // blank goes to the left
        }
        arr[j] = key; // when no element is greater than the element popped out before or we have reached the left edge,
                      //  fill the current position of blank with the popped value
    }
}

#endif
