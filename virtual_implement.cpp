#include <iostream>
#include <array>

class Animal
{
private:
    std::string m_name{};
    // std::string m_speak{}; // we don't need this anymore

protected:
    Animal(std::string_view name)
        : m_name{name}
    {}

    Animal(Animal &&) = default;
    Animal(const Animal &) = delete;
    Animal &operator=(const Animal &) = delete;
public:
    virtual ~Animal() = default;
    std::string_view getName() const { return m_name; }
    virtual std::string_view speak() const { return "???"; } // set virtual, this will not actually be called
};

class Cat: public Animal
{
public:
    Cat(std::string_view name)
        :   Animal{name}
    {}
    Cat(Cat &&) = default;
    virtual ~Cat() = default;
    std::string_view speak() const override { return "Meow\n"; } // and override here (implicit virtual because The same function in the Base is Virtual)
};

class Dog: public Animal
{
public:
    Dog(std::string_view name)
        :   Animal{name}
    {}

    Dog(Dog &&) = default;
    virtual ~Dog() = default;
    // virtual was a great help
    virtual std::string_view speak() const { return "Woof\n"; } // if there are 100 kinds of animals, you need write this for 100 times
};

int main()
{
    const Cat fred{ "Fred"};
    const Cat misty{ "Misty" };
    const Cat zeke{ "Zeke" };

    const Dog garbo{ "Garbo" };
    const Dog pooky{ "Pooky" };
    const Dog truffle{ "Truffle" };

    // C++20
    const auto &cats{std::to_array<Cat>({{"Fred"}, {"Misty"}, {"Zeke"}})}; // we need initialize cat's sound every time, but it is better than 100 times doom
    const auto &dogs{std::to_array<Dog>({{"Garbo"}, {"Pooky"}, {"Truffle"}})};

    const auto animals{std::to_array<const Animal *>({&fred, &garbo, &misty, &pooky, &truffle, &zeke})};
    
    // Derived Mode (Bad)
    for (const auto& cat : cats)
    {
        std::cout << cat.getName() << " says " << cat.speak() << '\n'; // virtual doesn't work when the object is not a refence or a pointer of a Drived Class
    }                                                                  // it works as usual

    for (const auto& dog : dogs)
    {
        std::cout << dog.getName() << " says " << dog.speak() << '\n';
    }

    // Roll Back to Animal
    for(const auto animal:animals) // pointer here and `virtual` working
    {
        std::cout << animal->getName() << " says " << animal->speak() << '\n'; // Animal::speak() here
    }

    return 0;
}
