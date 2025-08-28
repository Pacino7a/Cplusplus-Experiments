#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

const std::size_t g_INSERTION_SORT_CUTOFF = 15;

// 插入排序：用于小数组
void insertionSort(std::vector<int>& arr, std::size_t lo, std::size_t hi)
{
    for (std::size_t i = lo + 1; i <= hi; ++i)
    {
        int key = arr[i]; // pop-out
        std::size_t j = i; // blank
        while (j > lo && arr[j - 1] > key) // when lo == 0, j >= lo will cause trouble
        {
            arr[j] = arr[j - 1]; // if the element before the blank is greater, move it to the right
            --j; // blank goes to the left
        }
        arr[j] = key; // when no element is greater than the element popped out before or we have reached the left edge,
                      //  fill the current position of blank with the popped value
    }
}

// 归并操作：将 src[lo..mid] 和 src[mid+1..hi] 合并到 dest[lo..hi]
// `src` the latest merged result, `dest` the array to be updated with `src`
void merge(const std::vector<int>& src, std::vector<int>& dest, std::size_t lo, std::size_t mid, std::size_t hi)
{
    std::size_t i = lo, j = mid + 1;  // split the array as two parts
    for (std::size_t k = lo; k <= hi; ++k) // go through two parts
    {
        if (i > mid) dest[k] = src[j++]; // left runs out
        else if (j > hi) dest[k] = src[i++]; // right runs out
        else if (src[j] < src[i]) dest[k] = src[j++]; // right part's current element is smaller (extract right to dest)
        else dest[k] = src[i++]; // left part's current element is smaller (extract left to dest)
    }
}

// 主递归函数：src 为读源，dest 为写目标
void mergeSort(std::vector<int>& src, std::vector<int>& dest, std::size_t lo, std::size_t hi) 
{
    if (hi - lo <= g_INSERTION_SORT_CUTOFF) 
    {
        insertionSort(dest, lo, hi); // dest is always the target we want to update, whatever it actually is
        return;
    }

    std::size_t mid = lo + (hi - lo) / 2;

    // we need update the src to take the advantage of recursion,
    // otherwise we failed the recursion, this will become a Brute force solution

    // EXCHANGE the src and dest (2 buffer) is a good solution for updating
    // to replace (src -> dest -> src) updating (time costy)
    mergeSort(dest, src, lo, mid);     // 注意参数顺序反转：dest ↔ src, reverse per layer
    mergeSort(dest, src, mid + 1, hi);

    // 优化：已经有序则跳过 merge
    if (src[mid] <= src[mid + 1]) // src is always the lastest update
    {
        std::copy(src.begin() + static_cast<int>(lo), src.begin() + static_cast<int>(hi) + 1, dest.begin() + static_cast<int>(lo));
        return;
    }

    merge(src, dest, lo, mid, hi); // we use the recursion result (Updated src) to merge and get the Sorted result (update dest)
}

// 对外接口函数
void optimizedMergeSort(std::vector<int>& arr) 
{
    if (arr.empty()) return;
    std::vector<int> aux{arr}; // 拷贝一份作为初始 src
    mergeSort(aux, arr, 0, arr.size() - 1);
}

void mergeNative(std::vector<int>& src, std::vector<int>& dest,std::size_t lo, std::size_t mid, std::size_t hi)
{    
    // Traditional way of Merge. 
    // the latest Sorting Result is always in DEST
    // You need to update the SRC everytime before you merge

    // we copy a part of dest that we need, instead of the whole array
    // so we minus `lo` for j to get right index.

    src = std::vector(dest.begin() + static_cast<int>(lo), dest.begin() + static_cast<int>(hi) + 1);
    std::size_t i{};
    std::size_t j{mid - lo + 1}; // split 'aux' into two parts

    for (std::size_t k = lo; k <= hi; ++k) // go through two parts (k doesn't need to change)
    {
        if (i > mid-lo) dest[k] = src[j++]; // left runs out
        else if (j > hi-lo) dest[k] = src[i++]; // right runs out
        else if (src[j] < src[i]) dest[k] = src[j++]; // right part's current element is smaller (extract right to dest)
        else dest[k] = src[i++]; // left part's current element is smaller (extract left to dest)
    }
}

