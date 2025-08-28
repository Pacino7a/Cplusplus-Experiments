#include "diy.h"

int main()
{
    char first_char{'a'};
    int count{1};
    std::cout << "question one:\n";
    while (first_char != 'z' + 1)
    {
        std::cout << first_char << '(' << static_cast<int>(first_char) << ')' << ' ';
        if(count++ % 13 == 0)
            std::cout << '\n';
        ++first_char;
    }

    std::cout << "question two:\n";
    int outer{5};
    while (outer > 0)
    {
        int inter{outer};
        while (inter > 0)
        {
            std::cout << inter << ' ';
            --inter;
        }
        std::cout << '\n';
        --outer;
    }

    std::cout << "question three:\n";
    int row{5};
    int row_index{1};
    while (row_index <= row)
    {
        int column{row}; // 5x5 // decrease
        while (column > 0)
        {
            if(column > row_index)
                std::cout << "  ";
            else
            std::cout << column << ' ';
            --column;
        }
        std::cout << '\n';
        ++row_index;
    }
    /*------------------------------------*/
    int i{0}; // good but not recommended
    do
    {
        std::cout << i << '\n';
    } while (++i<5);

    // equal choice - better than while()
    int selection{};
    do
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1)Addition\n";
        std::cout << "2)Substraction\n";
        std::cout << "3)Division\n";
        std::cin >> selection;
    } while (selection > 3 || selection < 1);

    std::cout << "Question1: ";
    for (int number = 1; number < 21; ++number)
    {
        (isEven(number)) ? (std::cout << number << ' ') : (std::cout << "  ");
    }

    std::cout << "\nQuestion2: "
              << "Please enter the number that you want accumulate to: ";
    int sumTo_num{};
    std::cin >> sumTo_num;
    std::cout << "Sum of all the numbers from 1 to " << sumTo_num << " is: " << sumTo(sumTo_num) << '\n';

    std::cout << "Question3/4: Please enter a number for FizzBuzzPop: ";
    int test_fizz{};
    std::cin >> test_fizz;
    fizzbuzz(test_fizz);

    return 0;
}
