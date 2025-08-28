#include <iostream>
#include <memory>
#include <utility>
#include <compare>
// RedBlack Tree -> 2-3 Tree
const bool g_red{true};
const bool g_black{false};
class Node;
using NodePtr = std::unique_ptr<Node>;

class Node
{
public:
    explicit Node(char key, int value, bool color, int size = 1, NodePtr left = nullptr, NodePtr right = nullptr)
        :   m_key{key}, m_value{value}, m_color{color}, m_size{size},
            m_left{std::move(left)}, m_right{std::move(right)}
    {}
    Node(const Node &) = delete;
    Node &operator=(const Node &) = delete;

    Node(Node&& other) noexcept
        :   m_key{std::move(other.m_key)}, m_value{std::move(other.m_value)}, m_color{other.m_color}, m_size{other.m_size}, 
            m_left{std::move(other.m_left)}, m_right{std::move(other.m_right)}
    {}

    Node& operator=(Node&& other)
    {
        if(this == &other)
            return *this;

        m_key   = std::move(other.m_key);
        m_value = std::move(other.m_value);
        m_color = other.m_color;
        m_size  = std::move(other.m_size);
        m_left  = std::move(other.m_left);
        m_right = std::move(other.m_right);
        return *this;
    }
    // compare keys only
    auto operator<=>(const Node &other) const { return m_key <=> other.m_key; } // if you use default, it will compare following the definition order below
    bool operator==(const Node &other) const { return m_key == other.m_key; }

    char m_key{};
    int m_value{};
    bool m_color{}; // color of the node is the color of the link to its parent node, which is work at the situation of insertion (for rotation the node)
                    // which is the key of make this binary tree balance.
    int m_size{};
    NodePtr m_left;
    NodePtr m_right;

};

class RedBlackTree // cooperate with Class Node
{
public:
    void insert(char key, int value)
    {
        m_root = insert(std::move(m_root), key, value); // Create (Shape again) the tree
        m_root->m_color = g_black; // 根节点始终为黑
    }
    void insert234(char key, int value) // create a 2-3-(4)(temporal) Tree
    {
        m_root = insert234(std::move(m_root), key, value);
        m_root->m_color = g_black; // 根节点始终为黑
    }

    void print() const { print(m_root); }
    void deleteMin()
    { 
        if(!isRed(m_root->m_left) && !isRed(m_root->m_right))
            m_root->m_color = g_red;
        deleteMinHelper(m_root);
        if(m_root) m_root->m_color = g_black;
    }
    void deleteMax()
    { 
        if(!isRed(m_root->m_left) && !isRed(m_root->m_right))
            m_root->m_color = g_red;
        deleteMaxHelper(m_root);
        if(m_root) m_root->m_color = g_black;
    }
    void deleteNode(char key) 
    {
        if(!isRed(m_root->m_left) && !isRed(m_root->m_right))
            m_root->m_color = g_red;
        deleteNodeHelper(m_root, key);
        if(m_root) m_root->m_color = g_black;
    }
    int* at(char key) { return searchHelper(m_root, key); }

private:
    NodePtr m_root{nullptr};
    NodePtr m_unfindNode{nullptr};
    int m_unfind{-1};
    static int getSize(const NodePtr &h) { return h ? h->m_size : 0; }
    bool isRed(const NodePtr& node) const
    {
        // if(!node) return false;
        // return node->m_color == g_red;
        return node && node->m_color == g_red;
    }
    // Core of this structure
    void fixNodes(NodePtr &node);
    NodePtr rotateLeftHelper(NodePtr node);
    NodePtr rotateRightHelper(NodePtr node);
    void rotateLeft (NodePtr& h) { h = rotateLeftHelper (std::move(h)); } // do the rotate to `h` Node
    void rotateRight(NodePtr& h) { h = rotateRightHelper(std::move(h)); }
    void flipColors(NodePtr& node);
    // manipulate the tree
    NodePtr insert(NodePtr h, char key, int value);
    NodePtr insert234(NodePtr h, char key, int value);
    void print(const NodePtr& node) const;
    void swapContent(NodePtr &node, NodePtr &other); // this function just swap key, value and color
    void deleteMinHelper(NodePtr& h);
    void flipColorsReal(NodePtr &h);
    void moveRedLeft(NodePtr &h);
    void moveRedRight(NodePtr &h);
    void deleteMinSedgwick(NodePtr &h);
    void deleteMaxHelper(NodePtr &h);
    NodePtr moveSuccessor(NodePtr &node);
    void deleteNodeHelper(NodePtr &h, char key);
    int* searchHelper(NodePtr &h, char key);
};