void mergeOptimized(std::vector<int>& src, std::vector<int>& dest,std::size_t lo, std::size_t mid, std::size_t hi)
{
    // Optimized Merge (Both sides should be local orderd (Ascending))
    for (std::size_t i{1}; i < std::size(dest); ++i)
    {
        if(dest[i-1] > dest[i])
        {
            std::cout << "Sorry, your dest is Not Local Ordered!\n";
            return;
        }
    }

    // No need for checking the run-out situation
    for (std::size_t k{lo}; k <= mid; ++k)
    {
        src[k] = dest[k];
    }
    for (std::size_t k{hi},l{mid+1}; k > mid; --k,++l) // reverse
    {
        src[l] = dest[k];
    }

    // e.g dest: 3,5,7,|| 2,8,9 -> src: 3,5,7,9,8,2
    //                             (lo)i^         ^j(hi)
    std::size_t i{lo};
    std::size_t j{hi};
    // both sides start from the smallest element
    // and both pointer are heading to the biggest element in that array
    // which means the Collision of the two pointers will take place eventually.

    for (std::size_t k{lo}; k <= hi; ++k)
    {
        if(src[j] < src[i])
            dest[k] = src[j--];
        else
            dest[k] = src[i++];
    }
}

void mergeSortBU(std::vector<int>& arr)
{
    if(arr.empty()) return;
    bool updateFromAux{true};
    bool roughSorted{false};

    std::vector aux{arr};
    for (std::size_t size{1}; size<arr.size(); size *= 2, roughSorted = true) // we set size here (2 <1, 1>, 4 <2, 2>, 8 <4,4>)
    {
        for (std::size_t lo{0}; lo < arr.size() - size; lo += 2 * size) // The loop continue when there is capacity for 2*size
        {
            std::size_t mid{lo + size - 1};
            std::size_t hi{std::min(lo + 2 * size - 1, arr.size() - 1)};
            if(roughSorted && aux[mid] <= aux[mid + 1])
                continue;

            if(updateFromAux) // update arr
                merge(aux, arr, lo, mid, hi);
            else // after arr has been updated, arr->aux
                merge(arr, aux, lo, mid, hi); // if the final result has been saved in aux (current flag will be reversed)
        }
        updateFromAux = !updateFromAux; // updateFromAux is needed after one layer has been sort, NOT A SINGLE SORT!
    }
    if(updateFromAux) // if aux is the latest result
        arr = aux;
}

// merge a list
std::list<int> mergeLists(std::list<int>& a, std::list<int>& b) // 2 small list merge to a big one
{
    std::list<int> result;

    auto it1 = a.begin();
    auto it2 = b.begin();

    for( ;it1 != a.end() && it2 != b.end();)
    {
        if (*it1 <= *it2)
            result.splice(result.end(), a, it1++);
        else
            result.splice(result.end(), b, it2++);
    }

    // 把剩下的元素拼接到 result 末尾
    result.splice(result.end(), a);
    result.splice(result.end(), b);

    return result;
}

void mergeSortList(std::list<int>& lst)
{
    if (lst.size() <= 1) return;

    std::list<std::list<int>> work; // save unsorted list (1,2,4,..)
    for (auto& val : lst)
    {
        std::list<int> single{val}; // split one by one first
        work.push_back(std::move(single)); // no copy here
    }

    while (work.size() > 1) // just a queue, when the queue only has one, sort over
    {
        // extract two small list (maybe single, couple, triple,...)
        std::list<int> a = std::move(work.front()); work.pop_front();
        std::list<int> b = std::move(work.front()); work.pop_front(); 

        std::list<int> merged = mergeLists(a, b); // if a and b are single list, then merged will be a couple one
        work.push_back(std::move(merged)); // we push this after all the single list and go to the next round
    }

    lst = std::move(work.front());
}

// 测试
int main() {
    std::vector data{8, 3, 1, 7, 0, 10, 2, 5, 4, 6, 9, 11, 13, 12, 14, 15};
    // optimizedMergeSort(data); // recursion (Top Down) (8->4->2->1)
    mergeSortBU(data); // Bottom Up to the top (2->4->8)

    for (int x : data)
        std::cout << x << ' ';

    std::cout << '\n';

    std::list lst{8, 3, 1, 7, 0, 10, 2, 5, 4, 6, 9, 11, 13, 12, 14, 15};
    mergeSortList(lst);

    for (int x : lst) std::cout << x << ' ';
    std::cout << '\n';

    return 0;
}
