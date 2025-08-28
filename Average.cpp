#include <iostream>

class Average
{
private:
    double m_average{};
public:
    explicit Average(double value = 0)
        : m_average{value}
    {}
    friend std::ostream &operator<<(std::ostream &out, const Average &avg);
    Average& operator+=(const std::int32_t value)
    {
        static int count{0};
        static double sum{0};
        sum += value;
        m_average = (sum/++count);
        return *this;
    }
};

std::ostream &operator<<(std::ostream &out, const Average &avg)
{
    return out << avg.m_average;
}

int main()
{
    Average avg{};
	std::cout << avg << '\n';

	avg += 4;
	std::cout << avg << '\n'; // 4 / 1 = 4

	avg += 8;
	std::cout << avg << '\n'; // (4 + 8) / 2 = 6

	avg += 24;
	std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

	avg += -10;
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

	(avg += 6) += 10; // 2 calls chained together
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

	Average copy{ avg };
	std::cout << copy << '\n';

	return 0;
}