// int RedBlackTree::getNodeSize(NodePtr& h) // return current Node's number of children (SubNodes) directly
// {
//     if(!h)
//         return 0;
    
//     int temp_size{1};
//     if(h->m_left)
//         temp_size += size(h->m_left);
//     if(h->m_right)
//         temp_size += size(h->m_right);

//     return temp_size;
// }

// Rotation one node is shift the connection node (from the RED node, 3-Node) to its parent.
// And at the same time, properly change the connections to the RED NODE's children

void RedBlackTree::fixNodes(NodePtr &h)
{
    if(isRed(h->m_right))
        rotateLeft(h);
    if(isRed(h->m_left) && isRed(h->m_left->m_left))
        rotateRight(h);
    if(isRed(h->m_left) && isRed(h->m_right))
        flipColors(h);

    h->m_size = 1 + getSize(h->m_left) + getSize(h->m_right); // update node's size
}

NodePtr RedBlackTree::rotateLeftHelper(NodePtr h) // use your left hand make the left node on the red connection down, and do the drop if it need
{                                                 // Apparently, make the left one down, the right one will rise by then
    auto x{std::move(h->m_right)}; // extract the right node as the new root

    h->m_right = std::move(x->m_left); // transfer the right node's left child to the place where its parent node was before
    x->m_left =  std::move(h); // now the left part is constructed, we make it(old root) become `x`'s left child (ori: its right child is `x`)
    
    // x->m_left == h
    x->m_color = x->m_left->m_color; // we restore the color from the ori node, which is on the left position now
    x->m_left->m_color = g_red; // we make the connection between the rotated node(left child now) and its right child(local root) RED
    x->m_size = x->m_left->m_size; // inherit the size from the old root 
    x->m_left->m_size = 1 + getSize(x->m_left->m_left) + getSize(x->m_left->m_right); // Re-calculate the size (old root -> left child)

    return x; // return the new root(new tree)
    // P.S. Because we moved the old tree into this function, so after we modified it we returns the new tree to the same position is reasonable.
}

NodePtr RedBlackTree::rotateRightHelper(NodePtr h) // use your right hand make the right node on the red connection down, and do the drop if it need
{
    auto x{std::move(h->m_left)};

    h->m_left = std::move(x->m_right);
    x->m_right =  std::move(h); // h becomes nullptr from here
    
    // x->m_right == h
    x->m_color = x->m_right->m_color;
    x->m_right->m_color = g_red; // 
    x->m_size = x->m_right->m_size;
    x->m_right->m_size = 1 + getSize(x->m_right->m_left) + getSize(x->m_right->m_right);

    return x;
}

void RedBlackTree::flipColors(NodePtr& node) // make the link to current node RED and make the color of links to its children BLACK
{
    // we just make this operation at the LAST when we INSERT
    node->m_color = g_red;
    node->m_left->m_color  = g_black;
    node->m_right->m_color = g_black;
}

// Insertion from the bottom of the RedBlackTree to the top.
// There is also a method of TOP to down
NodePtr RedBlackTree::insert(NodePtr h, char key, int value)
{
    if (!h) return std::make_unique<Node>(key, value, g_red); // if root is nullptr, which means this is a nulltree (or subtree). So we just create one

    // otherwise we insert this node to the left child or the right child or just update the value
    if (key < h->m_key)
        h->m_left  = insert(std::move(h->m_left), key, value); // we move left subtree for insertion and it returns a new subtree back
    else if (key > h->m_key)
        h->m_right = insert(std::move(h->m_right), key, value);
    else
        h->m_value = value;  // handle the repeat keys, update its value

    // 修复红黑树性质 (when insertion has done, we do those repairs from the bottom to the top)
    // The essence of repair is to modify the root node
    // rotate sequentially if it is
    fixNodes(h);
    return h; // return the root in each layer
}

