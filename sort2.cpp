#include "diy.h"

int main()
{
    int x{7};
    int y{5};

    std::cout << "x y\n";
    std::cout << x << ' ' << y << '\n';
    sort2(x, y);
    std::cout << x << ' ' << y << '\n';
    sort2(x, y);
    std::cout << x << ' ' << y << '\n';

    return 0;
}
