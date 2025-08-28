#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <string>
#include <string_view>
#include <vector>
#include <list>
#include <exception>
#include <memory>


// Database Graphs:
// Neo4j, ArangoDB, Apache Giraph
constexpr std::string strToLower(std::string_view str)
{
    std::string lower{};
    std::transform(str.begin(), str.end(), std::back_inserter(lower), 
                    [](char c)
                   { 
                        return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                    });
    return lower;
}

// Graph = Vertex(self) + Edges (Bidirectional Graph)
class Person // Vertex
{
private:
    std::string m_name{};
    std::list<std::reference_wrapper<Person>> m_friends{}; // we use list instead of a vector here (Edges)
    bool m_visit{false};
    const std::list<std::reference_wrapper<Person>> &getFriends() const { return m_friends; }
    void resetVisit() { m_visit = false; }
    void setVisit() { m_visit = true; }
    bool hasFriend() const { return !m_friends.empty(); }
    void displayNetwork_DFSHelper(Person& person, std::vector<std::reference_wrapper<Person>>& visited);
public:
    explicit Person(const std::string& name)
        :   m_name{name}
    {}

    void addFriend(Person &person) { m_friends.emplace_back(std::ref(person)); }
    void addFriends(std::initializer_list<std::reference_wrapper<Person>> list)
    {
        m_friends.insert(m_friends.end(), list.begin(), list.end());
    }
    std::string_view getMe() const { return m_name; }
    void displayNetwork();
    void displayNetwork_DFS();

    void distanceTo(const Person &target);
    std::vector<Person*> mutualFriends(const Person &other);
    std::vector<Person*> recommendFriends();

    std::list<std::reference_wrapper<Person>>& getFriends() { return m_friends; }
    bool operator==(const Person &other) { return strToLower(m_name) == strToLower(other.m_name); }
    friend std::ostream &operator<<(std::ostream &out, const Person &p);
};

std::ostream &operator<<(std::ostream &out, const Person &p)
{
    out << p.getMe() << " with Friend[ ";
    for(const auto friend_:p.getFriends())
        out << friend_.get().getMe() << ' ';
    return out << "]";
}

void Person::distanceTo(const Person& target)
{
    std::vector<std::reference_wrapper<Person>> toReset{};
    std::list<std::reference_wrapper<Person>> queue{(*this)};
    this->setVisit();
    for (int level{}, buffer{}, count{}; !queue.empty();)
    {
        // Based on the BFS
        auto current_vertex{queue.front()};
        queue.pop_front();
        toReset.emplace_back(current_vertex);
        if(buffer) --buffer; // if current level has not searched over yet, we just keep count
        if(current_vertex.get() == target) // if we find the target, print the level
        {
            std::cout << "The distance from " << this->getMe() << " to " << current_vertex.get().getMe() << " is " << level << ".\n";
            break;
        }

        for(auto friend_:current_vertex.get().getFriends())
        {
            if(!friend_.get().m_visit)
            {
                friend_.get().setVisit();
                queue.emplace_back(friend_);
                ++count; // count friends of current level (people in the next level)
            }
        }
        if (!buffer) // if we have searched over in this level (buffer == 0)
        {
            buffer = count; // get the number of people in the next level
            count = 0; // and clear it for next counting
            ++level; // most important, level(distance) goes up
        }
    }
    for(auto person2reset:toReset)
        person2reset.get().resetVisit();
}

std::vector<Person*> Person::mutualFriends(const Person& other)
{
    std::unordered_set<Person*> myFriendsSet; // hash-set boost the speed of finding here
    std::vector<Person*> mutual;

    for (const auto& f : this->getFriends()) // get myFriends
        myFriendsSet.insert(&f.get());

    for (const auto &f : other.getFriends()) // get others' friends
    {
        if (myFriendsSet.count(&f.get())) // if we have common friends
            mutual.emplace_back(&f.get()); // add them to the vector
    }

    return mutual;
}