NodePtr RedBlackTree::insert234(NodePtr h, char key, int value)
{
    if (!h) return std::make_unique<Node>(key, value, g_red); // if root is nullptr, which means this is a nulltree (or subtree). So we just create one

    if(isRed(h->m_left) && isRed(h->m_right)) // insert a 2-3-4 Tree you just need change these statements's position
        flipColors(h); // we filp the color here makes the existence of 4-Node, but 4-Node is temporal
    
    // otherwise we insert this node to the left child or the right child or just update the value
    if (key < h->m_key)
        h->m_left  = insert(std::move(h->m_left), key, value); // m_left becomes root node and update itself
    else if (key > h->m_key)
        h->m_right = insert(std::move(h->m_right), key, value); // m_right becomes root node
    else
        h->m_value = value;

    fixNodes(h); // fix from the bottom to the top
    return h; // return the root in each layer
}


void RedBlackTree::print(const NodePtr& node) const
{  
    // middle-order
    if(!node)
        return;
    
    if(node->m_left)
        print(node->m_left);
    
    std::cout << "[Key: " << node->m_key << ", Value: " << node->m_value << ", Color: " << (node->m_color ? " RED " : "BLACK") << "]\n";
    
    if(node->m_right)
        print(node->m_right);
}

void RedBlackTree::swapContent(NodePtr &node, NodePtr &other)
{
    // we don't want modify the tree's structure but swap the basic contents of two Nodes between two nodes
    if(&node == &other)
        return;
    
    std::swap(node->m_key, other->m_key);
    std::swap(node->m_value, other->m_value);
    std::swap(node->m_color, other->m_color);
}


void RedBlackTree::deleteMinHelper(NodePtr& h) // Native implementation
{
    // a RedBlack Tree has no situation of single leg (i.e. m_left exist but m_right doesn't)
    // begining check
    if(!h)
        return;
    
    if(!h->m_left) // if current tree is a SINGLE NODE tree, we just delete it (ONLY single Node tree has this situation)
    {
        h = nullptr;
        return;
    }

    if(h->m_left->m_left) // dive to the very left on the bottom
        deleteMinHelper(h->m_left);
    else
    {
        if(isRed(h->m_left)) // if the node we want delete is not a 2-Node <CASE 0>
        {
            h->m_left = nullptr; // we just delete it
        }
        else if(!isRed(h) && !isRed(h->m_left) && !isRed(h->m_right)) // if current node is the root node, and it is also a 2-Node <CASE 1>
        {
            h->m_left = nullptr; // we delete the very left
            h->m_right->m_color = g_red;
            rotateLeft(h);
        }
        else if(!isRed(h->m_left) && isRed(h->m_right->m_left)) // if the node we want delete is a 2-Node but its slibing is not. <CASE 2>
        {
            if(h->m_right->m_left->m_left) // if the slibing is a 4-Node
            {
                // h.swap(h->m_right->m_left->m_left); // NOTICE: we can't do this because this will swap subtrees too. The situation is not we want to see
                swapContent(h, h->m_right->m_left->m_left);       // change the root's content first
                h->m_color = h->m_right->m_left->m_left->m_color; // restore the root's color
                h->m_right->m_left->m_left->m_color = g_red; //
                h->m_left->m_right = std::move(h->m_right->m_left->m_left);
                rotateLeft(h->m_left);
                h->m_left->m_left = nullptr; // delete the min
            }
            else // otherwise it's a 3-Node
            {
                swapContent(h, h->m_right->m_left); // change the content
                h->m_color = h->m_right->m_left->m_color; // restore the root's color
                h->m_right->m_left->m_color = g_red; //
                h->m_left->m_right = std::move(h->m_right->m_left->m_left);
                rotateLeft(h->m_left);
                h->m_left->m_left = nullptr; // delete the min
            }
        }
        // <CASE 3> if the node we want delete and its slibing are 2-Node but their parent is 3-Node or 4-Node 
        else if(isRed(h) && !isRed(h->m_left) && !isRed(h->m_right)) 
        {
            h->m_left->m_color = g_red;
            swapContent(h, h->m_right);
            h->m_left->m_right = std::move(h->m_right);
            rotateLeft(h->m_left);
            h->m_left->m_left = nullptr;
        }
    }

    fixNodes(h);
}

void RedBlackTree::flipColorsReal(NodePtr& h) // delete
{
    // we do this kind of flip when we deleting the nodes
    if(!h) return;
        h->m_color = !h->m_color;
    if(h->m_left)
        h->m_left->m_color = !h->m_left->m_color;
    if(h->m_right)
        h->m_right->m_color = !h->m_right->m_color;
}

