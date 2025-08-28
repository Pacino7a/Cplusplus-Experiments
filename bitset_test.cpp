#include <iostream>
#include <bitset>

int main()
{
    // first look
    std::bitset<8> bits{0b0000'0101}; // Use a Byte to carry 8 bit flags
    bits.set(3); // set the value of position 3 to 1
    bits.flip(1); // flip the value of position 1, 0 <-> 1
    bits.reset(0); // set bit (position) 0 back to 0

    std::cout << "All the bits: " << bits << '\n';
    std::cout << "bit 0 gets: " << bits.test(0) << '\n'; // look up the value of position 0 of the bits,
    std::cout << "bit 3 gets: " << bits.test(3) << '\n'; // or extract the value of specific position

    // implement (Status Recorder)
    [[maybe_unused]] constexpr int isHungry{0}; // {num} is the position or an index
    [[maybe_unused]] constexpr int isSad{1};
    [[maybe_unused]] constexpr int isMad{2};
    [[maybe_unused]] constexpr int isHappy{3};
    [[maybe_unused]] constexpr int isLaughing{4};
    [[maybe_unused]] constexpr int isAsleep{5};
    [[maybe_unused]] constexpr int isDead{6};
    [[maybe_unused]] constexpr int isCrying{7};

    std::bitset<8> myStatus{0b1000'0000};
    myStatus.set(isHappy);
    myStatus.set(isAsleep);
    myStatus.set(isHungry);
    myStatus.flip(isMad);
    myStatus.reset(isCrying);

    std::cout << "All the Status (if you can read): " << bits << '\n';
    std::cout << std::boolalpha;
    std::cout << "Is happy? " << myStatus.test(isHappy) << '\n';
    std::cout << "Is hungry? " << myStatus.test(isHungry) << '\n';
    std::cout << "Is Mad? " << myStatus.test(isMad) << '\n';
    std::cout << "Is Crying? " << myStatus.test(isCrying) << '\n';

    // size of bitset
    // bitset is optimized for speed, instead of memory savings.
    // <=32 --> 4 Bytes, >32 --> 8 Bytes (rounded up)
    std::bitset<36> temp{};
    std::cout << "Size of bitset: " << sizeof(temp) << " Bytes\n";

    // quering
    std::cout << myStatus.size() << " bits are in the set.\n";
    std::cout << myStatus.count() << " bits are true.\n";
    std::cout << "All bits are true? " << myStatus.all() << '\n';
    std::cout << "Some bits are true? " << myStatus.any() << '\n';
    std::cout << "No bits are true? " << myStatus.none() << '\n';

    // bit-shift
    std::bitset<8> x {0b1011'1010};
    std::cout << x << 1 << '\n';   // you need parentheses
    std::cout << (x << 1) << '\n'; // shift is fine
    std::cout << "NOT for every bit: " << ~x << '\n'; // FILP altogether
    std::cout << (std::bitset<4>{0b1001} | std::bitset<4>{0b0110}) << '\n'; // OR
    std::cout << (std::bitset<4>{0b1001} & std::bitset<4>{0b0110}) << '\n'; // AND
    std::cout << (std::bitset<4>{0b1001} ^ std::bitset<4>{0b0110}) << '\n'; // XOR (0^1 == 1)

    // bitwise assignment
    // x <<= y, x >>= y, x |= y, x &= y, x ^= y; assign the value of bitwise calculation to x.
    // x = ~x


    return 0;
}
