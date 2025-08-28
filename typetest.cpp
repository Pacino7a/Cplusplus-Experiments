#include <iostream>
#include <cstdint> // size_t 

int main()
{
    std::size_t typesize_size_t{sizeof(size_t)};
    std::size_t typesize_char{sizeof(char)};
    std::size_t typesize_short{sizeof(short)};
    std::size_t typesize_int{sizeof(int)};
    std::size_t typesize_long{sizeof(long)};
    std::size_t typesize_longlong{sizeof(long long)};
    std::size_t typesize_float{sizeof(float)};
    std::size_t typesize_double{sizeof(double)};
    std::size_t typesize_longdouble{sizeof(long double)};
    std::size_t typesize_int_16{sizeof(std::int16_t)};
    std::size_t typesize_int_fast_16{sizeof(std::int_fast16_t)};
    std::size_t typesize_int_least_16{sizeof(std::int_least16_t)};
    std::size_t typesize_bool{sizeof(bool)};
    std::size_t typesize_nullpointer{sizeof(nullptr)};

    std::cout << "Size of char: " << typesize_char << " Byte." << '\n'
              << "Size of short: " << typesize_short << " Bytes." << '\n'
              << "Size of int: " << typesize_int << " Bytes." << '\n'
              << "Size of long: " << typesize_long << " Bytes." << '\n'
              << "Size of longlong: " << typesize_longlong << " Bytes." << '\n'
              << "Size of float: " << typesize_float << " Bytes." << '\n'
              << "Size of double: " << typesize_double << " Bytes" << '\n'
              << "Size of long double: " << typesize_longdouble << " Bytes." << '\n'
              << "Size of int_16: " << typesize_int_16 << " Bytes" << '\n'
              << "Size of int_fast16: " << typesize_int_fast_16 << " Bytes" << '\n'
              << "Size of int_least16: " << typesize_int_least_16 << " Bytes" << '\n'
              << "Size of size_t: " << typesize_size_t << " Bytes." << '\n'
              << "Size of nullpointer: " << typesize_nullpointer << " Bytes." << '\n'
              << "Size of bool: " << typesize_bool << " Bytes." << '\n'
              << std::endl;

    return 0;
}
