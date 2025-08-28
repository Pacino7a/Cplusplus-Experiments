#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdint>

using int_16 = std::int16_t;
using int_8 = std::int8_t;

class FixedPoint2
{
private:
    int_16 m_nfractional{}; // base
    int_8 m_fractional{}; // decimal
public:
    explicit FixedPoint2(const int_16 nf_part, const int_8 f_part)
    :   m_nfractional{nf_part},m_fractional{f_part}
    {
        if(m_fractional < 0 || m_nfractional < 0) // At least one part of the fixed-point number is negative, we need check further
        {
            // Both of the situations can't happen in the same time
            if(m_fractional > 0) // if the fractional part is positive, we flip it
                m_fractional = -m_fractional;
            else if(m_nfractional > 0) // if the base part is positive, flip it
                m_nfractional = -m_nfractional;
            // otherwise, both of them are negative. We do Nothing here
        }
        // assert(m_fractional > -100 && m_fractional < 100); // 2 digits
        // <Overflow handling>
        // if(m_fractional < -99)
        // {
        //     // m_fractional = -99; // strategy one
        //     // m_fractional += 100; // strategy two

        //     m_nfractional -= 1; // carry is needed
        // }
        // else if(m_fractional > 99)
        // {
        //     // m_fractional = 99; // Stratege One
        //     m_fractional -= 100; // Stratege Two

        //     m_nfractional += 1; // carry is needed
        // }
        m_nfractional += m_fractional / 100;    // e.g. 204 / 100 = 2, -204 / 100 = -2
        m_fractional  = m_fractional % 100;     // e.g. 204 % 100 = 4, -204 % 100 = -4
    }
    explicit FixedPoint2(const double fp) // e.g. -6.28
        : m_nfractional{static_cast<int_16>(fp)} // -6
    {
        double temp_fractional{};
        if(fp >= 0)
            temp_fractional = (fp - m_nfractional) * 100 + 0.5; // frational -> fixed point and round it
        else
            temp_fractional = (fp - m_nfractional) * 100 - 0.5; // -28.5 
        m_fractional = static_cast<int_8>(temp_fractional);// -28.5 -> -28
        // FixedPoint2(m_nfractional, m_fractional);  // Delegate the rest to the original constructor
        m_nfractional += m_fractional / 100;    // e.g. 204 / 100 = 2, -204 / 100 = -2
        m_fractional   = m_fractional % 100;    // e.g. 204 % 100 = 4, -204 % 100 = -4
    }

    // FixedPoint2(double d) :
    // FixedPoint2(
    //     static_cast<int_16>(std::trunc(d)),
    //     static_cast<int_8>(std::round(d * 100) - std::trunc(d) * 100)
    // )
    // {}
    // friend std::ostream &operator<<(std::ostream &out, const FixedPoint2 &fixpoint);
    friend bool testDecimal(const FixedPoint2 &fp);
    explicit operator double() const // type-cast overload here (*this --cast--> double)
    {
        // if(m_fractional >= 0 && m_nfractional >= 0)
        return static_cast<double>(m_nfractional) + (static_cast<double>(m_fractional) / 100);
        // else
            // return -(static_cast<double>(std::abs(m_nfractional)) + (static_cast<double>(std::abs(m_fractional)) / 100));
    }
    friend bool operator==(const FixedPoint2 &fp1, const FixedPoint2 &fp2);
    friend bool operator<(const FixedPoint2 &fp1, const FixedPoint2 &fp2);
    friend bool operator!=(const FixedPoint2 &fp1, const FixedPoint2 &fp2);
    friend bool operator>(const FixedPoint2 &fp1, const FixedPoint2 &fp2);
    friend bool operator>=(const FixedPoint2 &fp1, const FixedPoint2 &fp2);
    friend bool operator<=(const FixedPoint2 &fp1, const FixedPoint2 &fp2);
    // auto operator<=>(const FixedPoint2 &) const = default;
    // bool operator==(const FixedPoint2 &) const = default;
    friend FixedPoint2 operator+(const FixedPoint2 &fp1, const FixedPoint2 &fp2);
    friend std::istream &operator>>(std::istream &in, FixedPoint2 &fp);
    FixedPoint2& operator-(){
        m_nfractional = -m_nfractional;
        m_fractional  = -m_fractional;
        return *this;
    }
};

std::ostream &operator<<(std::ostream &out, const FixedPoint2 &fixedpoint)
{
    // const int_16 nf_part{fixpoint.m_nfractional};
    // const int_8 f_part{fixpoint.m_fractional};
    // if(nf_part < 0 ||  f_part< 0)
    //     return out << '-' << nf_part << '.' << static_cast<int>(f_part); // int_8 here will be interpreted as a char
    // else
    //     return out << nf_part << '.' << static_cast<int>(f_part);
    return out << static_cast<double>(fixedpoint);
}

bool operator==(const FixedPoint2 &fp1, const FixedPoint2 &fp2)
{
    return fp1.m_fractional == fp2.m_fractional && fp1.m_nfractional == fp2.m_nfractional;
}

bool operator<(const FixedPoint2 &fp1, const FixedPoint2 &fp2)
{
    return (fp1.m_nfractional < fp2.m_nfractional || (fp1.m_nfractional == fp2.m_nfractional && fp1.m_fractional < fp2.m_fractional));
}