// find friends's friend (level 2)
std::vector<Person *> Person::recommendFriends()
{
    std::vector<std::reference_wrapper<Person>> toReset{};
    std::list<std::reference_wrapper<Person>> queue{(*this)};
    std::vector<Person *> recommend{};
    this->setVisit();
    for (int level{}, buffer{}, count{}; level < 3 && !queue.empty();)
    {
        // the Person who call this function is on the level 0 (Only)
        // his friend is on the level 1
        // so we only need to find the people in the level 2 (friends' friend) at level 1 for recommendation

        // Based on the BFS
        auto current_vertex{queue.front()};
        queue.pop_front();
        toReset.emplace_back(current_vertex);
        if(level == 2)
            recommend.emplace_back(&current_vertex.get());
        if(buffer) --buffer; // if current level has not searched over yet, we just keep count

        for(auto friend_:current_vertex.get().getFriends())// find friends in the next level
        {
            if(!friend_.get().m_visit)
            {
                friend_.get().setVisit();
                queue.emplace_back(friend_);
                ++count; // count firends of his (who is in the next level)
            }
        }
        if (!buffer) // if we have searched over in this level (buffer == 0)
        {
            buffer = count; // get the number of people in the next level
            count = 0; // and clear it for next counting
            ++level; // most important, level(distance) goes up
        }
    }

    for(auto person2reset:toReset)
        person2reset.get().resetVisit();

    return recommend;
}

// Breadth First Search (BFS)->O(V(ertice)+2E(dges)) == O(V+E)
void Person::displayNetwork() // This method is based on a queue(list) who has the feature FIFO and a vertex(first element of the queue that popped front)
{
                                                           // we use this to save the visited people
    std::vector<std::reference_wrapper<Person>> toReset{}; // after our search over, we need restore the status of each Person, in case of interupting the result of next operation
    std::list<std::reference_wrapper<Person>> queue{(*this)}; // Core of this algmyFriendsthm,   <-A-[-, B C D E, F G, H I <-]-J-
    this->setVisit();
    for (;!queue.empty();)
    {
        auto current_vertex{queue.front()}; // pop the first element of the queue for current vertex and get its friends to the queue
        queue.pop_front();
        toReset.emplace_back(current_vertex);
        std::cout << current_vertex.get().getMe() << ' ';

        for(auto friend_:current_vertex.get().getFriends())
        {
            if(!friend_.get().m_visit)
            {
                friend_.get().setVisit(); // after we visited somebody(pushed to the queue), we set it as Visited to avoid infinite loop(A push B, B push A)
                queue.emplace_back(friend_);
            }
        }
    }
    for(auto person2reset:toReset) // After we done, restore the status
        person2reset.get().resetVisit();
}

void Person::displayNetwork_DFS()
{
    std::vector<std::reference_wrapper<Person>> visited{};
    displayNetwork_DFSHelper(*this, visited); // delegate the other one to do so for keeping the interface simple

    for (auto& p : visited) // restore status
        p.get().resetVisit();
}

// Deep First Search (DFS), traversal all the people who have relationship(friend's friend's  counts) with given person
void Person::displayNetwork_DFSHelper(Person& person, std::vector<std::reference_wrapper<Person>>& visited)
{
    // we passed each edge twice (go there and returns)
    if(person.m_visit) // Ignore the person who we visited before
        return;

    // otherwise, we print his name
    std::cout << person.getMe() << ' ';
    person.setVisit(); // mark him as a visited person
    visited.emplace_back(person); // and save it for reset

    // then go deeper, find all his friends to do the same thing
    for(auto friend_:person.getFriends())
    {
        displayNetwork_DFSHelper(friend_.get(), visited);
    }

}


// Weighted Graph
class City
{
private:
    std::string m_name{};

public:
    explicit City()
        : m_name{"NULL"}
    {}

    explicit City(const std::string& name)
        : m_name{name}
    {}

    std::string getName() const { return m_name; }
    bool operator==(const City& other) const { return m_name == other.m_name; } // <<<---- for hash
    bool isNull() const { return m_name == "NULL"; }
};

namespace std
{
    template<>
    struct hash<City> // <<<----- for hash
    {
        std::size_t operator()(const City& city) const noexcept
        {
            return std::hash<std::string>{}(city.getName());
        }
    };

}

class Graph
{
private:
    // 城市名字 -> City对象 (string->City) - Manage the nodes
    std::unordered_map<std::string, std::unique_ptr<City>> m_cities{};  // manage cities(Vertice) in the graph
    // 城市 -> 邻居城市和价格 (City -> [otherCity, Price]) - Manage the routes
    std::unordered_map<City*, std::vector<std::pair<City*, int>>> m_edges{}; // manage routes(Edges) between 2 cities(Vertice)
    
