#include <iostream>
#include <vector>
#include <cassert>
#include "insertion_sort.h"
#include "random_s_class.h"
// This section shows QuickSort (Recursion)
// O(N*log(N))
constexpr std::size_t g_insertionCutoff{6}; // 5~15

std::size_t partition(std::vector<int>& array, std::size_t left, std::size_t right)
{
    std::size_t pivot{right}; // we make the right most element as the pivot
    --right; // and move the right edge

    for (;;)
    {
        for (;array[left] < array[pivot] && left <= pivot;) // move the left pointer firstly until the element is bigger than the pivot or it can't move anymore (arrived the real right edge)
        {
            ++left;
        }
        for (;array[right] > array[pivot] && right > left;) // move the right pointer until the element is smaller than the pivot or the two pointers have overlapped
        {               // there is no need for moving when (right <= left). which means the numbers before current position are all smaller than the pivot,
            --right;    // or we just at the left edge already.
        }

        if(left >= right) // if overlapping has happened
        {
            // After the two pointers have overlapped, which means we have found the real position of the pivot [--smaller--{PIVOT}--bigger--]
            // we swap the final left (the values before it are all smaller than the pivot) with the pivot
            // and because of the overlapping, we can confirm the values after the final left are bigger than the pivot
            // so this is make sense
            std::swap(array[pivot], array[left]);
            return left; // the final left position is the real pivot position, we need return it for keep sorting
        }
        else // otherwise, we didn't find the position yet, just handle the reverse situation
        {
            std::swap(array[left], array[right]);
        }
    }
    

}

void quickSort(std::vector<int>& array, std::size_t left, std::size_t right) // we use 2 indice (pointers) here
{
    // if(left >= right) // QUIT only if our partition's length <= 1, No need for sorting
    //     return;

    if(left + g_insertionCutoff >= right) // small array uses insertion sort
    {
        insertionSort(array, left, right);
        return;
    }

    std::size_t pivot{partition(array, left, right)}; // put one number to the right place and divide the array to 2 parts

    if(pivot > left)
        quickSort(array, left, pivot - 1); // keep sorting with the left part
    quickSort(array, pivot + 1, right); // and the right part
}

// Based on QuickSort
int quickFind(std::vector<int>& array, std::size_t position, std::size_t left, std::size_t right) // find the value in the Array[position] after it sorted
{
    if(left >= right) // final return, no room for dividing, this is the answer you want
        return array[left];

    std::size_t pivot{partition(array, left, right)};

    if(position > pivot) // if the value we are looking for is bigger than the pivot, it must be in the right side or doesn't exist
        return quickFind(array, position, pivot + 1, right); // partition for the right side
    else if(position < pivot) // smaller, look the left side
        return quickFind(array, position, left, pivot - 1);
    else
        return array[position]; // if we just figure real value of the position out directly, return the result,
                                // otherwise, waiting for the final return at the begining of this function
}

void quickSort3WAY(std::vector<int>& array, std::size_t left, std::size_t right) // the most efficient
{
    // if(left >= right) // final return, no room for dividing, this is the answer you want
    //     return;
    if(left + g_insertionCutoff >= right) // small array uses insertion sort
    {
        insertionSort(array, left, right);
        return;
    }

    // [---(<v)---|lt-1|---(==v)---|gt+1|---(>v)---]
    // Notice:
    // we can conform that the values before lt (Not include itself) are all smaller than the pivot
    // and the values after gt (Not include) are all greater than the pivot
    // the values between lt and gt (include) are all equal to the pivot

    // In 3WAY, we need 3 indices to control the result
    std::size_t lt{left};
    std::size_t gt{right};
    std::size_t i{left + 1};

    // Randomlization (Simple Example)
    // std::mt19937 gen{std::random_device{}()}; // generator
    // std::uniform_int_distribution<std::size_t> dist(left, right);
    // std::swap(array[left], array[dist(gen)]);
    
    std::swap(array[left], array[left + Random::getRandomIndex() % (right - left + 1)]); // get random pivot
    int value{array[left]}; // set pivot

    for (;i <= gt;)
    {
        if(array[i] < value) // if current value is smaller than the pivot, current value joins lt
        {
            std::swap(array[i++], array[lt++]); // lt's length increase 1, and current Index move to the next
        }
        else if(array[i] > value && gt > 0) // if current value is bigger than the pivot, current value joins gt
        {
            std::swap(array[i], array[gt--]); // gt's length increase 1(reversed). we don't increase i 
                                              // becasue current value has been update after swap with array[gt]
        }
        else
            ++i; // if the current value is equal to the pivot, move the cursor to the next position
    }

    // lt-1 and gt+1 is the REAL BORDER for smaller area and Bigger area, as we mentioned before
    // make sure the smaller area is valid
    if(lt > left) 
        quickSort3WAY(array, left, lt - 1);
    quickSort3WAY(array, gt + 1, right);
}

int main()
{
    // std::vector arr{7, 6, 5, 3, 2, 1, 4};
    // std::vector arr1{0, 5, 2, 1, 6, 3};
    // quickSort(arr, 0, std::size(arr)-1);
    // //  ~~^~~(Pre_Sort Array, left edge, right edge)
    // for(const auto num:arr)
    //     std::cout << num << ' ';
    // std::cout << '\n';
    // quickSort(arr1, 0, std::size(arr1)-1);
    // for(const auto num:arr1)
    //     std::cout << num << ' ';
    // std::cout << '\n';

    // std::vector arr3{0, 50, 20, 10, 60, 30};
    // std::size_t position{3};
    // assert(position < std::size(arr3));
    // std::cout << "Arr3[" << position << "] should be: " << quickFind(arr3, position, 0, std::size(arr3) - 1) << '\n';
    //                                                                     //----^--find the # smallest number in the array

    std::vector arr3{7, 5, 6, 3, 1, 2, 4, 2, 1, 4, 8, 9, 5, 2, 1, 4, 5, 6, 3, 2, 1, 9, 7, 8, 0};
    quickSort3WAY(arr3, 0, std::size(arr3)-1);
    for(const auto num:arr3)
        std::cout << num << ' ';
    std::cout << '\n';
    return 0;
}
