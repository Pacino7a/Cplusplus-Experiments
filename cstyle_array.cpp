#include "diy.h"
#include <array> // using std::array by including this
#include <vector>

constexpr int perfectSquare[]{0, 1, 4, 9};

int main()
{
    int testScore[30]{};

    for(int& score:testScore)
    {
        static int i{1};
        score += i;
        ++i;
        std::cout << score << ' ';
    }
    std::cout << '\n';

    constexpr std::size_t length{20}; // C-style array's length should be a constexpr value (std::size_t)
    [[maybe_unused]] int number_classes[length]{}; // variable-length C-Style Array is not valid in C++

    const int array[]{9, 8, 2, 4, 3}; // Inferred length by the compiler (list initialization is recommended)
    int signed_index{3};
    std::cout << array[signed_index] << '\n'; // we can use a signed-int value to index the element of an array

    std::vector vec{1, 2, 3, 4};
    vec = {2, 3, 4, 5}; // assignment ok for std::vector
    std::array arr{1, 2, 3, 4};
    arr = {7, 8, 3, 2}; // assignment ok for std::array
    int src[]{1, 2, 3};
    int dest[]{4, 5, 6};
    // dest = src; // not work for C-style array(right value)
    std::copy(std::begin(src), std::end(src), std::begin(dest)); // copy values from src to dest
    for(const auto ele:dest)
        std::cout << ele << ' ';
    std::cout << '\n';

    [[maybe_unused]] constexpr int quiz1[3]{}; // same with constexpr std::array<int,3> quiz1{};

    for (;;)
    {
        std::cout << "Please enter a value between 0~9 or enter -1 to Quit: ";
        int user_int{getInt()};
        if(user_int == -1)
            break;
        if(user_int < 0 || user_int > 9)
        {
            std::cout << "Your input is out of range (0~9)!\n";
            continue;
        }
        bool isPerfect{false};
        for (const int ele:perfectSquare)
        {
            if(user_int == ele)
            {
                isPerfect = true;
                std::cout << user_int << " is a perfect Square Number in the range of (0~9).\n";
                break;
            }
        }
        if(isPerfect) continue;
        std::cout << user_int << " is NOT a perfect Square Number in the range of (0~9).\n";
    }

    return 0;
}
