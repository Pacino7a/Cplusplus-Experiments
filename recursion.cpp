#include <vector>
#include <ranges>
#include "diy.h"

// Recursion
int fibonacci(const std::size_t count) // LUT method, the efficiency is much greater than the base-line
{
    static std::vector result{0, 1};
    
    if(count < std::size(result))// if we have figured out the result before, return it from the cache
        return result[count]; 
    
    else // we need to figure it out and push it the cache
    {
        result.push_back(fibonacci(count - 2) + fibonacci(count - 1)); // push the new result to the cache
        return result[count]; // return the fresh result
    }
}

int factorial(const std::size_t count)
{
    static std::vector result{1}; // 1,1,2,6,24

    if(count < std::size(result))
        return result[count];
    else
    {
        result.push_back(result[count - 1] * static_cast<int>(count));
        return result[count];
    }
}

void parseIntegerToSum(const int value)
{
    static std::vector<int> result{};
    static const int ori{value};

    if(value < 10)
        result.push_back(value);
    else
    {
        parseIntegerToSum(value / 10); // shift right 1
        result.push_back(value % 10);  // extract the ones digit, if you want extract the tens and ones digits you can % 100
    }
    if(value == ori) // output only in the first layer of called function
    {
        int sum{};
        std::size_t count{};
        std::size_t len{std::size(result)};
        for(const int num:result)
        {
            sum += num;
            ++count;
            std::cout << num << ((count < len) ? '+' : '=');
        }
        std::cout << sum << '\n';
    }
}

int sumDigits(int x) // using this function you can only get the result
{
	if (x < 10)
		return x;

	return sumDigits(x / 10) + x % 10;
}

std::vector<int> decimal2Binary(int64_t decimal, const int length_seq)
{
    if(decimal < 0) // keep the sym-bit and transform the negative value to be positive
    {
        assert(decimal >= -powint(2, length_seq - 1) && "Binary Seq Overflowed, Please choose a longer sequnce to hold.\n");
        decimal = powint(2, length_seq) + decimal;
    }
    static std::vector<int> binary_seq{};
    static int64_t ori_dec{decimal};
    if(decimal < 2)
        binary_seq.push_back(static_cast<int>(decimal));
    else
    {
        binary_seq.push_back(static_cast<int>(decimal % 2)); // 8 -> 001
        decimal2Binary(decimal / 2, length_seq);
    }
    if(decimal==ori_dec)
    {
        for (;std::size(binary_seq) < static_cast<std::size_t>(length_seq);) // 8 -> 0010'0000'0000'...
        {
            binary_seq.push_back(0);
        }
        return binary_seq;
    }
    else
        return {};
}

int main()
{
    std::cout << "Fibonacci:\n";
    for (size_t i = 0; i < 13; ++i)
    {
        std::cout << fibonacci(i) << ' ';
    }
    std::cout << '\n'
              << "Factorial:\n";
    for (size_t i = 0; i < 13; ++i)
    {
        std::cout << factorial(i) << ' ';
    }
    std::cout << '\n';

    parseIntegerToSum(93427);

    // int to Binary
    const std::size_t len_BinSeq{16};
    const int64_t decimal_number{-9};
    // std::cout << decimal_number;
    if(decimal_number >= 0) // keep the syb bit (check overflow)
        assert(decimal_number < powint(2, len_BinSeq - 1) && "Binary Seq Overflowed, Please choose a longer sequnce to hold.\n");

    const std::vector binary_seq{decimal2Binary(decimal_number, len_BinSeq)}; // move semantic
    std::cout << "\nHere is Decimal to Binary Transformer:\n";
    std::cout << "(Decimal) " << decimal_number << "\n(Binary)  0b";
    std::size_t count{1};
    for(const int num:binary_seq | std::views::reverse) // because the array is made by push, so we need to reverse it to get its view
    {
        std::cout << num << ((count % 4 == 0 && count != std::size(binary_seq)) ? "\'" : "");
        ++count;
    }

    return 0;
}
