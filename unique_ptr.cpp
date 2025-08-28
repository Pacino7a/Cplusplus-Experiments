#include <iostream>
#include <memory> // for unique_ptr
#include <utility> // for std::move()

class Fraction
{
private:
	int m_numerator{ 0 };
	int m_denominator{ 1 };

public:
	Fraction(int numerator = 0, int denominator = 1) :
		m_numerator{ numerator }, m_denominator{ denominator }
	{
	}

	friend std::ostream& operator<<(std::ostream& out, const Fraction &f1)
	{
		out << f1.m_numerator << '/' << f1.m_denominator;
		return out;
	}
};

void printFraction(const Fraction* ptr)
{
	if (ptr)
		std::cout << *ptr << '\n';
	else
		std::cout << "No fraction\n";
}

int main()
{
    // std::unique_ptr<Fraction> ptr_o{new Fraction{3, 5}};
    auto ptr{std::make_unique<Fraction>(3, 5)}; // <<---- Perfer this one

    printFraction(ptr.get());

	// delete ptr; // the smart ptr will delete the dynamic allocated resource by itself, so we don't need this anymore

	return 0;
}
