#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <unordered_map>
#include <unordered_set>

class Node
{
public:
    explicit Node(const std::string& key, double value)
        :   m_key{key}, m_value{value}
    {}

    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;

    explicit Node(Node&& node)
    {
        m_key   = std::move(node.m_key);
        m_value = std::move(node.m_value);
    }

    Node& operator=(Node&& node)
    {
        if(this == &node)
            return *this;
        
        m_key   = std::move(node.m_key);
        m_value = std::move(node.m_value);
        return *this;
    }

    std::string getKey() const { return m_key; }
    double getValue() const { return m_value; }

private:
    std::string m_key{};
    double m_value{};
};

using NodePtr = std::shared_ptr<Node>;

struct NodeCompare
{
    bool operator()(const NodePtr& l, const NodePtr& r)
    {
        return l->getKey() < r->getKey();
    }
};

class DirGraph
{
public:
    explicit DirGraph(std::size_t size)
        : m_size{size}, m_edges(size)
    {
        m_visited.reserve(size);
    }

    void addNode(const NodePtr& node);
    void addEdge(const NodePtr& from, const NodePtr& to, int weight);
    void printID(const NodePtr& node) const;
    void printTo(const NodePtr& node) const;
    bool isFullyConnected(); // we can traversal the whole dirGraph from one start
    void printReversedPostOrder(); // print the Topological order
    bool hasCircle(); // check is there a circle(strong connection) in the graph
    std::vector<std::vector<std::size_t>> getSCC(); // find the SCCs in the Graph. if no SCC, a Node is a SCC
    std::string idToKey(std::size_t id) { return m_nodes.at(id)->getKey(); } 

private:
    bool m_hasCircle{};
    std::size_t m_size{};
    std::size_t m_counts{0};
    std::vector<bool> m_visited{}; // we can't use range-based method to reset the remarks, because the vector's elements a A BIT instead of a bool.
    std::vector<NodePtr> m_nodes{}; // ID2Node
    std::unordered_map<std::string, std::size_t> m_ids{}; // Key2ID
    std::vector<std::unordered_map<std::size_t, int>> m_edges{}; // std::vector<std::vector<std::pair<std::size_t, int>>> More Complex

    bool m_enableOrder{false};
    std::vector<std::size_t> m_preOrder{};
    std::vector<std::size_t> m_postOrder{};
    std::vector<std::size_t> m_reversedPostOrder{};

    const std::size_t* getID(const NodePtr &node) const;
    void resetVisited();
    void setVisited(std::size_t id) { m_visited[id] = true; }
    bool hasVisited(std::size_t id) const { return m_visited[id]; }
    void deepFirstSearch(const std::vector<std::unordered_map<std::size_t, int>>& edge);
    void deepFirstSearchHelper(const std::vector<std::unordered_map<std::size_t, int>>& edge, std::size_t currentID, std::size_t ori);
    void enableOrderRecord() { clearOrders(); m_enableOrder = true;}
    void disableOrderRecord() { m_enableOrder = false; }
    void clearOrders();
    std::vector<std::size_t> getReversedPostOrder();
    std::vector<std::unordered_map<std::size_t, int>> getReversedGraph() const;
};

void DirGraph::addNode(const NodePtr& node)
{
    if(m_ids.contains(node->getKey()))
        return;
    m_ids[node->getKey()] = m_counts;
    m_nodes.emplace_back(node); // the indice of the both vectors should be Aligned with counts
    m_visited.emplace_back(false);
    ++m_counts;
}

void DirGraph::addEdge(const NodePtr& from, const NodePtr& to, int weight)
{
    if(from == to || from->getKey() == to->getKey()) return; // avoid self-Circle
    addNode(from);
    addNode(to);
    auto fromID{*getID(from)};
    auto toID{*getID(to)};
    m_edges[fromID][toID] = weight; // if a repeat edge was defined, we will override the old weight of this edge instead of create a Parallel edge.

    if(m_counts == m_size/2) // dynamic expansion
    {
        m_size *= 2;
        m_edges.resize(m_size);
    }
}

