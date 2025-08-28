#include "diy.h"

bool greater(std::string a,std::string b) // if [currrent] > [bestIndex] --> [bestIndex] = [current] --> loop ends:[start] swap [bestIndex]
{
    return a > b;
}

int main()
{
    std::cout << "How many Names do you want to type in: ";
    const std::size_t num_name{static_cast<std::size_t>(getInt())};

    auto *names{new std::string[num_name]{}};
    for (size_t i = 0; i < num_name; ++i)
    {
        std::cout << "Enter Name #" << i + 1 << ": ";
        std::getline(std::cin >> std::ws, *(names + i));
    }
    std::cout << "\nHere is your sorted List:\n";
    std::sort(names, names + num_name, greater); // C-style names can not use begin() or end() so that all the iterator-based methods are failed.
    for (size_t i = 0; i < num_name; ++i)
    {
        std::cout << "Name #" << i + 1 << ": " << names[i] << '\n';
    }

    delete[] names; // when the names finished its life purpose, we should release it.

    return 0;
}
