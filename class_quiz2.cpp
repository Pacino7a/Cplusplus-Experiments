#include <iostream>
#include <string>
class Vector3d;

class Point3d
{
private:
    double m_x{};
    double m_y{};
    double m_z{};
public:
    explicit Point3d(double x, double y, double z)
        : m_x{x},m_y{y},m_z{z}
    {}

    void print() const
    {
        std::cout << "Point(" << m_x << ", " << m_y << ", " << m_z << ")\n";
    }

    void moveByVector(const Vector3d &v);
};

class Vector3d
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    explicit Vector3d(double x, double y, double z)
        : m_x{x},m_y{y},m_z{z}
    {}

    void print() const
    {
        std::cout << "Vector(" << m_x << ", " << m_y << ", " << m_z << ")\n";
    }

    friend void Point3d::moveByVector(const Vector3d& v);
};

void Point3d::moveByVector(const Vector3d& v) // Point3d (main), Vector3d (side)
{
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;
    print(); // from the class where this function located at
}

int main()
{
    Point3d point{1.0, 2.0, 3.0};
    Vector3d vector{2.0, 2.0, -3.0};

    point.print();
    point.moveByVector(vector);
    return 0;
}
