//#define NDEBUG // `release` mode
#include "diy.h"

// assert before you run the program (compiler)
static_assert(sizeof(int) >= 4, "Int must be at least 4 Bytes"); 
// static_assert needs constexpr for conditions

int main()
{
    std::cout << "Please enter an number: ";
    int number{getInt()};

// #ifndef NDEBUG
    assert(number > 0 && "Input Error!"); // during debuging
// #endif

    if(number <= 0) // during releasing
    {
        std::cout << "Wrong Number!";
        std::exit(1); // terminate the program as error code 1
        // or throw an exception
    }    
    std::cout << number << " must be Postive";

    return 0;
}
