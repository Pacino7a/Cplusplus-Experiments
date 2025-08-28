#include <iostream>
#include <list>
#include <iomanip>
#include <string>
#include <cassert>
#include <initializer_list>
// Learning List in this section

struct Person
{
    std::string name{};
    int age{};
};

template <typename T>
class Enhanced_List
{
private:
    std::list<T> m_list{};
    std::size_t m_length{};

public:
    explicit Enhanced_List(std::initializer_list<T> list)
        :   m_length{list.size()}
    {
        m_list.insert(m_list.end(), list.begin(), list.end());
        // std::copy(list.begin(), list.end(), std::back_inserter(m_list));
    }
    T& operator[](int index) 
    {
        assert(static_cast<std::size_t>(index) < m_list.size());

        auto it{m_list.begin()};
        auto dest{m_list.begin()};
        std::advance(dest, index);
        for (; it != dest; ++it)
        {}
        return *it;
    }
    T operator[](int index) const
    {
        assert(static_cast<std::size_t>(index) < m_list.size());
        
        auto it{m_list.begin()};
        auto dest{m_list.begin()};
        std::advance(dest, index);
        for (; it != dest; ++it)
        {}
        return *it;
    }

    bool find(T value2find) const
    {
        for (auto it{m_list.begin()}; it != m_list.end(); ++it)
        {
            if(value2find == *it)
                return true;
        }
        return false;
    }

    T front() const { return m_list.front(); }
    T back() const { return m_list.back(); }

    void push_back(T value) { m_list.push_back(value); }
    void push_front(T value) { m_list.push_front(value); }
    void pop_back() { m_list.pop_back(); }
    void pop_front() { m_list.pop_front(); }
};

int main()
{
    // std::list<int> aa;
    std::list mylist{1, 2, 3, 4};

    mylist.push_back(10);
    mylist.push_front(0);

    for(auto num:mylist)
        std::cout << num << ' ';
    std::cout << '\n';

    auto its{mylist.begin()};
    std::advance(its, 1); //  move `it`(cursor) to the second place, same with <its = mylist.begin()+1>
    mylist.insert(its, 99); // insert a number at the second place, the cursor will advance 1 implicitly (at the third place)

    for (std::list<int>::iterator it{mylist.begin()}; it != mylist.end(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    // mylist.remove(99); // remove all elements equal to this value
    mylist.erase(--its); // more precise
    
    for(auto num:mylist)
        std::cout << num << ' ';
    std::cout << '\n';

    std::cout << "The List Size: " << mylist.size() << '\n'
              << std::boolalpha << "The List is Empty: " << mylist.empty() << '\n';

    mylist.clear();
    std::cout << "The List is Empty: " << mylist.empty() << '\n';

    std::list myMates{Person{"Alice", 22}, {"Bruce", 23}, {"Carter", 21}};

    myMates.push_back({"David", 20});
    myMates.emplace_back(Person{"Edward", 24});
    myMates.emplace_front(Person{"Administor", 0});

    for(const auto& mate:myMates) // travesal is not good enough for list
        std::cout << mate.name << ' ' << mate.age << '\n';

    // std::cout << myMates[1]; CAN'T BE INDEXED (aka. Random access is prohibited) (the pointer is hiding that can't be use directly)
    // LIST is GOOD at insert/erase element
    // Good at Implement queues, cache elimination strategies, etc.
    // Good at Stable-Sort

    // list.sort() is stable sort, which means sorting the list with the rule based on the original order
    // aka. it will not screw up the ori order.
    myMates.sort([](const Person &p1, const Person &p2)
                 { return p1.age < p2.age; });
    std::cout << "----------------STABLE_SORT---------------------\n";
    for(const auto& mate:myMates)
        std::cout << mate.name << ' ' << mate.age << '\n';

    Enhanced_List mylist_enhance{1, 2, 3};
    int index{2};
    int find{3};
    std::cout << "List [" << index << "]: " << mylist_enhance[index] << '\n';
    std::cout << std::boolalpha << "The List gets " << find << "? " << mylist_enhance.find(find) << '\n';
    std::cout << "Front: " << mylist_enhance.front() << ", Back: " << mylist_enhance.back() << '\n';
    return 0;
}
