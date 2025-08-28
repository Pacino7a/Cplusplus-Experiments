#include "diy.h"

void foo(int bravo)
{
    std::cout << "Bravo " << bravo << '\n';
}

int goo(int bravo)
{
    std::cout << "Bravo " << bravo << '\n';
    return 7;
}

void SelectionSort(int* array, int size, bool (*comparation)(int, int))
{
    if (!array)
        return;

    // Step through each element of the array
    for (int startIndex{ 0 }; startIndex < (size - 1); ++startIndex)
    {
        // bestIndex is the index of the smallest element we've encountered so far.
        int bestIndex{ startIndex };

        // Look for smallest element remaining in the array (starting at startIndex+1)
        for (int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex)
        {
            // If the current element is smaller than our previously found smallest
            if (comparation(array[bestIndex],array[currentIndex])) // COMPARISON DONE HERE
            {
                // This is the new smallest or largest number for this iteration
                bestIndex = currentIndex;
            }
        }

        // Swap our start element with our smallest element
        std::swap(array[startIndex], array[bestIndex]);
    }
}

bool ascending(int a, int b)
{
    return a > b; // recording the smallestIndex if the second is smaller than the first one for swapping ([3][1] --> [1][3])
}

bool descending(int a, int b)
{
    return a < b; // recording the largestIndex ([1][3] --> [3][1])
}

int main()
{
    void (*fcnPtr)(int){foo}; // function's pointer (which only accept the function with an int parameter returns nothing)
    std::cout << "we need Bravo here: ";
    fcnPtr(6); // like an alias for function
    int (*fcnPtr_int)(int){goo};
    std::cout << fcnPtr_int(7) << '\n';
    fcnPtr = nullptr;

    int array[]{3, 5, 6, 2, 1, 7, 4};
    SelectionSort(array, std::size(array), descending);
    assert(array != nullptr);
    for (std::size_t i{0};i<std::size(array);++i)
    {
        std::cout << array[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}
