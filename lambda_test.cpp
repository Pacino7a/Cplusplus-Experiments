#include "diy.h"
#include <functional>

//  case 1
void repeat1(const int repeatimes, const std::function<void(int)>& fcn)
{
    for (int i{0}; i < repeatimes;++i)
        fcn(i);
    std::cout << '\n';
}

// case 2
template <typename T>
void repeat2(const int repeatimes, const T& fcn)
{
    for (int i{0}; i < repeatimes;++i)
        fcn(i);
    std::cout << '\n';
}

// case 3 (recommended)
void repeat3(const int repeatimes, const auto& fcn)
{
    for (int i{0}; i < repeatimes;++i)
        fcn(i);
    std::cout << '\n';
}

// case 4 (only for no captures)
void repeat4(const int repeatimes, void (*fcn)(int))
{
    for (int i{0}; i < repeatimes;++i)
        fcn(i);
    std::cout << '\n';
}

struct Student
{
    std::string name{};
    int points{};
};

struct Season
{
    std::string_view name{};
    double averageTemperature{};
};

void myInvoke(const std::function<void()>& fn)  // if you use lambda directly here, you will get a lot of copys of the lambda, make your output go wrong
{                                               // so we recommend use std::function type `lambda` here or use std::ref() to avoid making copys
fn();                                           // which could maintain the consistency of your output.
}

int main()
{
    constexpr std::array<std::string_view, 4> arr{"apple", "banana", "walnut", "lemon"};
    auto found{ std::find_if(arr.begin(), arr.end(), 
        [](std::string_view str){ return str.find("nut") != std::string_view::npos; })}; 
                    // sting_view::find returns std::string_view::npos if it doesn't find the specific substring
                    // otherwise it returns the index where it localed at.
                    // When the lambda gets a True, find_if will return the adress where it happens,
                    // otherwise it will return the end() for Nothing.
    if(found == arr.end())
        std::cout << "Not found!\n";
    else
        std::cout << "Found " << *found << '\n';

    auto lambda{   // store a lambda as auto is recommended and you can also choose to store it as std::function<xx>
        [](int i)
        {
            std::cout << i << ' ';
        }};

    std::function<void(int)> lambda_f{      // store the lambda in a std::function
        [](int i)
        {
            std::cout << i << ' ';
        }};

    void (*fcnPtr)(int) =           // as a function pointer
        [](int i)
    {
        std::cout << i << ' ';
    };

    repeat1(3, lambda);
    repeat2(3, lambda);
    repeat3(3, lambda);
    repeat4(3, lambda);

    constexpr std::array months{ // pre-C++17 use std::array<const char*, 12>
        "January",  // <--- begin()
        "February",
        "March",
        "April",
        "May",
        "June",  // <--- find and quit
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"  // <--- count will drive here   <end()-1>
      };

    const auto sameLetter{
        std::adjacent_find(months.begin(), months.end(),
                           [](const auto &month_1, const auto &month_2)
                           {
                               return (month_1[0] == month_2[0]);               // adjacent here for (first, first + 1) --> (i, i + 1) --> (end - 2, end - 1)
                    })};                                                        // the search logistics based on your design (aka. lambda)
                                                                                // if the function found that, it will return the i'th element's adress
                                                                                // otherwise, it returns the end() for Not found
    if(sameLetter != months.end())
    {
        std::cout << *sameLetter << " and " << *std::next(sameLetter)
                  << " start with the same letter.\n";
    }

    // we can use constexpr here because <count_if> is a constexpr in C++20 and later
    constexpr auto fiveLetterMonths{std::count_if(months.begin(), months.end(), // we use `count_if` here, ++count when the if-statement gets True
                                    [](std::string_view str)
                                {   // `auto` is NOT always Good as you expected
                                    // if we use `auto` here, the type will be deduced as const char *, so that we can't use `length()`.
                                    // as a consequence, this will make your program more complex
                                        return str.length() == 5;
                                })};
    std::cout << "There are " << fiveLetterMonths << " Months with  5 letters.\n";

    auto print{
        [](auto value)
        {
            static int count_value{};
            std::cout << count_value++ << ": " << value << '\n';
        }};

    print("hello"); // type const char*  count 0
    print("world"); // type const char*  count 1
    print(1);   // type int count 0
    print(2);   // type int count 1
    print("ding ding"); // type const char*  count 2
    // the static value maintain in the specific type call, aka. different type has different static value.

    auto divide{ [](int x, int y, bool intDivision) -> double {
        if (intDivision)
          return x / y; // will do an implicit conversion of result to double (1 -> 1.0)
        else
          return static_cast<double>(x) / y;
      } };
    
    std::cout << divide(3, 2, true) << '\n'; //
    std::cout << divide(3, 2, false) << '\n';

    std::array<Student, 8> nameAndPoints{
        { { "Albert", 3 },
          { "Ben", 5 },
          { "Christine", 2 },
          { "Dan", 8 }, // Dan has the most points (8).
          { "Enchilada", 4 },
          { "Francis", 1 },
          { "Greg", 3 },
          { "Hagrid", 5 } }
      };

    const auto bestStident{std::max_element(nameAndPoints.begin(), nameAndPoints.end(),
                                      [](const Student &student_1, const Student &student_2)
                                      {
                                          return student_1.points < student_2.points;  // if [maxIndex] < [currentIndex] -> [maxIndex] = [currentIndex]
                                      })};
    std::cout << bestStident->name << " is the best student.\n";

    std::array<Season, 4> seasons{
        { { "Spring", 285.0 },
          { "Summer", 296.0 },
          { "Fall", 288.0 },
          { "Winter", 263.0 } }
      };

    std::sort(seasons.begin(), seasons.end(),
              [](const Season &season_1, const Season &season_2)
              {
                  return season_1.averageTemperature < season_2.averageTemperature; // [current] < [bestIndex] -> [bestIndex] = [current] (put the small ahead)
              });

    for(const auto& season:seasons)
    {
        std::cout << season.name << '\n';
    }

    int i{0};
    auto caller{
        [i]() mutable
        {
            std::cout << ++i << '\n';
        }};
    
    // use std::function or reference_wrapper here for avoiding make copys
    myInvoke(std::ref(caller));
    myInvoke(std::ref(caller));
    myInvoke(std::ref(caller));
    
    return 0;
}







