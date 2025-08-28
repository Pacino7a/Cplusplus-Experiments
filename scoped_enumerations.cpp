#include "diy.h"
#include <utility> // to_underlying(), converts an enumerator to a value of the underlying type (数据基本构型，如int8,int16,...) of the enumeration

// Scoped Enumeration
enum class Color // scoped enumeration which has `class` keyword, but this is NOT a Class-Type
{
    red,
    green,
    blue,
};
enum class Fruit
{
    banana,
    apple,
    orange,
};
enum struct Item // same with enum class (non-idiomatic)
{
    cup,
    junk,
    phone,
};
enum class Animal
{
    pig,
    chicken,
    goat,
    cat,
    dog,
    duck,
};

constexpr std::string_view getAnimalName(Animal animal)
{
    using enum Animal;

    switch (animal)
    {
    case pig:
        return "Pig";
    case chicken:
        return "Chicken";
    case goat:
        return "Goat";
    case cat:
        return "Cat";
    case dog:
        return "Dog";
    case duck:
        return "Duck";

    default:
        return "??? This is an ALIEN!\n";
    }
}

constexpr void printNumbersOfLegs(Animal animal)
{
    using enum Animal;

    switch (animal)
    {
    // NOT [[fallthrough]]
    // just multiple cases use a same statements
    case pig:
        // std::cout << "A " << getAnimalName(animal) << " has " << 4 << " legs.\n";
        // [[fallthrough]]; // fallthrough means it will not stop at the end of this case and get into other cases. Something bad will happen in the most of time.
    case goat:
    case cat:
    case dog:
        std::cout << "A " << getAnimalName(animal) << " has " << 4 << " legs.\n";
        break;
    
    case chicken:
    case duck:
        std::cout << "A " << getAnimalName(animal) << " has " << 2 << " legs.\n";
        break;

    default:
        std::cout << "Is this a Fish?\n";
    }
}

constexpr std::string_view getColor(Color color)
{
    // don't forget `enum`
    using enum Color; // bring the enumerators in the Color Enumeration in

    switch (color)
    {
    case red: // we don't need add a prefix (Color::) here anymore
        return "Red";
    case green:
        return "Green";
    case blue:
        return "Blue";
    default:
        return "??? It seems lead us to a Mysterious Place.\n";
    }

}

// overload the unary + operator to convert Item to the underlying type(Int or its variants)
// or you can use std::to_underlying(item) instead (C++23)
constexpr auto operator+(Item item) noexcept
{
    return static_cast<std::underlying_type_t<Item>>(item); // converts the scoped enumerator to a value
}

int main()
{

    [[maybe_unused]] Color color{Color::red};
    [[maybe_unused]] Fruit fruit{Fruit::banana};
    [[maybe_unused]] Item item{Item::cup};
    [[maybe_unused]] Item item_2{2}; // (C++23) we can initialize the enumerators by Integers
    int input{};
    std::cin >> input;
    item = static_cast<Item>(input); // 

    //std::cout << color; // not work for scoped enumeration
    std::cout << static_cast<int>(color) << '\n';   // converts enumerator to an Integal Value
    std::cout << std::to_underlying(color) << '\n'; // converts enumerator to the underlying type of Enumeration
    std::cout << getColor(color) << " is your Lucky Color!\n";
    if(color == Color::red)
        std::cout << "This shirt is red.\n";
    if(item == Item::junk)
        std::cout << "Throw the junk out please!\n";
    if(item_2 == Item::phone)
    {
        std::cout << "Where is my phone?\n";
        std::cout << "And Phone's position in the Enumeration is " << +item_2 << '\n'; //unary `+` here for transforming the enumerator 2 integer value
        std::cout << "And Phone's position in the Enumeration is " << std::to_underlying(item_2) << '\n';
    }

    printNumbersOfLegs(Animal::cat);
    printNumbersOfLegs(Animal::chicken);

    return 0;
}
