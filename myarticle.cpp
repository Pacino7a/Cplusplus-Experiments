#include <iostream>
#include <cstdint>
#include <bitset>
// bitflags with bitmasks
// set the masks, use the masks and manipulate the bitflags
int main()
{
    // bit masks
    [[maybe_unused]] constexpr std::uint8_t option_viewed{0x01};    // 0000 0001
    [[maybe_unused]] constexpr std::uint8_t option_edited{0x02};    // 0000 0010
    [[maybe_unused]] constexpr std::uint8_t option_favorated{0x04}; // 0000 0100
    [[maybe_unused]] constexpr std::uint8_t option_shared{0x08};    // 0000 1000
    [[maybe_unused]] constexpr std::uint8_t option_deleted{0x10};   // 0001 0000

    std::uint8_t myArticleFlags{option_favorated}; // initialized with favorated
    myArticleFlags |= option_viewed; // SET view the article

    std::cout << std::boolalpha;
    std::cout << "Article Viewed? " << static_cast<bool>(myArticleFlags & option_viewed) << '\n'; // READ the bit
    std::cout << "Article deleted? " << static_cast<bool>(myArticleFlags & option_deleted) << '\n';

    // myArticleFlags &= ~option_favorated;  // we get conversion warning
    myArticleFlags &= static_cast<uint8_t>(~option_favorated); // RESET the favorated

    std::cout << "Article favorated? " << static_cast<bool>(myArticleFlags & option_favorated) << '\n';
    std::cout << std::bitset<8>{myArticleFlags} << '\n';

    return EXIT_SUCCESS;
}
