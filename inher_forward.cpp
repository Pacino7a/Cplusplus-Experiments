#include <iostream>


class Base
{
private:
    int m_value{};
public:
    Base(int value)
        :   m_value{value}
    {}
protected:
    void printValue() const { std::cout << m_value; }
};

class Derived: public Base
{
public:
    Derived(int value)
    :   Base{value}
    {}

    using Base::printValue; // we use this statement make the `protected` member in Base to `public` in Derived
                            // using xxx in public here
};
int main()
{
    [[maybe_unused]]Base base{7};
    // base.printValue(); // protected here (not allow access from PUBLIC)

    Derived derived{7};
    derived.printValue();

    return 0;
}

