#include <iostream>
template <typename T>
class Pair1
{
private:
    T m_value1{};
    T m_value2{};
public:
    explicit Pair1(T value1, T value2)
        : m_value1{value1}, m_value2{value2}
    {}

    T first() const { return m_value1; }
    T second() const { return m_value2; }
};

template <typename T, typename U>
class Pair
{
private:
    T m_value1{};
    U m_value2{};
public:
    explicit Pair(T value1, U value2)
        : m_value1{value1}, m_value2{value2}
    {}

    T first() const { return m_value1; }
    U second() const { return m_value2; }
    T &first()  { return m_value1; }
    U &second() { return m_value2; }
};

// inheritance
// template <typename T, typename U>
// class StringValuePair: public Pair<T,U>
// {
// };

template <typename T>
class StringValuePair: public Pair<std::string, T> // we can partical specialize the Base directly
{
public:
    explicit StringValuePair(const std::string &str, T value)
        : Pair<std::string, T>{str, value} // you need to specify the type-parameters here (CAN'T IGNORE)
    {}
};

int main()
{
	Pair1<int> p1 { 5, 8 };
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair1<double> p2 { 2.3, 4.5 };
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    Pair<int, double> p3 { 5, 6.7 };
	std::cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';

	const Pair<double, int> p4 { 2.3, 4 };
	std::cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';

    StringValuePair<int> svp{"hello", 2};
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';


    return 0;
}
