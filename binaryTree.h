#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <iostream>
#include <memory>
#include <utility>
#include <exception>
#include <functional>

template<typename T>
class Binary_Tree
{
private:
    T m_value{};
    std::unique_ptr<Binary_Tree<T>> m_leftNode{};
    std::unique_ptr<Binary_Tree<T>> m_rightNode{};
    
    std::pair<Binary_Tree<T>*, Binary_Tree<T>*> findSuccessorNode();
    void eraseHelper(Binary_Tree<T>* current, Binary_Tree<T>* parent, bool checked, const T& value);

public:
    explicit Binary_Tree()
        : Binary_Tree(T{}) {}

    explicit Binary_Tree(T value,
                         std::unique_ptr<Binary_Tree<T>> leftNode = nullptr,
                         std::unique_ptr<Binary_Tree<T>> rightNode = nullptr)
        : m_value{std::move(value)},
          m_leftNode{std::move(leftNode)},
          m_rightNode{std::move(rightNode)}
    {}

    Binary_Tree(const Binary_Tree&) = delete;
    Binary_Tree& operator=(const Binary_Tree&) = delete;

    Binary_Tree(Binary_Tree&& otherTree) noexcept
        : m_value{std::move(otherTree.m_value)},
          m_leftNode{std::move(otherTree.m_leftNode)},
          m_rightNode{std::move(otherTree.m_rightNode)}
    {
        otherTree.m_value = T{};
    }

    Binary_Tree& operator=(Binary_Tree&& otherTree) noexcept
    {
        if (this == &otherTree)
            return *this;

        m_value = std::move(otherTree.m_value);
        m_leftNode = std::move(otherTree.m_leftNode);
        m_rightNode = std::move(otherTree.m_rightNode);
        otherTree.m_value = T{};
        return *this;
    }

    T getValue() const { return m_value; }
    int count() const;
    int height() const;
    bool existence(const T& value) const;
    bool empty() const { return m_value == T{} && !m_leftNode && !m_rightNode; }
    Binary_Tree<T>* search(const T& value);
    void insert(const T& value);
    void print() const;
    void erase(const T& value) { eraseHelper(this, nullptr, false, value); }
};

template <typename T>
void Binary_Tree<T>::insert(const T& value)
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
template <typename T>
Binary_Tree<T>* Binary_Tree<T>::search(const T& value)
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

template <typename T>
bool Binary_Tree<T>::existence(const T& value) const
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

template <typename T>
void Binary_Tree<T>::print() const
{
    if(m_leftNode) // left-child tree first print
    {
        m_leftNode->print();
    }
    
    std::cout << m_value << ' '; // then itself
    
    if(m_rightNode) // right-child tree at last
    {
        m_rightNode->print();
    }

}

template <typename T>
int Binary_Tree<T>::count() const
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

template <typename T>
int Binary_Tree<T>::height() const
{
    int height{1};

    if(m_leftNode && m_rightNode) // If both subtrees exist, then find the maximum height of the two subtrees. Add it to the basic height
        height += std::max(m_leftNode->height(),m_rightNode->height());
    else if(m_leftNode && !m_rightNode) // otherwise, Add the single subtree's height
        height += m_leftNode->height();
    else if(!m_leftNode && m_rightNode)
        height += m_rightNode->height();
    else // if no subtree exists, return current height
        return height;
    
    return height; // return the final height
}

template <typename T>
std::pair<Binary_Tree<T>*,Binary_Tree<T>*> Binary_Tree<T>::findSuccessorNode()
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
template <typename T>
void Binary_Tree<T>::eraseHelper(Binary_Tree<T>* current, Binary_Tree<T> *parent, bool checked, const T& value)
{
    if(!checked && !current->existence(value)) // check is there value existed, at the beginning of erasing the value that user specified
    {
        std::cout << "We can't eraser an element that doesn't exist in this Tree.\n";
        return;
    }

    // if the value existed, the value will be found eventually
    if(value < current->m_value) // if the value is small than current node's value, we check the left child tree
    {
        parent = current; // save current node's pointer as parent, we need update the current node. Parent for `swap`
        eraseHelper((current->m_leftNode.get()), parent, true, value); // RECURSION
    }
    else if(value > current->m_value) // if the value is greater than current value, we check the right child tree
    {
        parent = current;
        eraseHelper((current->m_rightNode.get()), parent, true, value);
    }
    else // END CONDITION
    {
        if(!current->m_leftNode && !current->m_rightNode) // if the node we want to erase has no child
        {
            if(parent->m_leftNode.get() == current)
                parent->m_leftNode = nullptr; // delete it directly (from its parent, we can't delete itself directly)
            else
                parent->m_rightNode = nullptr;
        }
        else if((current->m_leftNode && !current->m_rightNode) || (!current->m_leftNode && current->m_rightNode)) // if the node has one child
        {
            if(current->m_leftNode)
            {
                current->m_value = current->m_leftNode->getValue; // use its child's value replace itself('s value)
                current->m_leftNode = nullptr; // and delete the child
            }
            else
            {
                current->m_value = current->m_rightNode->getValue();
                current->m_rightNode = nullptr;
            }
        }
        else // otherwise, it got 2 child, we need find its successor first, use the successor to replace it
        {   //  <--[--erase element <--]----[--successor <--]---[--successor's right child (if it has)]
            auto [successor_parent, successor] = current->findSuccessorNode(); // (pre-erase) current node's right child's `left leaf` child
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
#endif
