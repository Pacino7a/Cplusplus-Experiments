// #define NDEBUG
#include "diy.h"
#include "random_s_class.h"
#include <vector>

// template <typename T>
// void printArr(const std::vector<T> arr) // only accept std::vector
// void printArr(const T& arr) // read only, more general (accept all kinds of data as long as it has the firs elements)
void printArr(const auto& arr, const int index) //auto
{
    assert(index >= 0 && index < std::ssize(arr) && "Your Index is out of the bound!\n");
    if(index >= 0 && index < std::ssize(arr))
        std::cout << "The " << index+1 << " element of current Array is " << arr.data()[index] << ".\n";
    else
    {
        std::cout << "Your Index " << index << " is out of the bound!\n";
        // std::abort();
    }
}

// int getInt0_9()
// {
//     for (int temp{0};;)
//     {
//         std::cout << "Please enter an Integer between 0 and 9: ";
//         std::cin >> temp;
//         if(!std::cin) // if extract failed
//         {
//             if(std::cin.eof()) // if user's input is EOF, exit the program
//                 std::exit(0);

//             std::cin.clear(); //else, reset cin
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the buffer
//             continue;
//         }
//         if(!std::cin.eof() && std::cin.peek()!='\n') // if user's input more than an Integer
//         {
//             std::string rest{};
//             std::cin >> rest; // extract the rest
//             std::cout << "What does " << '`' << temp << rest << "` means?\n"; // pop the hint
//             continue; // try again
//         }

//         if(temp >= 0 && temp <= 9) // all fine, Output
//             return temp;
//     }
// }

template <typename T>
auto get0_9()
{
    for (T temp{};;)
    {
        std::cout << "Please enter an Number between 0 and 9: ";
        std::cin >> temp;
        if(!std::cin)
        {
            if(std::cin.eof())
                std::exit(0);

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if(!std::cin.eof()&&std::cin.peek()!='\n')
        {
            std::string rest{};
            std::cin >> rest;
            std::cout << "What does " << temp << rest << " means? Please Try Again.\n";
            continue;
        }
        if(temp >= 0 && temp <= 9)
            return temp;
    }
}

template <typename T>
std::optional<std::size_t> findIndex(const std::vector<T>& arr, const T value)
{
    for (size_t i = 0; i < arr.size(); ++i)
    {
        if(value == arr[i])
            return i;
    }

    return std::nullopt;
}

template <typename T>
void printResult(const T search_value, const std::vector<T>& arr)
{
    std::optional<std::size_t> index {findIndex(arr, search_value)};
    if(index)
        std::cout << "The value " << search_value << " that you are looking for is in the position of [" << *index << "] in the Array.\n";
    else
        std::cout << "The array does not have value `" << search_value << "`.\n";
}

template<typename T>
class ArraysMaxAndIndex
{
public:
    ArraysMaxAndIndex(const std::vector<T>& arr_0)
    :m_vec{arr_0},m_max{0},m_index{0}
    {}

    T getArrayMax() const { return m_max; }
    std::size_t getArrayIndex() const { return m_index; }
    bool getStatus() const { return m_empty; }
    void calculateArrayMaxAndIndex();

private:
    std::vector<T> m_vec{};
    T m_max{};
    std::size_t m_index{};
    bool m_empty{false};
};


template <typename T>
void ArraysMaxAndIndex<T>::calculateArrayMaxAndIndex()
{
    if(m_vec.size() == 0)
        m_empty = true;
    else
    {
        m_max = m_vec[0];
        for (std::size_t i{0};i < m_vec.size();++i)
        {
            if(m_vec[i] > m_max)
            {
                m_max = m_vec[i];
                m_index = i;
            }
        }
    }
}

template <typename T>
void printMaxAndIndex(const ArraysMaxAndIndex<T>& inf)
{
    if(!inf.getStatus()) // Array is not empty
    std::cout << "The Current Array's Max:" << inf.getArrayMax() << ", which is on the position [" << inf.getArrayIndex() << "].\n";
    else
    std::cout << "The Current Array is Empty, So No Maximum(0).\n";

}

std::vector<int> getRandomVec(std::size_t size)
{
    std::vector<int> rand_vec(size);
    for (size_t i = 0; i < size; ++i)
    {
        rand_vec[i] = Random::get<int, int>(1, 200);
    }
    return rand_vec;
}

void fizzbuzzEnhance(const std::vector<int>& arr)
{
    static const std::vector fizz_n{3, 5, 7, 11, 13, 17, 19}; // constexpr is better, but we can't do that with vectors. std::array is Ok for this
    static const std::vector fizz_ch{"fizz", "buzz", "pop", "bang", "jazz", "pow", "boom"};
    assert(fizz_n.size() == fizz_ch.size() && "divisors' size not match with words' size!");

    bool printed{};
    for (size_t n{0}; n < arr.size(); ++n)
    {
        printed = false; // work?
        for (size_t i{0}; i < fizz_n.size(); ++i)
        {
            if(arr[n]%fizz_n[i] == 0)
            {
                std::cout << fizz_ch[i];
                printed = true; // worked!
            }
        }

        if(!printed)
            std::cout << arr[n];

        std::cout << '\n';
    }

}


int main()
{
    constexpr int index{1};
    size_t index{1};
    // size_type  is a nested typedef(std::size_t's alias) that is an alias for the type used to store the length (and indices, if supported) of a standard library container.
    std::vector v0{'h', 'e', 'l','l','o'};
    std::cout << "The array has " << std::ssize(v0) << " elements.\n"
              << v0.data()[1] << v0[index] << v0.at(1); // we usually use `arr[index]` because of its efficiency
    std::vector v1{8, 1, 3, 4, 2};
    std::string str{"helloWorld!\n"};
    [[maybe_unused]] std::array t1{1};
    printArr(v1, 0);
    printArr(str, 1);
    printArr(v1, 5);
    printArr(v1, -1);

    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };
    std::vector arr_d{ 4.4, 6.6, 7.7, 3.3, 8.8, 2.2, 1.1, 9.9 };
    auto search_value{get0_9<int>()};
    auto search_value_d{get0_9<double>()};
    printResult(search_value, arr);
    printResult(search_value_d, arr_d);

    std::vector<int> data0{};
    // std::cout << "default Size: " << data0.size(); // size == 0
    std::vector data1 { 84, 92, 76, 81, 56 };
    std::vector data2 { -13.0, -26.7, -105.5, -14.8 };

    ArraysMaxAndIndex data0_inf{data0};
    data0_inf.calculateArrayMaxAndIndex();
    printMaxAndIndex(data0_inf);
    ArraysMaxAndIndex data1_inf{data1};
    data1_inf.calculateArrayMaxAndIndex();
    printMaxAndIndex(data1_inf);
    ArraysMaxAndIndex data2_inf{data2};
    data2_inf.calculateArrayMaxAndIndex();
    printMaxAndIndex(data2_inf);

    std::vector random_vector_150{getRandomVec(150)};
    fizzbuzzEnhance(random_vector_150);

    return 0;
}
