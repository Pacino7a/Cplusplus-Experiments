#include <iostream>

bool isEqual(int, int);

int main()
{
    int x{};
    int y{};

    std::cout << "Enter an Integer: ";
    std::cin >> x;
    std::cout << "Enter another one: ";
    std::cin >> y;

    std::cout << std::boolalpha; // make 0 -> false and other -> true
    //std::cin >> std::boolalpha // Only accept true and false for input
    // Conversion
    //std::cout << std::noboolalpha // make false -> 0 and true -> 1.
    //To deactivate the statement above
    //std::cin >> std::noboolalpha // Default Setting (NOT necessary)
    std::cout <<" Are "<< x << " and " << y << " Equal? " << '\n';
    if(isEqual(x,y))
        std::cout << "EQUAL!" << std::endl;
    else
        std::cout << "NOT EQUAL!" << std::endl;

    return 0;
}

bool isEqual(int x, int y)
{
    return x == y;
}
