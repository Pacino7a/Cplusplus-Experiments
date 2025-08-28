#include "diy.h"
#include <vector>

constexpr std::string_view capitalize(std::string& name)
{
    if(name.empty())
        return name;
    name.at(0) = static_cast<char>(std::toupper(static_cast<unsigned char>(name.at(0))));
    for(size_t i{1}; i<name.length(); ++i)
        name.at(i) = static_cast<char>(std::tolower(static_cast<unsigned char>(name.at(i))));
    return name;
}
template <typename T>
constexpr bool isValueInArray(const T& value,const std::vector<T>& arr)
{
    // we'll use ref here because we don't know whether the type of elements is copying expensive.
    for(const auto& element : arr)
    {
        if(value == element)
            return true;
    }
    return false;
}

namespace Students
{
    enum Names
    {
        Alex,
        Betty,
        Caroline,
        Dave,
        Emily,
        Fred,
        Greg,
        Holly,
        max_students
    };
}

enum class Students_C
{
    Alex,
    Betty,
    Caroline,
    Dave,
    Emily,
    Fred,
    Greg,
    Holly,
    max_students
};

constexpr auto operator+(Students_C student) noexcept
{
    return static_cast<std::underlying_type_t<Students_C>>(student);
}

namespace Data // use a class or a namespace to hold the unscoped enumeration (avoid converting scoped enumeration to int)
{   // Recommended: use a namespace to hold the unscoped enumeration
    enum Animals
    {
        chiken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        max_animals
    };

    const std::vector<int> animal_legs{2, 4, 4, 4, 2, 0};
};

class Data_C 
{
public:
    enum Animals // we can use this without the class object's existence
    {
        chiken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        max_animals
    };

    const std::vector<int> animal_legs{2, 4, 4, 4, 2, 0}; // existence of this member variable is related to the class object's existence
    // static constexpr std::array<int, max_animals> animal_legs_c{2, 4, 4, 4, 2, 0}; // this is a constexpr, so we can use it in the static_assert
};

constexpr std::string_view getAnimalName(const Data::Animals animal)
{
    switch(animal)
    {
        case Data::chiken: return "chiken";
        case Data::dog: return "dog";
        case Data::cat: return "cat";
        case Data::elephant: return "elephant";
        case Data::duck: return "duck";
        case Data::snake: return "snake";
        default: return "unknown";
    }
}

constexpr void printArrayCap(const std::vector<int>& arr)
{
    std::cout << "The capacity is: " << arr.capacity() << '\n';
}


int main()
{
    // --------------------------------------------------------------------------------------------
    // std::vector fibonacci{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
    // for(auto num: fibonacci) //traversal through the Range-based for loop, iterator's type should be the same with the array obj following.
    //     std::cout << num << ' '; // this does not require us to use the array's length, nor does it require us to index the array
    // std::cout << '\n';
    // --------------------------------------------------------------------------------------------
    // std::vector words{ "peter", "likes", "frozen", "yogurt" }; // avoid to copy a string by using ref
    // for(const auto& word: words) // read only. if the element declaration is non-const, your change of `word` will be saved in `words`
    //     std::cout << word << ' ';
    // std::cout << '\n';
    // --------------------------------------------------------------------------------------------
    // std::vector<std::string_view> names{"Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly"};
    // std::cout << "Enter a Name: ";
    // std::string user_name{};
    // std::cin >> user_name;
    // std::string_view name_view{capitalize(user_name)};
    // bool found{isValueInArray(name_view,names)};
    // // for(std::string_view name: names)
    // // {
    // //     if(name == name_view)
    // //     {
    // //         std::cout << name << " was found.\n";
    // //         found = true;
    // //         break;
    // //     }
    // // }
    // // if(!found)
    // //     std::cout << name_view << " was not found.\n";

    // std::cout << name_view << (found ? " was found.\n" : " was not found.\n");

    // --------------------------------------------------------------------------------------------
    std::vector<int> score_students(Students::max_students);
    score_students[Students::Alex] = 100; // we can use the enum value as the index and the index will not be converted to a size_t (constexpr)
    Students::Names name{Students::Betty}; // but this is not a constexpr
    score_students[name] = 90; // so conversion may happen here
    std::cout << "The class has " << Students::max_students << " students.\n";
    std::cout << "Alex's score is " << score_students[Students::Alex] << '\n';

    std::vector<double> testscore{100,98.5,91.5,88.5,85.5,80.5,78.5,75.5};
    assert(std::size(testscore) == Students::max_students && "The number of students and the number of test scores do not match.");// if testscore is constexpr, we can use static assert here
    //--------------------------------------------------------------------------------
    std::vector<double> testscore_c(+Students_C::max_students); // scoped enumeration can't be converted to Int (constexpr), so we overload operator+ for converting it
    testscore_c[+Students_C::Alex] = 76.5; //overloaded
    std::cout << "The class has " << +Students_C::max_students << " students.\n"; //overloaded
    // quiz
    assert(std::size(Data::animal_legs) == Data::max_animals && "The number of animals and the number of animal legs do not match.");
    std::cout << getAnimalName(Data::elephant) << " has " << Data::animal_legs[Data::elephant] << " legs.\n";
    // ---------------------------------------------------------------------------------
    std::vector array_1{1, 2, 3, 4, 5}; // only std::vector is a dynamic array. std::array and c-style array are static arrays
    std::cout << "The length is : " << std::size(array_1) << '\n';
    printArrayCap(array_1);
    array_1.resize(3); // even the array has been instantiated, we can still resize it (bigger or smaller)
    std::cout << "The length is : " << std::size(array_1) << '\n';
    array_1.shrink_to_fit(); // shrink the capacity to the size
    printArrayCap(array_1);
    array_1.resize(5);
    std::cout << "The length is : " << std::size(array_1) << '\n';
    printArrayCap(array_1);
    // for(auto num: array_1)
    //     std::cout << num << ' ';
    return 0;
}
