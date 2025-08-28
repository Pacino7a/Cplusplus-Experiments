// focus on std::vector (array)
#include <iostream>
#include <vector>
#include <cassert>

// P.S.
// CTAD (Class Template Argument Deduction)

struct Foo
{
    // no CTAD here
    std::vector<int> v{1, 2, 3, 4};
    // std::vector<int> v0(8); Directly initialization is not allowed within a class type, so that we can't create a vector with 8 elements directly,
    std::vector<int> v1{std::vector<int>(8)}; // create a std::vector with a <capacity> of 8 (COPY ONLY for a member of class type)
};

template<typename T>
void sumAndProduct(std::vector<T>& vector) // in order to pass a vector, we need explicitly specify the type <T> here
{
    using size_type = std::vector<T>::size_type; // alias for the type used for the length (and indices, if supported) of the container.
    // In the most of time, T::size_type == std::size
    size_type length{vector.size()};
    T sum{};
    T product{1};
    std::cout << "You need input " << length << " numbers.\n";
    for (size_type i{0}; i < length; ++i) // index can't be signed int (aka. int), which will lead narrowing conversion
    {
        // std::cin >> vector[i];
        if(i == 0)
        {
            std::cout << "Please enter the first element: ";
            std::cin >> vector[i];
        }
        else
        {
            std::cout << "Please enter the next: ";
            std::cin >> vector[i];
        }
        sum += vector[i];
        product *= vector[i];
    }
    std::cout << "The sum is: " << sum << '\n'
              << "The product is: " << product << '\n';
}

// there are few shortages of unsigned-int index, such as Logic error due to underflow(-1->MAX), Implicit Type Conversion and inconsistency of the type between value and algorithm
template <typename T>
void printElement(const T& arr,const int index)
{
    // we use signed int to Safe handling of boundary conditions
    // assert(index >= 0 && index < std::ssize(arr)); // runtime assert and (debug only)
    if(index >= 0 and index < std::ssize(arr)) // ssize() accept signed int
        std::cout << "The element has value " << arr.data()[index] << '\n'; // data()[] accept int too
    else
        std::cout << "Invalid Index.\n";
}

std::vector<int> vec_generator_copy() // copy elision or copy semantics
{
    std::vector<int> arr1{1, 2, 3, 4, 5};
    return arr1; //if this is a rvalue (temporary obj) and the returned type support move semantics,
    // then the returned value can be moved instead of copied into the destination obj
}

std::vector<int> vec_generator_move() // move semantics
{
    return {1, 2, 3, 4, 5}; //this is a rvalue (temporary obj) and the returned type support move semantics,
    // so the data will move into the destination obj
    
}

struct Employee
{
    std::string name{};
    int id{};
    double salary{};
};

int main()
{
    std::vector<int> empty{};
    std::vector<int> primes{2, 3, 5, 7}; // specify the type
    std::vector vowel{'a', 'e', 'i', 'o', 'u'}; // deduce the type (perfered)
    std::cout << "hell" << vowel[3] << "!\n"; // use `[]`(subscript operator) to access array elements (by ref)
    // an index is the offset from the first element of that array (actually) (adress of the first)
    std::vector<int> v9(9); // create an array with 9 elements (zero initialization)
    std::vector<int> v9_1{9}; // create an array that has only 1 element `9`
    std::cout << "v9:" << v9.size() << '\n';
    std::cout << "v9_1:" << v9_1.size() << '\n';
    std::vector<double> temperature(365);

    // std::vector<double> sum_prdt(5);
    // sumAndProduct(sum_prdt);

    constexpr int s{1};                 // both length of vector and index are uint
    [[maybe_unused]] unsigned int u{s}; // constexpr int -> uint (safe), int <-- uint (unsafe)

    std::vector<double>::size_type first{0}; // Type of indices and return value (length of array) from size()
    std::size_t second{1}; // perfered
    std::vector<double> arr_d{1.2, 3.3};
    std::cout << "Arrayd size:" << arr_d.size() << '\n' // member function
              << "First:" << arr_d.at(first) << '\n'
              << "Second:" << arr_d.at(second) << '\n';

    std::vector arr1{'h', 'e', 'l', 'l', 'o'};
    std::cout << "Array1 size:" << std::ssize(arr1) << '\n' // non-member function (perfered)
              << "1:" << arr1[1] << '\n' // same with constexpr int {1}
              << "at(1):" << arr1.at(second) << '\n';

    std::vector v1{0, 1, 2, 3, 4};
    printElement(v1, 2);
    printElement(v1, 5);

    std::vector v2{1.1, 2.2, 3.3};
    printElement(v2, 0);
    printElement(v2, -1);

    auto v_g{vec_generator_copy()}; // make a potentially expensive copy (arr1 destroied)
    v_g[0] = 2;
    std::cout << "vector_generated: ";
    for (size_t i = 0; i < std::size(v_g); ++i)
    {
        std::cout << v_g[i] << '\t';
    }
    std::cout << '\n';

    std::vector employeeManagement{Employee{"John", 1, 5212.23}, {"Kate", 2, 6736.41}, {"Joe", 3, 8862.3}};

    return 0;
}
