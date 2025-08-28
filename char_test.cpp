#include <iostream>

int main()
{
    std::cout << "Hello\bworld\n"; // Backspace
    std::cout << "Hello\rWorld\n"; // Back to the beginning of this line
    std::cout << "Hello\tWorld\n"; // Horizontal Tab
    std::cout << "Hello\vWorld\n"; // Vertical Tab
    std::cout << "\'Hello World\'\n"; // 'Hello World'
    std::cout << "\"Hello World\"\n"; // "Hello World"
    std::cout << "\\Hello World\\\n"; /* \Hello World\ */
    std::cout << "141(Octal) is char '\141'\n"; // Transform \(141)(Octal) to a
    std::cout << "61(Hex) is char '\x61'\n"; // Transform \x(61) to a

    // explicit type conversion via static_cast
    std::cout << static_cast<int>(5.5) << '\n'; // Transform a double to a int
    std::cout << static_cast<char>(98) << '\n'; // int -> char

    /* Int and Unsigned Int */
    int s{-1}; // int (-1)
    unsigned int u{4294967295}; // max of uint
    
    // signed int <--> unsigned 
    // Such conversion will get overflowed when the int is nagative
    // or the uint is the maximum

    // unsigned-int gets 4 Bytes whose range is [0, 4294967295]
    // The range of int is [-2147483648,2147483647]
    std::cout << static_cast<unsigned int>(s) << '\n'; 
    std::cout << static_cast<int>(u) << '\n';
    // The reason why this happen is The range cannot be aligned
    // and Signed-int is stored as complementary code format (inverse order)
    // <int>(-1) --> 1111 1111 1111 1111 1111 1111 1111 1111
    // <int>(-2147483648) --> 1000 0000 0000 0000 0000 0000 0000 0000
    // it makes unsigned's max <--> int (-1)

    // int8_t uint8_t corresponding char and usigned char
    std::int8_t myInt{65};
    std::cout << myInt << '\n'; // You will get a char, instead of an int

    std::int8_t notInt{};
    std::cin >> notInt; // The type of your input will be char

    return 0;
}
