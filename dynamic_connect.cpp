#include <iostream>
#include <vector>
#include <map>
// Union_Find
const int N = 1000;
int parent[N];
int size[N];

// 初始化
void init(int n)
{
    for (int i = 0; i < n; ++i) parent[i] = i;
    for (int i = 0; i < n; ++i) size[i] = 1;
}

// 查找代表元素
// we just made a tree
// OUR find() don't need to traversal the whole array (only find the root)
int find(int x)
{
    if (parent[x] != x) // find its root
        parent[x] = find(parent[x]); // 路径压缩 (all the nodes which have the same root, we make them toward to it)

    return parent[x];
}

// make connection
void unite(int x, int y)
{
    int fx = find(x), fy = find(y);
    if(fx == fy) return; // if x and y have the same root, return

    // merge connections
    if(size[fx] < size[fy]) // if tree `fx` is smaller than `fy`
    {
        parent[fx] = fy; // we make the smaller one's root to the greater one
        size[fy] += size[fx]; // and change the size of greater one at the same time
    }
    else // otherwise (fx is equal or greater than fy)
    {
        parent[fy] = fx;
        size[fx] += size[fy];
    }
}

// 获取所有连通块
std::map<int, std::vector<int>> getConnectedComponents(int n)
{
    std::map<int, std::vector<int>> components;
    for (int i = 0; i < n; ++i)
    {
        int root = find(i);
        components[root].push_back(i);
    }
    return components;
}

int main()
{
    init(5);
    unite(0, 1);
    unite(2, 3);
    unite(1, 2);
    auto components{getConnectedComponents(5)};
    for(const auto& [vertex,connections]:components)
    {
        std::cout << vertex << ": ";
        for(auto connectionNode:connections)
            std::cout << connectionNode << ' ';
        std::cout << '\n';
    }
    return 0;
}
