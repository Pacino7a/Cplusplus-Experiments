#include <iostream>
#include <exception> // for std::exception
#include <stdexcept>
#include <numeric>
#include <memory>
#include <utility>

class FractionException: public std::runtime_error
{
private:
    std::string m_error{};
public:
    explicit FractionException(const std::string& error)
        :   std::runtime_error{error}
    {}
};

class Fraction
{
private:
    // int m_numerator{};
    // int m_denominator{};
    std::unique_ptr<int[]> m_data{};
    void reduce(int& numerator, int& denominator)
    {
        const int f_gcd{std::gcd(numerator, denominator)};
        if(f_gcd)
        {
            numerator /= f_gcd;
            denominator /= f_gcd;
        }
    }
    int getNumerator() const { return m_data.get()[0]; }
    int getDenominator() const { return m_data.get()[1]; }
public:
    // explicit Fraction(int numerator, int denominator) try
    // : m_numerator{numerator}, m_denominator{denominator}
    // {
    //     if(m_denominator == 0)
    //         throw FractionException{"You Set the Denominator of a Fraction as a ZERO!"};
    //     reduce();
    // }
    explicit Fraction(int numerator, int denominator) try
    : m_data{new int[2]{numerator,denominator}}
    {
        if(m_data.get()[1] == 0)
            throw FractionException{"You Set the Denominator of a Fraction as a ZERO!"};
        reduce(m_data.get()[0], m_data.get()[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Construction failed: " << e.what() << '\n';
        throw;
    }

    Fraction(const Fraction &f) = delete;
    Fraction &operator=(const Fraction &f) = delete;

    // Fraction(Fraction&& f) noexcept
    // {
    //     m_numerator = f.m_numerator;
    //     m_denominator = f.m_denominator;
    // }
    // Fraction& operator=(Fraction&& f) noexcept
    // {
    //     m_numerator = f.m_numerator;
    //     m_denominator = f.m_denominator;
    //     return *this;
    // }

    Fraction(Fraction&& f) noexcept
    {
        m_data = std::move(f.m_data);
    }
    Fraction& operator=(Fraction&& f) noexcept
    {
        m_data = std::move(f.m_data);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const Fraction &f);
};

std::ostream &operator<<(std::ostream &out, const Fraction &f)
{
    try
    {
        if(!f.m_data)
            throw FractionException{"You are trying to Resolve a NullPtr, instead of a valid Fraction"};
        if(f.getDenominator() != 1 && f.getNumerator() != 0)
            return out << "Fraction: " << f.getNumerator() << '/' << f.getDenominator();
        else
            return out << "Fraction: " << f.getNumerator();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Resolving Fraction Error: (" << e.what() << ")";
        return out;
    }
}

int getInt()
{
    for (int temp{};;)
    {
        std::cin >> temp;
        if(!std::cin)
        {

            if(std::cin.eof())
                std::exit(0);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid, Retry: ";
            continue;
        }
        if(!std::cin.eof() && std::cin.peek() != '\n')
        {
            std::string rest{};
            std::cin >> rest;
            std::cout << "What does " << '`' << temp << rest << "` means?\nRetry: ";
            continue;
        }

        return temp;
    }
}
Fraction getFraction()
{
    std::cout<<"Enter the numerator: ";
    const int numerator{getInt()};
    std::cout<<"Enter the denominator: ";
    const int denominator{getInt()};
    return Fraction{numerator, denominator};
}

int main()
{
    try
    {
        Fraction f1{4,6};
        std::cout << f1 << '\n';
        Fraction f2{std::move_if_noexcept(f1)}; // move constructor
        std::cout << f1 << '\n';
        std::cout << f2 << '\n';
        Fraction f3{getFraction()};
        std::cout << f3 << '\n';
        f3 = std::move_if_noexcept(f2); // move assignment
        std::cout << f2 << '\n';
        std::cout << f3 << '\n';


    }
    catch(const FractionException& fe)
    {
        std::cerr << fe.what() << '\n';
    }
    
    return 0;
}
