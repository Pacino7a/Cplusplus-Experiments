#include "diy.h"
#include <map>
#include <charconv>

bool inputMatches(std::string_view input, std::string_view pattern)
{
    if(input.length() != pattern.length())
        return false;

    static const std::map<char, int (*)(int)> valiadators{   // we need a dirctionaray here for mapping
        {'#', std::isdigit},
        {'@', std::isalpha},
        {'-', std::isspace},
        {'?', [](int){ return 1; }}
    };

    return std::ranges::equal(input, pattern, [](char ch, char mask) -> bool
    {
        auto found{valiadators.find(mask)};

        // if we found the mask, we use mask(function) to validate the charcter
        if(found != valiadators.end())
            return (*found->second)(ch);

        // otherwise, we did't have current character's mask and its function (e.g. '*')
        // but we need an exact match
        return ch == mask; });
}

template <typename T>
T getANumber()
{
    for (T num{};;)
    {
        std::cout << "Enter a number here: ";
        std::cin >> num;

        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // if extraction good, ignore the remaining content
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // <<<-------------------------------------------------+
        // NOTICE: gcount will only record the number of charaters that you extracted by std::cin, get()... AT the last time       |
        if(std::cin.gcount() > 1) // if we ignored more than one character after our extraction successful ------------------------+
            continue; // retry
        if(num > 0) // we only accept a positive number here
            return num;
    }
}

// same result with above
template <typename T>
std::optional<T> extractNumber(std::string_view number)
{
    T num{};
    const auto end{number.data() + number.length()};

    // from_chars gets two members (.ptr and .ec, .ec shows whether the extraction is successful)
    // ec will be changed only when we failed at the very begining
    if(std::from_chars(number.data(),end,num).ec != std::errc{}) // if ec is not the default std::errc{}, which means something bad just happened.
        return {};

    // otherwise, extrated well
    if(num <= 0)
        return {};

    return num;
}

int main()
{

    // std::string name{};

    // do
    // {
    //     std::cout << "Enter your name: ";
    //     std::getline(std::cin, name); // when you use `getline` and `std::cin` at the same time, (std::cin >> std::ws is necessary)
    // } while (isInvalidName(name));

    // std::cout << "Name Length: " << name.length() << '\n';
    // std::cout << "Hello " << name << '\n';

    // std::string phoneNumber{};

    // do
    // {
    //     std::cout << "Enter a phone number (###) ###-####: "; // fixed-pattern (very inflexible)
    //     std::getline(std::cin, phoneNumber);
    // } while (!inputMatches(phoneNumber, "(###) ###-####"));

    // std::cout << "You entered: " << phoneNumber << '\n';

    // double what{getANumber<double>()};
    // std::cout << "You entered: " << what << '\n';

    int age{};

    while (true)
    {
        std::cout << "Enter your age: ";
        std::string strAge{};

        // Try to get a line of input
        if (!std::getline(std::cin >> std::ws, strAge))
        {
            // If we failed, clean up and try again
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Try to extract the age
        auto extracted{ extractNumber<int>(strAge) };

        // If we failed, try again
        if (!extracted)
            continue;

        age = *extracted; // get the value
        break;
    }

    std::cout << "You entered: " << age << '\n';
    return 0;
}