void RedBlackTree::moveRedLeft(NodePtr& h) 
{
    flipColorsReal(h); // we borrowed one already
    if(!h->m_right) return; // if NO slibing, creation is over

    // fix the situation that FixNode() can't fix
    if (isRed(h->m_right->m_left)) // if the right slibing can NOT be fixed automatically to restore the balance, we do it MANUALLY
    {
        rotateRight(h->m_right); // bring one node out of the right 3-Node
        rotateLeft(h); // then press the current node join the left child, making it a 3-Node and the borrowed one becomes the new root
        flipColorsReal(h); // restore the color of root and make both sides balance
    }
}

void RedBlackTree::moveRedRight(NodePtr& h) 
{
    flipColorsReal(h);  // make sure the right child RED
    if(!h->m_left) return; // if NO slibing, creation is over
    if (isRed(h->m_left->m_left)) // if the left slibing can NOT be fixed automatically to restore the balance, we do it MANUALLY
    { // do the fix to the REAL LLBlack Node
        rotateRight(h); // press the 2-Node the the right. If you press a Node of a 3-Node to the right, the rest of it will break the balance
        flipColorsReal(h); // restore the new root's color. 
    }
}


void RedBlackTree::deleteMinSedgwick(NodePtr& h) // much simpler than the native one
{
    if (!h) return;

    // 基本情况：已经到达最左端叶子节点
    if (!h->m_left)
    {
        h = nullptr;
        return;
    }

    // A 2-NODE satisfies the following conditions if you goes left
    // first condition: left is not red connected with Parent
    // second condition: and it's not red connected with Child neither.
    // Complete 2-Node
    if (!isRed(h->m_left) && !isRed(h->m_left->m_left))// if current node is a native 2-Node, and its left child is a 2-Node too (or empty)
        moveRedLeft(h);  // 使得左子为红

    deleteMinSedgwick(h->m_left);

    // 删除后修复红黑树结构以及更新结点数
    fixNodes(h);
}

void RedBlackTree::deleteMaxHelper(NodePtr& h)
{
    if (!h) return;

    if(isRed(h->m_left)) // if current node is a 3-plus Node
        rotateRight(h); // we press one node into the right child (unfold this node)
    
    // 基本情况：已经到达最右端叶子节点
    if (!h->m_right)
    {
        h = nullptr;
        return;
    }

    // When this node can't be expanded, we consider to borrow a node from the slibing (can't be a 3PlusNode, which will cause ) <PHRASE 2>
    // A 2-NODE satisfies the following conditions if you goes right
    if(!isRed(h->m_right) && !isRed(h->m_right->m_left)) // if next node is a native 2-Node, we need to make it a 3-Node
        moveRedRight(h);  // 使得右子为红

    deleteMaxHelper(h->m_right);

    // 删除后修复红黑树结构以及更新结点数
    fixNodes(h);
}

NodePtr RedBlackTree::moveSuccessor(NodePtr &node) // current right then to the left left node
{
    if(node->m_left)
    {
        if(!isRed(node->m_left) && !isRed(node->m_left->m_left))// if current node is a native 2-Node, and its left child is a 2-Node too (or empty)
            moveRedLeft(node);  // make sure the successor is a 3-Node
        return moveSuccessor(node->m_left);
    }
    else
    {
        auto successor{std::make_unique<Node>(node->m_key, node->m_value, node->m_color)};
        if(node->m_right) // if the successor has a right child
        {
            node = std::move(node->m_right);
        }
        else
        {
            node = nullptr;
        }
        return successor;
    }
}

// void RedBlackTree::deleteNodeHelper(NodePtr &h, char key)
// {
//     if(!h) return;

