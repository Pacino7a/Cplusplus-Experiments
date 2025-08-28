#include <iostream>
#include <memory>
#include <utility>

struct List
{
    int value{};
    std::unique_ptr<List> next{};

    explicit List(int v, std::unique_ptr<List> n)
        :   value{v}
    {
        next = std::move(n);
    }
    explicit List(List&& other)
    {
        value = std::move(other.value);
        next  = std::move(other.next);
    }
};

using ListPtr = std::unique_ptr<List>;

void printList(const ListPtr& head)
{
    for(const List* current{head.get()}; current != nullptr;)
    {
        std::cout << current->value << ' ';
        current = current->next.get();
    }
    std::cout << '\n';
}

void reverseList(ListPtr &head) // there is a swap way to swap (n/2) times, just swap the content, exclude the next Pointer. (maybe need 2 pointers)
{
    std::unique_ptr<List> prev{nullptr}; // prev for replacing next
    for (ListPtr current{std::move(head)}, tempNext{}; current != nullptr;)
    {
        tempNext = std::move(current->next); // reverse the order (head becomes tail and tail becomes head)
        current->next = std::move(prev);     // KEY
        prev = std::move(current);      // current become the next in the next round
        current = std::move(tempNext);  // cursor goes to the next
    }
    head = std::move(prev);
}

int main()
{
    List head{1, std::make_unique<List>(2, std::make_unique<List>(3, std::make_unique<List>(4, std::make_unique<List>(5, nullptr))))};
    auto headPtr{std::make_unique<List>(std::move(head))};
    printList(headPtr);
    reverseList(headPtr);
    printList(headPtr);

    return 0;
}
