// Introdution to unique(smart) ptr and move semantics
// the base of smart-ptr, NOT the real one
#include <iostream>
#include <memory>
#include <utility>

template <typename T>
class Auto_PtrII
{
    T *m_ptr{};
public:
    Auto_PtrII(T *ptr = nullptr)
    :   m_ptr{ptr}
    {}

    ~Auto_PtrII()
    {
        delete m_ptr;
    }

    // we use the below
    Auto_PtrII(Auto_PtrII& a_ptr) // no const here
    {
        // transfer the management of the adress from the existed one to our new one
        m_ptr = a_ptr.m_ptr;
        a_ptr.m_ptr = nullptr;
    }

    Auto_PtrII& operator=(Auto_PtrII& a_ptr) // no const here too
    {
        if(&a_ptr == this) // check whether the assignment is a self-copy (if so, they will have the same adress)
            return *this;

        delete m_ptr; // before the transfer we need uninstall the resource
        m_ptr = a_ptr.m_ptr;
        a_ptr.m_ptr = nullptr;
        return *this;
    }

    T &operator*() const { return *m_ptr; } // return the content the ptr holds
    T *operator->() const { return m_ptr; } // return the ptr itself for choosing the members
    bool isNull() const { return m_ptr == nullptr; }


};

class Resource
{
public:
    Resource() { std::cout << "Resource accquired!\n"; }
    ~Resource(){std::cout << "Resource destoried!\n"; }
};

template <typename T>
class Auto_PtrIII
{
    T *m_ptr{};
public:
    Auto_PtrIII(T *ptr = nullptr)
    :   m_ptr{ptr}
    {}

    ~Auto_PtrIII()
    {
        delete m_ptr;
    }

    // we use the below
    Auto_PtrIII(const Auto_PtrIII& a_ptr) // do deep copy here
    {
        // transfer the management of the adress from the existed one to our new one
        m_ptr = new T; // allocate the mem
        *m_ptr = *a_ptr.m_ptr; // assignment
    }

    Auto_PtrIII(Auto_PtrIII&& a_ptr) noexcept // we use T&& to distinguish Lvalue and Rvalue
        :   m_ptr{a_ptr.m_ptr}
    {
        // we need make the rvalue to a nullptr to avoid our new Ptr being dangling
        a_ptr.m_ptr = nullptr; // because we just move a rvalue to our obj, so we don't need the rvalue anymore
    }                          // aka. we just simply get(steal) its content and set it a nullptr
                               // On the other hand, we can't delete the rvalue although we don't use it anymore,
                               // the content that we just took over will be dangling if we delete the rvalue.

    Auto_PtrIII& operator=(const Auto_PtrIII& a_ptr)
    {
        if(&a_ptr == this) // check whether the assignment is a self-copy (if so, they will have the same adress)
            return *this;

        delete m_ptr; // before the transfer we need uninstall the resource
        m_ptr = new T;
        *m_ptr = *a_ptr.m_ptr; // we just copy the value and we can't set the lvalue a nullptr

        return *this;
    }

    Auto_PtrIII& operator=(Auto_PtrIII&& a_ptr) noexcept
    {
        if(&a_ptr == this)
            return *this;

        delete m_ptr;

        m_ptr = a_ptr.m_ptr;
        a_ptr.m_ptr = nullptr; // same reason as above (we still need the content but we don't want the original one controls it)
        return *this;
    }

    T &operator*() const { return *m_ptr; } // return the content the ptr holds
    T *operator->() const { return m_ptr; } // return the ptr itself for choosing the members
    bool isNull() const { return m_ptr == nullptr; }

};

int main()
{
    Auto_PtrII ap1{new Resource}; // 0
    Auto_PtrII ap2{ap1}; // 1 (copy constructor)
    Auto_PtrII<Resource> ap3; // 0

    std::cout << "ap1 is " << (ap1.isNull() ? "null\n" : "not null\n");
	std::cout << "ap2 is " << (ap2.isNull() ? "null\n" : "not null\n");
	std::cout << "ap3 is " << (ap3.isNull() ? "null\n" : "not null\n");
    std::cout << "***********************************\n";

    ap3 = ap2; // overload the assignment

    // if you dereferencing a nullptr here, your program probably will crash <still dangerous>
    std::cout << "ap1 is " << (ap1.isNull() ? "null\n" : "not null\n");
	std::cout << "ap2 is " << (ap2.isNull() ? "null\n" : "not null\n");
	std::cout << "ap3 is " << (ap3.isNull() ? "null\n" : "not null\n");

    // unique_ptr
    std::unique_ptr<Resource> res1{new Resource{}};
    std::unique_ptr<Resource> res2{};

    std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
	std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");

    res2 = std::move(res1); // copy assignment has been `deleted`, we can only use move semantic (key of unique_ptr)

    auto content{*res2}; // get the reference of the resource it holds
    auto ori_ptr{res2.get()}; // get the original ptr of the resource it holds

    std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
	std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");

    return 0;
}
