#include "diy.h"
#include <vector>
#include <functional>

namespace Color
{
    enum Type
    {
        none,
        black,
        red,
        green,
        blue,
        cyan,
        max_colortypes
    };

    using namespace std::literals;
    constexpr std::array colorName{"None"sv,"Black"sv, "Red"sv, "Green"sv,"Blue"sv, "Cyan"sv};
    constexpr std::array colorArray{black, red, green, blue, cyan};

    static_assert(colorName.size() == max_colortypes && "Type Number calculation Error here!\n"); // Align the lengths on enumeration and NameArray
}

constexpr std::string_view getColorName(const Color::Type type)
{
    return Color::colorName[static_cast<std::size_t>(type)];
}

std::ostream& operator<<(std::ostream& out, Color::Type type) // enumerator -> stringview
{
    return out << getColorName(type);
}

constexpr void capitialize(std::string& str)
{
    for(char& character:str)
    character = static_cast<char>(tolower(static_cast<unsigned char>(character)));
    str[0] = static_cast<char>(toupper(static_cast<unsigned char>(str[0])));

}

// Overwrite cin
// Color::Types type{};
// std::cin >> type;
std::istream& operator>>(std::istream& in, Color::Type& type) // string -> enumerator
{
    std::string input{};
    std::getline(in >> std::ws, input); // skip all the whitespace before the valid context and drop the vaild context to string `input`
    capitialize(input);

    for (std::size_t index{0}; index < Color::max_colortypes; ++index)
    {
        if(input == Color::colorName[index])
        {
            type = static_cast<Color::Type>(index);
            return in;
        }
    }

    // if no match, set cin's state as Failed
    in.setstate(std::ios_base::failbit);

    type = {}; // we just value-initialize it for the failure situation
    return in; // then we return the os' input component back
}

int main()
{
    // Color::Type type{};
    // std::cout << "Please enter Your favoriate color: ";
    // std::cin >> type;
    // if (std::cin) // if user's input is matched with Color::type
    //     std::cout << "Oh! " << type << " is my favorate too!\n";
    // else
    //     std::cout << "You just input an invalid Color.\n";

    for(const auto color:Color::colorArray) // compiler is incapable to traversal a numeration but array<numerator> is fine
        std::cout << color << ' ';
    std::cout << '\n';

    return 0;
}
