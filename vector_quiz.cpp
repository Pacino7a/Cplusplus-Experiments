#include "diy.h"
#include <vector>

namespace Game
{
    
    enum Player_Item
    {
        health_potions,
        torches,
        arrows,
        max_itemtype
    };
    
    static const std::vector s_default_item{1, 5, 10};
};

class Player
{
public:
    explicit Player(const std::vector<int>& item = Game::s_default_item)
    : m_players_item{item}, m_player_heal{100}, m_player_damage{10}
    {
        assert(m_players_item.size() == Game::max_itemtype && "Item Type Management Error!");
        for(auto num:m_players_item)
            if(num < 0)
                std::abort();
    }
    int getNumHealPotions() const { return m_players_item[Game::health_potions]; }
    int getNumTorches() const { return m_players_item[Game::torches]; }
    int getNumArrows() const { return m_players_item[Game::arrows]; }
    friend void printNumOfItems(const Player& player);

private:
    std::vector<int> m_players_item{};
    int m_player_heal{};
    int m_player_damage{};
};

constexpr const std::string_view getItemName(const bool plural, const Game::Player_Item playeritem)
{
    if(plural)
    {
        switch (playeritem)
        {
            case Game::health_potions : return " Health Potions.\n";
            case Game::torches : return " Torches.\n";
            case Game::arrows : return " Arrows.\n";
            default: std::cout << "Fatal Error!\n"; std::abort();
        }
    }
    else
    {
        switch (playeritem)
        {
            case Game::health_potions : return " Health Potion.\n";
            case Game::torches : return " Torch.\n";
            case Game::arrows : return " Arrow.\n";
            default: std::cout << "Fatal Error!\n"; std::abort();
        }
    }
}
void printNumOfItems(const Player& player)
{
    int num_types{0};
    int num_items{0};
    int value{0};
    bool plural{false};
    for (size_t i{0}; i < Game::max_itemtype; ++i,++num_types,plural=false)
    {
        value = player.m_players_item[i];
        if(value > 1)
            plural = true;
        std::cout << "You have " << value << getItemName(plural,static_cast<Game::Player_Item>(i));
        num_items += value;
    }
    std::cout << "Player have " << num_types << " kinds of item and " << num_items << " items in the bag in total.\n";
}

template <typename T>
constexpr std::pair<typename std::vector<T>::size_type,typename std::vector<T>::size_type> findMaxAndMinIndex(const std::vector<T>& arr)
{
    assert(arr.size() > 0 && "The array can not be Empty!\n");
    // if(arr.size() <= 0)
    // {
    //     std::cout << "The array can not be Empty!\n";
    //     std::abort();
    // }
    using Index = std::vector<T>::size_type;
    Index max_index{0};
    Index min_index{0};
    // T max{arr[0]};
    // T min{arr[0]};
    // T value{};
    for (Index i{1}; i < arr.size(); ++i)
    {
        // value = arr[i];
        if(arr[i] > arr[max_index])
        {
            // max = value;
            max_index = i;
        }
        else if(arr[i] < arr[min_index])
        {
            // min = value;
            min_index = i;
        }
    }

    return {min_index, max_index};
}

template <typename T>
constexpr void printMaxMinWithIndex(const std::pair<typename std::vector<T>::size_type,typename std::vector<T>::size_type>& index, const std::vector<T>& arr)
{
    assert(arr.size() > 0 && "The array can not be Empty!\n");
    // if(arr.size() <= 0)
    // {
    //     std::cout << "The array can not be Empty!\n";
    //     std::abort();
    // }
    std::cout << "With Array ("; // With Array (1 ,2 ,3)
    bool first{true};
    for(const auto element:arr)
    {
        if(!first)
            std::cout << ", ";
        std::cout << element ;
        first = false;
    }
        
    std::cout<<"):\n";
    const auto min_index{index.first};
    const auto max_index{index.second};
    std::cout << "The min element has index " << min_index << " and value " << arr[min_index] << '\n';
    std::cout << "The max element has index " << max_index << " and value " << arr[max_index] << '\n';

}

template <typename T>
constexpr const T enterNumber() // we don't need to know how many scores we gotta input, just make the vector to deal with all the storage issues
{
    // arr.reserve(number_score);
    for (;;)
    {
        T enter_value{};
        std::cin >> enter_value;
        if(!std::cin)
        {
            if(std::cin.eof())
                std::exit(0);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // if(!std::cin.eof() && std::cin.peek() != '\n')
        // {
        //     std::string drop{};
        //     std::cin >> drop;
        //     std::cout << "What does " << enter_value << drop << " means? Please Try again.\n";
        //     continue;
        // }

        return enter_value;
    }
}

template <typename T>
void reciveVecFromUser(std::vector<T>& arr)
{
    std::cout << "Please enter Numbers and use `-1` to Stop: ";
    for (;;)
    {
        
        const T user_input{enterNumber<T>()};
        if(user_input == -1)
            break;
        else
        {
            if(user_input >= 0)
                arr.push_back(user_input);
            else
                std::cout << "We only accept Positive Number for now.\n";
        }

    }
}

int main()
{
    // quiz 1
    Player player1{};
    printNumOfItems(player1);
    Player player2{{1, 2, 3}};
    printNumOfItems(player2);
    // quiz 2
    std::vector v1 { 3, 8, 2, 5, 7, 8, 3 };
    std::vector v2 { 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };
    auto v1index_maxandmin {findMaxAndMinIndex(v1)};
    printMaxMinWithIndex(v1index_maxandmin, v1);
    auto v2index_maxandmin {findMaxAndMinIndex(v2)};
    printMaxMinWithIndex(v2index_maxandmin, v2);
    //  quiz 3
    std::vector<int> user_i1{};
    reciveVecFromUser(user_i1);
    printMaxMinWithIndex(findMaxAndMinIndex(user_i1), user_i1);
    std::vector<double> user_i2{};
    reciveVecFromUser(user_i2);
    printMaxMinWithIndex(findMaxAndMinIndex(user_i2), user_i2);
    // quiz 4
    // C++man

    return 0;
}
