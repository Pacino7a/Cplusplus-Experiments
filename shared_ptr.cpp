#include <iostream>
#include <memory>

class Resource
{
public:
    Resource() { std::cout << "Resource accqired here.\n"; } 
    ~Resource() { std::cout << "Resource destoried here.\n"; }
};

int main()
{
    // auto res{new Resource{}};
    // std::shared_ptr<Resource> ptr1{new Resource{}};
    // std::shared_ptr<Resource> ptr1{res};
    auto ptr1{std::make_shared<Resource>()}; // Perfer 
    {
        std::shared_ptr<Resource> ptr2{ptr1}; // copy semantic
        // std::shared_ptr<Resource> bad{res};               // create shared_ptr directly from `res` (this doesn't know the existence of ptr1)
        std::cout << "Shared Ptr goes to An End here.\n"; // NO resource destruction here (`bad` will destory itself with its resource here)
    }
    std::cout << "Program Ends, all the shared ptr are distoried here.\n";

    // get the raw pointer
    [[maybe_unused]] auto ptr{ptr1.get()}; // usage is consistent with unique_ptr
    // get the content(ref) it holds
    [[maybe_unused]] auto content{*ptr};

    if(ptr1)
        std::cout << "Output the Resource the Ptr holds.\n";
    else
        std::cout << "The ptr is null.\n";
    
    return 0;

}
