#include <iostream>
#include <vector>
#include <array>
#include "random_s_class.h"
#include "diy.h"

class Creature
{
public:
    explicit Creature(const std::string_view name, const char symbol, const int health, const int damage, const int gold)
        : m_name{name}, m_symbol{symbol}, m_health{health}, m_damage{damage}, m_gold{gold}
    {
    }

    std::string_view getName() const { return m_name; }
    char getSymbol() const { return m_symbol; }
    int getHealth() const { return m_health; }
    int getDamage() const { return m_damage; }
    int getGold() const { return m_gold; }

    void reduceHealth(const int damage) { m_health -= damage; }
    bool isDead() const { return m_health <= 0; }
    void addGold(const int gold) { m_gold += gold; }
    void addDamage() { ++m_damage; }

    void healFromPotion(const int heal) { m_health += heal; }
    void poisonedFromPotion(const int poison) { m_health -= poison; }
    void strongerFromPotion(const int strength) { m_damage += strength; }
    void strengthPotionNoLongerWorks(const int damage_before) { m_damage = damage_before; }

private:
    std::string m_name{};
    char m_symbol{};
    int m_health{};
    int m_damage{};
    int m_gold{};
};

struct Potion_CombinationSV
{
    std::string_view effect{};
    std::string_view type{};
};

class Potions
{
public:
    enum Types
    {
        health,
        strength,
        poison,
        max_type
    };
    enum Effect
    {
        small,
        medium,
        large,
        max_effect
    };

private:
    static inline Potion_CombinationSV combinations[][3]{{{"Small", "Health"}, {"Small", "Strength"}, {"Small", "Poison"}},
                                                         {{"Medium", "Health"}, {"Medium", "Strength"}, {"Medium", "Poison"}},
                                                         {{"Large", "Health"}, {"Large", "Strength"}, {"Large", "Poison"}}};

    Types m_type{};
    Effect m_effect{};
    explicit Potions(const Types type, const Effect effect)
        : m_type{type}, m_effect{effect}
    {
    }

public:
    Potion_CombinationSV getPotionSV() const { return combinations[m_effect][m_type]; }
    static Potions getRandomPotion() { return Potions{static_cast<Types>(Random::get<int>(0, max_type - 1)), static_cast<Effect>(Random::get<int>(0, max_effect - 1))}; }
    Types getPotionType() const { return m_type; }
    Effect getPotionEffect() const { return m_effect; }
};

class Player : public Creature
{
private:
    int m_level{};

public:
    explicit Player(const std::string_view name, const char symbol, const int health, const int damage, const int gold, const int level) // full constructor
        : Creature{name, symbol, health, damage, gold}, m_level{level}
    {
    }

    explicit Player(const std::string_view name) // basic constructor
        : Player(name, '@', 10, 1, 0, 1)
    {
    }

    int getLevel() const { return m_level; }
    void levelUp()
    {
        ++m_level;
        addDamage();
    }
    bool hasWon() const { return m_level >= 20; }
};

class Monster : public Creature
{
private:
    explicit Monster(const std::string_view name, const char symbol, const int health, const int damage, const int gold)
        : Creature{name, symbol, health, damage, gold}
    {
    }

    // CAUTION: A `protected` member can't be accessed outside of the constructor or member function!
    // And you can't create a Monster table by calling Monster() here neither, because our class is INCOMPLETE yet.
    static inline Creature monsterData[]{Creature{"Dragon", 'D', 20, 4, 100}, Creature{"Orc", 'O', 4, 2, 25}, Creature{"Slime", 'S', 1, 1, 10}};
    // because all of our Monsters are predefined, so we use a look-up table for construction
    // static_assert
    

public:
    enum Types
    {
        dragon,
        orc,
        slime,
        max_type
    };

    explicit Monster(const Types type)
        : Creature{monsterData[type]}
    {}

    static Monster getRandomMonster() { return Monster{static_cast<Types>(Random::get<int>(0, max_type - 1))}; }
};

// void gameLoop(Player& player)
// {
//     for (;!player.hasWon() && !player.isDead();) // gameloop
//     {
//         Monster encounter{Monster::getRandomMonster()};
//         std::cout << "You have encounter a " << encounter.getName() << "(" << encounter.getSymbol() << ")\n";
//         for (char user_cmd{};;) // combat loop
//         {
//             std::cout << "(R)un or (F)ight:";
//             user_cmd = getCharacter();
//             if (static_cast<char>(static_cast<unsigned int>(user_cmd)) == 'f')
//             {
//                 // player first
//                 // player's turn
//                 encounter.reduceHealth(player.getDamage());
//                 std::cout << "You hit the " << encounter.getName() << " for " << player.getDamage() << " damage!\n";
//                 if (encounter.isDead())
//                 {
//                     std::cout << "You killed " << encounter.getName() << '\n';
//                     player.addGold(encounter.getGold());
//                     player.levelUp();
//                     break;
//                 }
//             }
//             else
//             {
//                 if (Random::get<int>(0, 1) == 1)
//                 {
//                     std::cout << "You successfully fled.\n";
//                     break;
//                 }
//                 else
//                     std::cout << "You failed to fled.\n";
//             }

//             // monster's turn
//             std::cout << encounter.getName() << " is roaring and hitting you for " << encounter.getDamage() << " damage.\n";
//             player.reduceHealth(encounter.getDamage());
//             if(player.isDead()) break;
//         }
//     }
//     if(player.hasWon())
//     {
//         std::cout << "Congratulations! You beat the Game\n"
//                   << "With " << player.getHealth() << "Health and " << player.getGold() << " gold.\n";
//     }
//     else
//         std::cout << "You died at level " << player.getLevel() << " and with " << player.getGold() << " gold.\n"
//                   << "Too bad you can't take it with you!";
// }

