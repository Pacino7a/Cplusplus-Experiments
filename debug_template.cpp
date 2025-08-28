// Way_1 Press F5 to use Debugger is RECOMMENDED
#include <iostream>
// Way_2 or you can choose a Logger for logging what has happened
#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>

// Way_3 EVEN you can use the cerr to print out the states by yourself
// #define ENABLE_DEBUG

int getValue()
{
// The statement that is used for debugging doesn't need to indent
// cerr for debugging, Print out the state the function and the value of output

// #ifdef ENABLE_DUBUG
// std::cerr << "getValue() called\n"; 
// #endif

    PLOGD << "getUserInput() called";

    return 5;
}
int main()
{
// Don't indent here
//std::cerr << "main() Called\n";
    plog::init(plog::none, "Debug_template_Logfile.txt");
    PLOGD << "main() Called";
    std::cout << getValue() << std::endl;

return 0;
}
