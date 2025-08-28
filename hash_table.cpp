#include <iostream>
#include <unordered_map> // hash-table
// hash-table in C++ likes dictionary in Python
#include <unordered_set> // group of no repeating elements

// BOOST YOUR EFFICIENCY BY HASH
// hash-table can provide our an effective program
// thanks to its brilliant advantage in Reading and Instertion
int main()
{
    std::unordered_map<std::string, int> score; // table
    [[maybe_unused]] std::unordered_map<std::string, double> cities{{"Beijing", 852.3}, {"Shanghai", 757.8}, {"Guangzhou", 556.2}};
    // LIFO
    score["Alice"] = 90;
    score["Bob"] = 89;
    score["Carter"] = 80;
    score.emplace("David", 86); // good efficiency

    for(const auto&[candidate,value]:score)
        std::cout << candidate << " gets " << value << '\n';
    
    if(score.find("Bob") != score.end())
        std::cout << "Bob gets " << score["Bob"] << '\n'; // score.at("Bob")
    else
        std::cout << "Sorry, we didn't find that.\n";

    // Hash-Group
    std::unordered_set<int> s;

    s.insert(3);
    s.insert(5);
    s.insert(7);
    s.insert(3); // repeat element, no effect

    std::cout << "Hash Group Size: " << s.size() << '\n';
    for(auto num:s)
        std::cout << num << ' ';
    std::cout << '\n';

    // Vote system (hash-table) -> O(1) finding complexity
    std::unordered_map<std::string, int> votes;
    votes.reserve(20); // no more than 14 keys

    for (std::string candidate{};candidate != "q";)
    {
        std::cout << "Please enter the candidate's name who you want to vote for (Press `q` to Quit): ";
        std::getline(std::cin, candidate);
        if(candidate.size() < 2)
            break;
        if(votes[candidate])
            ++votes[candidate];
        else
            votes[candidate] = 1;
    }

    for(const auto& [candidate,vote]:votes) // extract every bucket in the hash table
        std::cout << candidate << ": " << vote << " Vote(s).\n";

    std::unordered_map<std::string, int> map{{"Beijing", 1}, {"Shanghai", 2}, {"Guangzhou", 3}, {"Shenzhen", 4}, {"Shanghai",6}};
    std::cout << map.count("Shanghai") << '\n';                                                                 // ~~~^~~ Invalid Insertion (Override)
    std::cout << std::boolalpha << map.contains("Guangzhou") << '\n';
    map.at("Beijing") = 10; // valid existed key's value's modification
    map.insert({"Shanghai", 8}); // invalid override(ignore)
    map.erase("Shanghai");
    map.insert({"Shanghai", 6}); // valid insert
    for(const auto& [city,num]:map)
        std::cout << city << ", " << num << '\n';

    return 0;
}
