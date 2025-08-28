#include "diy.h"
// This module contains struct, Unscoped enumeration and operator overloading

// P.S using like assignment, typedef like a sentence (in the perspective of order)
// using Color = int;
// typedef int Color_d;

// constexpr Color red{0};
// constexpr Color green{1};
// constexpr Color blue{2};

// new type (Your own design)
// Structure (compund type)
struct Fraction
{
    int numerator{};
    int denominator{};
    std::string name{};
};

//  Unscoped enumeration
// `Unscoped` means the enumeration that you defined are visable in the whole place where it located at.
enum Color // global visable
{
    // enumerators
    // default value = 0, following ++value
    red, // do all the things above for you (aka using Color = int and constexpr color red{0})
    green, // so these are implicitly constexpr
    blue,
    black,
};

enum DaysOfWeek
{
    sunday,
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
};

// handle the error situations
enum FileReadResult
{
    readResultSucess,
    readResultFailedFileOpen,
    readResultFailedFileRead,
    readResultFailedFileParse,
};

// best practice of enumeration
namespace Flags
{
    //Visable in namespace Flags
    enum State // we can ignore this name when we use the enumerators, e.g Flags::isHungry
    {
        isHungry,
        isSad,
        isMad,
        isHappy,
        isLaughing,
        isAsleep,
        isDead,
        isCrying,
    };
} // namespace Flags

namespace Itemtype
{
    enum Itemtype
    {
        cup, 
        toothbrush,
        pen,
        pencil,
        car,
        phone,
        computer,
    };
} // namespace Itemtype

namespace EnemyType
{
    enum MonsterType : std::int16_t // you can explicitly specify an underlying type for enumerators,
    // aka explicitly specify a base
    {
        orc,
        zombie,
        goblin,
        troll,
        ogre,
        skeleton,
    };
}

bool openFile() { return true; }
bool readFile() { return true; }
bool parseFile() { return true; }

// common usage of enumeration
FileReadResult readFileContents()
{
    if(!openFile())
        return readResultFailedFileOpen;
    if(!readFile())
        return readResultFailedFileRead;
    if(!parseFile())
        return readResultFailedFileParse;

    return readResultSucess;
}

// enumerator -> string_view
constexpr std::string_view getColorName(Color color)
{
    switch (color)
    {
    case red:
        return "Red";
    case green:
        return "Green";
    case blue:
        return "Blue";
    case black:
        return "Black";

    default:
        std::cout << "Fatal Error!\n";
        std::abort();
    }
}

// output transform (enumerator -> string_view)
constexpr std::string_view getWeekDays(DaysOfWeek day)
{
    switch (day)
    {
    case sunday:
        return "Sunday";
    case monday:
        return "Monday";
    case tuesday:
        return "Tuesday";
    case wednesday:
        return "Wednesday";
    case thursday:
        return "Thursday";
    case friday:
        return "Friday";
    case saturday:
        return "Saturday";
    default:
        return "We are not on the Earth anymore?\n";
    }
}

// user's input(string/value) -> enumeration ->  output(string)
// user's input transform (string -> enumerators)
constexpr std::optional<Itemtype::Itemtype>getItemEnu(std::string_view item)
{
    if(item == "cup")
        return Itemtype::cup;
    if(item == "car")
        return Itemtype::car;
    if(item == "computer")
        return Itemtype::computer;
    if(item == "phone")
        return Itemtype::phone;
    if(item == "pen")
        return Itemtype::pen;
    if(item == "pencil")
        return Itemtype::pencil;
    if(item == "toothbrush")
        return Itemtype::toothbrush;

    return {std::nullopt};
}

// output transform (enumerator -> string_view) <don't make a string copy> <cheap>
constexpr std::string_view getItemName(Itemtype::Itemtype item)
{
    switch (item)
    {
    case Itemtype::pen:
        return "Pen";
    case Itemtype::pencil:
        return "Pencil";
    case Itemtype::cup:
        return "Cup";
    case Itemtype::toothbrush:
        return "Toothbrush";
    case Itemtype::car:
        return "Car";
    case Itemtype::computer:
        return "Computer";
    case Itemtype::phone:
        return "Phone";
    default:
        return "Fatal Error!\n";
    }
}

// operator overload
// teach operator<< how to print Color (enumerator)
// std::ostream is the type of std::cout, std::cerr ...
// the return type and parameter type are reference (to prevent copies from being made)
// we just modified the contents that need be printed out
std::ostream& operator<< (std::ostream& out, Color color)
{
    out << getColorName(color); // print out color(enumerator's name) to whatever output stream out
    return out; // operator<< conventionally returns its left operand
    
    // or
    // return out << getColorName(color);
}

