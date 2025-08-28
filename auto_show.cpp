#include "diy.h"

auto here()->int{ return 5u; } // auto with Trailing return (we want the return value be a int)
auto add(int, int) -> int;
auto printSomething() -> void;
auto compare_(int x, int y) -> std::common_type_t<decltype(x), decltype(y)>;
auto compare_good(int, double) -> std::common_type_t<int, double>;
std::common_type<int, double>::type compare(double, int); // old-shool

// this becomes a template (the parameters in the function are auto)
void add_Print(auto x, auto y) { std::cout << x << '+' << y << '=' << x + y << '\n'; } 

int main()
{
    using namespace std::literals; // suffix (s and sv)

    [[maybe_unused]]auto a{5.0}; // double
    std::cout << "a is " << typeid(a).name() << '\n';
    [[maybe_unused]]auto b{1};  // int
    [[maybe_unused]]auto c{2u}; // unsigned int
    [[maybe_unused]]auto d{1.23f}; // float
    [[maybe_unused]]auto e{"hello"sv}; // string_view
    [[maybe_unused]]auto e_{"world"s}; // string
    [[maybe_unused]]const int f{5};
    [[maybe_unused]]auto f_{f}; // non-const (which has been dropped)
    [[maybe_unused]]const auto g{f}; // const int
    [[maybe_unused]]constexpr auto h{f}; // constexpr int
    [[maybe_unused]]std::string str{e}; // expensive conversion (string_view2string) <BAD CONVERSION>
    [[maybe_unused]]auto str_{e}; // GOOD, w/o any bad conversion
    std::cout << typeid(here()).name() << '\n';
    add_Print(1, 1); // available for C++20

    return 0;
}
