#include "diy.h"
#include <sstream>

// argv is an array whose elements are pointers pointing to char
int main(int argc, char * argv[]) // argc is the number of comand line arguments which are contained in argv
{
    // std::cout << "There are " << argc << " Command line arguments.\n";
    // for (int i{0}; i < argc;++i) 
    // {
    //     std::cout << "Argument #" << i << ": " << argv[i] << '\n';
    // }
    
    if (argc <= 1)
	{
		// On some operating systems, argv[0] can end up as an empty string instead of the program's name.
		// We'll conditionalize our response on whether argv[0] is empty or not.
		if (argv[0])
			std::cout << "Usage: " << argv[0] << " <number>" << '\n';
		else
			std::cout << "Usage: <program name> <number>" << '\n';

		return 1;
	}

    // conversion is necessary if you want extract the value from your command line arguments (which are interpreted as strings by complier)
    std::stringstream convert{argv[1]};

    int myint{};
    if(!(convert>>myint))
        myint = 0;
    std::cout << "Got Interger " << myint << '\n';

    return 0;
}
