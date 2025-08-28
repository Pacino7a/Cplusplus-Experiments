#include "diy.h"

int main()
{
    // void ptr can be initialized with a nullptr
    void *ptr{nullptr};
    // number
    int value{10};
    ptr = &value;
    std::cout << *static_cast<int *>(ptr) << '\n';
    // string
    std::string hello{"hello\n"};
    ptr = &hello;
    std::cout << *static_cast<std::string*>(ptr) << '\n';
    // C_style string
    char world[]{"world\n"};
    ptr = world;
    std::cout << static_cast<char *>(ptr) << '\n';
    // Test (No Warning, but very dangerous here)
    ptr = &value; // int*
    std::cout << *static_cast<double *>(ptr) << '\n'; // we indirect int* as a double*, which is a undefined behavior

    return 0;
}
