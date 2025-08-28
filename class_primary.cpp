#include "diy.h"

class Date
{
    // Any member define here will be private member
public:
    // member function
    void print() const
    {
        std::cout << "Today: " << m_month << '/' << m_day << '/' << m_year << '\n';
    }
    // member function can be overloaded
    void print(std::string_view prefix) const
    {
        std::cout << prefix << m_month << '/' << m_day << '/' << m_year << '\n';
    }

    // set private members (setter)
    void setDay(int day) { m_day = day; }
    void setMonth(int month) { m_month = month; }
    void setYear(int year) { m_year = year; }

private:

    int m_day{31};
    int m_month{12};
    int m_year{2024}; // default initialization

    // we need a guard here for keeping the class invariant
    // in case the Class invariants is broken


};

class Point3d
{
private:
    int m_x{};
    int m_y{};
    int m_z{};

public:
    
    void setValue(int x,int y,int z) // initialization function
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }

    void print() const
    {
        std::cout << '<' << m_x << ", " << m_y << ", " << m_z << ">\n";
    }

    bool isEqual(Point3d& othr_point)
    {
        return (m_x == othr_point.m_x and m_y == othr_point.m_y and m_z == othr_point.m_z);
    }

    int getX() const { return m_x; } // getter. Notice: if we return a ref we need set the return as a const ref
    void setX(int x) { m_x = x; } // setter

    int getY() const { return m_y; } // getter
    void setY(int y) { m_y = y; } // setter

    int getZ() const { return m_z; } // getter
    void setZ(int z) { m_z = z; } // setter
};

// class's default member access level is Private, so an non-member function can't get the Private member of the Class
// void printDate(const Date& date) // non-member function (free function)
// {
//     // access deny (Public -X-> Private)
//     std::cout << "Today: " << date.m_month << '/' << date.m_day << '/' << date.m_year << '\n';
// }

struct Person // <struct> here
{
// public default

    std::string name{};
    int age{};

    void kisses(Person& person) const
    {
        std::cout << name << " kisses " << person.name << '\n';
    }

    const auto& getName() { return name; } // if we use string_view here, it will have a conversion (string->string_view)
};

struct HelloWorld // namespace recommended
{
    void helloworld() // we should put this into a namespace, instead of a struct definition.
    {
        std::cout << "Hello, World!\n";
    }
};

struct IntPair
{
    int first{};
    int second{};
    
    // member functions that should not modify member variables and the function should get the qualifier <const>
    void print() const { std::cout << "Pair(" << first << ", " << second << ")\n"; }
    bool isEqual(IntPair& otherone) const
    {
        return (first == otherone.first and second == otherone.second) ? true : false;
    }
};

struct Something
{
    void print()
    {
        std::cout << "Non-const\n";
    }
    void print() const
    {
        std::cout << "Const\n";
    }
};

class Employee
{
    std::string m_name{}; // class invariant
public:
    // constructor - Special Function must be executed
    explicit Employee(std::string_view name) // we don't use `explicit` here (aka we allow conversion), although we only have one argument to fill,
                                    // reason1. the constructed obj is semantically equivalent to the argument value (Employee's name == string)
                                    // reason2. the conversion is proformant (string_view -> string)
        : m_name { name != "" ? name : "Name"} // member initialization list, notice the `:`
    {
        std::cout << "Hello " << name << '\n';
    }

    void setName(std::string_view name) 
    {
        if(name != "")
            m_name = name;
        else
        {
            std::cerr << "Invalid Name!\n";
            std::abort();
        }
    }

    const std::string &getName() const { return m_name; }

};

// Non-member function is perfered to maintain the consistancy(what the data should be like) of structs or classes
// (1
char firstInitial(const std::string_view name) { return name.front(); } // we should not access any empty string's first initial
// (2
void print(const Employee& employee) 
{
    std::string_view name{employee.getName()};
    if( name != "Name")
        std::cout << "Employee " << name << " has first initial " << firstInitial(name) << '\n';
    else
    {
        std::cerr << "Please Create a valid Employee first!\n";
        std::abort();
    }
}