const std::size_t* DirGraph::getID(const NodePtr& node) const
{
    if(!m_ids.contains(node->getKey()))
        return nullptr;
    return &m_ids.at(node->getKey());
}

void DirGraph::printID(const NodePtr& node) const
{
    const auto& key{node->getKey()};
    if(!m_ids.contains(key))
    {
        std::cout << "Sorry, `" << node->getKey() << "` is not in the Graph yet.\nPlease ADD it first.\n";
        return;
    }
    std::cout << key << " ID: " << m_ids.at(key) << '\n';
}

void DirGraph::printTo(const NodePtr &node) const
{
    const auto& key{node->getKey()};
    if(!m_ids.contains(key))
    {
        std::cout << "Sorry, `" << node->getKey() << "` is not in the Graph yet.\nPlease ADD it first.\n";
        return;
    }
    const auto id{m_ids.at(key)};
    for(const auto& [toID,weight]:m_edges[id]) // traversal current Node's map
        std::cout << key << " --> " << m_nodes[toID]->getKey() << ", " << weight << " KiloMeters.\n";
}

void DirGraph::resetVisited()
{
    for(size_t i{0}; i < m_visited.size(); ++i)
        m_visited[i] = false;
}

std::vector<std::unordered_map<std::size_t, int>> DirGraph::getReversedGraph() const
{
    std::size_t size{m_edges.size()};
    std::vector<std::unordered_map<std::size_t, int>> reversed(size);

    for (std::size_t i{0}; i < size; ++i)
    {
        const auto& maps{m_edges[i]};
        for(const auto& [to, weight]:maps)
            reversed[to][i] = weight;       // Noticed the Original edges's definition is `m_edges[count(from)][to] = weight`
    }

    return reversed;
}

void DirGraph::deepFirstSearchHelper(const std::vector<std::unordered_map<std::size_t, int>>& edge, std::size_t currentID, std::size_t ori)
{
    setVisited(currentID);
    if(m_enableOrder)
        m_preOrder.emplace_back(currentID);
    for(const auto& [to, weight]:edge[currentID])
    {
        if(!hasVisited(to))
        {
            deepFirstSearchHelper(edge, to, ori);
            if(m_enableOrder)
            {
                m_postOrder.emplace_back(to); // linear visiting
                m_reversedPostOrder.emplace_back(to); // stack pop visiting
            }
        }
        else // if we from the destination goes back to somewhere we have visited (because of single direction), A circle is existed in the graph
            m_hasCircle = true;
    }
    if(m_enableOrder && currentID == ori) // add the root at the end
    {
        m_postOrder.emplace_back(currentID);
        m_reversedPostOrder.emplace_back(currentID);
    }
}

void DirGraph::deepFirstSearch(const std::vector<std::unordered_map<std::size_t, int>>& edge)
{
    for(std::size_t i{0}; i < m_ids.size(); ++i)
    {
        if(!hasVisited(i))
        {
            deepFirstSearchHelper(edge, i, i);
        }
    }
    resetVisited(); // a reset MUST Follow with a DFS
}

void DirGraph::clearOrders()
{
    m_preOrder.clear();
    m_postOrder.clear();
    m_reversedPostOrder.clear();
}

std::vector<std::size_t> DirGraph::getReversedPostOrder()
{
    return m_reversedPostOrder;
}

bool DirGraph::isFullyConnected()
{
    int part{};
    for(std::size_t i{0}; i < m_ids.size(); ++i)
    {
        if(!hasVisited(i))
        {
            deepFirstSearchHelper(m_edges, i, i);
            ++part;
        }
    }
    resetVisited();
    if(part == 1)
        return true;
    else
        return false;
}

