#include "diy.h"
#include <vector>

template <typename T>
constexpr void printStack(const std::vector<T>& stack)
{
    std::cout<<"---------------------------------------------\n";
    if(stack.empty())
        std::cout << "The stack is Empty.";
    for(const auto element : stack) // we don't need any information about index or length here
        std::cout << element << ' ';
    std::cout << '\n';
    std::cout << "Size: " << stack.size() << ", Capacity: " << stack.capacity() << '\n';
}

template <typename T>
constexpr void getScore(std::vector<T>& arr) // we don't need to know how many scores we gotta input, just make the vector to deal with all the storage issues
{
    // arr.reserve(number_score);
    for (;;)
    {
        std::cout << "Enter a Score [0 ~ 100] (Enter `-1` to Quit) : ";
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
        if(!std::cin.eof() && std::cin.peek() != '\n')
        {
            std::string drop{};
            std::cin >> drop;
            std::cout << "What does " << enter_value << drop << " means? Please Try again.\n";
            continue;
        }
        if(enter_value < 0 || enter_value > 100)
        {
            if(enter_value == -1)
                break;
            std::cout << "Your Input is Out of Range! Please Try again.\n";
            continue;
        }
        arr.push_back(enter_value);
    }
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
        if(!std::cin.eof() && std::cin.peek() != '\n')
        {
            std::string drop{};
            std::cin >> drop;
            std::cout << "What does " << enter_value << drop << " means? Please Try again.\n";
            continue;
        }

        return enter_value;
    }
}

namespace Order
{
    enum Indicators
    {
        push,
        pop,
        none,
        quit
    };
};

constexpr const std::string_view string2Lower(std::string& str)
{
    if(str.size() == 0)
        return "";
    else
    {
        for(auto& character:str)
            character = static_cast<char>(tolower(static_cast<unsigned char>(character)));
        return str;
    }
}
Order::Indicators getIndicator()
{
    int idc{};
    for (;;)
    {
        std::cout << "+------------------------------------------------+\n";
        std::cout << "| Please Choose the mode manipulate the array:   |\n";
        std::cout << "|                                                |\n";
        std::cout << "| 1.Push      2.Pop       3.None      4.Quit     |\n";
        std::cout << "+------------------------------------------------+\n";
        std::cout << "Your Choice: ";
        idc = getInt();
        if(idc < 1 || idc > 4)
        {
            std::cout << "Your Input is Invalid, Please Try again.\n";
            continue;
        }
        break;
    }
    switch (idc)
    {
    case 1:
        return Order::push;
    case 2:
        return Order::pop;
    case 3:
        return Order::none;
    case 4:
        return Order::quit;

    default:
        std::cout << "Fatal Error -1\n";
        std::abort();
    }
}

template <typename T>
constexpr void pushAndPopArray(std::vector<T> &arr, const Order::Indicators indicator)
{
    // all of those must be initialized here instead of initializing in the cases
    T value{};
    T pop_value{};
    std::string input{};
    switch(indicator)
    {
    case Order::push:
        std::cout << "Push ";
        value = enterNumber<T>();
        input = std::to_string(value);
        std::cout << "\033[1A"; // 光标上移一行
        std::cout << "\033[" << (5 + input.length() + 1) << "C"; // 光标右移到 "Push XX <here>"
        arr.push_back(value);
        break;
    case Order::pop:
        pop_value = arr.back();
        arr.pop_back();
        std::cout << "Pop " << pop_value << "  ";
        break;
    default:;
    }
    std::cout << "(Stack: ";
    if(arr.empty())
        std::cout << "Empty)\n";
    else
    {
        for(const auto element:arr)
            std::cout << element << ' ';
        std::cout << ")\n";
    }

}

int main()
{
    // std::vector<int> stack{};
    // printStack(stack);

    // stack.push_back(1);
    // printStack(stack);

    // stack.push_back(2);
    // printStack(stack);

    // stack.push_back(3);
    // printStack(stack);

    // std::cout<<"Top: "<<stack.back()<<'\n'; //

    // stack.pop_back();
    // printStack(stack);

    // stack.pop_back();
    // printStack(stack);

    // stack.pop_back();
    // printStack(stack);

    // std::vector<double> testScore{};
    // // constexpr const int number_score{10};
    // getScore(testScore);
    // printStack(testScore);

    std::vector<int> testarr{};
    for (Order::Indicators indicator{};;)
    {
        indicator = getIndicator();
        if(indicator == Order::quit)
            break;
        if(indicator == Order::pop && testarr.empty())
        {
            std::cout << "Stack is Empty, Can't Pop anything!\n";
            continue;
        }
        pushAndPopArray(testarr,indicator);
    }
    
    return 0;
}
