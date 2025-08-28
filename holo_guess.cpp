#define NDEBUG
#include "diy.h"
#include "random_mt.h"

namespace guess
{
    namespace 
    {
        constexpr int chance{7};
        constexpr int MAX{100}; // static global variable
        constexpr int MIN{1};
    }
    
} // namespace guess

int getGuess(int count, int min, int max)
{
    for (int user_guess{};;)
    {
        std::cout << "Guess #" << count + 1 << ": ";
        std::cin >> user_guess;
        if(!std::cin) // extract guess number failed
        {
            std::cout << "Invalid input! Try again. ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        else if ((!std::cin.eof() && std::cin.peek() != '\n')) // extract success, but user have entered
        // extraneous contents
        {
            std::string rest{};
            std::cin >> rest;
            std::cout << "What does `" << user_guess << rest << "` means? We want to try again.\n";
            continue;
        }
        else // extracted a pure number
        {
            assert(user_guess >= min && user_guess <= max && "Guess Out of Range!");
            if (user_guess < min || user_guess > max) // if the guess is out of the range, retry
            {
                std::cout << "Guess out of range!\n"
                          << "Please guess an number within [" << guess::MIN << ", " << guess::MAX << "]\n";
                continue;
            }
            else
                return user_guess;
        }

    }
}

int main()
{
    bool first{true};// first get in
    bool start{true};// first one doesn't need to be checked
    while (true)
    {
        if(start) // check whether we need to start
            std::cout << "Let's play a game. I'm thinking of a number between "
                      << guess::MIN << '~' << guess::MAX << ". You have " << guess::chance
                      << " tries to guess what it is.\n"
                      << ((first) ? "Let's Rock? (y/n):" : "");
        else // don't need to start, terminate the program
            break;
        
        // is the first time?
        if(first)
        {
            first = !first; // not the first time anymore
            if(!holo_start(onlyAccept())) // user input n(no), terminate the program
            break;
        }
        // play holo
        int answer{Random::get(guess::MIN, guess::MAX)};
        bool win{false};
        for (int i{0},user_guess{}; i < guess::chance; ++i)
        {
            // std::cout << "Guess #" << i + 1 << ": ";
            // user_guess = getInt(); // get user's guess
            // assert(user_guess >= guess::MIN && user_guess <= guess::MAX && "Guess Out of Range!");
            // if (user_guess < guess::MIN || user_guess > guess::MAX) // if the guess is out of the range, retry
            // {
            //     std::cout << "Guess out of range!\n"
            //               << "Please guess an number within [" << guess::MIN << ", " << guess::MAX << "]\n";
            //     --i;
            //     continue;
            // }
            user_guess = getGuess(i, guess::MIN, guess::MAX);
            if (user_guess > answer)
                std::cout << "Your guess is too high.\n";
            else if(user_guess < answer)
                std::cout << "Your guess is too low.\n";
            else
            {
                std::cout << "Correct. You Win!\n"; // win, get out and ask whether to execute the next round
                win = true;
                break;
            }
        }
        if(!win) // not win, give the answer
            std::cout << "Sorry, you lose. The correct number was " << answer << ".\n";
        std::cout << "Would you like to play again?(y/n): "; // query for the next round
        start = holo_start(onlyAccept());
    }
    
    std::cout << "Thank you for playing!\n";

    return 0;
}
