#include "diy.h"
#include <vector>
#include <map> // better use STL for mapping

struct StudentGrade
{
    std::string name{};
    char grade{};
};

class GradeMap
{
private:
    std::vector<StudentGrade> m_map{};

public:
    char& operator[](std::string_view name);
};

// char& GradeMap::operator[](std::string_view name)
// {
//     const auto findName{
//         [name](const StudentGrade& student)
//         { return toASCIILowerCase(student.name) == toASCIILowerCase(name); }};
//     const auto find{std::find_if(m_map.begin(), m_map.end(), findName)};
//     // assert(find != m_map.end() && "Name Not Found!");
//     if(find != m_map.end()) // if we find the student, return his grade's ref
//         return find->grade;
//     else // otherwise, we create the student and put his grade as 'N' (none)
//     {
//         // m_map.emplace_back(StudentGrade{name, 'N'});
//         // return m_map.back().grade;
//         return m_map.emplace_back(std::string{name},'N').grade;
//     }
// }

char& GradeMap::operator[](std::string_view name)
{
    auto comp{
        [](const StudentGrade &sg, std::string_view n)
        {
            return toASCIILowerCase(sg.name) < toASCIILowerCase(n);
        }};

    auto it{std::lower_bound(m_map.begin(), m_map.end(), name, comp)}; // binary search and returns the iterator

    if (it != m_map.end() && toASCIILowerCase(it->name) == toASCIILowerCase(name)) // if we didn't find any name matched
        return it->grade;
    else
        return m_map.emplace(it, StudentGrade{std::string{name}, 'N'})->grade; // emplace(position, content) (aka. insert the element to that position)
}

int main()
{
    GradeMap grades{};

    // grades["Joe"] = 'A';
    // grades["Frank"] = 'B';

    // std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
	// std::cout << "Frank has a grade of " << grades["Frank"] << '\n';

    // <POTENTIALLY NOT WORK>
    // the code below may probably not work as expected
    // because of the extension of m_map vector
    // which leads to a new allocation for the elements inside it
    // and makes the references dangling
    // 
	char& gradeJoe{ grades["Joe"] }; // does an emplace_back
	gradeJoe = 'A';

	char& gradeFrank{ grades["Frank"] }; // does a emplace_back
	gradeFrank = 'B';

	std::cout << "Joe has a grade of " << gradeJoe << '\n';
	std::cout << "Frank has a grade of " << gradeFrank << '\n';


    return 0;
}
