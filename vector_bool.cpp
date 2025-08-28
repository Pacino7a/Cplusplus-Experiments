#include "diy.h"
#include <vector>

// vector<bool> is not recommended to use, because it does not hold Bool (bitset) and the way of using it is not simmilar with other type vectors
// vector<char> (bool) and the third-party (boost::dynamic_bitset) is recommended.
int main()
{
    std::vector<bool> vec_bl{true, false, true, false};
    for(auto elem:vec_bl)
        std::cout << elem << "  ";
    std::cout << '\n'
              << "The cost of bool Vector is: " << (sizeof(std::vector<bool>)) << " Bytes.\n"; // 40 Bytes, very costy

    return 0;
}
