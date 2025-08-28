#include <iostream>
#include <cassert>
#include <cmath>
#include <numeric>

int binarySearch_Iterative(const int* array, int target, int min, int max)
{
    assert(array); // make sure the array exists

    for (int midpoint{};;)
    {
        if(min == max) // check whether the search is on the edge
        {
            return (array[max] == target) ? max : -1; // if it still failed to find the value, return -1, otherwise return the index of the target
        }
        if(min > max) // it seems this is not going to happen (if we didn't have the first judgement, min will increase because of `midpoint + 1`)
        {
            return -1;
        }

        midpoint = std::midpoint(min, max);
        // int midpoint{((max - min) / 2) + min}; // old school
        if(target == array[midpoint])
            return midpoint;
        else if(target < array[midpoint]) // if the target is smaller
        {
            max = midpoint - 1; // we giong to look up the first half
        }
        else // if the target is bigger
        {
            min = midpoint + 1; // we going to look up the second half
        }
    }
}

int binarySearch_Recursion(const int* array, int target, int min, int max) // Recursion
{
    if(min == max) // stop recursion
    {
        return (array[max] == target) ? max : -1;
    }
    if(min > max) // stop recursion
    {
        return -1;
    }
    int midpoint{std::midpoint(min, max)};
    if(target == array[midpoint])  // stop recursion
        return midpoint;
    else if(target < array[midpoint])
    {
        max = midpoint - 1;
        return binarySearch_Recursion(array, target, min, max);   // if we can't find the target at this time, we change the bound and let new me to take it over
    }                                                   // the value it returns is ours too.
    else
    {
        min = midpoint + 1;
        return binarySearch_Recursion(array, target, min, max);
    }
}

int main()
{
    // std::binary_search(), return true when it found the target

    constexpr int array[]{ 3, 6, 8, 12, 14, 17, 20, 21, 26, 32, 36, 37, 42, 44, 48 };

    // We're going to test a bunch of values to see if the algorithm returns the result we expect

    // Here are the test values
    constexpr int testValues[]{ 0, 3, 12, 13, 22, 26, 43, 44, 48, 49 };

    // And here are the results that we expect for those test values
    int expectedResult[]{ -1, 0, 3, -1, -1, 8, -1, 13, 14, -1 };

    // Make sure we have the same number of test values and expected results
    static_assert(std::size(testValues) == std::size(expectedResult));

    int numTestValues { std::size(testValues) };
    // Loop through all of the test values
    for (int count{ 0 }; count < numTestValues; ++count)
    {
        // See if our test value is in the array
        int index{ binarySearch_Iterative(array, testValues[count], 0, static_cast<int>(std::size(array)) - 1) };
        // If it matches our expected value, then great!
        if (index == expectedResult[count])
             std::cout << "test value " << testValues[count] << " passed!\n";
        else // otherwise, our binarySearch() function must be broken
             std::cout << "test value " << testValues[count] << " failed.  There's something wrong with your code!\n";
    }

    return 0;
}