// we can transform this to a member function of Player
Player &playerDrinksPotion(Player &player, bool &stronger)
{
    Potions drop_potion{Potions::getRandomPotion()};
    std::cout << "You found a mythical potion! ";
    char user_cmd{};
    do
    {
        std::cout << "Do you want to drink it? [y/n]: ";
        user_cmd = getCharacter();
        user_cmd = static_cast<char>(tolower(static_cast<unsigned int>(user_cmd)));
    } while (user_cmd != 'y' && user_cmd != 'n');
    if (user_cmd == 'y') // player choose to drink it
    {
        std::cout << "You drank a " << drop_potion.getPotionSV().effect << " Potion of " << drop_potion.getPotionSV().type << '\n';
        Potions::Effect effect{drop_potion.getPotionEffect()};
        switch (drop_potion.getPotionType())
        {
        case Potions::health:
            if (effect == Potions::small)
                player.healFromPotion(1);
            else if (effect == Potions::medium)
                player.healFromPotion(3);
            else
                player.healFromPotion(5);
            return player;
        case Potions::poison:
            if (effect == Potions::small)
                player.poisonedFromPotion(2);
            else if (effect == Potions::medium)
                player.poisonedFromPotion(3);
            else
                player.poisonedFromPotion(4);
            return player;
        case Potions::strength:
            stronger = true;
            if (effect == Potions::small)
                player.strongerFromPotion(1);
            else if (effect == Potions::medium)
                player.strongerFromPotion(2);
            else
                player.strongerFromPotion(4);
            return player;
        default:
            std::cerr << "Fatal Error -1.\n";
            std::exit(-1);
        }
    }
    else
    {
        std::cout << "You dropped the Potion and chose to keep Going.\n";
        return player;
    }
}

bool attackMonster(Player &player, Monster &monster, int &ori_damage, bool &stronger)
{
    monster.reduceHealth(player.getDamage());
    std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage!\n";
    if (stronger)
    {
        std::cout << "The Potion's Power Dissipated.\n";
        player.strengthPotionNoLongerWorks(ori_damage);
        stronger = false;
    }
    if (monster.isDead())
    {
        std::cout << "You killed the " << monster.getName() << '\n';
        std::cout << "You found " << monster.getGold() << " gold.\n";
        player.addGold(monster.getGold());
        player.levelUp();
        std::cout << "You are now level " << player.getLevel() << '\n';
        if (Random::get<int>(0, 9) < 3) // 30% getting a Potion to drink
        {
            ori_damage = player.getDamage(); // save current damage for restoring it
            playerDrinksPotion(player, stronger);
        }

        return true; // if we killed the monster
    }
    return false;
}

bool attackPlayer(Player &player, Monster &monster)
{
    std::cout << monster.getName() << " is roaring and hitting you for " << monster.getDamage() << " damage.\n";
    player.reduceHealth(monster.getDamage());
    if (player.isDead())
        return true;
    else
        return false;
}

void fightMonster(Player &player, Monster &monster) // combat loop
{
    for (char user_cmd{};;)
    {
        static int original_damage{};
        static bool stronger_enhanced{false};
        do
        {
            std::cout << "(R)un or (F)ight:";
            user_cmd = getCharacter();
            user_cmd = static_cast<char>(tolower(static_cast<unsigned int>(user_cmd)));
        } while (user_cmd != 'f' && user_cmd != 'r');
        if (user_cmd == 'f')
        {
            // player first
            // player's turn
            if (attackMonster(player, monster, original_damage, stronger_enhanced)) // if player kill the monster, go to the next round
                return;
        }
        else
        {
            if (Random::get<int>(0, 1) == 1)
            {
                std::cout << "You successfully fled.\n";
                return; // if player fled, go to the next round
            }
            else
                std::cout << "You failed to fled.\n";
        }

        // monster's turn
        if (attackPlayer(player, monster)) // if The monster killed Player, end the game
            return;
    }
}

void gameLoop(Player &player)
{
    for (; !player.hasWon() && !player.isDead();) // gameloop
    {
        Monster encounter{Monster::getRandomMonster()};
        std::cout << "You have encounter a " << encounter.getName() << "(" << encounter.getSymbol() << ")\n";
        fightMonster(player, encounter);
    }
    if (player.hasWon())
    {
        std::cout << "Congratulations! You beat the Game\n"
                  << "With " << player.getHealth() << "Health and " << player.getGold() << " gold.\n";
    }
    else
        std::cout << "You died at level " << player.getLevel() << " and with " << player.getGold() << " gold.\n"
                  << "Too bad you can't take it with you!\n";
}

int main()
{
    // Creature o{ "orc", 'o', 4, 2, 10 };
    // o.addGold(5);
    // o.reduceHealth(1);
    // std::cout << "The " << o.getName() << " has " << o.getHealth() << " health and is carrying " << o.getGold() << " gold.\n";

    std::cout << "What's Your name? ";
    std::string name{};
    std::cin >> name;
    Player player{name};
    std::cout << "Welcome " << player.getName() << '\n';
    //           << "You have " << player.getHealth() << " health and are carrying " << player.getGold() << " gold.\n";

    // Monster m{ Monster::Types::orc };
    // std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";

    // for (int i{ 0 }; i < 10; ++i)
    // {
    // 	Monster m_r{ Monster::getRandomMonster() };
    // 	std::cout << "A " << m_r.getName() << " (" << m_r.getSymbol() << ") was created.\n";
    // }
    gameLoop(player);

    system("pause");

    return 0;
}
