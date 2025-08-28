#include "diy.h"
#include <functional>

template <typename T>
using Operation = T (*)(T, T);
// using Operation = std::function<T(T, T)>;

template <typename T, std::size_t N>
void calculator(T a, char operator_, T b, const std::array<Operation<T>,N>& operation)
{
    T result{};
    switch (operator_)
    {
    case '+':
        result = {operation[0](a, b)}; //add(a,b)
        break;
    case '-':
        result = {operation[1](a, b)}; //subtract(a,b)
        break;
    case '*':
        result = {operation[2](a, b)}; //multiply(a,b)
        break;
    case '/':
        result = {operation[3](a, b)}; //divide(a,b) (double only)
        break;
    default:
        std::cout << "Fatal Error! operation failed!\n";
        std::exit(-1);
    }
    std::cout << a << ' ' << operator_ << ' ' << b << " = " << result << '\n';

}

auto add(auto a, auto b)
{
    return a + b;
}

auto subtract(auto a, auto b)
{
    return a - b;
}

auto multiply(auto a, auto b)
{
    return a * b;
}

auto divide(auto a, auto b)
{
    return a / b;
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

int main()
{
    // Operation<int> add_i{add};
    constexpr std::array<Operation<int>, 4> operations_i{{{add}, {subtract}, {multiply}, {divide}}};
    constexpr std::array<Operation<double>, 4> operations_d{{{add}, {subtract}, {multiply}, {divide}}};
    std::cout << "Please chose The mode of Calculator working at: 0. Integer  1. Double  \nYour choice:";
    int mode{0};
    for (;;)
    {
        mode = getInt();
        if(mode != 0 && mode != 1)
        {
            std::cout << "0 for Int or 1 for Double: ";
            continue;
        }
        break;
    }
    std::cout << "Please enter two inputs and a mathematical operation ('+', '-', '*', '/') below:\n";
    // calculator(1, '/', 2, operations_i);
    std::cout << "Operand #1: ";
    const auto op1{mode?getDouble():getInt()};
    std::cout << "Mathematical operation ('+', '-', '*', '/'): ";
    const char operator_{getOperator()};
    std::cout << "Operand #2: ";
    const auto op2{mode?getDouble():getInt()};
    if(!mode && operator_=='/' && op1<op2)
    {
        std::cout << op1 << " / " << op2 << " = 0 (Integer Result)\n"
                  << "you can choose <double> mode for more precise Result.\n";
    }
    else if (operator_ == '/' && op2 == 0)
    {
        std::cout << "You chose '/' but your denominator is a ZERO!\nPlease check your input.";
    }
    else
    {
        if(mode)
            calculator<double>(op1, operator_, op2, operations_d);
        else
            calculator<int>(static_cast<int>(op1), operator_, static_cast<int>(op2), operations_i);
    }

    // Integer calculator---- answer of this quiz
    // int operand{getInt()};
    // char operator_{getCharacter()};
    // int operand_2{getInt()};

    // Operation<int> fcnPtr{};
    // switch (operator_)
    // {
    // case '+':
    //     fcnPtr = &add; //add(a,b)
    //     break;
    // case '-':
    //     fcnPtr = &subtract; //subtract(a,b)
    //     break;
    // case '*':
    //     fcnPtr = &multiply; //multiply(a,b)
    //     break;
    // case '/':
    //     fcnPtr = &divide; //divide(a,b) (double only)
    //     break;
    // default:
    //     std::cout << "Fatal Error! operation failed!\n";
    //     fcnPtr = nullptr;
    // }

    // if(fcnPtr)
    // {
    //     if(operator_ != '/' || operand_2 != 0)
    //         std::cout << operand << operator_ << operand_2 << " = " << fcnPtr(operand, operand_2) << '\n';
    //     else
    //         std::cout << "Mathmatics semantic Error by divide.\n";
    // }
    // else
    //     std::cout << operator_ << " is not support yet.\n";

    return 0;
}
