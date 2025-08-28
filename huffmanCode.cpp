#include <iostream>
#include <memory>
#include <utility>
#include <queue>
#include <string>
#include <unordered_map>

struct HuffmanNode
{
    char ch;
    int freq;
    std::unique_ptr<HuffmanNode> left;
    std::unique_ptr<HuffmanNode> right;

    HuffmanNode(char c, int f)
        : ch{c}, freq{f}, left{nullptr}, right{nullptr}
    {
    }
    HuffmanNode(int f)
        : ch{'\0'}, freq{f}, left{nullptr}, right{nullptr}
    {
    }
};

// 比较器：优先队列使用小顶堆
struct Compare
{
    bool operator()(const std::unique_ptr<HuffmanNode> &a, const std::unique_ptr<HuffmanNode> &b) const
    {
        return a->freq > b->freq; // 小的优先 // greater's specification, the Greater ones sink
    }
};

// 3. 遍历生成编码
void buildCode(const HuffmanNode *node, std::string code, std::unordered_map<char, std::string> &table)
{
    if (!node)
        return;
    if (!node->left && !node->right)
    {
        if (node->ch != '\0') // 确保是叶子节点且有有效字符
        {
            table[node->ch] = code;
        }
        return;
    }
    buildCode(node->left.get(), code + "0", table); // dive to the bottom and return
    buildCode(node->right.get(), code + "1", table);
}

int main()
{
    using NodePtr = std::unique_ptr<HuffmanNode>;
    std::priority_queue<NodePtr, std::vector<NodePtr>, Compare> minHeap;
    std::unordered_map<char, int> frequencyMap{{'a', 1}, {'b', 4}, {'c', 9}};

    // 1. 初始化：统计频率后构造叶子节点
    for (auto [c, freq] : frequencyMap)
    {
        minHeap.push(std::make_unique<HuffmanNode>(c, freq)); // a b c
    }

    /*  Huffman Encoding */ // Use minHeap(MinPQ), build this from the bottom to the top, 2 Node were extracted AT ONCE. Until Only the ROOT Node left in the PQ
    //
    //               <14>
    //              0/  \1
    //             <5>  <'c'>
    //            0/ \1
    //           <a> <b>
    // 
    // a:00, b:01, c:1
    
    // 2. 构建霍夫曼树
    while (minHeap.size() > 1)
    {
        auto left = std::move(const_cast<NodePtr &>(minHeap.top())); minHeap.pop();
        auto right = std::move(const_cast<NodePtr &>(minHeap.top())); minHeap.pop();

        NodePtr parent{std::make_unique<HuffmanNode>(left->freq + right->freq)};
        parent->left  = std::move(left);
        parent->right = std::move(right);

        minHeap.push(std::move(parent));
    }

    // 3. 生成编码表
    std::unordered_map<char, std::string> codeTable;
    if (!minHeap.empty())
        buildCode(minHeap.top().get(), "", codeTable);

    // 打印编码表
    for (const auto &[ch, code] : codeTable)
        std::cout << ch << ": " << code << '\n';

    return 0;
}
