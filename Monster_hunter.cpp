// the programming procedure like this is procedural programming
// good in school, but not good in industrial
// So we need to change the way of programming

// <Object-Oriented Programming> (OOP) is Recommended
// it is the core of C++

#include "Monster.h"

void printValue(int* value) // pass by adress
{
    if(value!=NULL and value!= nullptr)
        std::cout << "Value: " << *value << '\n';
    else
        std::cout << "None_Value, " << 0 << '\n';
}

int main()
{
    using enum Monster::Monstertype;

    Monster orge_1{orge, "Torg", 145};
    Monster slime_1{slime, "Blurp", 23};

    printMonster(orge_1);
    printMonster(slime_1);

    int hasvalue = 5;
    int* nonvalue{NULL}; // if you want to pass an int with NULL or nullptr is a valiad argument,
                         // you need pass it by adress

    printValue(&hasvalue);
    printValue(nonvalue);

    return 0;
}
