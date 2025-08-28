#ifndef MONSTER_H
#define MONSTER_H
#include <iostream>
#include <string>

struct Monster
{
    enum class Monstertype
    {
        orge,
        dragon,
        orc,
        giant_spider,
        slime,
    };

    Monstertype type{}; // we can just value-initialize the member variables
    std::string name{}; 
    double health{};
};

// An enumerated type holds integral value, for the sake of performance, which should pass by value
// AKA. pass by a ref will make a ptr and may introduce additional indirect addressing, 
// which may slightly increase access time.
constexpr std::string_view getMonsterType(const Monster::Monstertype type)
{
    using enum Monster::Monstertype;
    switch (type)
    {
    case orge:
        return "Orge";
    case orc:
        return "Orc";
    case dragon:
        return "Dragon";
    case giant_spider:
        return "Giant Spider";
    case slime:
        return "Slime";
    default:
        std::cout << "Fatal Error (Enumeration Out of the Bound)\n";
        std::abort();
    }
}

std::ostream &operator<<(std::ostream &out, Monster::Monstertype type) // enumeration is an integral value 
{                                                                      // and using its reference will be costy
    return out << getMonsterType(type);
}

void printMonster(Monster &monster)
{
    std::cout << "This " << monster.type << " is named " << monster.name << " and has " << monster.health << " health.\n";
}

#endif
