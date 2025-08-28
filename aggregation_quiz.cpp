#include <iostream>
#include <vector>

class Teacher
{
private:
    std::string m_name{};
public:
    Teacher(std::string&& name)
    :   m_name{name}
    {}

    std::string_view getName() const { return m_name; }
};

class Department
{
private:
    std::vector<std::reference_wrapper<const Teacher>> m_teachers{}; // because a vector full of refs works not pretty well, we need use a wrapper here

public:
    void add(const Teacher &teacher) { m_teachers.emplace_back(teacher); } // we can directly pass the reference to the vector
    friend std::ostream &operator<<(std::ostream &out, const Department &dp);
};

std::ostream &operator<<(std::ostream &out, const Department &dp)
{
    for(const auto& teacher:dp.m_teachers)
        out << teacher.get().getName() << "  ";
    return out << '\n';
}

int main()
{
  // Create a teacher outside the scope of the Department
  Teacher t1{ "Bob" };
  Teacher t2{ "Frank" };
  Teacher t3{ "Beth" };

  {
    // Create a department and add some Teachers to it
    Department department{}; // create an empty Department

    department.add(t1);
    department.add(t2);
    department.add(t3);

    std::cout << department;

  } // department goes out of scope here and is destroyed

  std::cout << t1.getName() << " still exists!\n";
  std::cout << t2.getName() << " still exists!\n";
  std::cout << t3.getName() << " still exists!\n";
  // Note:
  // The existence of Teacher(Member) is independent of Department(Object:class)
  // which means they are aggregation
  // Not composition (strong dependent)
  // and we should use both of the two methods more flexible

  return 0;
}
