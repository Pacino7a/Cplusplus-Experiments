#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <list>
#include <memory>
#include <utility>

class Node
{
public:
    explicit Node() = default;
    explicit Node(char key, int value)
        : m_key{key}, m_value{value}, m_visit{false}
    {}

    char getKey() const { return m_key; }
    int getValue() const { return m_value; }
    bool isVisit() const { return m_visit; }
    void setVisit() { m_visit = true; }
    void resetVisit() { m_visit = false; }
    void setLevel(int level) { m_level = level; }
    int getLevel() const { return m_level; }
    void setColor(bool color) { m_color = color; }
    bool getColor() const { return m_color; }

private:
    char m_key{};
    int m_value{};
    bool m_visit{};
    int m_level{};
    bool m_color{false};
};

struct NodeComparator 
{
    bool operator()(const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs) const
    {
        return lhs->getKey() < rhs->getKey();
    }
};

class GraphOfNodes
{
public:
    explicit GraphOfNodes(std::size_t vertice)
        : m_numOfVertice{vertice}
    {
        m_edges.resize(m_numOfVertice);
        for(auto& connection:m_edges)
            connection.reserve(m_numOfVertice - 1);
    }
    std::size_t getNumberofEdges() const { return m_numOfEdges; }
    std::size_t getNumberofVertice() const { return m_numOfVertice; }
    void addEdges(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2)
    {
        if(node1 == node2) // no self circle
            return;
        auto uid{getID(node1->getKey())}; // 1
        auto vid{getID(node2->getKey())}; // 2
        for(const auto& vertex:m_edges[uid]) // no Parallel Edges (std::unordered_map<key,std::unordered_set<std::shared<Node>> maybe better)
            if(vertex == node2) return;
        m_edges[uid].emplace_back(node2); // 1 -> 2
        m_edges[vid].emplace_back(node1); // 2 -> 1
        m_nodes.insert(node1);
        m_nodes.insert(node2);
        ++m_numOfEdges;
    }
    std::optional<int> id(char key) const
    {
        if(keyToID.contains(key))
            return keyToID.at(key);
        else
            return std::nullopt;
    }
    void searchFrom_DFS(std::shared_ptr<Node> node)
    {
        if(!keyToID.contains(node->getKey()))
        {
            std::cout << "This node is not existed in the network yet.\n";
            return;
        }
        std::vector<std::shared_ptr<Node>> visited{};
        deepFirstSearch(node, visited);
        for(auto& vertex:visited)
            vertex->resetVisit();
    }
    void searchFrom_BFS(std::shared_ptr<Node> node)
    {
        if(!keyToID.contains(node->getKey()))
        {
            std::cout << "This node is not existed in the network yet.\n";
            return;
        }
        std::vector<std::shared_ptr<Node>> visited{};
        breadthFirstSearch(node, visited);
        for(auto& vertex:visited)
            vertex->resetVisit();
    }
    void hasPath(std::shared_ptr<Node> from, std::shared_ptr<Node> to)
    {
        if(!keyToID.contains(to->getKey()) || !keyToID.contains(from->getKey()))
        {
            std::cout << "The node is not in the network yet.\n";
            return;
        }

        std::vector<std::shared_ptr<Node>> visited{};
        bool found{false};
        hasPathHelperDFS(from, to, visited, found);
        if(found)
        {
            for(auto& vertex:visited)
            {
                vertex->resetVisit();
                if(!(vertex == to))
                    std::cout << vertex->getKey() << '-';
                else
                {    std::cout << vertex->getKey();}
            }
            std::cout << '\n';
        }
        else
        {
            std::cout << "Sorry there is no path from " << from->getKey() << " to " << to->getKey() << '\n';
            for(auto& vertex:visited)
                vertex->resetVisit();
        }
    }
    void findShortestPath(std::shared_ptr<Node> from, std::shared_ptr<Node> to)
    {
        if(!keyToID.contains(to->getKey()) || !keyToID.contains(from->getKey()))
        {
            std::cout << "The node is not in the network yet.\n";
            return;
        }
        if(from == to)
        {
            std::cout << "You are looking for yourself right now.\n";
            return;
        }

        std::vector<std::shared_ptr<Node>> visited{};
        std::vector<std::shared_ptr<Node>> path{};

        bool found{false};
        findShortestPathHelper(from, to, path, visited, found);
        if(found)
        {
            for(auto& vertex:path)
            {
                if(!(vertex == to))
                    std::cout << vertex->getKey() << '-';
                else
                {    std::cout << vertex->getKey();}
            }
            std::cout << '\n';
        }
        else
        {
            std::cout << "Sorry there is no path from " << from->getKey() << " to " << to->getKey() << '\n';

        }
        for(auto& vertex:visited)
            vertex->resetVisit();
    }
    void getConnections()
    {
        std::vector<std::shared_ptr<Node>> visited{};
        std::vector<std::vector<char>> connections{};
        for(auto& vertex:m_nodes)
        {
            if(!vertex->isVisit())
            {
                std::vector<char> currentConnections{};
                connectionDFS(vertex, visited, currentConnections);
                connections.emplace_back(std::move(currentConnections));
            }
        }
        std::cout << "This network has " << connections.size() << " Components.\n";
        for(const auto& component:connections)
        {
            for(auto key:component)
                std::cout << key << ' ';
            std::cout << '\n';
        }
        for (auto &vertex : visited)
            vertex->resetVisit();
    }
    bool hasCircle()
    {
        std::vector<std::shared_ptr<Node>> visited{};
        bool result{false};
        for(auto vertex:m_nodes)
        {
            if(!vertex->isVisit())
                if(hasCircleHelper(vertex, vertex, visited)) // if a part of the graph is a circle, the whole graph is a circle
                {
                    result = true;
                    break;
                }
        }
        for (auto &vertex : visited)
            vertex->resetVisit();
        return result;
    }
    bool isCircle()
    {
        std::vector<std::shared_ptr<Node>> visited{};
        std::vector<std::size_t> degrees{};
        bool result{false};
        int count{0};
        for(auto vertex:m_nodes)
        {
            if(!vertex->isVisit())
            {
                if(count == 0)
                    result = isCircleHelper(vertex, vertex, visited, degrees);
                ++count;
            }
        }
        if(count > 1) // if the graph has many parts it's not a simple circle
            result = false;
        else // Otherwise(the network just has one component), we need check the inside. Make sure all vertice have 2 degrees
        {
            for(auto degree:degrees)
                if(degree != 2)
                {
                    result = false;
                    break;
                }
        }
        for (auto &vertex : visited)
            vertex->resetVisit();
        return result;
    }
    bool isBipartiteGraph()
    {
        std::vector<std::shared_ptr<Node>> visited{};
        bool result{false};
        bool color{false};
        for(auto vertex:m_nodes)
        {
            if(!vertex->isVisit())
            {
                result = isBipartiteGraphHelper(vertex, color, visited);
            }
            if(!result)
                break;
        }
        for (auto &vertex : visited)
            vertex->resetVisit();
        return result;
    }

private:
    // std::vector<std::unique_ptr<Node>> m_nodes{};
    // std::unordered_map<char, Node *> m_edges{};
    std::vector<std::vector<std::shared_ptr<Node>>> m_edges{};
    std::set<std::shared_ptr<Node>,NodeComparator> m_nodes{};
    std::size_t m_numOfVertice{};
    std::size_t m_numOfEdges{};
    std::unordered_map<char, std::size_t> keyToID{};
    std::unordered_map<std::size_t, char> idToKey{};
    std::size_t m_id{0};
    std::size_t getID(const char key)
    {
        if(!keyToID.contains(key))
        {
            keyToID.insert({key, m_id});
            idToKey.insert({m_id, key});
            ++m_id;
        }
        return keyToID.at(key);
    }
    void deepFirstSearch(std::shared_ptr<Node> node, std::vector<std::shared_ptr<Node>>& visited);
    void connectionDFS(std::shared_ptr<Node> vertex, std::vector<std::shared_ptr<Node>>& visited, std::vector<char>& currentConnections);
    void breadthFirstSearch(std::shared_ptr<Node> node, std::vector<std::shared_ptr<Node>>& visited);
    void hasPathHelperDFS(std::shared_ptr<Node> from, std::shared_ptr<Node> to, std::vector<std::shared_ptr<Node>> &visited, bool& found);
    void findShortestPathHelper(std::shared_ptr<Node> from, std::shared_ptr<Node> to, std::vector<std::shared_ptr<Node>> &path, std::vector<std::shared_ptr<Node>> &visited, bool& found);
    bool isCircleHelper(std::shared_ptr<Node> ori, std::shared_ptr<Node> from, std::vector<std::shared_ptr<Node>> &visited, std::vector<std::size_t>& degrees);
    bool hasCircleHelper(std::shared_ptr<Node> ori, std::shared_ptr<Node> from, std::vector<std::shared_ptr<Node>> &visited);
    bool isBipartiteGraphHelper(std::shared_ptr<Node> node, bool& color, std::vector<std::shared_ptr<Node>> &visited);
};

