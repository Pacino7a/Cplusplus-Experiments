#include <iostream>
#include <string>
#include <string_view>

constexpr std::string_view getQuantityPhrase(int number)
{
    if(number < 0)
        return "Negative";
    else
    {
        switch (number)
        {
            case 0:
                return "No";
            
            case 1:
                return "a Single";
            
            case 2:
                return "a Couple of";
            
            case 3:
                return "a Few";
            
            default:
                return "Many";
        }
    }
}

constexpr std::string_view getApplesPluralized(int number)
{
    return number == 1 ? "Apple" : "Apples";
}

int main()
{
    constexpr int maryApples{3};
    std::cout << "Mary has " << getQuantityPhrase(maryApples)
              << ' ' << getApplesPluralized(maryApples) << ".\n";

    std::cout << "How many apples do you have?\n";
    int num_Apples{};
    std::cin >> num_Apples;
    std::cout << "You have " << getQuantityPhrase(num_Apples)
              << ' ' << getApplesPluralized(num_Apples) << ".\n";

    return EXIT_SUCCESS;
}
