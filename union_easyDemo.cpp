#include <iostream>

union DemoUnion
{
    int a;
    int b;
    int c;
    char d;

    void hello() { std::cout << "helloWorld.\n"; }
};

int main()
{
    DemoUnion union_{1}; // A single move affects the entire body
    std::cout << union_.a << ' ' << union_.b << ' ' << union_.c << ' ' << union_.d << '\n';
    union_.d = 'h';
    std::cout << union_.a << ' ' << union_.b << ' ' << union_.c << ' ' << union_.d << '\n';
    union_.hello();

    return 0;
}
