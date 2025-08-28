#define NDEBUG
#include <iostream>
#include <cmath>
#include <cassert>

void sayHello(std::string* str_ptr)
{
    assert(str_ptr && "You just passed a nullptr!"); // handle the nullptr, avoid the program crash

    if(!str_ptr)
    {
        std::cout << "you just passed a nullptr!\n";
        return;
    }
    
    std::cout << *str_ptr << '\n';
}

void sayHelloR(const std::string& str)
{
    std::cout << str << '\n';
}

void showID(const int* id=nullptr) // (USE THIS when makes a copy of its argument is expensive)
{
    if (!id) // can't recongize the crash values if <id> didn't be initialized
    {
        std::cout << "We can't find your id.\n";
    }
    else
    {
        std::cout << "Your id is: " << *id << '\n';
    }
}

void showID_O(std::optional<int> id = std::nullopt) // (RECOMMENDED when the argument is good for passing by value)
{
    if(id)
        std::cout << "Your id is " << *id << '\n';
    else
        std::cout << "Sorry, we can't find your ID.\n";
}

// pass by adress by reference
void nullify(int*& ptr) // the reference of a pointer (pointer's aliases)
{
    ptr = nullptr; // make the parameter pointer point at nothing
    // because we use the reference, so we can change the argument(original pointer) here,
    // which can't be done with (only)passing by adress (you just change the parameters of the function, instead of argument)
}

const std::string& returnbyRef()
{
    static const std::string sayHi{"Hi"}; // the object who needs be returned must exist after the fuction returns
    return sayHi;
}

int& five()
{
    static int here{5};
    std::cout << "Here is " << here << '\n';
    return here;
}

void getSinCos(double degress, double& sinO, double& cosO)
{
    constexpr double pi{3.14159265358979323846};
    double radians = degress * pi / 180.0; // degress is an In-Parameter
    sinO = std::sin(radians); // sinO is an Out-Parameter
    cosO = std::cos(radians);
}

std::string *getPtr() { static std::string cowsay{"cow"}; return &cowsay;}

// global variable
namespace constants 
{
    constexpr int great{6};
} // namespace constants

// std::optional function
template<typename T>
std::optional<T> doDivision(T x, T y) // return a ptr (valiad (works fine) or nullptr (Failed))
{
    if(y==0)
        return {}; // or {std::nullopt}, which means <nothing>
    else
        return x / y;
}

struct Employee
{
    std::string name{};
    int id{};
};

void printEmployeeid()
{
    std::cout << "Who?\n";
}
void printEmployeeid(const Employee& ep)
{
    std::cout << "Hello " << ep.name << ", Your ID is " << ep.id << '\nThanks for Your Contribution!\n';
}



int main()
{

    int x{7};
    int *ptr{&x};
    double y{5.2};
    [[maybe_unused]] double *ptr_d{&y};

    std::cout << "Adress: " << ptr << '\n';
    std::cout << x << " is " << *ptr << '\n';
    std::cout << typeid(&y).name() << '\n';

    std::cout << "ptr's size: "<<sizeof(ptr)<<'\n'; // 64-bit -> 8 Bytes (based on the program)
    std::cout << "*(ptr)'s size: "<<sizeof(*ptr)<<'\n'; // *ptr -> int -> 4 Bytes

    // int *ptr_n{nullptr};
    // std::cout << *ptr_n; // make the program crash (Dereference a nullptr)

    std::string hello{"Hello, World!"};

    // (RECOMMENDED) pass by reference
    sayHelloR(hello); // pass by reference, the syntax for passing is natural
    sayHelloR("hello,world"); // and it can accept rvalues and lvalues
    
    // pass by adress when you must (you must be careful to deal with dangling and nullptr)
    sayHello(&hello);
    std::string *ptr_s{&hello};
    std::string *ptr_none{nullptr};
    sayHello(ptr_s);
    sayHello(ptr_none);
    // common uses for pass by adress 
    // (optional argument)
    showID();
    showID(ptr); // in parameter
    // std::optional as optional parameter
    showID_O();
    int user_id{34};
    showID_O(user_id);
    showID_O(42);
    // ....

    // changing what the pointer parameter points at
    std::cout << "ptr is a " << (ptr ? "non-nullptr" : "nullptr") << '\n';
    nullify(ptr); // out parameter
    std::cout << "ptr is a " << (ptr ? "non-nullptr" : "nullptr") << '\n';

    // return by const-reference
    std::cout << returnbyRef() << '\n';
    five();
    five() = 8;
    five();
    // Out-Parameter (return the information back to the caller)
    double degrees{60.0};
    double sin{}; // this
    double cos{}; // and this
    getSinCos(degrees, sin, cos);// parameter (sin,cos) are out-parameters
    std::cout << "Sin(" << degrees << ")=" << sin << " and Cos(" << degrees << ")=" << cos << '\n';

    constexpr const int &again{constants::great};
    std::cout << "How are you? I'm " << again << '\n';

    // auto(ptr) and auto*
    [[maybe_unused]] const auto ptr1{getPtr()};
    [[maybe_unused]] auto const ptr2{getPtr()};
    // the methods above are same, const for ptr not type
    /************************************/
    [[maybe_unused]] auto *const ptr3{getPtr()}; // const for ptr <const xx>
    [[maybe_unused]] const auto *ptr4{getPtr()}; // const for type

    // std::optional (deal with function's return error)
    const std::optional<int> result{doDivision(20, 5)};
    if(result) // one bool indicate whether the function works fine (a valiad ptr or a nullptr)
        std::cout << "Result 1: " << *result << '\n'; // the return value saved in the adress within the ptr
    else
        std::cout << "Result 1: Failed!\n";
    const std::optional<double> result2{doDivision(3.6, 1.1)};
    if(result2)
        std::cout << "Result 2: " << *result2 << '\n';
    else
        std::cout << "Result 2: Failed!\n";
    const std::optional<int> result3{doDivision(5, 0)};
    if(result3)
        std::cout << "Result 3: " << *result3 << '\n';
    else
        std::cout << "Result 3: Failed!\n";

    std::optional<int> o1{5};
    std::optional<int> o2{};
    std::optional<int> o3{std::nullopt};
    // boundary
    if(o1.has_value()) // get bool (explict)
        std::cout<<"o1 has value.\n";
    if(o2)
        std::cout<<"o2 has value.\n";
    if(o3)
        std::cout<<"o3 has value.\n";

    std::cout << *o1 << '\n'; // dangerous, o1 maybe null
    //std::cout << o2.value() << '\n'; // get value stored in o2, throws exception if o2 doesn't have a value
    std::cout << o3.value_or(50) << '\n'; // if o3 doesn't have a value, overwrite it with a specific value

    return 0;

}
