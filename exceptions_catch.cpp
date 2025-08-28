// #define NDEBUG
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstddef> // for std::size_t
#include <exception> // for std::exception
#include <limits>
#include <string> // for this example
#include <stdexcept>

void function1(int x)
{
    if(x < 0)
        throw -1;
    else
        std::cout << x << '\n';
}

class DummyException // An exception type that will never be hit (can't be instantiated)
{
    DummyException() = delete;
};

class ArrayExceptions
{
private:
    std::string m_error{};
public:
    explicit ArrayExceptions(std::string_view error)
        :   m_error{static_cast<std::string>(error)}
    {}

    std::string_view getError() const { return m_error; }
};

class ArrayExceptionsR: public std::runtime_error // we derived from the derived class of std::exception
{
public:
    explicit ArrayExceptionsR(const std::string& error)
        :   std::runtime_error{error}
    {}
    // No need for get() or what() anymore
};


class IntArray
{
private:
    int m_array[5]{};
    int m_length{};

public:
    IntArray() = default;

    explicit IntArray(std::initializer_list<int> list) // when exception takes place here, all the member variables which has been initialized will be distructed
        :   m_length{static_cast<int>(list.size())}    // the construction will be terminated, the members with RAII strategy will be fine.
    {
        if(list.size() > 5)
            throw ArrayExceptionsR{"Overwhelming allocation"}; // if we use const char* directly here to identify what caused the exceptions
        std::copy_n(list.begin(), list.size(), m_array);                    // we could only get ONE solution by catch(const char*)
    }                                                                          // which is Inflexible
    int& operator[](int index)
    {
        if(index < 0 || index >= m_length)
            throw ArrayExceptionsR{"Invalid index"};
        return m_array[index];
    }
};

class A
{
private:
	int m_x;
public:
	A(int x) : m_x{x}
	{
		if (x <= 0)
			throw 1; // Exception thrown here
	}
};

class B : public A
{
public:
	B(int x) try : A{x} // note addition of try keyword here
	{
	}
	catch (...) // note this is at same level of indentation as the function itself
	{
                // Exceptions from member initializer list or
                // from constructor body are caught here

        std::cerr << "Exception caught in class\n";

        throw; // rethrow the existing exception
	}
};

int main()
{
    // One
    try
    {
        function1(6);
    }
#ifdef NDEBUG // if we are in Release Mode, we need catch-all handler for Clean the program when the exception was not caught
    catch(...) // match every exception to handle it. aka Last line of defense
    {
        std::cerr << "Abnormal termination\n";
    }
#else // if we are debugging, we don't want the exception hit the catch and Make Clean to the program which will lose all the informations we need to solve the problem
    catch(DummyException) // a try requires at least a catch but we don't want this catch to match any exceptions, so we just make a mission impossible for matching
    {

    }
#endif
    // Two
    try
    {
        IntArray arr{1, 2, 3, 4, 5};
        int value{arr[4]};
        std::cout << "value: " << value << '\n';
    }
    catch(const ArrayExceptions& error) // all kinds of Error in class ArrayError can be handled here, instead of One solution matched with a string
    {
        std::cerr << "An array exception occured (" << error.getError() << ")\n";
    }
    // Three
    try
    {
        std::string s;
        s.resize(std::numeric_limits<std::size_t>::max()); // detect standard exceptions here
    }
        // One of std::exception's Derived class
    catch(const std::length_error& length_errpr) // take care std::lengtherror (one derived of standard exceptions) here
    {
        std::cerr << "You ran out of memory!" << '\n';
    }
        // the Deriveds can be taken over by the Base catch
    catch(const std::exception& e) // std::exception is a Base class (interface class), we will handle all the standard exceptions here if the exception didn't be take care berfore
    {
        std::cerr << "Standard exception: " << e.what() << '\n'; // what() is a virtual function
    }
    // Four
    try
	{
		throw std::runtime_error("Bad things happened"); // you can throw std::exception (Derived class, not itself) manually
	}
	// This handler will catch std::exception and all the derived exceptions too
	catch (const std::exception& exception)
	{
		std::cerr << "Standard exception: " << exception.what() << '\n';
	}
    // Five
    try
    {
        IntArray arr_1{1, 2, 3, 4, 5, 6};
    }
    catch (const ArrayExceptionsR& error)
    {
		std::cerr << error.what() << '\n'; // Inherited from runtime_error
    }
	catch (const std::exception& exception)
	{
		std::cerr << "Standard exception: " << exception.what() << '\n';
	}
    // Six
    try
	{
		B b{0};
	}
	catch (int)
	{
		std::cout << "Oops\n";
	}
    return 0;
}
