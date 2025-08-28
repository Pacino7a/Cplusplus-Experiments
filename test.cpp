#include "array.h"
#include "diy.h"
#include <fstream>

// class Foo
// {
// public:
//     Foo(int , int)
//     {
//         std::cout << "Foo(int, int)" << '\n';
//     }

//     Foo(std::initializer_list<int>)
//     {
//         std::cout << "Foo(initializer_list)" << '\n';
//     }
// };

int main()
{
    // IntArray array{ 5, 4, 3, 2, 1 }; // initializer list constructor favored

    // IntArray array{}; // if you want value initialize to your object, you need default constructor here
    // array = {1, 2, 3, 4, 5, 6};
    // for (int count{ 0 }; count < array.getLength(); ++count)
	// 	std::cout << array[count] << ' ';

    // Foo f1{1, 2};
    // Foo f2(1, 2);

    // IntArray array { 5, 4, 3, 2, 1 }; // initializer list
	// for (int count{ 0 }; count < array.getLength(); ++count)
	// 	std::cout << array[count] << ' ';

	// std::cout << '\n';

	// array = { 1, 3, 5, 7, 9, 11 };

	// for (int count{ 0 }; count < array.getLength(); ++count)
	// 	std::cout << array[count] << ' ';

	// std::cout << '\n';
    // Array arr{1, 2, 3, 4};
    // std::cout << arr << '\n';
    // arr.earse();
    // arr.reAllocate(8);
    // arr.insert(2, 2); // insert 2 at index [2]
    // arr.resize(3);
    // std::cout << arr << '\n';
    // Array arr_d{1.2, 3.4, 5.6};
    // std::cout << arr_d;
    // arr_d.earse();

    // char strBuf[11]{};
    // // Read up to 10 characters
    // std::cin.getline(strBuf, 11);
    // std::cout << strBuf << '\n';

    // // Read up to 10 more characters
    // std::cin.getline(strBuf, 11);
    // std::cout << strBuf << '\n';
    // std::cout << std::cin.gcount() << " characters were read" << '\n';

    // everytime you do this, the file will be reflashed.
    // std::ofstream outfile{"sample.txt"};
    // std::ofstream outfile{"sample.txt", std::ios::app}; // append mode
    // std::fstream file("sample.txt", std::ios::app);
    // if(!file)
    // {
    //     std::cerr << "Uh Oh, Your file couldn't be opened for writing!\n";
    //     return 1;
    // }

    // file << "Hello, World.\n"; // write a line
    // file << "This is China.\n"; // write a new line
    // // outfile.put('A'); // put a char
    // file.close();

    // file.open("sample.txt", std::ios::in | std::ios::out | std::ios::ate); // modes need manually set (NO Default here)
    // std::streampos endPos{file.tellg()}; // g for `get` (read mode)
    // std::cout << "File size: " << endPos << " bytes\n";

    // file.seekp(0); // p for `put` (write mode)
    // file << "hello";
    // file.close();

    // std::ifstream infile{"sample.txt"};

    // if(!infile)
    // {
    //     std::cerr << "Uh Oh, Your file couldn't be opened for Reading!\n";
    //     return 2;
    // }

    // std::string strFromfile{};
    // //while(infile >> strFromfile) // extract each strings, whitespace is not included
    // while(std::getline(infile,strFromfile)) // extract a line and drop '\n'.
    //     std::cout << strFromfile << '\n';

    return 0;
}

