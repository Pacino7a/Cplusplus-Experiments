#include "diy.h"

// Ball
// enum class Color // nested type
// {
//     blue,
//     red,
//     black,
//     green

// };

class Ball
{
private:

    enum Color // nested type
    {
        blue,
        red,
        black,
        green

    };

    Color transEmuColor(std::string_view color);

    // default initialization for members (Using default initializer is recommended)
    static constexpr Color d_color{black};
    static constexpr std::string_view d_color_str{"black"};
    static constexpr double d_radius{10.0};

    Color  m_color{d_color};  // can be a string
    double m_radius{d_radius}; // if we have a default value, we could don't need delegating anymore
    
    friend std::string_view getColorStr(const Color color);
    friend std::ostream &operator<<(std::ostream &out, const Color color);

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

// write in another .cpp
Ball::Color Ball::transEmuColor(std::string_view color) // private member function
{
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

std::string_view getColorStr(const Ball::Color color) // friend
{
    using enum Ball::Color;
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

std::ostream &operator<<(std::ostream &out, const Ball::Color color) // friend
{
    return out << getColorStr(color);
}

int main()
{
    Ball black{12.0};
    Ball blue{"blue", 10.5};

    return 0;
}
