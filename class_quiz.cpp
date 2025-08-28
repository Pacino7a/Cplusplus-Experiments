#include <iostream>
#include <cmath>

template <typename T>
constexpr T square(T x)
{
    return (x * x);
}

class Point2d
{
public:
    constexpr Point2d(){} // default
    Point2d(double x,double y) // main
        :m_x{x},m_y{y} // you don't need make a list when you just have few members, just write them as one line.
    {}

    void print() const // we should put this out here
    {
        std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
    }

    double distanceTo(Point2d& othr_point)
    {
        return std::sqrt(square(m_x - othr_point.m_x) + square(m_y - othr_point.m_y));
    }

private:
    double m_x{}; // default initialization
    double m_y{};
};

class Fraction
{
public:
    explicit Fraction(int numerator = 0, int denominator = 1)    // we use `explicit` to prevent implicit conversion,
        : m_numerator{numerator}, m_denominator{denominator}     // e.g. true -> 1 -> {1, default value} -> Fraction{1,1}
    {                                                            // aka. we just use A `true` and get A Fraction
        if(denominator == 0)                                     // which doesn't make any sense, so it must be blocked by `explicit`
        {
            std::cerr << "Create Fraction Failed, becaues your denominator is ZERO!\n";
            std::abort();
        }
    }

    Fraction multiply(const Fraction& othr_fraction) const // we don't need get this out, because it will make situation more complicated
    {
       return Fraction{m_numerator * othr_fraction.m_numerator, m_denominator * othr_fraction.m_denominator};
    }

    int getNumerator() const { return m_numerator; }
    int getDenominator() const { return m_denominator; }

private:
    int m_numerator{};
    int m_denominator{1};
};

Fraction getFraction()
{
    int numerator{};
    int denominator{};
    std::cout << "Enter a value for numerator: ";
    std::cin >> numerator;
    std::cout << "Enter a value for denominator: ";
    std::cin >> denominator;
    if(denominator == 0)
    {
        std::cerr << "get Failed, becaues your denominator is ZERO!\n";
        std::abort();
    }

    return Fraction{numerator, denominator}; // return {numerator, denominator}; will not convert to Fraction (implicit)
}

void printFraction(const Fraction& f)
{
    std::cout << f.getNumerator() << '/' << f.getDenominator() << '\n';
}

int main()
{
    // quiz 1
    Point2d first{};
    Point2d second{3.0, 4.0};
    // Point2d third{4.0}; // no constructor

    first.print();
    second.print();
    std::cout << "The distance between the first point and the second is " << first.distanceTo(second) << '\n';
    // quiz 2
    // (1) all in class
    // Fraction f1{};
    // f1.getFraction(); // if we let getFraction as a member function, we must create an instance to call
    // Fraction f2{};
    // f2.getFraction();

    // (2) separate some functions
    Fraction f1{getFraction()}; // f1 = {1,2} and f1 = (1,2) blocked
    Fraction f2{getFraction()};
    std::cout << "Your fraction multiplied together: ";

    // f1.multiply(f2).printFraction(); // member function way (will break the consistency). Separating this out of the class is needed.

    printFraction(f1.multiply(f2));


    return 0;
}
