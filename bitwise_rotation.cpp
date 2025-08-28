#include <iostream>
#include <bitset>

constexpr std::bitset<8> rotlr(std::bitset<8> x, int move, bool left)
{
    // constexpr std::bitset<8> seven{0b1000'0000};
    // constexpr std::bitset<8> zero{0b0000'0001};

    if(left)
    {        
        for (int i = 0; i < move; i++) // shift left, step by step
        {
            if(x.test(7)) // if the highest bit has been set
            // if((x & seven) == seven)
            {
                x <<= 1; // shift left 1 step, and re-assign to itself
                x.set(0); // set the lowest bit
                // x |= 1;
            }
            else // highest bit is empty
                x <<= 1;  // just shift left
        }
    }
    else // right
    {
        for (int i = 0; i < move; i++)
        {
            if(x.test(0))
            //if((x & zero) == zero)
            {
                x >>= 1;
                x.set(7);
                //x |= seven;
            }
            else
                x >>= 1;
        }
    }

    return x;
}

int main()
{
    std::uint8_t me{};
    // bit masks
    [[maybe_unused]] constexpr std::uint8_t isHungry{1 << 0}; // status of hungry at position 0
    //...
    [[maybe_unused]] constexpr std::uint8_t isCrying{1 << 7}; // status of crying at position 7

    // joint the states of isHungry and isCrying
    constexpr std::uint8_t Hungry_Crying{isHungry | isCrying};

    me |= Hungry_Crying;    // set Hungry and Crying
    me &= ~isCrying;   // reset crying

    std::cout << std::boolalpha;
    std::cout << "I am hungry? " << static_cast<bool>(me & isHungry) << '\n'; // read the status
    std::cout << "I am Crying? " << static_cast<bool>(me & isCrying) << '\n';
    
    if(0)
    {
        constexpr std::bitset<8> mySet{0b1001'0110};
        constexpr int move{2};
        constexpr bool left{false}; // false - left, true - right
        std::cout << "Origin Set: " << mySet << '\n';
        std::cout << ((left) ? "shift left " : "shift right ")
                << move << " Steps: " << rotlr(mySet, move, left) << '\n';
    }

    return EXIT_SUCCESS;
}
