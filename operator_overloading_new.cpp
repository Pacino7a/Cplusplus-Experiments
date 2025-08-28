#include <iostream>
#include <cassert>
#include <cmath>
#include <numeric> // std::gcd() for reduce the fractions to the lowest terms
#include <utility>

class Fraction
{
private:
    int m_numerator{};
    int m_denominator{};
    void reduce() {
        const int f_gcd{std::gcd(m_numerator, m_denominator)};
        if(f_gcd) // make sure no divide by 0
        {
            m_numerator /= f_gcd;
            m_denominator /= f_gcd;
        }
    }
public:
    explicit Fraction(const int numerator = 0, const int denominator = 1) // we set default parameters here for default initialization
    : m_numerator{numerator}, m_denominator{denominator}
    {
        assert(m_denominator != 0); // make sure  all the fraction which is math semantics correct
        reduce(); // and to the lowest term
    }

    void print() const { 
        if(m_denominator != 1 && m_numerator != 0)
            std::cout << m_numerator << "/" << m_denominator << '\n';
        else
            std::cout << m_numerator << '\n';
    }
    friend Fraction operator*(const Fraction &f1, const Fraction &f2);
    friend Fraction operator*(const int value, const Fraction &f2); // if we remove two of these (This line and the below one And `explicit` ahead of the constructor)
    friend Fraction operator*(const Fraction &f1, const int value); // the program will still work
    friend std::istream &operator>>(std::istream &in, Fraction &fraction);
    friend std::ostream &operator<<(std::ostream &out, const Fraction &fraction);
};

Fraction operator*(const Fraction &f1, const Fraction &f2)
{
    return Fraction{f1.m_numerator * f2.m_numerator, f1.m_denominator * f2.m_denominator};
}

Fraction operator*(const int value, const Fraction &f2)
{
    return Fraction{value * f2.m_numerator, f2.m_denominator};
}

Fraction operator*(const Fraction &f1, const int value)
{
    return value * f1; // We delegate this to another operator function.
}

int gcd(int a, int b) // the greatest common divisor (GCD) (Traditional)
{
    return (b == 0) ? std::abs(a) : gcd(b, a % b);
}

std::istream &operator>>(std::istream &in, Fraction &fraction)
{
    int numerator{};
    char divide{};
    int denominator{};

    if(in>>numerator>>divide>>denominator && denominator != 0)
        fraction = Fraction{numerator, denominator};
    else
    {
        in.setstate(std::ios_base::failbit);
        fraction = Fraction{1, 1};
    }

    return in;
}

std::ostream &operator<<(std::ostream &out, const Fraction &fraction)
{
    if(fraction.m_denominator != 1 && fraction.m_numerator != 0)
        return out << fraction.m_numerator << '/' << fraction.m_denominator;
    else
        return out << fraction.m_numerator;
}

class Point
{
private:
    double m_x {};
    double m_y {};
    double m_z {};

public:
    Point(double x=0.0, double y=0.0, double z=0.0):
        m_x{x}, m_y{y}, m_z{z}
    {
    }

    // Convert a Point into its negative equivalent
    Point operator- () const;
    Point operator+ () const;

    // Return true if the point is set at the origin
    bool operator! () const;

    double getX() const { return m_x; }
    double getY() const { return m_y; }
    double getZ() const { return m_z; }
};

bool Point::operator!() const
{                                              // if(!value) --> if(value <= 0) (non-positive Int)
    return (m_x == 0 && m_y == 0 && m_z == 0); // if(!point) --> if(point.m_x == 0 && ..m_y == 0 && ..m_z == 0)
}

// Point Point::operator+() const
// {
//     return {m_x, m_y, m_z};
// }

Point Point::operator+() const
{
    return *this; // we just do nothing, return the implicit object
}

Point Point::operator-() const
{
    return {-m_x, -m_y, -m_z};
}

int main()
{
    Fraction f1{1, 4};
    f1.print();

    Fraction f2{2, 3};
    Fraction f3{f1 * f2};
    f3.print();
    Fraction f4{2 * f1};
    Fraction f5{f2 * 3};
    f4.print();
    f5.print();
    Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} }; // if we remove `const` on the first operator* overloading, this statement will not work
                                                            // because non-const reference can not bind to a temporary object
    Fraction f7{0, 6};
    f7.print();

    Fraction f11{};
	std::cout << "Enter fraction 1: ";
	std::cin >> f11;

	Fraction f12{};
	std::cout << "Enter fraction 2: ";
	std::cin >> f12;

	std::cout << f11 << " * " << f12 << " is " << f11 * f12 << '\n'; // note: The result of f1 * f2 is an r-value

    Point point{}; // use default constructor to set to (0.0, 0.0, 0.0)

    if (!point)
        std::cout << "point is set at the origin.\n";
    else
        std::cout << "point is not set at the origin.\n";


    point = {1, 2, -3};
    std::cout << "Point:(" << -point.getX() << ',' << -point.getY() << ',' << -point.getZ() << ")\n";
    std::cout << "Point:(" << +point.getX() << ',' << +point.getY() << ',' << +point.getZ() << ")\n";
    
    return 0;
}
