#include <iostream>
#include <print> //C++23
#include <format>   //C++20
#include <bitset>

int main()
{
    int x{20};
    // Convert the objects' output format
    std::cout << "Hexadecimal:" << std::hex << x << '\n';
    std::cout << "Octal:" << std::oct << x << '\n';

    // bitset
    // Set binary object and output them directly
    std::bitset<8> b1{0b1000'1001}; // which can be initialized by a value in other format - binary with prefix
    std::bitset<8> b2{0xC3};
    std::cout << "Bitset<8>:" << "b1: " << b1 << " " << "b2: " << b2 << '\n';

    // C++20 more flexiable
    // Output binary format
    std::cout << __cplusplus << '\n';
    std::cout << std::format("{:b}\n", 0b1010);
    std::cout << std::format("{:#b}\n", 0b1010); // keep the 0b-prefixed
    // Output Hexadecimal Octal Decimal
    std::cout << std::format("Hexadecimal:{:#x}, Decimal:{:#d}, Octal:{:#o}", 0b1010, 0b1010, 0b1010); 


    // C++23
    // std::println("{:b} {:#b}", 0b1010, 0b1010);

    return 0;
}
