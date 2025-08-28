#include <iostream>

namespace Data
{
    enum Color
    {
        red,
        green,
        blue,
        purple,
        pink,
        yellow,
        max_type
    };
}

class Fruit
{
private:
    std::string m_name{};
    Data::Color m_color{};
public:
    explicit Fruit(const std::string& name, const Data::Color color)
        : m_name{name}, m_color{color}
    {}

    std::string_view getName() const { return m_name; }
    std::string_view getColor() const;
    friend std::ostream& operator<<(std::ostream& out, const Fruit& fruit)
    {
        return out << fruit.getName() << ", " << fruit.getColor();
    }
};

std::string_view Fruit::getColor() const
{
    switch (m_color)
    {
    case Data::red:
        return "Red";
    case Data::green:
        return "Green";
    case Data::blue:
        return "Blue";
    case Data::pink:
        return "Pink";
    case Data::purple:
        return "Purple";
    case Data::yellow:
        return "Yellow";
    default:
        return "None";
    }
}

class Apple: public Fruit
{
private:
    double m_fiber{};
public:
    explicit Apple(const std::string& name, const Data::Color color, const double fiber)
    :   Fruit{name,color}, m_fiber{fiber}
    {}
    friend std::ostream& operator<<(std::ostream& out, const Apple& apple)
    {
        // return out << "Apple(" << apple.getName() << ", " << apple.getColor() << ", " << apple.m_fiber << ")\n";
        return out << "Apple(" << static_cast<const Fruit &>(apple) << ", " << apple.m_fiber << ")\n"; 
        // In order to call parent's friend, we need to pretend to be our parent
    }
};

class Banana: public Fruit
{
public:
    explicit Banana(const std::string& name, const Data::Color color)
    :   Fruit{name,color}
    {}
    friend std::ostream& operator<<(std::ostream& out, const Banana& banana)
    {
        return out << "Banana(" << static_cast<const Fruit &>(banana) << ")\n";
    }
};

int main()
{
    const Apple a{ "Red delicious", Data::red, 4.2 };
	std::cout << a << '\n';

	const Banana b{ "Cavendish", Data::yellow};
	std::cout << b << '\n';
    return 0;
}

