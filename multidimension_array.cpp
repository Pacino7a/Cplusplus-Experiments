#include "diy.h"
#include <iostream>
#include <array>
#include <functional>


template <typename T, std::size_t Rows, std::size_t Cols>
using Array2D = std::array<std::array<T, Cols>, Rows>;

template <typename T, std::size_t Rows, std::size_t Cols , std::size_t Depth>
using Array3D = std::array<std::array<std::array<T,Depth>,Cols>,Rows>;

template <typename T, std::size_t Rows, std::size_t Cols>
constexpr void printArray2D(const Array2D<T,Rows,Cols>& arr)
{
    for(const auto& arow:arr)
    {
        for(const auto& ele:arow)
            std::cout << ele << ' ';
        std::cout << '\n';
    }

    std::cout << "Array printing has completed.\n";
}

template <typename T, std::size_t Rows, std::size_t Cols>
constexpr std::size_t getArray2Drows(const Array2D<T,Rows,Cols>&) // we don't need parameter instance here
{
    return Rows;
}

template <typename T, std::size_t Rows, std::size_t Cols>
constexpr std::size_t getArray2Dcols(const Array2D<T,Rows,Cols>&)
{
    return Cols;
}

template <typename T, std::size_t Rows, std::size_t Cols>
using Array2DFlat = std::array<T, Rows * Cols>;

template <typename T, std::size_t Rows, std::size_t Cols>
class Array2DView // we use this to read the flat array (2D -> 1D)
{
private:
    std::reference_wrapper<Array2DFlat<T, Rows, Cols>> m_arr{};
public:
    Array2DView(Array2DFlat<T,Rows,Cols>& arr)
        : m_arr{arr}
    {}

    T &operator[](int i) { return m_arr.get()[static_cast<std::size_t>(i)]; }
    const T &operator[](int i) const { return m_arr.get()[static_cast<std::size_t>(i)]; }

    // prior to C++23 
    // T &operator()(int row, int col) { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; } // arr(3,4) -> get to the begining of the third row and we shift 4
    // const T &operator()(int row, int col) const { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }

    // C++23
    T &operator[](int row, int col) { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }
    const T &operator[](int row, int col) const { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }

    int rows() const { return static_cast<int>(Rows); }
    int cols() const { return static_cast<int>(Cols); }
    int length() const { return static_cast<int>(Rows * Cols); }

};


int main()
{
    constexpr Array2D<int,3,4> arr3x4{{
        {1, 2, 3, 4},
        {2, 3, 4, 5},
        {3, 4, 5, 6}
    }};
    printArray2D(arr3x4);
    std::cout << "This Multidimensional array gets " << arr3x4.size() << " Rows and " << arr3x4[0].size() << " Cols.\n"; // maybe dangerous if some dimension except the last one has 0 length
    std::cout << "This Multidimensional array gets " << getArray2Drows(arr3x4) << " Rows and " << getArray2Dcols(arr3x4) << " Cols.\n"; // always ok to print

    Array2DFlat<int, 3, 4> arr3x4F{   // This is a flat-2D array (3x4)
        1, 2, 3, 4,
        2, 3, 4, 5,
        3, 4, 5, 6
    };
    Array2DView<int,3,4> arr3x4View{arr3x4F}; // we can define a class to save its informations such as Rows, Cols and Length and even index the elements by 2D index (coordinates)
    std::cout << "This Flat Array has: " << arr3x4View.rows() << " rows and " << arr3x4View.cols() << " cols.\n";
    for (int i{0};i<arr3x4View.length();++i) // we can traversal the 2D array by one loop
    {
        std::cout << arr3x4View[i] << ' ';
    }
    std::cout << "\n\n";
    for (int row{0};row<arr3x4View.rows();++row)
    {
        for (int col{0};col<arr3x4View.cols();++col)
            std::cout << arr3x4View[row, col] << ' ';
        std::cout << '\n';
    }

    std::size_t rows{3};
    std::size_t cols{4};
    double count{1.0};
    std::vector<std::vector<double>> twoDimension(rows, std::vector<double>(cols));
    for(auto& rs:twoDimension)
    {
        for(auto& ele:rs)
            ele = count++;
    }
    for(const auto& rs:twoDimension)
    {
        for(auto ele:rs)
            std::cout << ele << ' ';
        std::cout << '\n';
    }

    return 0;
}
