#include <iostream>
#include <cassert>
#include <utility>

class Matrix
{
private:
    double m_data[4][4]{}; // we create a 4x4 matrix which holds double values
public:
    // const double &operator()(const int row, const int col) const;
    double &operator()(const int row, const int col); // overload the parentesis as [][] for index the 2 dimension matrix
    double operator()(const int row, const int col) const;
    void operator()();
    // double &operator[](const int row, const int col); // Not work so far
};

// const double& Matrix::operator()(const int row, const int col) const
// {
//     assert(row >= 0 && row < 4 && col >= 0 && col < 4);
//     return m_data[row][col];
// }

double &Matrix::operator()(const int row, const int col)
{
    assert(row >= 0 && row < 4 && col >= 0 && col < 4);
    return m_data[row][col];
    // return const_cast<double &>(std::as_const(*this)(row, col));
}

double Matrix::operator()(const int row, const int col) const // this is more efficient than pass a reference (NO modification)
{
    assert(row >= 0 && row < 4 && col >= 0 && col < 4);
    return m_data[row][col];
}

void Matrix::operator()() // we don't set any parameters here, the purpose of this overloading is reset the values inside the matrix
{                         // may be not clear (Not recommended)
    for (int row{0}; row < 4;++row)
    {
        for(int col{0}; col < 4;++col)
            m_data[row][col] = 0;
    }
}

class Accumulator
{
private:
    int m_counter{};
public:
    int operator()(int i) { return (m_counter += i); } // overload the parenthesis as a functor (accumulate i and return the result)
    void reset() { m_counter = 0; }
};

class MyString
{
private:
    std::string m_str{};
public:
    explicit MyString(const std::string_view str)
        : m_str{str}
        {}
    friend std::ostream &operator<<(std::ostream &out, const MyString &mystr);
    std::string_view operator()(const int begin, const int len) const; // functor
};

std::ostream &operator<<(std::ostream &out, const MyString &mystr)
{
    return out << mystr.m_str;
}

std::string_view MyString::operator()(const int begin, const int len) const
{
    assert(begin >= 0 && len>= 0 && len <= std::ssize(m_str)- begin);
    // return m_str.substr(static_cast<std::size_t>(begin), static_cast<std::size_t>(len)); // will return a string
    std::string_view look{m_str}; // the view is binded with a object's member variable which means this will not dangling
    return look.substr(static_cast<std::size_t>(begin), static_cast<std::size_t>(len)); // and this will be more efficient if you don't need own the string
    // make 3 string_view at the most
}


int main()
{
    Matrix m1{};
    m1(0, 2) = 4;
    // const Matrix matrix{};

    std::cout << m1(0, 2) << '\n';
    // std::cout << matrix(0, 2) << '\n';
    m1(); // reset the matrix
    std::cout << m1(0, 2) << '\n';

    Accumulator a1{};
    std::cout << "Acc: " << a1(1) << '\n';
    std::cout << "Acc: " << a1(3) << '\n';
    std::cout << "Acc: " << a1(5) << '\n';
    a1.reset();

    std::string test{"hello"};
    std::cout << "Strlen: " << std::size(test) << '\n';

    MyString s { "Hello, world!" };
    std::cout << s(7, 5) << '\n'; // start at index 7 and return 5 characters (7~11)

    return 0;
}