void GraphOfNodes::deepFirstSearch(std::shared_ptr<Node> node, std::vector<std::shared_ptr<Node>>& visited)
{
    auto currentID{keyToID.at(node->getKey())};
    node->setVisit();
    visited.emplace_back(node);
    std::cout << node->getKey() << ", " << node->getValue() << '\n';

    for(auto& vertex:m_edges[currentID])
    {
        if(!vertex->isVisit())
        {
            deepFirstSearch(vertex, visited); // push to call stack until no way to dive
        }

    }
}

void GraphOfNodes::connectionDFS(std::shared_ptr<Node> vertex, std::vector<std::shared_ptr<Node>>& visited, std::vector<char>& currentConnections)
{
    auto currentID{keyToID.at(vertex->getKey())};
    vertex->setVisit();
    visited.emplace_back(vertex);
    currentConnections.emplace_back(vertex->getKey()); // we push every node's key in the component to represent this node

    for(auto& nextVertex:m_edges[currentID])
    {
        if(!nextVertex->isVisit())
            connectionDFS(nextVertex, visited, currentConnections);
    }
}

void GraphOfNodes::hasPathHelperDFS(std::shared_ptr<Node> from, std::shared_ptr<Node> to, std::vector<std::shared_ptr<Node>> &visited, bool& found)
{
    auto currentID{keyToID.at(from->getKey())};
    from->setVisit();
    visited.emplace_back(from);
    if(from == to)
    {
        found = true;
        return;
    }

    for(auto& vertex:m_edges[currentID])
    {
        if(!vertex->isVisit())
            hasPathHelperDFS(vertex, to, visited, found);
        if(found)
            return;
    }
}

