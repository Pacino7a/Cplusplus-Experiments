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
    
    Cents& operator+=(const Cents& other)
    {
        m_cents += other.m_cents;
        return *this;
    }
    Cents& operator/=(const Cents& other)
    {
        m_cents /= other.m_cents;
        return *this;
    }
    Cents& operator/=(const int value)
    {
        m_cents /= value;
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &out, const Cents &cent); // use your friendship when you use a STL class or third-party class
    friend Cents operator/(const Cents &cent, int value); // use your friendship when you don't need to modify the obj

    auto operator<=>(const Cents &cent) const = default; // >,<,>=,<=
    bool operator==(const Cents &cent) const = default;  // ==,!=
    // friend double operator/(const Cents& cent, int value);
    // operator int() { return m_cents; } // Cents -> int
};

std::ostream& operator<<(std::ostream &out, const Cents &cent)
{
    return out << cent.m_cents;
}

Cents operator/(const Cents& cent, int value)
{
    return Cents{cent.m_cents / value};
}

template <typename T>
T average(const T* array, int length)
{
    T sum{};
    for (int i = 0; i < length; ++i)
    {
        sum += array[i];
    }
    return sum/length;
}

int main()
{
    Cents centsArray[]{Cents{3}, Cents{4}, Cents{5}, Cents{6}};
    std::cout << "The average of Cents: " << average(centsArray, 4);

    return 0;
}
