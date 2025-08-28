#include "diy.h"
#include "random_s_class.h"
#include <vector>

constexpr std::vector<char> stringvTrans2Vector(const std::string_view guess);
constexpr std::vector<char> preGuessInitial(const std::vector<char>& words)
{
    std::vector<char> vec{};
    vec.reserve(words.size());
    for (std::size_t i{0}; i < words.size(); ++i)
    {
        vec.push_back('_');
    }
    return vec;
}

namespace Words
{
    std::vector<std::string_view> words{"mystery", "broccoli", "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage"};

    static std::string_view words_rand{words[Random::get<std::size_t>(0, words.size() - 1)]};
    static const std::vector<char> words_rand_vec{stringvTrans2Vector(words_rand)};
    static std::vector<char> pre_guess_vec{preGuessInitial(words_rand_vec)};

    constexpr int wrong_times{7};
};


constexpr void initialization()
{
    std::cout << "Welcome to C++man (a variant of Hangman)\n"
              << "To win: guess the word.  To lose: run out of pluses.\n\n";
}

constexpr std::vector<char> stringvTrans2Vector(const std::string_view guess)
{
    std::vector<char> guess_vector{};
    for(const auto character:guess)
        guess_vector.push_back(character);
    return guess_vector;
}

char getUsersGuess()
{
    for (;;)
    {
        std::cout << "Enter your Letter: ";
        char user_char{};
        std::cin >> user_char;
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
            std::cout << "What does " << user_char << drop << " means? Please Try again.\n";
            continue;
        }
        user_char = static_cast<char>(static_cast<unsigned char>(tolower(user_char)));
        const int input_ascii{static_cast<int>(user_char)};
        if(input_ascii > 96 && input_ascii < 123)
            return user_char;
        else
            std::cout << "We only accept alphabet, Please Try again.\n";
    }
}

class Session
{
public:
    const std::vector<char> &getGT() const { return m_guess_gt; }
    const std::vector<char> &getGS() const { return m_guess; }
    friend void guess(const std::string_view answer, Session &play);

private:
    std::vector<char> m_guess_gt{Words::words_rand_vec};
    std::vector<char> m_guess{Words::pre_guess_vec};
};

void guess(const std::string_view answer, Session &play)
{
    std::vector<char> guess_wrong(Words::wrong_times);
    for(char& symb:guess_wrong) // initializing wrong Recorder
        symb = '+';
    int wrong_time{0};
    int right_time{0};
    for (; (wrong_time <= Words::wrong_times) && (right_time <= std::ssize(play.getGT()));) // Keep this loop until chances have been used up or You get the answer
    {
        std::cout << "The word: ";
        for(const char guess_underscore:play.getGS())
            std::cout << guess_underscore;
        std::cout << "   ";
        std::cout << "Wrong guesses: ";
        for(const char wrong:guess_wrong)
            std::cout << wrong;
        std::cout << '\n'; // print user interface
        if(wrong_time == Words::wrong_times || right_time == std::ssize(play.getGT())) // if the game has come to an end, we just print UI
            break;
        const char user_guess{getUsersGuess()}; // get user's input
        // std::cout << "You entered: " << user_guess;
        bool right{false};
        for (std::size_t index{0}; index < play.m_guess_gt.size(); ++index) // check user's input is right or not
        {
            if(user_guess == play.m_guess_gt[index] && play.m_guess[index] != play.m_guess_gt[index]) // right and we never Guess this position out before
            {
                std::cout << "Yes, '" << user_guess << "' is in the word!\n\n";
                play.m_guess[index] = user_guess;
                right = true;
                ++right_time;
                break;
            }
        } 
        if(right) continue; // your guess is right, keep going
         // original position on the last element of the wrong recording vector
        static const std::size_t wrong_top{static_cast<std::size_t>(guess_wrong.size() - 1)}; // original position on the last element of the wrong recording vector
        static std::size_t wrong_cur_index{wrong_top};
        bool already_wrong{false};
        for (std::size_t bias{0} ;bias < guess_wrong.size() - wrong_cur_index; ++bias) // check from the last element to the curent element for the same wrong
        {
            if(user_guess == guess_wrong[guess_wrong.size() - 1 - bias])
            {
                already_wrong = true;
                std::cout << "You already guessed that.  Try again.\n\n";
                break;
            }
        }
        if(!already_wrong) // if this is a new wrong, recording it
        {
            std::cout << "No, '" << user_guess << "' is not in the word!\n\n";
            for (std::size_t i{0}; i < wrong_top - wrong_cur_index; ++i) // judge how many elements need to be moved
            {
                guess_wrong[wrong_cur_index + i] = guess_wrong[wrong_cur_index + i + 1]; // sequense toward to the left 
            }
            guess_wrong[wrong_top] = user_guess; // recording your wrong
            ++wrong_time; // wrong goes up
            --wrong_cur_index;
        }
        // else continue; // you make the same mistake, but we sparate you, try again
    }
    if(wrong_time == Words::wrong_times)
        std::cout << "You lost!  The word was:" << answer << '\n';
    else
        std::cout << "You Win!  You have Figured it out what the word is!\n";
}

int main()
{
    initialization();
    Session play;
    guess(Words::words_rand, play);

    return 0;
}