    std::unordered_map<City*, std::unordered_map<City*, int>> getCheapestRouteHelper(const std::string &startCity);
public:

    City* addCity(const std::string& name)
    {
        auto city = std::make_unique<City>(name);
        City* cityPtr = city.get();
        m_cities[name] = std::move(city);
        return cityPtr;
    }


    void addRoute(City* from, City* to, int price)
    {
        m_edges[from].emplace_back(to, price);
    }

    std::unordered_map<City *, std::unordered_map<City *, int>> getCheapestRouteFrom(const City* startCity)
    {
       return getCheapestRouteHelper(startCity->getName());
    }

};

bool isVisit(const std::vector<City*>& vector, const City* value)
{
    for(const auto& ele:vector)
    {
        if(ele == value)
            return true;
    }
    return false;
}

// Dijkstra (can solve the minimum problem ---> minimum path), I
std::unordered_map<City *, std::unordered_map<City *, int>> Graph::getCheapestRouteHelper(const std::string &startCity)
{
    std::unordered_map<City*, std::unordered_map<City*, int>> routesToCity; // RECODER (2 vertice and 1 edge with direction)
    // routesToCity{{ destination, [from_where, cheapest_price_of_this_route] }, ...} 

    // if you want to travel to the city where you are, it's free
    routesToCity.emplace(m_cities[startCity].get(), std::unordered_map<City*, int>{{m_cities[startCity].get(), 0}});
    // otherwise, we write down all the other dest in the table
    for(const auto& [cityname,cityPtr]:m_cities)
    {
        if(cityname != startCity) // AT FIRST we don't know the lowest price and from where to reach here
            routesToCity.emplace(cityPtr.get(), std::unordered_map<City*, int>{{nullptr, std::numeric_limits<int>::max()}}); 
    }

    std::vector<City*> visited{}; // mark the cities that we have visited

    City* current_city{m_cities[startCity].get()}; // set current vertex
    for (;current_city;)
    {
        visited.emplace_back(current_city); // mark it

        for(const auto& route:m_edges[current_city]) // extract each route start from current city
        {
            auto [dest, cur2destPrice] = route; // extract the dest

            // first Half (Looking up the record, How much to get current city in the cheapest price?)
            auto& innerMapVertex = routesToCity[current_city]; // extract how much we need (cheapest) to reach this vertex from the Beginning Vertex
            int toCurrent; // this the price from beginning to current vertex
            for(auto&[vertex, basicPrice]:innerMapVertex) // once
            {
                toCurrent = basicPrice; // but this must be the cheapest way to get current position
            }
            // second Half 
            auto& innerMap = routesToCity[dest]; // extract how much we need (cheapest) to get this destination so far from the record
            int cheapestPrice;// (currentCity) --> destination (CHEAPEST) (IN THE RECORD)
            for(auto&[record_from, priceToHere]:innerMap) // once
            {
                cheapestPrice = priceToHere;
            }

            // { Base(beginning City) -cheapest-> ""Current Vertex (current City)"" --(cheapest?)--> Destination Vertex (RECORD THE CURRENT CITY if it's cheapest) }
            // toCurrent == from the BEGINING vertex to this Vertex's cheapest price
            // cur2destPrice == Vertex to the Destination's price
            // cheapestPrice that was recorded in the hash-table should be the cheapest price FROM the BEGINING to CURRENT DESTINATION

            if(cheapestPrice > toCurrent + cur2destPrice) // if current route to the dest is cheaper than the record, override it
            {
                routesToCity[dest] = {{current_city, (toCurrent + cur2destPrice)}};// replace the cheapest price and use current vertex to override the cheapest Origin
            }// replace recorder~^~~, investigating~^~, ~^from the recorder, ^~ from the Native Data in investigating
        }
        current_city = nullptr;
        int nextCheapest{std::numeric_limits<int>::max()};
        for(const auto& [dest,route]:routesToCity) // read current record
        {
            for(const auto& [from, price]:route)// find the lowest first half that we have investigated (next beginning)
            {
                if(nextCheapest > price && !isVisit(visited, dest)) // find the next(nearest/Cheapest) vertex(dest) that has not been visited
                {
                    current_city = dest;  // `dest` is the possible next vertex(BFS like), NOT `from`
                    nextCheapest = price; // only the vertex who has been reached has a price(lowest so far)
                }
            }
        }
    }
    return routesToCity;
}

