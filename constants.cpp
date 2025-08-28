#include "diy.h"

namespace constants
{
    // constexpr better to define in the header
    // when the compiling time is long
    // the definitions can be moved here

    // moved to the header
    // extern constexpr double pi{3.141592653};
    // extern constexpr double myGravity{9.87};
    extern int g_x; // uninitialized, should be 0
    extern constexpr int g_number_apple{10}; // const or constexpr must be initialized by a value
    // or it will be parsed as a declaration.

    void foo(){}

} // namespace constants