//     if(key == h->m_key) // current is we need delete
//     {
//         // if the node is a Part of a Big RedLeaf (must be a 3-Node, recursion Did This)
//         // Why?
//         // Because there is NO such Node only has one leftChild or no child in the tree!
//         if(!h->m_right)
//         {
//             if(!h->m_left) // if this Node is the red one
//                 h = nullptr; // directly delete
//             else // or it is the black one(Original), but it has been Transformed to Red. Replace it (May Never trigger)
//             {
//                 auto color{h->m_color};
//                 swapContent(h, h->m_left); // use its left child replace itself
//                 h->m_left = nullptr;
//                 h->m_color = color; // restore the color
//             }
//         }
//         else // if it has a right child, it must in the Tree, so we find its Successor (We DON'T CARE its LEFTCHILD)
//         {
//             // we will go right then go to the very left leaf in this branch
//             // h = std::move(moveSuccessor(h->m_right)); // this will destroy the links
//             auto color{h->m_color};
//             if(!isRed(h->m_right) && !isRed(h->m_right->m_left)) // Make sure the right is safe
//                 moveRedRight(h);
//             auto successor{moveSuccessor(h->m_right)};
//             swapContent(h, successor);
//             h->m_color = color;
//         }
//     }
//     else if (key < h->m_key) // Red traversal the left subtree
//     {
//         if(h->m_left)
//         {
//             if (!isRed(h->m_left) && !isRed(h->m_left->m_left)) // if we need to go left, fix all the left 2-Node
//                 moveRedLeft(h);  // 使得左子为红
//             deleteNodeHelper(h->m_left, key);
//         }
//         else
//             std::cout << "Sorry, there is NO [" << key << "] in this tree.\n";
//     }
//     else // > otherwise, Red traversal the right subtree
//     {
//         if(h->m_right)
//         {
//             if(isRed(h->m_left))
//                 rotateRight(h);
//             if(!isRed(h->m_right) && !isRed(h->m_right->m_left)) // otherwise, if it still a 2-Node
//                 moveRedRight(h);  // 使得右子为红
//             deleteNodeHelper(h->m_right, key);
//         }
//         else
//             std::cout << "Sorry, there is NO " << key << " in this tree.\n";
//     }

//     // Backtracking repair
//     if(h) // Our node may be Nullptr, we just left the Repairation to its Parent Node
//         fixNodes(h);
// }

void RedBlackTree::deleteNodeHelper(NodePtr &h, char key)
{
    if(!h) // if the right subtree has been traversed
    {
        std::cout << "Sorry, there is NO [" << key << "] in this tree.\n";
        return; // we don't need to fix a empty Node
    }
    if (key < h->m_key)
    {
        if(h->m_left)
        {
            if (!isRed(h->m_left) && (h->m_left && !isRed(h->m_left->m_left)))  // if we need to go left, fix all the left 2-Node
                moveRedLeft(h);  // 使得左子为红
            deleteNodeHelper(h->m_left, key);
        }
        else
            std::cout << "Sorry, there is NO [" << key << "] in this tree.\n";
    }
    else
    {
        if(isRed(h->m_left)) // throw all Left Red Child Out
            rotateRight(h);
        if(h->m_key == key && !h->m_right) // Leaf(A node has 1 or 0 child must be a Leaf), and No left child Now(Thrown), we can directly delete it
        {
            h = nullptr;
            return;
        }
        if (!isRed(h->m_right) && (h->m_right && !isRed(h->m_right->m_left))) // make sure right is SAFE
            moveRedRight(h);
        if(h->m_key == key) // if the node is in the tree(has a Right child)
        {
            auto color{h->m_color};
            auto successor{moveSuccessor(h->m_right)}; // SAFE
            swapContent(h, successor);
            h->m_color = color;
        }
        else // NOT MATCHED, m_key is bigger, keep go to the right Subtree(SAFE)
            deleteNodeHelper(h->m_right, key);
    }

    if(h)
        fixNodes(h);
}

int* RedBlackTree::searchHelper(NodePtr& node, char key)
{
    if(!node) return nullptr;

    if(key == node->m_key)
        return &(node->m_value);
    else if (key < node->m_key)
        return searchHelper(node->m_left, key);
    else
        return searchHelper(node->m_right, key);
}

int main()
{
    RedBlackTree rbtree{};
    // rbtree.insert('c', 1);
    // rbtree.insert('a', 2);
    // rbtree.insert('b', 3);
    // rbtree.insert('d', 7);
    // rbtree.insert('e', 8);
    rbtree.insert('a', 1);
    rbtree.insert('c', 2);
    rbtree.insert('e', 3);
    rbtree.insert('h', 4);
    rbtree.insert('l', 5);
    rbtree.insert('m', 6);
    rbtree.insert('p', 7);
    rbtree.insert('r', 8);
    rbtree.insert('s', 9);
    rbtree.insert('x', 10);
    rbtree.print();
    std::cout << "------DELETE------\n";
    // rbtree.deleteMin();
    // rbtree.deleteMin();
    // rbtree.deleteMin();
    // rbtree.deleteMax();
    // rbtree.deleteMax();
    // rbtree.deleteMax();
    rbtree.deleteNode('e');
    rbtree.deleteNode('r');
    // rbtree.deleteNode('k');
    rbtree.print();

    auto result{rbtree.at('h')};
    if(result)
        std::cout << *result << '\n';

    return 0;
}
