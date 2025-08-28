#include <iostream>
#include <array>

class Animal
{
private:
    std::string m_name{};
    std::string m_speak{};

protected:
    Animal(std::string_view name, std::string_view speak)
        : m_name{name}, m_speak{speak}
    {}

    Animal(Animal &&) = default;
    Animal(const Animal &) = delete;
    Animal &operator=(const Animal &) = delete;
public:
    std::string_view getName() const { return m_name; }
    std::string_view speak() const { return m_speak; }
};

class Cat: public Animal
{
public:
    Cat(std::string_view name, std::string_view speak)
        :   Animal{name,speak}
    {}

    std::string_view speak() const { return "Meow\n"; }
};

class Dog: public Animal
{
public:
    Dog(std::string_view name, std::string_view speak)
        :   Animal{name,speak}
    {}

    std::string_view speak() const { return "Woof\n"; }
};

int main()
{
    const Cat fred{ "Fred", "Meow"};
    const Cat misty{ "Misty", "Meow" };
    const Cat zeke{ "Zeke", "Meow" };

    const Dog garbo{ "Garbo", "Woof" };
    const Dog pooky{ "Pooky", "Woof" };
    const Dog truffle{ "Truffle", "Woof" };

    // C++20
    const auto &cats{std::to_array<Cat>({{"Fred", "Meow"}, {"Misty", "Meow"}, {"Zeke", "Meow"}})}; // we need initialize cat's sound every time, but it is better than 100 times doom
    const auto &dogs{std::to_array<Dog>({{"Garbo", "Woof"}, {"Pooky", "Woof"}, {"Truffle", "Woof"}})};

    const auto animals{std::to_array<const Animal *>({&fred, &garbo, &misty, &pooky, &truffle, &zeke})};
    
    // Derived Mode
    for (const auto& cat : cats) // if there are 100 kinds of animals, you need write this for 100 times
    {
        std::cout << cat.getName() << " says " << cat.speak() << '\n';
    }

    for (const auto& dog : dogs)
    {
        std::cout << dog.getName() << " says " << dog.speak() << '\n';
    }

    // Roll Back to Animal
    // we add one member variable to achieve this
    // if we need more ways to differentiate Cats and Dogs
    // we need to add a GREAT number of variables to do that
    // Our Base-Class could become quite large memory-wise
    // Not good for random output and randomly initializing
    for(const auto animal:animals)
    {
        std::cout << animal->getName() << " says " << animal->speak() << '\n'; // Animal::speak() here
    }

    return 0;
}
