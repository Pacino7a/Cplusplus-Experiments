#include <iostream>
#include <string>
#include <string_view>
// Use string_view to solve costy problem of string copying
// Good replacement

void sayHelloSV(std::string_view content) // not recommend - pass a string is expensive
{
    std::cout << "Hello " << content << '\n';
}
void sayHello(std::string content) // not recommend - pass a string is expensive
{
    std::cout << "Hello " << content << '\n';
}
std::string_view alpha_f(std::string_view s1,std::string_view s2)
{
    return s1 > s2 ? s1 : s2;
}

int main()
{
    using namespace std::string_literals; // for string type
    using namespace std::string_view_literals; // for string_view type
    // Initialization
    std::string_view tip1{"David!"};
    sayHelloSV(tip1); // initialize by a c-style string
    std::string tip2{"Tim!"};
    std::string_view tip2_sv{tip2}; // initialized by a string
    std::string_view tip3{tip2_sv}; // initialized by a string_view

    // call a fuction
    sayHelloSV("Carter!"); // C style argument
    sayHelloSV("Jamie!"s); // string argument
    sayHelloSV(tip1); // s_view argument

    // Convertion (Explicit Only)
    std::string tip1_conv{tip1};
    sayHello(static_cast<std::string>(tip1));

    // No error
    [[maybe_unused]] constexpr std::string_view A{"hello, world"};
    
    // Caution
    std::string_view B{};
    {
        std::string s{"what we got"};
        B = s;
    }// s will be destoried here
    std::cout << B << '\n'; // undefined behavior

    std::string_view nothing{alpha_f("David","Malan")};
    std::cout << nothing << '\n'; // undefined behavior
    std::cout << alpha_f("David", "Malan") << '\n';

    std::string h{"hello world"};
    std::string_view change{h};
    h = "hello universe"; // undefined behavior (directly)
    change = h; // revalidation
    std::cout << change << '\n';
    
    // Modify the View
    // Modification will make the string to a substr,
    // which may not null-terminated
    change.remove_prefix(1);// The modifications will maintain until revalidation
    std::cout << change << '\n'; //
    change.remove_suffix(1);
    std::cout << change << '\n';
    change = h; // revalidation
    std::cout << change << '\n';
    std::string_view sub_text{change.substr(6, 3)}; // substring (start: 6th, width:3 )
    std::cout << sub_text << '\n';

    //std::cout << '.\n'; // undefined what the character'.\n' is

    return EXIT_SUCCESS;
}
 