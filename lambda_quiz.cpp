#include "diy.h"
#include "random_s_class.h"
#include <functional>

int getUsersNumber()
{
    for (;;)
    {
        std::cout << "Enter a Value: ";
        int user_int{};
        std::cin >> user_int;
        if(!std::cin)
        {
            if(std::cin.eof())
                std::exit(0);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if(!std::cin.eof() && std::cin.peek() != '\n')
        {
            std::string drop{};
            std::cin >> drop;
            std::cout << "What does " << user_int << drop << " means? Please Try again.\n";
            continue;
        }
        if (user_int <= 0)
        {
            std::cout << "We're so sorry for that, but we only accept Positive Value as Input for now.\n";
            continue;
        }
        
        return user_int;
    }
}

std::vector<int> Initialization()
{
    std::cout << "You want to Start from where?\n";
    int startValue{getUsersNumber()};
    std::cout << "How many numbers you want to guess?\n";
    std::size_t guessTimes{static_cast<std::size_t>(getUsersNumber())};
    std::vector<int> temp{};
    temp.reserve(guessTimes);  // allocate memory
    int multiplier{Random::get<int>(2, 4)};
    for (size_t i = 0; i < guessTimes; ++i, ++startValue)
    {
        temp.push_back(startValue * startValue * multiplier);
    }
    std::cout << "I generated " << guessTimes << " square numbers. Do you know what each number is after multiplying it by " << multiplier << " ?\n";
    return temp;
}

void play(std::vector<int>& sqr_numbers)
{
    for (;std::ssize(sqr_numbers) > 0;)
    {
        std::cout << "> ";
        int users_guess{getUsersNumber()};
        auto result{
            std::find_if(sqr_numbers.begin(), sqr_numbers.end(),
                         [users_guess](const int sqr_number)
                         {
                            return users_guess == sqr_number;
                         })};
        if(result != sqr_numbers.end())
        {
            std::size_t len{std::size(sqr_numbers)};
            sqr_numbers.erase(result);
            if(len != 0)
                std::cout << "Nice! " << len << " Number(s) left.\n";
            else
                std::cout << "Congratulations! You Win the Game!\n";
        }
        else
        {
            // int nearestValue{};
            // int distance{};
            // int minimum{100};
            // for(const int value:sqr_numbers)
            // {
            //     distance = std::abs(*result - value);
            //     if(distance < minimum)
            //     {
            //         nearestValue = value;
            //         minimum = distance;
            //     }
            // }

            const auto min_result{
                std::min_element(sqr_numbers.begin(), sqr_numbers.end(),
                                  [users_guess](const int a, const int b)
                                {
                                   return std::abs(a - users_guess) < std::abs(b - users_guess);   // (current - users_guess) < (current_min - users_guess)
                                })};

            const int nearest{*min_result};

            std::cout << users_guess << " is wrong! Try " << nearest << " next time.\n";
            break;
        }
    }
}

int main()
{
    std::vector sqr_guess{Initialization()};
    play(sqr_guess);

    return 0;
}