bool operator!=(const FixedPoint2 &fp1, const FixedPoint2 &fp2)
{
    return !(fp1 == fp2);
}

bool operator>(const FixedPoint2 &fp1, const FixedPoint2 &fp2)
{
    return (fp2 < fp1);
}

bool operator>=(const FixedPoint2 &fp1, const FixedPoint2 &fp2)
{
    return !(fp1 < fp2);
}

bool operator<=(const FixedPoint2 &fp1, const FixedPoint2 &fp2)
{
    return !(fp1 > fp2);
}

bool testDecimal(const FixedPoint2 &fp)
{
    if (fp.m_nfractional >= 0)
        return fp.m_fractional >= 0 && fp.m_fractional < 100;
    else
        return fp.m_fractional <= 0 && fp.m_fractional > -100;
}

FixedPoint2 operator+(const FixedPoint2 &fp1, const FixedPoint2 &fp2)
{
    return FixedPoint2(static_cast<double>(fp1) + static_cast<double>(fp2));
}

// FixedPoint2& operator-(FixedPoint2 &fp)
// {
//     fp.m_nfractional = -fp.m_nfractional;
//     fp.m_fractional = -fp.m_fractional;
//     return fp;
// }

std::istream &operator>>(std::istream &in, FixedPoint2 &fp)
{
    double temp{};
    for(;;)
    {
        in >> temp;
        if(!std::cin)
        {
            if(std::cin.eof())
                std::exit(0);

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if(!std::cin.eof() && std::cin.peek() != '\n')
        {
            std::string rest{};
            std::cin >> rest;
            std::cout << "What does " << '`' << temp << rest << "` means?\nWe want to try again:";
            continue;
        }
        break;
    }
    fp = FixedPoint2(temp); // we use the double constructor to make an anonymous obj
    return in;
}

int main()
{
    // Phrase 1
	// FixedPoint2 a{ 34, 56 };
	// std::cout << a << '\n';
	// std::cout << static_cast<double>(a) << '\n';
	// assert(static_cast<double>(a) == 34.56);

    // FixedPoint2 b{ -2, 8 };
	// assert(static_cast<double>(b) == -2.08);

	// FixedPoint2 c{ 2, -8 };
	// assert(static_cast<double>(c) == -2.08);

	// FixedPoint2 d{ -2, -8 };
	// assert(static_cast<double>(d) == -2.08);

	// FixedPoint2 e{ 0, -5 };
	// assert(static_cast<double>(e) == -0.05);

	// FixedPoint2 f{ 0, 10 };
	// assert(static_cast<double>(f) == 0.1);

    // Phrase 2
    // FixedPoint2 a{ 1, 104 };
	// std::cout << a << '\n';
	// std::cout << static_cast<double>(a) << '\n';
	// assert(static_cast<double>(a) == 2.04);
	// assert(testDecimal(a));

	// FixedPoint2 b{ 1, -104 };
	// assert(static_cast<double>(b) == -2.04);
	// assert(testDecimal(b));

	// FixedPoint2 c{ -1, 104 };
	// assert(static_cast<double>(c) == -2.04);
	// assert(testDecimal(c));

	// FixedPoint2 d{ -1, -104 };
	// assert(static_cast<double>(d) == -2.04);
	// assert(testDecimal(d));

    // Phrase 3
	// FixedPoint2 a{ 0.01 };
	// assert(static_cast<double>(a) == 0.01);

	// FixedPoint2 b{ -0.01 };
	// assert(static_cast<double>(b) == -0.01);

	// FixedPoint2 c{ 1.9 }; // make sure we handle single digit decimal
	// assert(static_cast<double>(c) == 1.9);

	// FixedPoint2 d{ 5.01 }; // stored as 5.0099999... so we'll need to round this
	// assert(static_cast<double>(d) == 5.01);

	// FixedPoint2 e{ -5.01 }; // stored as -5.0099999... so we'll need to round this
	// assert(static_cast<double>(e) == -5.01);

	// // Handle case where the argument's decimal rounds to 100 (need to increase base by 1)
	// FixedPoint2 f { 106.9978 }; // should be stored with base 107 and decimal 0
	// assert(static_cast<double>(f) == 107.0);

	// // Handle case where the argument's decimal rounds to -100 (need to decrease base by 1)
	// FixedPoint2 g { -106.9978 }; // should be stored with base -107 and decimal 0
	// assert(static_cast<double>(g) == -107.0);

    // Phrase 4
    assert(FixedPoint2{ 0.75 } == FixedPoint2{ 0.75 });    // Test equality true
	assert(!(FixedPoint2{ 0.75 } == FixedPoint2{ 0.76 })); // Test equality false

	// Test additional cases -- h/t to reader Sharjeel Safdar for these test cases
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 });    // both positive, no decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 });    // both positive, with decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }); // both negative, no decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }); // both negative, with decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 });  // second negative, no decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 });  // second negative, possible decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 });   // first negative, no decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 });   // first negative, possible decimal overflow

	FixedPoint2 a{ -0.48 };
	assert(static_cast<double>(a) == -0.48);
	assert(static_cast<double>(-a) == 0.48);

	std::cout << "Enter a number: "; // enter 5.678
	std::cin >> a;
	std::cout << "You entered: " << a << '\n';
	assert(static_cast<double>(a) == 5.68);

    return 0;
}
