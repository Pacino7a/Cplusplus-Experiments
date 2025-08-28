#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
        std::cout << "Size: " << vec.size() << ", Capacity: " << vec.capacity() << std::endl;
        // size following the number of vec elements but Capacity is the memory size that the compiler distributed for those elements,
        // Capacity >= size.
    }
    return 0;
}
