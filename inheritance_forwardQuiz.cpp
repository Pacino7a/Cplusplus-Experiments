#include <iostream>


class Fruit
{
private:
    std::string m_name{};
    std::string m_color{};
public:
    explicit Fruit(const std::string& name, const std::string& color)
        :   m_name{name}, m_color{color}
    {}
    std::string_view getName() const { return m_name; }
    std::string_view getColor() const { return m_color; }
};

class Apple: public Fruit
{
protected:
    explicit Apple(const std::string& name, const std::string& color) // only drived classes can access this constructor
        :   Fruit{name,color}
    {}
public:
    explicit Apple(const std::string& color = "Red")
        :   Fruit{"Apple",color}
    {}
};

class Banana: public Fruit
{
public:
    explicit Banana(const std::string& color = "Yellow")
        :   Fruit{"Banana",color}
    {}
};

class GrannySmith: public Apple
{
public:
    explicit GrannySmith(const std::string& name = "Granny Smith Apple", const std::string& color = "Green")
        :   Apple{name,color}
    {}
};

int main()
{
    Apple a{"red"};
    Banana b{};
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";


    return 0;
}
