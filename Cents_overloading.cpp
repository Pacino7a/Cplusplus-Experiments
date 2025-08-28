#include <iostream>
#include <utility>
#include <cassert>

// typecast overloading
class Cents
{
private:
    int m_cents{};
public:
    explicit Cents(int cents=0)
    : m_cents{cents}
    {}

    // int getCents() { return m_cents; }  // conversion (Cents -> int) of int cast (bad way, mess your program up)

    // when you make this `explicit`, the implicit conversion is not allowed anymore.
    // you need static_cast for `explicit` when you need convert this to another type.
    explicit operator int() const { return m_cents; } // overloaded int cast (can't be a static member function)
    void setCents(int cents) { m_cents = cents; }

};

class Dollars
{
private:
    int m_dollars{};
public:
    explicit Dollars(int dollars = 0)
        : m_dollars {dollars}
        {}


    operator Cents() const { return Cents{m_dollars * 100}; } // typecast (Dollar -> Cents) (Same thing)
};

void printInt(int value)
{
    std::cout << value << '\n';
}

void printCents(Cents cents)
{
    std::cout << static_cast<int>(cents) << '\n'; // cents will implicitly cast to int here
}

int main()
{
    Cents cent{10};
    
    // The statements below need typecast for conversion
    printInt(static_cast<int>(cent)); // we need a int parameter here, the compiler will check the conversion's existence -> operator int()
    std::cout << static_cast<int>(cent) << '\n';

    Dollars dollar{10};
    printCents(dollar); // Dollars will implicitly convert to Cents here

    return 0;
}
