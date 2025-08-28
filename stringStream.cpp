#include <iostream>
#include <sstream>

int main()
{
    // std::stringstream os {};
    // // os << "12345 67.89\n"; // way one
    // os.str("12345 67.89");  // way two
    // std::cout << os.str();

    // std::stringstream os{};
    // os << "12345 67.89";
    // std::string strValue{};
    // os >> strValue;
    // std::string strValue2{};
    // os >> strValue2;
    // std::cout << strValue << " ~ " << strValue2 << '\n';
    // std::cout << os.str();

    int x{1};
    double y{2.1};
    std::stringstream os{};
    os << x << ' ' << y << '\n';
    std::string str1, str2;
    os >> str1 >> str2; // (Value -> String) read reach the edge, raise flag of EOF 
    std::cout << str1 << " ~ " << str2 << '\n';

    int x_r{};
    double y_r{};
    os.clear(); // clear the flag for re-READ (ESSENTIAL)
    // os.str("7 8.6"); // set the stream, clear before ones
    os << "7 8.6\n"; // add new string into the stream
    std::cout << os.str();
    os >> x_r >> y_r; // (String -> Value)
    std::cout << x_r << " , " << y_r << '\n';

    // erase the stream
    os.str("");
    // os.str(std::string{});
    std::cout << "Str: " << os.str() << '\n';

    return 0;
}
