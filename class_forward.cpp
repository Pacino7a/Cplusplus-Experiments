#include <iostream>
#include <string>
#include "random_s_class.h"

// use `this`(hidden ptr within the class) make program interlocking(class method(member function) returns `this`)
class Calculator
{
public:
    Calculator(){} // if you have made one already(line 85), you should write this if you need (default + senario)
    explicit Calculator(double value)
        : m_value{value}
    {}
    Calculator& reset()
    {
        *this = {}; // default constructor
        return *this;
    }
    Calculator &add(int value) // return the object back by ref, in case of making a copy
    {                          // the operator `&` will be dropped
        m_value += value;
        return *this; // `this` contains the adress of current implicit Class Object, so we return the object back by reference
    }
    Calculator &sub(int value)
    { 
        m_value -= value;
        return *this;
    }
    Calculator &mult(int value)
    {
        m_value *= value;
        return *this;
    }

    double getValue() const { return m_value; }

private:
    double m_value{};
};

Calculator setCal(const double value)
{
    return Calculator{value};
}

// class template with its member functions
class Simple
{
public:
    Simple(int id = 0) // constructor
        : m_id{id}
    {
        std::cout << "Constructor Called.\n";
    }
    ~Simple() // destructor (implicit and automatic), whose purpose of life is Clean Up
    {
        std::cout << "Destructor Called.\n";
    }

    int getID() const { return m_id; }

private:
    int m_id{};
};

template <typename T>
class Pair
{
public:
    Pair(const T& first, const T& second)    // within the scope of templated class, we can use injected class name as the constructor's name
        : m_first{first}, m_second{second}  // injected class name (not Pair<T>) serves as convinent way to replace full templated name
    {}

    bool isEqual(const Pair<T> &othr_pair) const;

private:
    T m_first{};
    T m_second{};
};

template<typename T>                                // because the class is a template class so
bool Pair<T>::isEqual(const Pair& othr_pair) const  // we need (Pair<T>::) here, instead of (Pair::)
{   // because of the first Pair<T>, we can use Pair as the type of the parameter (elision NOT deduction)
    return m_first == othr_pair.m_first and m_second == othr_pair.m_second;
}

template <typename T, typename U, typename V>
class Triad
{
public:
    Triad(const T& first,const U& second,const V& third)
        : m_first{first},m_second{second},m_third{third}
    {}
    const T& first() const { return m_first; }
    const U& second() const { return m_second; }
    const V& third() const { return m_third; }
    void print() const;

private:
    T m_first{};
    U m_second{};
    V m_third{};
};

// we want to separate this from the definition of the class
// easy for compiling and make the definition more clear
template <typename T, typename U, typename V>
void Triad<T,U,V>::print() const
{
    std::cout << '[' << m_first << ", " << m_second << ", " << m_third << "]\n";
}

// static member (variables and functions)
struct Hi
{
    static int s_value; // static member variable is `global` variable in this translate unit,
                        //  which can be accessed by anybody
    static const int sc_value{7}; // const value
};

// non-const static
int Hi::s_value{7}; // defining it does not count as accessing it (protected and private access specifier not work here)

// for Classes
class Some
{
private:
    static const int s_value{7};
    static inline int s_value2{7}; // recommended (non-constant), inline for multiple translate units (ODR)
    static constexpr int s_value3{7}; // recommended (implicit inline) (constant)
};

class SchoolData
{
public:
    SchoolData(std::string_view name)
        :  m_name{name}, m_id{s_idGenerator++}
    {}
    int getID() const { return m_id; }
    std::string_view getName() const { return m_name; }

    static int getidGenerator() { return s_idGenerator; } // implicit inline (could be called directly)

private:
    static inline int s_idGenerator{1}; // Type of static member can be deducted and allow CTAD
    std::string m_name{}; // deduction blocked
    int m_id{}; // deduction blocked
};

void print(const SchoolData& data)
{
    std::cout << '[' << data.getName() << ", " << data.getID() << "]\n";
}

int main()
{
    // this
    Calculator value1{1};
    std::cout << "Result: " << value1.add(1).mult(2).sub(1).getValue() << '\n';
    std::cout << "Reset: " << value1.reset().getValue() << '\n';

    // Simple simple{};
    // Simple simple1{simple};
    // {
    //     Simple simple2{2};
    // }

    // Pair pair1{1, 2}; // not CTAD, compiler got the information from the constructor

    Triad<int, int, int> t1{1, 2, 3};
    t1.print();
    std::cout << t1.first() << '\n';

    using namespace std::literals;
    const Triad t2{1, 2.3, "Hello"s};
    t2.print();

    Hi::s_value = 8; // like global variable
    std::cout << "static Value:" << Hi::s_value << '\n';
    // practice
    SchoolData alan{"alan"};
    SchoolData bruce{"bruce"};
    SchoolData carter{"carter"};

    print(alan);   // 1
    print(bruce);  // 2
    print(carter); // 3

    std::cout << "ID Gen Status: " << SchoolData::getidGenerator() << '\n'; // we use a static member function 
                                                        // to get the private static member variable's value

    for (int i = 0; i < 10; ++i)
    {
        // we can hide the implementation by access specifier of Class
        std::cout << Random::get<int>(1, 6) << '\t'; // use class Random instead of namespace Random
        if(i == 4)
            std::cout << '\n';
    }

    std::cout << '\n';

    return 0;
}
