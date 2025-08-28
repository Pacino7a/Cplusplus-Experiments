// DIY_H
#ifndef DIY_H
#define DIY_H

#include <iostream>
#include <cmath>
#include <numeric>
#include <cassert>
#include <cstdint>
#include <algorithm>
#include <bitset>
#include <cctype>
#include <iterator>

// clear any extraneous input
constexpr void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // clear up the buffer or until a '\n' is removed
}

constexpr void cutString(std::string& str, size_t start, size_t end)
{
    str.erase(start, end); // str index -> (0~strlen-1), cut the str from position[start] to position[end]
}

// check if there is an unextracted input
bool hasUnextractInput() // eof for the current(must be read once),peek for the latter
{
    // peek() != '\n' is the key judgement, '\n' is not a valid thing for extracting
    return !std::cin.eof() && std::cin.peek() != '\n'; // EOF (end of a file or  after user input CTRL+Z)
}

// test and fix fail extranctions or overflow and remove extraneous input
bool clearFailedExtraction() // solve the problem of `Failure` mode of cin
{
    if (!std::cin)
    {
        if (std::cin.eof()) // if user input an eof, which is an error, we need terminate the program immediately
        {
            std::exit(0);
        }

        // (ESSENTIAL) put the cin form `failure` mode to `normal`, make cin back to work
        std::cin.clear(); // if just an error type, reset cin

        ignoreLine(); // and clear the buffer

        return true; // input Failed, but the situation has been reset
    }

    // std::cout << "Extracting...\n";
    return false; // input is fine
}

// we'd better use a loop for getting an valid input
int getInt()
{
    // std::cout << "Please enter an integer (-32768 ~ 32767):";
    for (int temp{};;)
    {
        std::cin >> temp;            // extract
        if (clearFailedExtraction()) // if extract failed
        {
            std::cout << "Invalid input, Please try again: ";
            continue;
        }

        // if there is still some value in the buffer
        if (hasUnextractInput())
        {
            std::string rest{};
            std::cin >> rest;
            std::cout << "What does " << '`' << temp << rest << "` means?\nWe want to try again:";
            continue;
        }

        // ignoreLine();
        return temp;
    }
}

double getDouble()
{
    for (double temp{};;)
    {
        // std::cout<<"Please enter a decimal number: ";
        std::cin >> temp;
        // bool success{std::cin};
        // std::cin.clear();
        // ignoreLine();

        // if(success)
        //     return temp;
        if (clearFailedExtraction()) // when extracting from the buffer has failed
        {
            std::cout << "Oops! your input is invalid, Please try again.\n";
            continue;
        }

        ignoreLine(); // if extraction is fine, clear the rest extraneous input in the buffer
        return temp;
    }
}

char getCharacter()
{
    for (char temp{};;)
    {
        // std::cout << "Now, you can enter a char: ";
        std::cin >> temp;

        if (clearFailedExtraction()) // fail to extract a character
        {
            std::cout << "Oops! your input is invalid, Please try again.\n";
            continue;
        }
        else
        {
            ignoreLine(); // while(getchar()!='\n'){} --> (old shool)
            return temp;
        }
    }
}

char getOperator()
{
    while (true)
    {
        // std::cout << "Please enter an operators (+,-,*,/): ";
        char op{};
        std::cin >> op;

        if (!clearFailedExtraction()) // when extraction success
        {
            ignoreLine(); // remove rest-stuff in the buffer
        }

        switch (op)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            return op;
        default:
            std::cout << "Oops! " << op << " is not a valid operator yet. Please try again\n";
        }
    }
}

char onlyAccept()
{
    for (char i{};;)
    {
        i = getCharacter();
        if (i != 'n' && i != 'N' && i != 'y' && i != 'Y')
        {
            std::cout << "We only accept (y/n), try again: ";
            continue;
        }
        return i;
    }
}
constexpr bool holo_start(char input_user)
{
    if (input_user != 'y' && input_user != 'Y')
        return false;
    else
        return true;
}

