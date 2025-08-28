#include "diy.h"

std::size_t getSingleIndex(int row, int cols, int numberOfColumns)
{
    assert(cols < numberOfColumns);
    return static_cast<std::size_t>(row * numberOfColumns + cols);
}

int main()
{
    constexpr int value{10};
    auto ptr{&value}; // native Pointer
    auto ptrptr{&ptr}; // Pointer's Pointer

    std::cout << "Adress: Ptr " << ptr << " Ptr's Ptr: " << ptrptr << ' ' << " which contains " << *ptrptr << '\n';
    std::cout << "Content: " << *ptr << " == " << **ptrptr << '\n';
    
    // multi-dimension arrays
    // int **array{new int[5][10]}; X
    int (*array)[10]{new int[7][10]}; // The array is allocated at once
    delete[] array; // delete at once
    auto array_auto{new int[3][4]{}};
    delete[] array_auto;
    
    int **array_create{new int *[5]}; // rows, not allocating the array all at Once
    for (size_t count = 0; count < 5; ++count)
    {
        array_create[count] = new int[10]; // cols
    }
    for (std::size_t count{0};count < 5;++count)  // In this way of allocation, we need change our way of deleting the array
        delete[] array_create[count]; // cols (release every col in each row)
    delete[] array_create; //rows
    
    int *array_flat{new int[50]};
    array_flat[getSingleIndex(3, 2, 3)] = 8; // (3x3) row 3 (4th row) col 2  -> 11
    return 0;
}
