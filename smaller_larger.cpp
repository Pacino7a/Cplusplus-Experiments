#include <iostream>
#include <utility> // swap
#include "diy.h"


int main()
{
    std::cout << "Please enter 2 Integer: ";
    int smaller{getInt()};
    int larger{getInt()};
    
    // if with block, temp is a localVariable
    if (smaller > larger)
    {
        // same
        std::swap(smaller, larger);

        // int temp{larger};
        // larger = smaller;
        // smaller = temp;

    }// temp will be destoried here

    std::cout << "Smaller:" << smaller << " " << "Larger:" << larger << std::endl;
    return 0;
}