// change the input-stream for enumeration
std::istream &operator>>(std::istream &in, Itemtype::Itemtype& item) // operator`>>` overloading
{
    std::string str{}; // get a string (input)
    in >> str;
    
    str = toASCIILowerCase(str);

    std::optional<Itemtype::Itemtype> match{getItemEnu(str)}; // string -> enumerator
    if(match)
    {
        item = *match;  // if match, change the contents of the enumeration variable (out parameter)
                        // we need modified the argument instead of a parameter(aka a copy)
                        // modifiying a parameter is meaningless
        return in;
    }

    // if we didn't find a match, so input must be invaliad
    // so we set the input stream state as Failed
    in.setstate(std::ios_base::failbit);

    item = {}; // do as before

    return in;
}

std::ostream& operator<< (std::ostream& out, Itemtype::Itemtype item)
{
    return out << getItemName(item);
}

    int main()
{
    [[maybe_unused]] Color appleColor{red};
    [[maybe_unused]] Color shirtColor{blue};
    Fraction f{3, 4,"David"};
    std::cout << "Hello " << f.name << '\n';
    std::cout << "Your Fraction is: " << f.numerator << '/' << f.denominator << '\n';
    std::cout << "Apple's Color is " << appleColor << '\n'; // normal '<<' will convert the enumerators to Int
                                                        // the overloaded `<<` will not
    if(readFileContents() == readResultSucess) // we can compare enumerators
        std::cout << "Read file sucess!\n";
    else
    {
        switch (readFileContents())
        {
        case readResultFailedFileOpen:
            std::cout << "File Can't Open!\n";
            break;
        case readResultFailedFileRead:
            std::cout << "File Can't be Read!\n";
            break;
        case readResultFailedFileParse:
            std::cout << "File Can't be Parsed!\n";
            break;
        default:
            std::cout << "Fatal Error!\n";
            break;
        }
    }

    std::bitset<8> me{};
    // we can use enumerators to operate Bit-operations
    me.set(Flags::isHungry);
    me.set(Flags::isSad);
    std::cout << "0b" << me << '\n';
    std::cout << std::boolalpha;

    std::cout << "Am I Happy? " << me.test(Flags::isHappy) << '\n';
    std::cout << "Am I Sad? " << me.test(Flags::isSad) << '\n';
    std::cout << "Am I Hungry? " << me.test(Flags::isHungry) << '\n';

// (namespace::enumeration (variable identifier) {namespace::enumerator})
    [[maybe_unused]] Itemtype::Itemtype user_own{Itemtype::computer};

    EnemyType::MonsterType levelone_monster{EnemyType::troll};
    [[maybe_unused]] EnemyType::MonsterType leveltwo_monster{3}; // we can initialize a numeration object with an Integral Value,
    levelone_monster = static_cast<EnemyType::MonsterType>(1);   // as long as the unscoped enumeration explicitly defined this value as its enumerator
    if(levelone_monster == EnemyType::troll)
        std::cout << "A wave of Trolls is coming.\n";
    else if(levelone_monster == EnemyType::zombie)
        std::cout << "A wave of Zombies is coming.\n";
    else
        std::cout<<"We are safe! For now...\n";


    DaysOfWeek today{monday};
    std::cout << "Now you can enter what the day of a week you at\nSunday<0>~Saturday<6> Forward: ";
    int today_user{};
    for (;;)
    {
        today_user = getInt();
        if(today_user < 0 || today_user > 6)
        {
            std::cout << "Your input is invaliad, please try again:";
            continue;
        }
        break;
    }
    today = static_cast<DaysOfWeek>(today_user); // Int(from the user) -> enumerators
    if (today != 0 && today != 6)
        std::cout << "Today is " << getWeekDays(today) << ", Hold " << 6 - today << " days to reach the Weekends!\n";
    else
        std::cout << "Today is " << getWeekDays(today) << "! Have a Great Weekends!\n";

    std::cout << "Please enter what item you get right now: ";
    // std::string user_item{};
    // std::cin >> user_item; // get input (string)
    // // user_item = toASCIILowerCase(user_item); // this will make a string copy

    // // string to lower (use lambda), lower every char in the string
    // std::for_each(user_item.begin(), user_item.end(), [](char &c)
    //               { c = static_cast<char>(std::tolower(static_cast<unsigned char>(c))); });

    // std::optional<Itemtype::Itemtype> userItem{getItemEnu(user_item)}; // string -> enumerator

    // if(!userItem) // check whether the user's input is a valiad enumerator
        // std::cout << "You just find an new item that we've never seen!\n"; // if it doesn't, drop a message
    // else // (valiad) enumerator -> string
        // std::cout << "You get a " << getItemName(*userItem) << '\n';// if it does, print what the enumerator as string

    Itemtype::Itemtype user_item{};
    std::cin >> user_item;
    std::cout << "You get a " << user_item << '\n';

    return 0;
}
