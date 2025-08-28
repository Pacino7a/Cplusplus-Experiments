#include "diy.h"
#include <iostream>
#include <array>

struct Student
{
    int id{};
    std::string_view name{};
};

struct Item
{
    std::string_view name{};
    int gold{};
};

constexpr std::array students{Student{1, "Jane"}, Student{2, "Joe"}, Student{3, "Kate"}};

const Student* findStudent(const int id)
{
    for(const auto& student:students)
    {
        if(student.id == id)
        {
            return &student;
        }
    }

    return nullptr;
}
template <std::size_t N>
constexpr void printItemArray(const std::array<Item,N>& arr)
{
    for(const auto& item:arr)
    {
        std::cout << "A " << item.name << " costs " << item.gold << " golds.\n";
    }
    std::cout << '\n';
}

namespace Animal
{
    enum Types
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        max_types
    };

    struct Data
    {
        Animal::Types type{};
        int num_legs{};
        std::string sound{};
    };

    using namespace std::literals;
    constexpr std::array animalType{"chicken"sv, "dog"sv, "cat"sv, "elephant"sv, "duck"sv, "snake"sv};
    constexpr std::array data{
        Data{chicken, 2, "cluck"},
        Data{dog, 4, "woof"},
        Data{cat, 4, "meow"},
        Data{elephant, 4, "pawoo"},
        Data{duck, 2, "quack"},
        Data{snake, 0, "sieess"}
    };
    static_assert(data.size() == max_types && data.size() == animalType.size() && "Data length doesn't match!\n");

}


constexpr void toLowerCase(std::string& str)
{
    for(char& character:str)
    character = static_cast<char>(tolower(static_cast<unsigned char>(character)));
}

std::istream& operator>>(std::istream& in,Animal::Data& animal)
{
    std::string input{};
    std::getline(in >> std::ws, input);
    toLowerCase(input);
    for (std::size_t index{0}; index < Animal::max_types; ++index)
    {
        if (input == Animal::animalType[index])
        {
            animal = Animal::data[index];
            return in;
        }
    }

    in.setstate(std::ios_base::failbit);

    animal = {};
    return in;
}

constexpr std::string_view getAnimalName(const Animal::Types type)
{
    return Animal::animalType[static_cast<std::size_t>(type)];
}
std::ostream& operator<<(std::ostream& out,const Animal::Types type)
{
    return out << getAnimalName(type);
}

std::ostream& operator<<(std::ostream& out,const Animal::Data& data)
{
    return out << "A " << data.type << " has " << data.num_legs << " and says " << data.sound << '\n';
}

void printUserAndRest(const bool in_vaild, const Animal::Data& user_input)
{
    if(in_vaild)
        std::cout << user_input;
    else
        std::cout << "That animal couldn't be found.\n";
    std::cout << "\nHere is the data for the rest of the animals:\n";
    for(const Animal::Data& animal:Animal::data)
    {
        if(in_vaild && animal.type == user_input.type) // if user's input is valid, we need ignore the input animal and print the other out
            continue;
        else
            std::cout << animal;
    }
}


int main()
{
    // constexpr std::array halo{'h', 'e', 'l', 'l', 'o'};
    // std::cout << "The length of halo is: " << halo.size() << '\n';
    // std::cout << halo[1] << halo.at(1) << std::get<1>(halo) << '\n'; // std::get<length>() is recommended

    // const Student *find1{findStudent(1)}; // ref and ptr are
    // std::cout << "You found " << (find1 ? find1->name : "Nobody") << '\n';
    // const Student *find2{findStudent(2)};
    // std::cout << "You found " << (find2 ? find2->name : "Nobody") << '\n';

    // constexpr std::array<Item, 4> store{{{"Sword", 5}, {"Dagger", 3}, {"Club", 2}, {"Spear", 7}}};
    // constexpr std::array<Item, 4> store_2{Item{"Sword", 5}, {"Dagger", 3}, {"Club", 2}, {"Spear", 7}}; // new way to make a aggregate type array
    // printItemArray(store);
    // printItemArray(store_2);

    Animal::Data user_animal{};
    std::cout << "Enter an animal: ";
    std::cin >> user_animal;
    const bool input_valid{(std::cin ? true : false)};
    if(!input_valid)
        std::cin.clear();
    printUserAndRest(input_valid, user_animal);

    return 0;
}