void DirGraph::printReversedPostOrder() // Print topological order
{
    if(m_reversedPostOrder.empty())
    {
        if(!isFullyConnected())
        {
            std::cout << "This Graph has many parts. we are not support for this yet!\n";
            return;
        }
        enableOrderRecord();
        deepFirstSearch(m_edges);
        resetVisited();
        disableOrderRecord();

    }

    auto order{m_reversedPostOrder};
    for (;!order.empty();)
    {
        std::cout << m_nodes[order.back()]->getKey();
        order.pop_back();
        if(!order.empty())
            std::cout << " --> ";
    }
    std::cout << '\n';
}

bool DirGraph::hasCircle()
{
    deepFirstSearch(m_edges);
    resetVisited();
    return m_hasCircle;
}

std::vector<std::vector<std::size_t>> DirGraph::getSCC() // for all kinds of dirGraph
{
    auto reversedEdges{getReversedGraph()};
    // get the Reversed Graph's Reversed-Post Order
    enableOrderRecord(); // The start record must appear together with the stop record
    for(int i{static_cast<int>(m_ids.size()-1)}; i >= 0; --i) // we can't use DFS() directly here, because we need to traversal the graph in a reversed way
    {
        if(!hasVisited(static_cast<std::size_t>(i)))
            deepFirstSearchHelper(reversedEdges, static_cast<std::size_t>(i), static_cast<std::size_t>(i));
    }
    disableOrderRecord();
    resetVisited();
    auto rReversedPostOrder{getReversedPostOrder()};
    std::unordered_set<std::size_t> recoder{};
    std::vector<std::vector<std::size_t>> scc{};
    scc.reserve(m_nodes.size());
    for (;!rReversedPostOrder.empty();) // pop the vertice from the Order
    {
        const auto vertex{rReversedPostOrder.back()};
        rReversedPostOrder.pop_back();
        if(!hasVisited(vertex))
        {
            deepFirstSearchHelper(m_edges, vertex, vertex);
            std::vector<std::size_t> temp{};
            for (std::size_t i{0}; i < m_visited.size(); ++i)
            {
                if(m_visited[i] && !recoder.contains(i)) // find the new comers and emplace them into our temporay result
                {
                    recoder.insert(i);
                    temp.emplace_back(i);
                }
            }
            scc.emplace_back(std::move(temp));
        }
    }
    resetVisited();
    return scc;
}

int main()
{
    DirGraph dirgraph{10};
    auto node1{std::make_shared<Node>("Beijing"  , 12.34)};
    auto node2{std::make_shared<Node>("Shanghai" , 13.45)};
    auto node3{std::make_shared<Node>("Guangzhou", 14.24)};
    auto node4{std::make_shared<Node>("Shenzhen" , 15.26)};

    dirgraph.addNode(node1);
    dirgraph.addEdge(node1, node2, 1213);
    dirgraph.addEdge(node3, node4,  138);
    dirgraph.addEdge(node1, node3, 1174);

    dirgraph.printID(node1);
    dirgraph.printID(node2);
    dirgraph.printID(node3);
    dirgraph.printID(node4);

    dirgraph.printTo(node1);

    std::cout << "DirGraph is Fully Connected? " << std::boolalpha << dirgraph.isFullyConnected() << '\n';
    std::cout << "DirGraph has a Circle? " << std::boolalpha << dirgraph.hasCircle() << '\n';
    std::cout << "DirGraph Reversed Post Order: "; dirgraph.printReversedPostOrder();

    auto dirGraphSCC{dirgraph.getSCC()}; // Strong Connected Components
    std::cout << "DirGraph has " << dirGraphSCC.size() << " Strong Connected Component(s):\n";
    for (std::size_t i{0}; i < dirGraphSCC.size(); ++i)
    {
        std::cout << "Component " << i + 1 << ": ";
        for(const auto vertex:dirGraphSCC[i])
            std::cout << dirgraph.idToKey(vertex) << ' ';
        std::cout << '\n';
    }

    return 0;
}
