#include <iostream>

// This function shows the INPUTS and OUTPUTS by std::cin and std::cout
int main()
{
    // char name[] {"David.\0"};

    // USE value initialize for an INPUT variable
    int temp1 {}, temp2 {}, temp3 {}; 
    // char name {"David"};
    std::cout<<"HI!"<<'\n';

    // std::cout<<std::endl; // <LIMITATION>
    // This statement's purpose is printing a New line
    // And flushing the buffer, which may Makes the program SLOW. 


    // When we didn't use the endl in the program
    // the buffer will be flushed automatically
    // which is more efficient

    std::cout<<"Enter an Integer:"; // Dont need any '\n' output

    // Input 2 numbers at the same time from the keyboard 
    // and assign them to temp1 and temp2 respectively
    // std::cin>>temp1>>temp2;

    std::cin>>temp1;
    std::cin>>temp2;
    std::cin>>temp3;
    std::cout<<"Input: "<<temp1<<", "<<temp2<<", "<<temp3;
    // Output 3 values of these variables at once

    // Print a New-line in this way without any Extra effect to the program
    std::cout<<'\n'; 

    // "<<" can link each pieces altogether in this statement
    std::cout<<"My name is "<<"David."<<std::endl; 
    // std::cout<<"My name is "<<name<<std::endl; 

    // The Direction of "<< (out)" and ">> (in)" is the "Direction" of data-streaming 

}
