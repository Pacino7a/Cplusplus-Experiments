// This module focus on the struct with its ptr and mixture of the both
#include <iostream>

struct Point
{
    double x{0.0};
    double y{0.0};
};

struct Triangle
{
    Point *a{}; // we use pointer as the member here
    Point *b{};
    Point *c{};
};

void printVertexInf(Triangle& triangle)
{
    std::cout << "Vertex: (x , y)" <<'\n';
    std::cout << "a:" << triangle.a->x << ", " << triangle.a->y << '\n'; // pointer use chain operator (`->`) to access the value of the member.
    std::cout << "b:" << triangle.b->x << ", " << triangle.b->y << '\n';
    std::cout << "c:" << triangle.c->x << ", " << triangle.c->y << '\n';

}

struct Paw
{
    int claw{};
};

struct Animal
{
    std::string name{"Name"};
    Paw paw{0};
};


int main()
{
    Point a{12.3, 45.2};
    Point b{15.7, 32.2};
    Point c{14.2, 55.3};

    Triangle triangle_1{&a, &b, &c};
    printVertexInf(triangle_1);

    Triangle *triangle_ptr{&triangle_1}; // Pointer of a struct of pointers
    std::cout << "a: " << triangle_ptr->a->x << ", " << triangle_ptr->a->y << '\n';

    /*----------------------------------------------------*/

    Animal puma{"Puma", 5};
    Animal *puma_ptr{&puma};
    std::cout << puma.name << " has " << puma.paw.claw << " claws.\n";
    std::cout << puma_ptr->name << " has " << puma_ptr->paw.claw << " claws.\n";

    return 0;
}
