#ifndef FRACTION_H
#define FRACTION_H
#include "diy.h"

struct Fraction
{
    int numerator{0};  // default -> Explicit Initialization
    int denominator{1};
};

Fraction getFraction() // CAN'T return a reference of the struct object which will make the caller dangling
{
    Fraction temp{}; // only input situation needs create a temporary object
    for (;;)
    {
        std::cout << "Enter a value for the numerator: ";
        temp.numerator = getInt();
        std::cout << "Enter a value for the denominator: ";
        temp.denominator = getInt();
        
        if(temp.denominator == 0)
            std::cout << "A Fraction's denominator should not be 0! Please try again\n";
        else
            return temp;
    } 

}

constexpr void printFraction(const Fraction& f) // (CAUTION) this is a const reference
{
    if(f.denominator == 1 || f.numerator == 0)
        std::cout << f.numerator <<'\n';
    else
        std::cout << f.numerator << '/' << f.denominator <<'\n';
}

constexpr Fraction fractionsMultiply(const Fraction& f1, const Fraction& f2)
{
    // Fraction temp{};
    // temp.numerator = f1.numerator * f2.numerator;
    // temp.denominator = f1.denominator * f2.denominator;

    std::cout << f1.numerator << '/' << f1.denominator;
    std::cout << " * ";
    std::cout << f2.numerator << '/' << f2.denominator;
    std::cout << " = ";
    
    return {f1.numerator * f2.numerator, f1.denominator * f2.denominator};
}

constexpr Fraction reducedFraction(const Fraction &f)
{
    if(f.numerator == 0)
        return f;
    else if(f.denominator == 0)
    {
        std::cerr << "A Fraction's Denominator Can NOT be Zero!\n";
        std::abort();
    }
    assert(f.numerator * f.denominator != 0);
    Fraction temp{f}; // temporary fraction
    bool nagative{false};
    if(temp.denominator < 0 && temp.numerator < 0) // reduce the symbol
    {
        temp.numerator = -temp.numerator;
        temp.denominator = -temp.denominator;
    }
    else if(temp.denominator * temp.numerator < 0 ) // maintain the consistency (-/+),(+/-)-->(+/+)
    {
        nagative = true;
        temp.numerator = std::abs(temp.numerator);
        temp.denominator = std::abs(temp.denominator);
    }
    for (;;)
    {
        if(temp.numerator == 1 || temp.denominator == 1) // if numerator or denominator equal to 1, stop reduce
        {
            if(nagative) // if the fraction is nagative
                temp.numerator = -temp.numerator; // make the numerator be nagative, (+/+)-->(-/+)
            return temp;
        }    
        if(temp.denominator%temp.numerator == 0) // e.g. 3/6 -> 1/2
        {
            temp.denominator /= temp.numerator;
            temp.numerator /= temp.numerator;
        }
        else if(temp.numerator%temp.denominator == 0) // e.g. 8/4 -> 2/1
        {
            temp.numerator /= temp.denominator;
            temp.denominator /= temp.denominator;
        }
        else // e.g. 62/42 -> 31/21 or 42/62 -> 21/31
        {
            for (int i{2}; i < getMin(temp.numerator, temp.denominator);++i)
            {
                if(temp.numerator%i == 0 && temp.denominator%i == 0) // if they have common
                {
                    temp.numerator /= i;
                    temp.denominator /= i;
                    break;
                }
                else if(i == getMin(temp.numerator, temp.denominator) - 1) // if they don't
                    return temp; // stop search, return the result
            }
        }

    }
}
#endif
