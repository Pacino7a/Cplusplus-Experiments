#include <iostream>
#include <string>

int main()
{
    // std::cout<<"Hello,
    // world";
    // The statement above is not allowed (Error)

    // But you can use the method below to seperate each Word in a Sentence.
    // Good for a long sentence.
    std::cout
        << "Hello! "
        << "World"
        << "\n"
        << "A New way here."
        << std::endl;

    std::cout << "Way"
                 "Two"
                 "\n";

    std::cout << 3 + 4 
        + 5 + 6 
        * 7 * 8
        <<std::endl;

    int x{2};
    // x = 5 assigns 5 to x and return x
    // after that the original statement becomes
    // std::cout << x
    // So it will print the value of x
    std::cout << (x = 5);

    return 0;

}
