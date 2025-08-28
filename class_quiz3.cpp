#include <iostream>
#include "random_s_class.h"

constexpr std::string_view chooseName(int name);
constexpr std::string_view chooseRoar(int roar);

// way 1
class Monster
{
public:
    enum Type
    {
        Dragon,
        Goblin,
        Orge,
        Orc,
        Skeleton,
        Troll,
        Vampire,
        Zombie,
        number_type
    };
    Monster(Type type, int choice_name, int choice_roar, int rand_health)
        : Monster(type,chooseName(choice_name), chooseRoar(choice_roar), rand_health)
    {}
    Monster(Type type,std::string_view name,std::string_view rora,int health)
        : m_type{type}
        , m_name{name}
        , m_roar{rora}
        , m_health{health}
    {}
    const std::string& getName() const { return m_name; }
    const std::string& getRoar() const { return m_roar; }
    constexpr void print() const;
    static Monster generate();

private:
    Type m_type{};
    std::string m_name{};
    std::string m_roar{};
    int m_health{};

    // all the static members have a whole Period of this Program
    // they are created at the begining of this program and will be distroied at the end of the program
    static inline Type random_type{static_cast<Type>(Random::get<int>(0,number_type-1))};
    static inline int random_name{Random::get<int>(1, 5)};
    static inline int random_roar{Random::get<int>(1, 5)};
    static inline int random_health{Random::get<int>(1, 100)};
};

constexpr void Monster::print() const
{
    std::cout << getName();
    switch (m_type)
    {
    case Dragon:
        std::cout << " the Dragon ";
        break;
    case Goblin:
        std::cout << " the Goblin ";
        break;
    case Orge:
        std::cout << " the Orge ";
        break;
    case Orc:
        std::cout << " the Orc ";
        break;
    case Skeleton:
        std::cout << " the Skeleton ";
        break;
    case Troll:
        std::cout << " the Troll ";
        break;
    case Vampire:
        std::cout << " the Vampire ";
        break;
    case Zombie:
        std::cout << " the Zombie ";
        break;
    default:
        std::cout << " You Know Who ";
        break;
    }

    if(m_health > 0)
        std::cout << "has " << m_health << " hit points and says " << getRoar() << ".\n";
    else
        std::cout << "is dead.\n";
}

Monster Monster::generate()
{
    return {random_type, random_name, random_roar, random_health};
}

constexpr std::string_view chooseName(int name)
{
    switch (name)
    {
    case 1:
        return "Bones";
    case 2:
        return "Bargle";
    case 3:
        return "Fizzc";
    case 4:
        return "Ezio";
    case 5:
        return "Anuild";

    default:
        return "YouKnowWho";
    }
}

constexpr std::string_view chooseRoar(int roar)
{
    switch (roar)
    {
    case 1:
        return "*rattle*";
    case 2:
        return "*hooha*";
    case 3:
        return "*crack*";
    case 4:
        return "*KILLSS*";
    case 5:
        return "*hhhhhaa*";

    default:
        return "*Silence*";
    }
}

// way 2
namespace MonsterGenerator
{
    Monster::Type random_type{static_cast<Monster::Type>(Random::get<int>(0,Monster::number_type-1))};
    int random_name{Random::get<int>(1, 5)};
    int random_roar{Random::get<int>(1, 5)};
    int random_health{Random::get<int>(1, 100)};
    std::string_view chooseName(int name)
    {
        switch (name)
        {
        case 1:
            return "Bones";
        case 2:
            return "Bargle";
        case 3:
            return "Kuga";
        case 4:
            return "Niioz";
        case 5:
            return "Anuild";

        default:
            return "YouKnowWho";
        }
    }

    std::string_view chooseRoar(int roar)
    {
        switch (roar)
        {
        case 1:
            return "*rattle*";
        case 2:
            return "*hooha*";
        case 3:
            return "*craak*";
        case 4:
            return "*KILLSS*";
        case 5:
            return "*hhhhhaa*";

        default:
            return "*Silence*";
        }
    }
    Monster generate()
    {
        return {random_type, chooseName(random_name), chooseRoar(random_roar), random_health};
    }
}

int main()
{
    // Monster Nobody{};
    Monster skeleton{Monster::Skeleton, "Bones", "*rattle*", 4};
    skeleton.print();

    Monster m{MonsterGenerator::generate()}; // namespace
    m.print(); // (method)
    
    Monster::generate().print(); // class (static method)



    return 0;
}
