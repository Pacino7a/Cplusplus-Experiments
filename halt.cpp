#include <iostream>

void cleanUp()
{
    // clean up code...
    std::cout << "clean up!\n";
}
int main()
{
    std::atexit(cleanUp); // register a procedure for clean up before execute exit()
    // std::at_quick_exit(cleanUp);

    std::cout << 1 << '\n';

    std::exit(0); // run `clean up` first, then call the exit(),
                  //this will clean the static duration things as well

    // std::quick_exit(0) // keep the base function of exit(), but do not execute the fixed-cleanning procedure.


    std::cout << 2 << '\n';

    return 0;
}
