#include <iostream>
#include <array>
// find the existence of same element in the Array

int main()
{
    constexpr std::array arr{std::to_array({1, 3, 7, 4, 5, 7, 3})};

    // O(N^2) --> 2 layers of for-loop
    for (size_t i = 0; i < std::size(arr); ++i)
    {
        for (size_t j = 0; j < std::size(arr); ++j)
        {
            if(i != j && arr[i] == arr[j])
            {
                std::cout << "There are two " << arr[i] << " in your arr!\n";
            }
        }
    }
    
    // O(N) --> one layer of for loop (better than N^2)
    std::array<std::string, 100> existingNumbers; // it will cost us a lot of memory if the range of numbers in the array is very wide
    existingNumbers.fill("NULL"); // memory space trades time efficiency
    bool repeated{false};
    for (size_t i = 0; i < std::size(arr); ++i) // the worst case for finding the repeating element is going through the whole arr and not found aka.O(N)
    {
        if(existingNumbers[static_cast<std::size_t>(arr[i])] == "NULL") // if the number is new
            existingNumbers[static_cast<std::size_t>(arr[i])] = "R"; // we mark it down
        else // otherwise, it repeated
        {
            std::cout << "There are two " << arr[i] << " in your arr!\n";
            repeated = true;
        }
    }
    if(!repeated)
        std::cout << "Your array has no repeat element.\n";
    return 0;
}
