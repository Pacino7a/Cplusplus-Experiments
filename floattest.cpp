#include <iostream>
#include <limits>
#include <iomanip>

int main()
{
    //check for IEEE-754
    std::cout << std::numeric_limits<float>::is_iec559 << '\n';
    std::cout << std::numeric_limits<double>::is_iec559 << '\n';
    std::cout << std::numeric_limits<long double>::is_iec559 << '\n';

    // 6 significant digits (Because float's precision is 6 )
    std::cout << 987.654321f << '\n';
    std::cout << 0.0000987654321f << '\n';

    // Output manipulator for changing Precision
    std::cout << std::setprecision(12);
    std::cout << 3.33333333333333333333333333f << '\n'; // float has only 6 significant digits
    std::cout << 3.33333333333333333333333333 << '\n'; // double has 15 ~ 17 significant digits

    double zero{0.0};
    double posinf{5.0 / zero};
    std::cout<<posinf<<'\n';

    double neginf{-5.0 / zero};
    std::cout << neginf << '\n';

    double nan{ zero / zero };
    std::cout << nan << '\n';

    return EXIT_SUCCESS;
}
