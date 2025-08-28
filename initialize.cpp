#include <iostream>

int main()
{
    int width; // Define a variable
    width = 3840; // Copy-assignment
    [[maybe_unused]]int traditional (6); // Traditional initial ways in line 6 & 7
    int height {2160}; // Initiallize by an Initializer. BTW {2160}-Initializer, 2160-Initial value (RECOMMENDED)

    [[maybe_unused]]int zero {0}; // Zero initialize needs you put a zero in the braces
    int temp {}; // {} for Value initialize, Narrowing conversion error for {0.1}
    temp = 5;
    // temp = 1.1; // Get a warning for data losing
    // Value initialize for a varible whose value will be changed immediately -> give it a temp value
    // So these two ways are different Although both of them will assign a zero for the variable

    [[maybe_unused]]int a {1}, b{2}; // Initialize mutiple variables in the same time

    double pi {3.1415926};

    std::cout<<width; // Print variable "width" to the monitor
    std::cout<<"x";
    std::cout<<height;
    std::cout<<std::endl<<"temp:"<<temp;
    std::cout<<std::endl;
    std::cout<<"Pi:"<<pi<<std::endl;

    // Last but not least, Initialize is different from Assignment
    // Directly-list-initialization is recommended all the time (e.g. line 8)
    // int x; is a Default Initialization that gives a random value to x
    // and the DIFFERENCE between value initialization & zero initialization should be noticed

    return 0;

}