void GraphOfNodes::breadthFirstSearch(std::shared_ptr<Node> node, std::vector<std::shared_ptr<Node>>& visited)
{
    std::list queue{node};
    node->setVisit();
    visited.emplace_back(node);
    for (;!queue.empty();)
    {
        auto currentVertex{queue.front()};
        auto currentID{keyToID.at(currentVertex->getKey())};
        queue.pop_front();
        std::cout << currentVertex->getKey() << ", " << currentVertex->getValue() << '\n';

        for(auto neighbor:m_edges[currentID])
        {
            if(!neighbor->isVisit())
            {
                queue.emplace_back(neighbor);
                neighbor->setVisit();
                visited.emplace_back(neighbor);
            }
        }
    }
}

void GraphOfNodes::findShortestPathHelper(std::shared_ptr<Node> from, std::shared_ptr<Node> to, std::vector<std::shared_ptr<Node>> &path, std::vector<std::shared_ptr<Node>> &visited, bool& found)
{
    std::list queue{from};
    from->setVisit();
    visited.emplace_back(from);
    int buffer{0};
    int count{0};
    int level{0};
    from->setLevel(level);

    for (;!queue.empty();--buffer)
    {
        auto currentVertex{queue.front()};
        currentVertex->setLevel(level);
        queue.pop_front();
        auto currentID{keyToID.at(currentVertex->getKey())};
        if(currentVertex == to)
        {
            found = true;
            path.emplace_back(currentVertex);
            std::cout << "The length of the shorest path from " << from->getKey() << " to " << to->getKey() << " is " << level << ".\n";
            for (;currentVertex->getLevel() != 0;)
            {
                for(const auto& neighbor:m_edges[currentID])
                {
                    if(neighbor->getLevel() == currentVertex->getLevel()-1 && neighbor->isVisit())
                    {
                        path.emplace_back(neighbor);
                        currentVertex = neighbor;
                        currentID = keyToID.at(currentVertex->getKey());
                        break;
                    }
                }
            }
            std::reverse(path.begin(), path.end());
            return;
        }

        for(auto neighbor:m_edges[currentID])
        {
            if(!neighbor->isVisit())
            {
                queue.emplace_back(neighbor);
                neighbor->setVisit();
                visited.emplace_back(neighbor);
                ++count;
            }
        }

        if(!buffer)
        {
            buffer = count;
            count = 0;
            ++level;
        }
    }
}

bool GraphOfNodes::isCircleHelper(std::shared_ptr<Node> ori, std::shared_ptr<Node> from, std::vector<std::shared_ptr<Node>> &visited, std::vector<std::size_t>& degrees)
{
    auto currentID{keyToID.at(from->getKey())};
    from->setVisit();
    visited.emplace_back(from);
    degrees.emplace_back(m_edges[currentID].size());

    for(auto& vertex:m_edges[currentID])
    {
        // make sure this is a Simple Circle 
        if(from == ori && vertex->isVisit()) // (if we are at the root) And the nodes in the next level have been visited early, this is a circle
        {
            return true;
        }
        if(!vertex->isVisit())
        {
            isCircleHelper(ori, vertex, visited, degrees);
        }
    }
    return false; // if the root and inside has no circle, the graph has no circle
}