// Fraction
class Fraction
{
    int m_numerator{0};
    int m_denominator{1};
    // constructor in Private, so only member function can create Fraction
    Fraction(int numerator,int denominator)
        :m_numerator{numerator}
        ,m_denominator{denominator}
    {
        std::cout << "Fraction: " << m_numerator << '/' << m_denominator << '\n';
    }
public:
    friend std::optional<Fraction> createFraction(int numerator, int denominator);
};
// we skip throw an exception, instead of create a true instance
std::optional<Fraction> createFraction(int numerator, int denominator)
{
    if(denominator == 0)
        return {std::nullopt};
    else
        return Fraction{numerator, denominator}; // as a friend member function, we can create Fraction here now
}

// Ball
enum class Color // nested type
{
    blue,
    red,
    black,
    green

};

Color transEmuColor(std::string_view color)
{
    using enum Color;
    
    if(color == "red")
        return red;
    if(color == "green")
        return green;
    if(color == "blue")
        return blue;
    if(color == "black")
        return black;
    else
        std::abort();
}

std::string_view getColorStr(Color color)
{
    using enum Color;

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
        std::abort();
    }
}

std::ostream& operator<<(std::ostream& out, Color color)
{
    return out << getColorStr(color);
}

class Ball
{
// public: (not work so well here if we want to use str input, but enuemrator input will be fine)
//     enum Color // nested type
//     {
//         blue,
//         red,
//         black,
//         green

//     };
private:
    // default initialization for members (Using default initializer is recommended)
    static constexpr Color d_color{Color::black};
    static constexpr std::string_view d_color_str{"black"};
    static constexpr double d_radius{10.0};

    Color  m_color{d_color};  // can be a string
    double m_radius{d_radius}; // if we have a default value, we could don't need delegating anymore

public:
    // Ball() = default; // this will execute zero initialzation first, then default initialization
    
    // 1) default
    // Ball() { print(); } // this just do default initialization (more efficient), replacement of above
    // 2) color only
    // Ball(std::string_view color) // call other constructor for more initialization
    //     // : Ball(color, d_radius)                          // delegating constructor
    //     : m_color{transEmuColor(toASCIILowerCase(color))}
    // {
    //     print();
    // }
    // 3a) radius only (Traditional)
    // Ball(double raidus)
    //     : m_radius{raidus}
    // {
    //     print();
    // }
    // 3b) radius only (Delegating constructor)
    Ball (double raidus)// when we just get radius, we add the first parameter(color), then let the main constructor take over of it
        : Ball(d_color_str, raidus)
    {
        // we don't need print() here anymore, because we have called other one which will print
        // the information for us
    }
    // a constructor either call a delegating constructor or be an initialization list
    // 4) default, color only (radius only can NOT be archieved) or passing both parameters
    Ball(std::string_view color = d_color_str, double radius = d_radius)
        : m_color{transEmuColor(toASCIILowerCase(color))} // because we want use this function, so we can't put enumeration in the class
        , m_radius{radius}
    {
        print();
    }

    // Copy Constructor (we should keep this away, just use the implicit one for optimization)
    // Ball(const Ball& ball) // must be a CONST and a REF
    //     : m_color{ball.m_color}
    //     , m_radius{ball.m_radius}
    // {
    //     std::cout << "The Copy of Ball has been Created!\n";
    // }

    double getRadius() const { return m_radius; }
    Color getColor() const { return m_color; }
    
    void print() const
    {
        std::cout << "Ball(" << m_color << ", " << m_radius << "cm)\n";
    }
};

// void print(const Ball& ball)
// {
//     std::cout << "Ball(" << ball.getColor() << ", " << ball.getRadius() << "cm)\n";
// }

Ball myball() // Temporary Object with Return by value (Function implementes)
{
    return {"red"}; // Copy Elision
}

int temporary()
{
    return 3;
}
constexpr int nonconst()
{
    int a{0};
    a = 1;
    return a;
}


