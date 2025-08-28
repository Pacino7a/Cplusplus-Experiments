#include <iostream>
#include <vector>
#include <queue> // priority queue
// Priority Queue
class MaxPQ // i.e.[4,3,2,1];  MinPQ == [1,2,3,4]
{
public:
    explicit MaxPQ() = default;
    explicit MaxPQ(int maxN)
    {
        m_pq.reserve(static_cast<std::size_t>(maxN) + 1); // we don't use the first element for index computing convenience
        m_pq.emplace_back(0); // set the first element 0
    }

    void insert(int value);
    int deleteMax();
    bool isEmpty() const { return m_realLength == 0; }
    std::size_t size() const { return m_realLength; }
private:
    std::vector<int> m_pq{}; // e.g. k is current vertex, k/2 is its parent, 2k and 2k+1 are its children
    // real length equals to [size()-1]
    std::size_t m_realLength{0}; // this saves [the index of the last element] becaues we have N+1 elements and it is also [the real length] not include the first `0`
    bool less(std::size_t i, std::size_t j) const { return m_pq[i] <= m_pq[j]; }
    void swim(std::size_t k);
    void sink(std::size_t k);
};

// swim the BIGGER elements to the surface(top) of the container
void MaxPQ::swim(std::size_t k)
{
    for (;k>1 && less(k/2,k);) // (e.g. The parent node of [4] and [5] is [2]) /// [1] don't have parent
    {
        std::swap(m_pq[k/2], m_pq[k]); // we do the swap when the parent is less than its child
        k /= 2; // keep tracking (back)
    }
}

// for MaxPQ we make the SMALLER elements sink to the bottom of the container
// MinPQ is the opposite, which sinks the BIGGER ones to the bottom
void MaxPQ::sink(std::size_t k)
{
    for (;k <= m_realLength/2;) // if the children of current vertex exists
    {
        std::size_t child{2 * k};
        if(child < m_realLength && less(child,child+1)) ++child; // make sure not goes out of the bound and find the biggest child
        if(!less(k,child)) break; // if current vertex is NOT smaller than its children, we're done.
        std::swap(m_pq[k], m_pq[child]); // otherwisee we swap them
        // STL implementation
        // if (std::less(k, 2*k)) <-- if you use stl-MaxPQ, you need use this compare
        //      std::swap(m_pq[k], m_pq[2*k]);
        // else
        //      break;
        k = child; // keep tracking (forward)
    }
}

void MaxPQ::insert(int value)
{
    m_pq.emplace_back(value);
    swim(++m_realLength);
}

int MaxPQ::deleteMax()
{
    int max{m_pq[1]}; // the first one is the biggest one
    std::swap(m_pq[1], m_pq[m_realLength--]); // this will not across the bound
    m_pq[m_realLength + 1] = 0; // set the deleted element null
    sink(1);
    if(m_realLength > 0 && m_realLength == (m_pq.size() - 1) / 4)
    {
        m_pq.resize(m_pq.size() / 2);
    }
    return max;
}

// for sorting (MAXPriQueue)
void sink(std::vector<int>& array, std::size_t currentIndex, std::size_t endIndex)
{
    for (;currentIndex <= endIndex / 2;)
    {
        std::size_t child{2 * currentIndex}; // not sure this is its child
        if(child < endIndex && array[child] < array[child+1])// make sure we don't cross the bound to find the biggest child
            ++child; 
        if(array[child] < array[currentIndex]) // if current Vertex is bigger than its biggest child, we done
            return;
        std::swap(array[currentIndex], array[child]); // otherwise, we exchange the position of them
        currentIndex = child; // and keep tracking until sink to the right place
    }
}

// Good sort (O(NlogN))
void heapSort(std::vector<int>& array)
{
    std::size_t length{array.size()}; // real length
    array.emplace_back(0);
    std::swap(array[0], array[array.size() - 1]); // fill one

    for(std::size_t k{length / 2}; k >= 1; --k)
       sink(array, k, length); // make Maxheaps, smaller elements are placed in the last (Phrase ONE)
    
    for(;length > 1;) // find the first maximum, the second, the third,..., and send them to the end (Phrase TWO)
    {
       std::swap(array[1], array[length--]);// move the maximum of current array to the very end (Descending -> Ascending)
       sink(array, 1, length); // and like selectionSort, find an new maximum in a new area(cut one)
    }
    array.erase(array.begin());
}

// good find method (10 out 1,000,000,000 is also efficient), i.e.TopM <if you want to get Top10 you need use "greater" otherwise "less"
void findTop(std::vector<int>& data, std::size_t k)
{
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap{};

    for(auto num:data)
    {
        if(minHeap.size() < k)
            minHeap.push(num);
        else if(num > minHeap.top()) // greater than the smallest in this temporal heap
        {
            minHeap.pop();
            minHeap.push(num);
        }
    }

    for (;!minHeap.empty(); minHeap.pop())
        std::cout << minHeap.top() << ' ';
    std::cout << '\n';
}

int main()
{
    // MaxPQ maxPQ{9};
    // maxPQ.insert(7);
    std::vector array1{7, 8, 5, 4, 7, 3, 2, 1, 0, 7, 9, 6};
    for(auto num:array1)
        std::cout << num << ' ';
    std::cout << '\n';

    heapSort(array1);
    for(auto num:array1)
        std::cout << num << ' ';
    std::cout << '\n';

    findTop(array1, 4);

    return 0;
}
