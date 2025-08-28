#include <iostream>
#include <memory>
#include <utility>
#include <exception>
#include <functional>

class BinaryTreeExceptions: public std::runtime_error
{
public:
    explicit BinaryTreeExceptions(const std::string &error)
        : runtime_error {error}
    {}
};

class Binary_Tree
{
private:
    int m_value{};
    std::unique_ptr<Binary_Tree> m_leftNode{};
    std::unique_ptr<Binary_Tree> m_rightNode{};
    std::pair<Binary_Tree*,Binary_Tree*> findSuccessorNode();
    void eraseHelper(Binary_Tree* current, Binary_Tree *parent, bool checked, int value);

public:
    explicit Binary_Tree()
        :   Binary_Tree(0)
    {}
    explicit Binary_Tree(int value, std::unique_ptr<Binary_Tree>leftNode = nullptr, std::unique_ptr<Binary_Tree>rightNode = nullptr)
        :   m_value{value}, m_leftNode{std::move(leftNode)}, m_rightNode{std::move(rightNode)}
    {}

    explicit Binary_Tree(const Binary_Tree&) = delete;
    Binary_Tree &operator=(const Binary_Tree&) = delete;

    explicit Binary_Tree(Binary_Tree&& otherTree) noexcept
        : m_value{otherTree.m_value}, // move value
          m_leftNode{std::move(otherTree.m_leftNode)}, // move the left subtree
          m_rightNode{std::move(otherTree.m_rightNode)} // move the right subtree
    {
        otherTree.m_value = 0;
    }

    Binary_Tree& operator=(Binary_Tree&& otherTree) noexcept
    {
        if(this == &otherTree)
            return *this;

        m_value = otherTree.m_value;
        m_leftNode = std::move(otherTree.m_leftNode);
        m_rightNode = std::move(otherTree.m_rightNode);
        otherTree.m_value = 0;
        return *this;
    }

    int getValue() const { return m_value; }
    int count() const;
    int height() const;
    bool existence(int value) const;
    bool empty() const { return m_value == 0 && !m_leftNode && !m_rightNode; }
    Binary_Tree* search(int value);
    void insert(int value);
    void print() const;
    void erase(int value) { eraseHelper(this, nullptr, false, value); };
};

// Efficiency -> O(logN)
void Binary_Tree::insert(int value)
{
    if(value < m_value)
    {
        if(m_leftNode == nullptr) // if there is no exist left child-Node, we create one for this
            m_leftNode = std::make_unique<Binary_Tree>(value);
        else // if there is a node, we check the node
            m_leftNode->insert(value); // find left child tree
    }
    else if(value > m_value)
    {
        if(m_rightNode == nullptr)
            m_rightNode = std::make_unique<Binary_Tree>(value);
        else
            m_rightNode->insert(value);
    }
    else
    {
        std::cout << value << " already Existed!\n";
    }
}

// Efficiency -> O(logN)
Binary_Tree* Binary_Tree::search(int value)
{
    if(value == m_value)
        return this;
    
    if(value < m_value)
    {
        if(!m_leftNode)
            return nullptr;
        else
            return m_leftNode->search(value);
    }
    else
    {
        if(!m_rightNode)
            return nullptr;
        else
            return m_rightNode->search(value);
    }
    
}

bool Binary_Tree::existence(int value) const
{
    if(value == m_value)
        return true;
    
    if(value < m_value)
    {
        if(m_leftNode == nullptr)
            return false;
        else
            return m_leftNode->existence(value);
    }
    else
    {
        if(m_rightNode == nullptr)
            return false;
        else
            return m_rightNode->existence(value);
    }

}

void Binary_Tree::print() const
{
    if(m_leftNode) // left-child tree first print
    {
        m_leftNode->print();
    }
    
    std::cout << m_value << ' '; // then parent
    
    if(m_rightNode) // right-child last
    {
        m_rightNode->print();
    }

}

int Binary_Tree::count() const
{
    int count{1}; // self
    if(m_leftNode) // count the left child tree
    {
        count += m_leftNode->count();
    }
    if(m_rightNode) // and the right child tree
    {
        count += m_rightNode->count();
    }
    return count;
}