constexpr std::int64_t powint(std::int64_t base, int exp) // integer pow()
{
    assert(exp >= 0 && "powint: exp parameter has a negative value!");
    // assert activate, when the expression inside gets a false
    // "xxx" == true
    // e.g. (exp < 0) -> assert

    if (base == 0)
        return (exp == 0) ? 1 : 0;
    else if (exp == 0)
        return 1;

    std::int64_t result{1};
    // bool negativeResult{false};

    // if(base < 0) // check whether the base is a negative number.
    // {
    //     base = -base;
    //     negativeResult = (exp & 1); // exponent is odd the result also be negative
    // }

    if (base > std::numeric_limits<int64_t>::max() / base) // check the base
    {
        std::cerr << "Base will be overflowed soon!\n"; // std::cout w/o the buffer
        if (exp > 1)
            return std::numeric_limits<std::int64_t>::max();
        else
            return base;
    }

    for (int i = 0; i < exp; i++)
    {
        if (result > std::numeric_limits<std::int64_t>::max() / base) // check current result
        {
            std::cerr << "Result overflowed!\n";
            return std::numeric_limits<std::int64_t>::max();
        }

        result *= base;
    }
    return result;
    // return negativeResult ? -result : result; // if the base is a negative number, flip it
}

constexpr bool isEven(int number) // check whether the number is a Even
{
    // return (number % 2 == 0) ? true : false;
    return !(number % 2); // odd gets true, needs flip
    // return !(number & 1) // odd gets true
}

constexpr bool approximatelyEqualRel(double a, double b, double relEpsilon, double absEpsilon)
{
    // abs distance
    // when both a and b are very close to 0,
    // the error that the algorithm can tolerate will be very very small (relEpsilon),
    // if we only use the relative error distance
    // the output of relative error will be invalid probably
    // so we need absEpsilon to handle this
    // return true when the distance between a and b is small enough
    if (std::abs(a - b) <= absEpsilon) // fix the problem of close to 0
        return true;

    // otherwise
    // adaptive distance for approximation,
    // which is controlled by scale relEpsilon (e.g. 2% of Maximum Magnitude -- 2% Error)
    // return true when the distance is in the range of the tolerance
    return (std::abs(a - b)) <= (std::max(std::abs(a), std::abs(b)) * relEpsilon);
}
constexpr std::bitset<8> rotl(std::bitset<8> x, std::size_t move, bool left) // bitwise shift (rotation)
{
    // constexpr std::bitset<8> seven{0b1000'0000};
    // constexpr std::bitset<8> zero{0b0000'0001};

    if (left)
    {
        // solution 1
        // for (int i = 0; i < move; i++)
        // {
        //     if(x.test(7))
        //     // if((x & seven) == seven)
        //     {
        //         x <<= 1;
        //         x.set(0);
        //         // x |= 1;
        //     }
        //     else
        //         x <<= 1;
        // }

        // solution 2
        return (x << move) | (x >> (8 - move)); // 8 is the size of the sequence, which can be replaced by a Parameter
        // sequence shift left x steps, and there are x bits will come to
        // the end of the sequence, we extract them by shift the sequence (8-move) to the opposite direction
        // we use OR to combine them, the job is done.
    }
    else // right
    {

        // for (int i = 0; i < move; i++)
        // {
        //     if(x.test(0))
        //     //if((x & zero) == zero)
        //     {
        //         x >>= 1;
        //         x.set(7);
        //         //x |= seven;
        //     }
        //     else
        //         x >>= 1;
        // }

        return (x >> move) | (x << (8 - move));
    }

    // return x;
}

constexpr void deci2Binar(int number)
// we should change the magic number inside (16 or 15)
// for better extend
{
    bool positive{true};
    int level{}; // 128 64 32 16

    if (number < 0)
    {
        positive = false;
        number = -number;
    }

    if (positive)
    {
        std::cout << "0b";
        for (int i = 15; i >= 0; --i)
        {
            level = static_cast<int>(powint(2, i));
            if (number >= level)
            {
                std::cout << '1'; // 1
                number -= level;
            }
            else
                std::cout << '0'; // 0
            if ((i % 4 == 0) && (i > 0))
                std::cout << "'";
        }
    }
    else
    {
        // reverse the positive procedure to get the reverse code
        std::bitset<16> negative_binary{};
        for (int i = 15; i >= 0; --i) // decimal -> binary -> reverse binary
        {
            level = static_cast<int>(powint(2, i));
            if (number >= level)
            {
                negative_binary.reset(static_cast<std::size_t>(i)); // 0
                number -= level;
            }
            else
                negative_binary.set(static_cast<std::size_t>(i)); // 1
            // if((i % 4 == 0) && (i > 0))
            //     std::cout << "'";
        }
        bool carry{1}; // complement to the lowest bit
        for (std::size_t i = 0; i < 16; ++i)
        {
            if (negative_binary.test(i) && carry) // 1(base) + 1(carry) = 0, carry = 1 (keep)
                negative_binary.reset(i);
            else if (!negative_binary.test(i) && carry) // 0 + 1 = 1, carry = 0 (Used up)
            {
                negative_binary.set(i);
                carry = false;
            }
            else
            {
            } // 1 + 0 = 1, 0 + 0 = 0, stay as they are.
        }
        std::cout << "(negative) 0b" << negative_binary << '\n';
    }
}

