#include "diy.h"
#include <array>


constexpr void printCstr(const char* begin_s,const char* end_s) // you can print a C-style like this one
{
    for (;begin_s != end_s; ++begin_s) 
    {
        std::cout << *begin_s;
    }
    std::cout << '\n';
}

constexpr void printCstrReverse(const char* begin_s,const char* end_s)
{
    --begin_s;
    for (;begin_s >= end_s; --begin_s)
    {
        std::cout << *begin_s;
    }
    std::cout << '\n';
}

int main()
{
    int test[]{0, 1, 2, 3, 4, 5, 6};

    const auto ptr = test;

    std::cout << &ptr[1] << ' ' << &1 [ptr] << '\n';
    std::cout << ptr[1] << ' ' << 1[ptr] << '\n'; // *(ptr + 1) and *(1 + ptr), lead same result (funny one)

    const char cstylestr[]{"hello, world"}; // 7 valid + 1 terminator
    // std::cin.get(cstylestr, std::size(cstylestr));
    // std::cout << "Your enter is " << cstylestr << '\n';
    const char *cStrBegin{cstylestr};
    const char *cStrEnd{cstylestr + std::size(cstylestr)}; // Length of the whole str array, maybe longer than the valid string's length
    printCstr(cStrBegin, cStrEnd);
    printCstrReverse(cStrEnd, cStrBegin);

    auto s1{"hello"};
    s1 = "Jack"; // this is ok. Constrain on the single character not the whole object
    auto *s2{"hello"};
    auto &s3{"hello"}; // deduced as const char normally (this is a reference of C-style string array)
    std::cout << s1 << ' ' << s2 << ' ' << s3 << '\n';
    // s1 is the adress of the first element ('h') and s2 is the adress as well 
    // s3 is the reference of the C-style string array (all of the above are const)
    std::cout << static_cast<const void *>(s2) << '\n'; // if you want to print the adress of C-style String, use const void* to convet.

    constexpr std::string_view s_best{"helloworld"};
    // s_best = "Hello, World.";
    std::cout << s_best << '\n';

    char str[]{"CanWeChangeThis?"};
    // str = "NO";

    return 0;
}
