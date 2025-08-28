#include <iostream>
#include <cstdbool>
#include <cassert>
#include <cmath>

int getInt0_9();
bool isPrime(int);

int main()
{
    // std::cout << "Please enter an Integer (0-9): ";
    // int x{getInt0_9()};
    // // std::cout << "Please enter another one (0-9) : ";
    // // int y{getInt0_9()};


    // if(isPrime(x))
    //     std::cout << x << " is a Prime" << '\n';
    // else
    //     std::cout << x << " is not a Prime" << '\n';

    /* TIPS */
    // These statemets are redundancies
    // if(x >= 2)
    //     return true;
    // else
    //     return false;

    // All you need is an one time judgement
    // you can return it DIRECTLY!
    // Just like this --> return x >= 2;

    int test_seq[]{0, 1, 2, 3, 4, 5, 7, 9, 11, 13, 15, 16, 17, 19, 97, 99, 13417};
    int len{sizeof(test_seq) / sizeof(int)};
    for (int i {0}; i < len ; ++i)
    {
        if (i == 2 || i == 3 || i == 5 || i == 6 || i == 8 || i == 9 || i == 12 || i == 13 || i == 14 || i == 16)
            assert(isPrime(test_seq[i]) && "Your isPrime() is bad!."); // assert(terminate program) when the condition is false
        else
            assert(!isPrime(test_seq[i]) && "Your isPrime() is bad!.");
    }

    std::cout << "Success!\n";

    return 0;
}

int getInt0_9()
{
    for (int temp{};;)
    {
        std::cin >> temp;
        if (temp >= 0 && temp <= 9)
        {
            return temp;
        }

        std::cout << "Invaild, Please try again: ";
    }
}

bool isPrime(int a)
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
