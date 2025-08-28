#include <iostream>
#include <memory> // for std::shared_ptr

class Resource
{
public:
	// std::shared_ptr<Resource> m_ptr {}; // initially created empty
    std::weak_ptr<Resource> m_ptr{}; // observer (has no management)

    Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};

std::weak_ptr<Resource> getWeakPtr()
{
    auto ptr{std::make_shared<Resource>()};
    return ptr; // return a weak_ptr
}

Resource* getDumbPtr()
{
    auto ptr{std::make_unique<Resource>()};
    return ptr.get(); // return a raw dumb ptr
}

int main()
{
	auto ptr1 { std::make_shared<Resource>() };

    // weak_ptr is the follower of shared_ptr, it can't managed shared_ptr's resource but observing
    // the followed dies, weak dies
    // Otherwise, if you create a shared_ptr in a shared_ptr and they shared a SAME RESOURCE, it will cause ENDLESS SHARING LOOP
    // And makes memory Leaks
    ptr1->m_ptr = ptr1; // m_ptr is now sharing the Resource that contains it
                        // definitely will cause Leak if `m_ptr` is shared

    auto dumb{getDumbPtr()}; // The ptr is not a nullptr even it's dangling.
    std::cout << "Our dumb is " << ((dumb == nullptr) ? "nullptr\n" : "non-nullptr\n");
    auto weak{getWeakPtr()}; // 
    std::cout << "Our weak is " << ((weak.expired())  ? "nullptr\n" : "non-nullptr\n"); // Weak_Ptr can check the validity of the adress it holds

    // shared can not initialize with same adress
    // e.g.
    // Resource *res{new Resource{}};
    // std::shared_ptr<Resource> p_bad1{res};
    // std::shared_ptr<Resource> p_bad2{res};
    
    // NOTES HERE:
    // the statements above will cause your program crash
    // although both of them are `shared` but in actually they are individuals,
    // p_bad1's destruction will cause p_bad2 nothing to do when it wants to destory the Resource it controls
    // which will lead the crash.
    // Of course you shouldn't write these when you use unique_ptr
    // because it makes no any sense

    auto ptr_a{std::make_shared<Resource>()};
    auto ptr_b{ptr_a};
    return 0;
}
