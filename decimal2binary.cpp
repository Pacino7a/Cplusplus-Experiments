#include "diy.h"

int main()
{
    std::cout << "Please input an Integer: ";
    int input{getInt()};
    std::cout << input << " is (Binary): ";
    deci2Binar(input);

    return 0;
}