int main()
{
    // we use a hash-table to achieve the graphy of relationship here
    std::unordered_map<std::string, std::vector<std::string>> relationship{
        {"Alice", {"Bob", "Diana", "Fred"}},
        {"Bob", {"Alice", "Cynthia", "Diana"}},
        {"Cynthina", {"Bob"}},
        {"Diana", {"Alice", "Bob", "Fred"}},
        {"Elise", {"Fred"}},
        {"Fred", {"Alice", "Diana", "Elise"}}
    };
    // we can also create a Unidirectional Graph by hash-table

    auto friends{relationship["Alice"]};
    std::cout << "Alice's friend: ";
    for(std::string_view friend_:friends)
        std::cout << friend_ << " ";
    std::cout<<'\n';

    // another way is making a class for achieving the Graph (Bidirectional Graph)
    Person Alice{"Alice"};
    Person Bob{"Bob"};
    Person Candy{"Candy"};
    Person Derek{"Derek"};
    Person Elaine{"Elaine"};
    Person Fred{"Fred"};
    Person Gina{"Gina"};
    Person Helen{"Helen"};
    Person Irena{"Irena"};

    Alice.addFriends({Bob, Candy, Derek, Elaine});
    Bob.addFriends({Alice, Fred});
    Candy.addFriend(Alice);
    Derek.addFriends({Alice, Gina});
    Elaine.addFriend(Alice);
    Fred.addFriends({Bob, Helen});
    Gina.addFriends({Derek, Irena});
    Helen.addFriend(Fred);
    Irena.addFriend(Gina);

    std::cout << Alice << '\n';
    std::cout << Irena << '\n';

    Alice.displayNetwork();
    std::cout << '\n';
    Alice.displayNetwork_DFS();
    std::cout << '\n';
    Alice.distanceTo(Helen);

    auto mutualFriends{Bob.mutualFriends(Candy)};
    std::cout << "Mutual Friends between Bob and Candy: ";
    for (const auto friend_:mutualFriends)
        std::cout << friend_->getMe() << ' ';
    std::cout << '\n';

    auto alice_rec{Alice.recommendFriends()};
    std::cout << "Alice's Recommendation: ";
    for(const auto friend_:alice_rec)
        std::cout << friend_->getMe() << " ";
    std::cout << '\n';

    /*Do not manage the relationship in one class!*/
    // City denver{"Denver"};
    // City elPaso{"El Paso"};
    // City chicago{"Chicago"};
    // City boston{"Boston"};
    // City atlanta{"Atlanta"};

    Graph cityGraph; // City is managed by Graph
    City* denver{cityGraph.addCity("Denver")};
    City* elPaso{cityGraph.addCity("El Paso")};
    City* chicago{cityGraph.addCity("Chicago")};
    City* boston{cityGraph.addCity("Boston")};
    City* atlanta{cityGraph.addCity("Atlanta")};

    // if we set both the same price, this will be a Weighted Bidirectional Graph
    // otherwise, Weighted Unidirectional graphs (has direction)
    cityGraph.addRoute(denver, chicago, 40);
    cityGraph.addRoute(denver, elPaso, 140);
    cityGraph.addRoute(elPaso,boston,100);
    cityGraph.addRoute(chicago, elPaso, 80);
    cityGraph.addRoute(boston, chicago, 120);
    cityGraph.addRoute(boston, denver, 180);
    cityGraph.addRoute(atlanta, boston, 100);
    cityGraph.addRoute(atlanta, denver, 160);

    // what's the cheapest route form A to B?
    // Minimum Path algo (Dijkstra)
    auto startCity{boston};
    auto cheapestRoutes{cityGraph.getCheapestRouteFrom(startCity)};
    for(const auto& [dest, formWhereAndPrice]:cheapestRoutes)
    {
        
        for(const auto& [form, cheapestPrice]:formWhereAndPrice)
        {
            if(cheapestPrice != std::numeric_limits<int>::max())
                std::cout << "The cheapest route From " << startCity->getName() << " to " << dest->getName() << " costs $" << cheapestPrice << '\n';
            else
                std::cout << "The route From " << startCity->getName() << " to " << dest->getName() << " is NOT available for now.\n";
        }
    }
    return 0;
}
