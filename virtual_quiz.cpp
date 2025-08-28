#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <string_view>

class Shape // Abstract Class
{
protected:
    virtual std::ostream &print(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Shape& shape)
    {
        return shape.print(out);
    }

public:
    virtual std::string_view identify() const = 0;
    virtual ~Shape() = default; // We use virtual destructor here, the Derived don't need write this if they don't need to allocate anything
                                // but if the Derived need allocate by theirselves, you need explicit write them
};

// namespace Data
// {
//     struct Point
//     {
//         int x{};
//         int y{};
//     };


// };
class Point
{
private:
    int m_x{};
    int m_y{};
public:
    explicit Point(const int x, const int y)
        :   m_x{x},m_y{y}
    {}

    friend std::ostream& operator<<(std::ostream& out, const Point& pt)
    {
        return out << "Point(" << pt.m_x << ", " << pt.m_y << ')';
    }
};

class Triangle: public Shape
{
private:
    Point m_vertex1;
    Point m_vertex2;
    Point m_vertex3;

protected:
    std::ostream& print(std::ostream& out) const override
    {
        return out << "Triangle(" << m_vertex1 << ", " << m_vertex2 << ", " << m_vertex3 << ')';
    }

public:
    explicit Triangle(const Point& p1,const Point& p2,const Point& p3)
        :   m_vertex1{p1}, m_vertex2{p2}, m_vertex3{p3}
    {}

    std::string_view identify() const override
    {
        return "Triangle";
    }
};

class Circle: public Shape
{
private:
    Point m_center;
    double m_radius{};

protected:
    std::ostream& print(std::ostream& out) const override
    {
        return out << "Circle(" << m_center << ", " << "radius " << m_radius << ')';
    }

public:
    explicit Circle(const Point& center, const double radius)
        :   m_center{center}, m_radius{radius}
    {}

    std::string_view identify() const override
    {
        return "Circle";
    }

    double getRadius() const { return m_radius; }
};

double getLargestRadius(const std::vector<Shape*>& shapes)
{
    double radius_max{};
    for(const auto shape:shapes)
    {
        const Circle *c{dynamic_cast<const Circle *>(shape)};
        // const Circle &cref{dynamic_cast<const Circle &>(*shape)};
        // if((*shape).identify() == "Circle")

        if(c)
        {
            double cur_radius{c->getRadius()};
            if(cur_radius > radius_max)
                radius_max = cur_radius;
        }

    }
    return radius_max;
}

double getLargestRadius(const std::vector<std::unique_ptr<Shape>>& shapes)
{
    double radius_max{};
    for(const auto& shape:shapes)
    {
        const Circle *c{dynamic_cast<const Circle *>(shape.get())};
        // const Circle &cref{dynamic_cast<const Circle &>(*shape)};
        if(c) // if downcast success
        {
            // double cur_radius{c->getRadius()};
            // if(cur_radius > radius_max)
            //     radius_max = cur_radius;
            radius_max = std::max(radius_max, c->getRadius());
        }

    }
    return radius_max;
}

int main()
{
    Circle c{ Point{ 1, 2 }, 7 };
    std::cout << c << '\n'; // implicit upcast for operator<<() overloading and use virtual print() to achieve poly

    Triangle t{Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }};
    std::cout << t << '\n';

    // you need delete those elements manually
    // std::vector<Shape*> v{
    //     new Circle{Point{ 1, 2 }, 7},
    //     new Triangle{Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }},
    //     new Circle{Point{ 7, 8 }, 3}
    //   };

    // Vector of Smart Ptrs
    // CAUTIONS: Management by Derived Class, but Declaration is the Base.
    // aka. Base* b {&derived}
    std::vector<std::unique_ptr<Shape>> v_n; // CAN'T use initializer_list here Because of Copy-Semantics
    v_n.emplace_back(std::make_unique<Circle>(Point{ 1, 2 }, 7));
    v_n.emplace_back(std::make_unique<Triangle>(Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }));
    v_n.emplace_back(std::make_unique<Circle>(Point{ 7, 8 }, 3));

    // for(const auto shape:v) // ptr Copy
    //     std::cout << *shape << '\n';

    for(const auto& shape:v_n) // Don't copy unique_ptrs
        std::cout << *shape << '\n';

    // std::cout << "The largest radius is: " << getLargestRadius(v) << '\n';
    std::cout << "The largest radius is: " << getLargestRadius(v_n) << '\n';

    // for(auto& shape:v)
    //     delete shape;
    
    return 0;
}
