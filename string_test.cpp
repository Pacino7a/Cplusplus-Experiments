#include <iostream>
#include <string>
#include <string_view>
using namespace std::string_literals;
//"Hello world" - C style string
//"hello world" - std::string type
// All the operations below that use string are MAKING a COPY!,
// Very expensive

void sayHello(std::string content) // not recommend - pass a string is expensive
{
    std::cout << "Please enter your " << content;
}
std::string helloWorld() { return "hello world"s; }
std::string returnStr() // 3 acceptable return
{
    //"hello world"s --> std::string { "hello world", 11 }
    std::string local{"hello world"s}; // copy a string, which is expensive
    return helloWorld(); // string from the other func
    return local; // local variable
    return "hello world"s; // temporary
}

int main()
{
    // constexpr std::string hobby{"Play the piano"s};
    sayHello("Name: ");
    std::string name{};
    // std::cin >> name; // Extract the first word before the SPACE (if your input has), FAIL to extract one line
    std::getline(std::cin >> std::ws, name); // solved the space problem

    //[[maybe_unused]] int Name_len{static_cast<int>(name.length())}; // Not include the null character
    int length_name { static_cast<int>(std::ssize(name)) }; // c++ 20
    // static_cast<> is necessary for storing

    // getline will take everything belongs to the line, and make '\n' --> '\0'
    sayHello("Age: ");
    int age{};
    std::cin >> age; // here is a number input, which will carry a '\n'
    sayHello("Color: ");
    std::string color{};
    std::getline(std::cin >> std::ws, color); 
    // to pass every White Space ahead the word needs be read immediately,
    // we need manipulator 'ws' to do so
    constexpr std::string A{"hello, world"s};
    // Error happens because what creating a string needs is dynamic allocation of memory

    //std::cin >> color;  // extract the second one after SPACE
    std::cout << "Your name gets " << length_name << " Characters" << '\n';
    std::cout << "Hello " << name << ", Your color is " << color
              << ", And your age is: " << age << '\n'
              << "your age + length of your name is: " << length_name + age << '\n';

    return 0;
}