int main()
{
    // Classes

    // Date today{30, 12, 24}; // aggregate initialize our Class is not work
    // printDate(today); // Non-Member Function not work
    Date today{};
    // today.m_day = 31; // member variable accessed using member selection operator `.` (Only work for public level)
    today.print(); // member function also used that too
    // `today` is an implict object and the properties of it are <acessed by the function in implict way>
    Date tomorrow{};
    tomorrow.setMonth(1);
    tomorrow.setDay(1);
    tomorrow.setYear(2025);
    tomorrow.print("Tomorrow: "); // overloaded

    Person joe{"Joe", 29};
    joe.name = "Nobody"; // dangerous
    Person kate{"Kate", 27};
    joe.kisses(kate); // we can see the which object is initiating the action and which is in support
    auto joe_name{joe.getName()};

    HelloWorld say{};
    say.helloworld();

    // Practice (struct)
    IntPair p1{1, 2};
    IntPair p2{3, 4};
    std::cout << "p1: ";
    p1.print();
    std::cout << "p2: ";
    p2.print();
    std::cout << "p1 and p1 " << (p1.isEqual(p1) ? "are equal.\n" : "are not equal.\n");
    std::cout << "p1 and p2 " << (p1.isEqual(p2) ? "are equal.\n" : "are not equal.\n");

    p1.first = 2;
    const IntPair p3{5, 6}; // read-only
    std::cout << "p3: ";
    p3.print(); // print() const is needed

    // rare
    const Something c_something{};
    Something something{};
    c_something.print(); // a const class object can only call a const member function
    something.print();

    // Class with private and public
    // practice
    Point3d point1{};
    point1.setValue(1, 2, 3);
    Point3d point2{};
    point2.setValue(1, 2, 3);
    std::cout << "Point1 and Point2 are" << (point1.isEqual(point2) ? " " : " not ") << "equal.\n";
    Point3d point3{};
    point3.setValue(3, 4, 5);
    std::cout << "Point1 and Point3 are" << (point1.isEqual(point3) ? " " : " not ") << "equal.\n";

    // Employee
    Employee mark{"Mark"};
    // mark.setName("Mark");
    print(mark);
    Employee john{"John"};
    // john.setName("John");
    print(john);
    print(Employee{"Kate"}); // temporary object
    // print({"Loius"}); // temporary object (implictly convert to Employee).
                        //  if we use keyword `explicit`, the conversion will be disabled, this statement will fail

    // Fraction
    auto f1{createFraction(1, 2)}; // we use private constructor and optional to avoid creating a bad fraction
    if(f1)
        std::cout << "Fraction has been constructed!\n";
    else
        std::cout << "Bad fraction!\n";

    // Ball
    Ball red{"red", 12.3}; // normal construction
    // print(red);
    Ball green{"green"}; // delegating construction
    // print(green);
    std::cout << "/---------------------------------------------------------/\n";
                     // user-defined default constructor value initialization.
    Ball black{};    // which will execute zero initialization(member) if uses Default Constructor, 
                     // but User-Defined Empty Constructor will NOT to do so.
    // Ball black;   // default initialization. will not execute zero initialization(member) before default initialization(member)
    // print(black);
    Ball blue{"blue"};
    // print(blue);
    Ball twenty{20.0};
    // print(twenty);
    Ball bluetwenty{"blue", 20.0};
    // print(bluetwenty);
    myball(); // temporary Ball insistantion, which will be destroied at the end of this statement
    Ball myball_copy{myball()}; // originally, this will call two constructors (normal one and copy one), but it just got one (normal)
    Ball blue_copy{blue}; // Copy constructor made this. Temporary object is not count a object, so that we don't need call Copy-Semantics
    blue_copy.print();
    // using namespace std::literals;
    print(Employee{"kala"}); // convert string_view to Employee -> Definition works fine
                             // keyword `explicit` in constructors means we want Explicit Class type (i.e Employee {"joe"}), instead of {"joe"}.
    [[maybe_unused]] constexpr int b{nonconst()};

    return 0;
}
