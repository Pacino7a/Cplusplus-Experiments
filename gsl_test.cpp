#include <iostream>
#include <gsl/algorithm> // gsl: Guidelines Support Library
#include <gsl/byte>
#include <vector>


int main()
{
    std::cout << "Size_t: " << std::numeric_limits<std::size_t>::max() << '\n';
    std::cout << "GSL_Index: " << std::numeric_limits<gsl::index>::max() << '\n';

    std::vector arr1{1, 2, 3, 4, 5, 6};
    gsl::span arrview{arr1};
    for(const auto& ele:arrview)
        std::cout << ele << ' ';
    std::cout << '\n';
    return 0;
}