bool GraphOfNodes::hasCircleHelper(std::shared_ptr<Node> ori, std::shared_ptr<Node> from, std::vector<std::shared_ptr<Node>> &visited)
{
    auto currentID{keyToID.at(from->getKey())};
    from->setVisit();
    visited.emplace_back(from);
    std::size_t count{};

    for(auto& vertex:m_edges[currentID])
    {
        if(vertex->isVisit() && from == ori) // (if we are at the root) And the nodes in the next level have been visited early, this is a circle
            return true;
        if(!vertex->isVisit())
        {
            if(hasCircleHelper(ori, vertex, visited)) // If there is a circle inside (a branch has a circle), then the graph has a circle
                return true;
            // return circleHelper(ori, vertex, visited); This will lead you to the end of the world, which ALWAYS RETURNS FALSE (aka. result at the leaf is the final result)
            ++count;
        }
    }
    if(from != ori) // if we are inside the network
    {
        std::size_t notVisitCount{m_edges[currentID].size()-1}; // `-1` for Eliminating interference from parent node
        if(count != notVisitCount) // a None-Circle Node should visit its new neighbors for size()-1 times.
            return true;           // if not, it's a circle
    }
    return false; // if the root and inside has no circle, the graph has no circle
}

bool GraphOfNodes::isBipartiteGraphHelper(std::shared_ptr<Node> node, bool& color, std::vector<std::shared_ptr<Node>> &visited)
{
    auto currentID{keyToID.at(node->getKey())};
    if(!visited.size())
        node->setColor(color); // initialization
    node->setVisit();
    visited.emplace_back(node);
    color = !color; // transform every layer
    bool vertexColor{color}; // reversed

    for(auto& vertex:m_edges[currentID])
    {
        if(!vertex->isVisit())
        {
            vertex->setColor(vertexColor); // the nodes in the next layer whose color should be the same
            if(!isBipartiteGraphHelper(vertex, color, visited))
                return false;
        }
        if (vertex->getColor() != vertexColor) // the vertice in the same level should have the same color
        {
            return false;
        }
    }
    return true;
}

int main()
{
    // This is a Non-Dir Graph
    GraphOfNodes graph{10};
    auto node1{std::make_shared<Node>('a', 1)};
    auto node2{std::make_shared<Node>('b', 2)};
    auto node3{std::make_shared<Node>('c', 3)};
    auto node4{std::make_shared<Node>('d', 4)};
    auto node5{std::make_shared<Node>('e', 5)};
    auto node6{std::make_shared<Node>('f', 6)};
    auto node7{std::make_shared<Node>('g', 7)};
    auto node8{std::make_shared<Node>('h', 8)};
    auto node9{std::make_shared<Node>('i', 9)};

    // graph.addEdges(node1, node2);
    // graph.addEdges(node1, node3);
    // graph.addEdges(node1, node6);
    // graph.addEdges(node1, node7);
    // graph.addEdges(node6, node4);
    // graph.addEdges(node6, node5);
    // graph.addEdges(node4, node5);
    // graph.addEdges(node5, node7);
    // graph.addEdges(node8, node9);

    // graph.addEdges(node1, node2);
    // graph.addEdges(node1, node3);
    // graph.addEdges(node2, node4);
    // graph.addEdges(node3, node4);
    // graph.addEdges(node4, node5);
    // graph.addEdges(node4, node6);
    // graph.addEdges(node6, node7);

    graph.addEdges(node1, node2);
    graph.addEdges(node2, node3);
    graph.addEdges(node3, node1);


    std::cout << "Edges: " << graph.getNumberofEdges() << '\n';
    // if(graph.id('a'))
    //     std::cout << *graph.id('a') << '\n';

    // graph.searchFrom_DFS(node1); // traversal the whole network start from node1 by DFS method
    // std::cout << '\n';
    // graph.searchFrom_DFS(node8);

    // graph.hasPath(node1, node5); // check whether the path existed between node1 and node5
    // graph.hasPath(node1, node9);

    // graph.searchFrom_BFS(node1); // traversal the whole network start from node1 by BFS method

    // graph.findShortestPath(node1, node5); // find the shorest path between node1 and node5 by BFS method
    // graph.findShortestPath(node1, node4); // DFS can't do this because it's unordered feature
    // graph.findShortestPath(node1, node3);
    // graph.findShortestPath(node2, node3);
    // graph.findShortestPath(node5, node1);
    // graph.findShortestPath(node1, node1);
    // graph.findShortestPath(node1, node9);
    // graph.searchFrom_DFS(node1);

    graph.getConnections();
    std::cout << "The Graph is a Circle? " << std::boolalpha << graph.isCircle() << '\n';
    std::cout << "The Graph has a Circle? " << std::boolalpha << graph.hasCircle() << '\n';
    std::cout << "The Graph is a Bipartite Graph? " << std::boolalpha << graph.isBipartiteGraph() << '\n';

    return 0;
}
