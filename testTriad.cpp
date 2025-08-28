#include "triad.h"
#include <iostream>

int main()
{
    Triad t1{1, 2, 3};
    printTriad(t1);

    Triad t2{1.2, 3.4, 5.6};
    printTriad(t2);

    return 0;
}
