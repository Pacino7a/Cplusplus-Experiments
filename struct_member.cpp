#include "fraction.h"

// aggregate data type
// 1.which does not get any constructors that designed by the programer
// 2.all the members' access level must be PUBLIC
// 3.Do not have any base class or virtual functions
struct Employee // program-defined type (compound type)
{
    // default initialization to avoid triger undefine behaviors
    // int dangerous; (a member without a initializer is very dangerous if our instance didn't initialize too)
    std::string name{"Name"}; // data member or member variable (non-static member)
    int id{0};
    double wage{100.0};
}; // your struct (body) must be visable in your program

struct Company
{
    // std::string_view nameOfCompany{"None"}; // (read only) we can't fully control this when it is altered or destroyed
    std::string nameOfCompany{"None"}; // perfer, fully control
    int numberOfEmployee{0};
    Employee CEO{}; // struct within a struct
};

// overloading operator `<<` to print a struct
std::ostream& operator<<(std::ostream& out, Employee& employee)
{
    return out << "Name: " <<employee.name << ", ID: " << employee.id << ", Wage: " << employee.wage << '\n';
}

struct Advertising
{
    int ad_watched{0};
    double percentage_click{0.0};
    double average_earning_per_ad{5.2};
};

Advertising getAdvertiseInf() // pass out (pass by value)
{
    Advertising temp{};
    std::cout << "How many ADs were shown today? ";
    // std::cin >> temp.ad_watched;
    temp.ad_watched = getInt();
    std::cout << "What percentage of ads were clicked on by users? ";
    // std::cin >> temp.percentage_click;
    temp.percentage_click = getDouble();
    std::cout << "What was the average earnings per click? ";
    // std::cin >> temp.average_earning_per_ad;
    temp.average_earning_per_ad = getDouble();

    return temp;
}

void printAdResult(const Advertising& ad) // pass in (pass by ref)
{
    std::cout << ad.ad_watched << " ADs has been watched, "
              << ad.percentage_click * 100 << "% of users clicked the ads, we can earn $"
              << ad.average_earning_per_ad << " from each user's click\n"
              << "So we can Earn $" << ad.ad_watched * ad.percentage_click * ad.average_earning_per_ad << " in total!\n";
}

void printCompany(const Company& cp)
{
    std::cout << cp.nameOfCompany << " has " << cp.numberOfEmployee << " Employees, "
              << "and Its CEO is " << cp.CEO.name << " whose ID is " << cp.CEO.id << " and his/her wage is "
              << "$" << cp.CEO.wage << '\n';
}

constexpr std::ostream& operator<<(std::ostream& out,Company& cp)
{
    return out << cp.nameOfCompany << ", CEO:" << cp.CEO.name << '\n';
}

int main()
{
    Employee ep0 = {"David", 00, 8848.88}; // this initialization will make a copy
    Employee ep1{"Jack", 01, 6231.27}; // but this will not, so we RECOMMEND this way to initialize a struct object
    Employee ep2{"Tom", 02, 5898.3};
    Employee ep3{};  //(Advantage of Initializer list)
                     // if the members do not have any initializer is still fine, they will be value-initialized
    Employee ep4("Carter", 03, 9865.77); // (C++20), not work for std::array
    const Employee ep5("Jamie", 04, 8662.23); // instance(Read Only)
    Employee ep6{.name{"Ken"},.wage{7882.2}}; // designated initializer
    ep6 = {.name = ep6.name, .id = 05, .wage = 8855.2}; // update Employee6's data
    Employee ep1_copy{ep1}; // ep1_copy = ep1 or ep1_copy(ep1),
                            // standard form of initialization, NOT aggregate initialization
                            // most commonly seen when a function returns a struct we need
    Employee *eptr{&ep1}; // pointer of a struct

    std::cout << ep1.name << " , " << ep2.name << " , " << ep3.name << '\n'; // use dot(.) to get the member in that struct
    ep3.name = "John"; // assign a member
    std::cout << ep1.name << " , " << ep2.name << " , " << ep3.name << '\n';
    std::cout << eptr->name << '\n'; // if you get the pointer of a struct, you need use an arrow to get the member
    std::cout << ep4; // overloading operator `<<` to print a Struct directly
    std::cout << ep6;

    /*********************************************************/

    Fraction f1;   // f1.numerator == 0 (default), f1.denominator == 1 (default)
    [[maybe_unused]] Fraction f2{}; // f1.numerator == 0 (default), f1.denominator == 1 (default)

    printFraction(f1);// pass a struct object (by ref)
    printFraction(Fraction{1, 2}); // support pass a temporary object (by ref)

    /*-----------------------------------------*/
    printAdResult(getAdvertiseInf());

    /*----------------------------------------*/
    Fraction f3{getFraction()};
    Fraction f4{getFraction()};
    printFraction(fractionsMultiply(f3, f4));

    printFraction(reducedFraction(Fraction{8, 2}));   // 4
    printFraction(reducedFraction(Fraction{2, 8}));   // 1/4
    printFraction(reducedFraction(Fraction{62, 42})); // 31/21
    printFraction(reducedFraction(Fraction{22, 48})); // 11/24
    printFraction(reducedFraction(Fraction{-2, -8})); // 1/4
    printFraction(reducedFraction(Fraction{-2, 8}));  //-1/4
    printFraction(reducedFraction(Fraction{2, -8}));  // 1/4
    printFraction(reducedFraction(Fraction{11, 17})); // 11/17
    printFraction(reducedFraction(Fraction{17, 11})); // 17/11

    Company Apple{"Apple.Inc", 100000, {"Tim Cook", 02, 15000000}}; // Nested Aggregation Initialization is Acceptable.
    std::cout << Apple;
    printCompany(Apple);

    std::cout << sizeof(std::string) + sizeof(int) + sizeof(double) << '\n'; // struct at least as large as the size of all the variables it contains
    std::cout << sizeof(Employee) << '\n'; // for performance reason, a struct will be larger than it should be
                                           // maybe (Int -> Long Long)  (4 Bytes -> 8 Bytes)

    return 0;
}