int Binary_Tree::height() const
{
    int height{1};

    if(m_leftNode && m_rightNode) // If both subtrees exist, then find the maximum height of the two subtrees. Add it with the basic height
        height += std::max(m_leftNode->height(),m_rightNode->height());
    else if(m_leftNode && !m_rightNode) // otherwise, Add the single subtree's height
        height += m_leftNode->height();
    else if(!m_leftNode && m_rightNode)
        height += m_rightNode->height();
    else // if no subtree exists, return current height
        return height;
    
    return height; // return the final height
}

std::pair<Binary_Tree*,Binary_Tree*> Binary_Tree::findSuccessorNode()
{
    Binary_Tree *parent{this};
    Binary_Tree *current{m_rightNode.get()};

    for (;current->m_leftNode;)
    {
        parent = current;
        current = current->m_leftNode.get();
    }

    return {parent, current};
}

// Efficiency -> O(logN)
void Binary_Tree::eraseHelper(Binary_Tree* current, Binary_Tree *parent, bool checked, int value)
{
    if(!checked && !current->existence(value))
    {
        std::cout << "We can't eraser an element that doesn't exist in this Tree.\n";
        return;
    }

    if(value < current->m_value)
    {
        parent = current; // save current node's pointer and we need go deep
        eraseHelper((current->m_leftNode.get()), parent, true, value);
    }
    else if(value > current->m_value)
    {
        parent = current;
        eraseHelper((current->m_rightNode.get()), parent, true, value);
    }
    else
    {
        if(!current->m_leftNode && !current->m_rightNode) // if the node we want to erase has no child
        {
            if(parent->m_leftNode.get() == current)
                parent->m_leftNode = nullptr; // delete it directly
            else
                parent->m_rightNode = nullptr;
        }
        else if((current->m_leftNode && !current->m_rightNode) || (!current->m_leftNode && current->m_rightNode)) // if the node has one child
        {
            if(current->m_leftNode)
            {
                current->m_value = current->m_leftNode->getValue(); // use its child('s value) replace itself('s value)
                current->m_leftNode = nullptr; // and delete the child
            }
            else
            {
                current->m_value = current->m_rightNode->getValue();
                current->m_rightNode = nullptr;
            }
        }
        else // otherwise, it got 2 child, we need find its successor first, use the successor to replace it
        {
            auto [successor_parent, successor] = current->findSuccessorNode();
            if(successor->m_rightNode) // if the successor has a right child, we need to use the child to fill the original position of successor
            {
                current->m_value = successor->m_value;
                successor->m_value = successor->m_rightNode->m_value;
                successor->m_rightNode = nullptr;
            }
            else
            {    
                current->m_value = successor->m_value;
                successor_parent->m_leftNode = nullptr;
            }
        }
    }
}

int main()
{
    Binary_Tree tree1{50};
    tree1.insert(25);
    tree1.insert(75);
    tree1.insert(10);
    tree1.insert(32);
    tree1.insert(56);
    tree1.insert(89);
    // tree1.insert(75);

    tree1.print();
    std::cout << '\n';

    int number{75};
    std::cout << "Existence of " << number << ": " << std::boolalpha << tree1.existence(number) << '\n';
    std::cout << "This Tree has " << tree1.count() << " Nodes.\n";
    try
    {
        auto searchObj{tree1.search(number)};
        if(!searchObj)
            throw BinaryTreeExceptions{"Can't resolve a NULL object!"};
        std::cout << "Search " << number << ": " << searchObj->getValue() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    tree1.erase(50);
    tree1.print();
    std::cout << '\n';

    std::cout << "Height: " << tree1.height() << '\n';

    Binary_Tree tree2{std::move(tree1)};
    std::cout << "Tree1 Empty? " << tree1.empty() << '\n'
              << "Tree2 Empty? " << tree2.empty() << '\n';

    tree1 = std::move(tree2);
    std::cout << "Tree1 Empty? " << tree1.empty() << '\n'
              << "Tree2 Empty? " << tree2.empty() << '\n';


    return 0;
}