// defined in constants.cpp
namespace constant // declarations need to be inside a namespace because of their definitions
{
    // inline(implicitly extern) means the linker can see the global variables
    inline constexpr double pi{3.14159265357};
    inline constexpr double gravity{9.88};

    extern int g_x;
    extern const int g_number_apple;

    void foo(); // a non-static function is a external one in default
} // global constants as external variables

constexpr int sumTo(int number)
{
    int result{0};
    for (int i = 1; i <= number; ++i)
    {
        result += i;
    }
    return result;
}

constexpr void fizzbuzz(int number)
{
    for (int i = 1; i <= number; ++i)
    {
        // if(i % 3 == 0 && i % 5 == 0 && i % 7 ==0)
        //     std::cout<<"fizzbuzzpop\n";
        // else if(i % 3 == 0)
        //     std::cout << "fizz\n";
        // else if(i % 5 == 0)
        //     std::cout << "buzz\n";
        // else
        //     std::cout << i << '\n';

        if (i % 3 == 0)
            std::cout << "fizz";
        if (i % 5 == 0)
            std::cout << "buzz";
        if (i % 7 == 0)
            std::cout << "pop";
        else if (i % 3 != 0 && i % 5 != 0)
            std::cout << i;
        std::cout << '\n';
    }
}

template <typename T, typename U>
void sort2(T &lesser, U &greater)
{
    if (lesser > greater)
        std::swap(lesser, greater);
}

constexpr std::string toASCIILowerCase(std::string_view str)
{
    std::string lower{};
    std::transform(str.begin(), str.end(), std::back_inserter(lower), 
                    [](char c)
                   { 
                        return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                    });
    return lower;
}

constexpr bool isPrime(int a)
{
    if(a <= 1)
    {
        std::cout << "Your input is " << a << ", Prime is an Integer bigger than 1!" << '\n';
        return false;
    }
    if(a == 2)
    {
        return true;
    }
    if(a % 2 == 0)
    {
        return false;
    }

    //float sqrt{std::sqrt(a)};
    //for (int i = 2; i < a; ++i) 
    for (int i {3}; i * i <= a; i += 2)// i <= sqrt(a) == i * i <= a, only need to check the odd
    {
        // This is not an One time judgement!
        if((a % i == 0))
        {
            return false;
        }
    }

    return true;
}

template<typename T>
constexpr T getMax(T a,T b)
{
    if(a > b)
        return a;
    else
        return b;
}

template<typename T>
constexpr T getMin(T a,T b)
{
    if(a > b)
        return b;
    else
        return a;
}

int binarySearch(const int* array, int target, int min, int max)
{
    assert(array); // make sure the array exists

    for (int midpoint{};;)
    {
        if(min == max) // check whether the search is on the edge
        {
            return (array[max] == target) ? max : -1; // if it still failed to find the value, return -1, otherwise return the index of the target
        }
        if(min > max) // it seems this is not going to happen (if we didn't have the first judgement, min will increase because of `midpoint + 1`)
        {
            return -1;
        }

        midpoint = std::midpoint(min, max);
        // int midpoint{((max - min) / 2) + min}; // old school
        if(target == array[midpoint])
            return midpoint;
        else if(target < array[midpoint]) // if the target is smaller
        {
            max = midpoint - 1; // we giong to look up the first half
            continue;
        }
        else // if the target is bigger
        {
            min = midpoint + 1; // we going to look up the second half
            continue;
        }
    }
}

// we use ios_base flags and a lambda object to validate the name
bool containsInvalidNameCharacters(std::string_view name) {
    return !std::ranges::all_of(name, [](char ch)
    { return std::isalpha(ch) || std::isspace(ch); });
}

auto spaceCount(std::string_view name)
{
    return std::ranges::count_if(name, [](char ch)
                                 { return std::isspace(ch); });
}

bool isInvalidName(std::string_view name)
{
    // if there is a name whose length smaller than 2,
    // OR has characters other than alphabets and space,
    // OR there is more than 1 space in the name
    // it is an invalid name
    return (name.length() < 2) || containsInvalidNameCharacters(name) || (spaceCount(name) > 1);
}

#endif
