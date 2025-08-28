#include <vector>
#include <iostream>

class Teacher {
public:
    Teacher(std::string name) : name(name) {}
    void teach() { /* ... */ }
private:
    std::string name;
};

class School {
public:
    void addTeacher(Teacher* teacher) {
        teachers.push_back(teacher);
    }
private:
    std::vector<Teacher*> teachers; // 聚合：存储指针，不管理生命周期
};

int main() {
    Teacher* alice = new Teacher("Alice"); // 教师由外部创建

    School schoolA;
    schoolA.addTeacher(alice); // Alice 属于 SchoolA

    School schoolB;
    schoolB.addTeacher(alice); // Alice 同时属于 SchoolB

    delete alice; // 教师由外部销毁
    return 0;
}
