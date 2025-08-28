#include <iostream>

// all those objs have internal linkage
// they are the locals
// in the same .cpp
static int g_x; // zero-initializer by default
static int g_x1{1}; //

const int g_y{2}; //
constexpr int g_y2{2};

static void internalFunc(){}; // 
// all of them are only exist in this (internal_linkage.cpp) file
// and can not be utilized by the linker
// The internal linkage is A LIMITATION
/*-----------------------------------------------------------*/
// real global
// Non-const variables are external by default
// definitions of external global variables (a.cpp)
int g_ex{}; // this is a global variable

extern const int g_ex_y{2};
extern constexpr int g_ex_y2{2}; // this will not work

void doNothing(){};

// main.cpp (declarations)
int g_ex;
extern const int g_ex_y;
//extern constexpr int g_exy_2; // error, the compiler can't see the variable in the other file!
void doNothing();
/*-----------------------------------------------------------*/
// you should not abuse global variable, especially non-cosnt global variable,
// it will make the whole program very ambiguous
/*--------------------------------------------*/
// (global constants as Internal Variables)
namespace constant
{
    constexpr double pi{3.14159265};
    constexpr double myGravity{9.2};
}

int main()
{

    return 0;
}
