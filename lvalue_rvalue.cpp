#include <iostream>
#include <string>


// T& is a lvalue reference
template <typename T>
constexpr bool is_lvalue(T&)
{
    return true;
}
// T&& is a rvalue reference
template <typename T>
constexpr bool is_lvalue(T&&)
{
    return false;
}

// (expr) will keep the value type what it was
#define PRINTVCAT(expr){std::cout << #expr << " is an " << (is_lvalue(expr) ? "lvalue\n" : "rvalue\n");} // Judge

template <typename T>
void printvcat(T expr)
{
    // expr is a local variable (lvalue), which doesn't fit this judgement
    // aka always return `lvalue`
    std::cout << expr << " is an " << ((is_lvalue(expr)) ? "lvalue\n" : "rvalue\n");
}
int getfive() { return 5; }

int main()
{
    PRINTVCAT(5);
    // printvcat(5); // fail to judge
    PRINTVCAT(getfive());
    int x{1};
    PRINTVCAT(x);
    PRINTVCAT(std::string{"hello, world!"});
    PRINTVCAT("hello")


    [[maybe_unused]] double y{1.0};
    [[maybe_unused]] int z{2};
    int &ref{x}; // aliases for object `x`, and reference must be initialized.
                // ref is bound to the object `x`
    int &ref2{ref}; // this is not a reference to a reference, `ref` here can be interpreted as `x`

    const double &ref_r{5};// we can use this to bound a rvalue
    const int &ref_r2{'c'};
    const int &ref_k{getfive()};

    std::cout << x << " is " << ref2 << '\n';
    std::cout << ref_r << ',' << ref_r2 << ',' << ref_k << '\n';

    std::string_view hel{"helloworld"};
    std::string uio{hel};
    std::cout << uio << '\n';

    return 0;
}
