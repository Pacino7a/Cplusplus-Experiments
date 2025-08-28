#include <iostream>
#include <string>

std::string getName(std::string_view tip, int index)
{
    std::cout << tip << index + 1 << ": ";
    std::string temp;
    std::getline(std::cin >> std::ws, temp);
    return temp;
}

int getAge(std::string_view tip, std::string_view name)
{
    std::cout << tip << name << ": ";
    int temp{};
    std::cin >> temp;
    return temp;
}

void compare(int num_of_people, std::string_view* name, int* age)
{
    int max{*age};
    int index{0};
    for (int i = 1; i < num_of_people; i++)
    {
        if(max < *(age+i))
        {
            max = *(age + i);
            index = i;
        }
    }
    std::cout << *(name + index) << " (age " << *(age + index) << ')' << " is older than ";
    for (int i = 0, count = 1; i < num_of_people; i++ , count++)
    {
        if(i == index)
            continue;
        else
            std::cout << *(name + i) << " (age " << 
            *(age + i) << ')'
                      << (((count == num_of_people)||((count == num_of_people - 1)&&(index == num_of_people - 1))) ? "" : "\nAnd ");
    }
}

int main()
{
    constexpr int num_people{3};
    std::cout << "Please enter" << num_people << " person(s) name and age below:" << '\n';

    std::string name[num_people]{};
    std::string_view name_sv[num_people]{};
    int age[num_people]{};
    
    constexpr std::string_view name_tip{"Enter the name of person #"};
    constexpr std::string_view age_tip{"Enter the age of "};

    for (int i = 0; i < num_people; i++)
    {
        name[i] = getName(name_tip, i);
        name_sv[i] = name[i];
        age[i] = getAge(age_tip, name[i]);
    }

    compare(num_people, name_sv, age);

    return EXIT_SUCCESS;
}
