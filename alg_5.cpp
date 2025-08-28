#include <iostream>
#include <vector>
// Shell Sort (Enhanced InsertionSort)
// O(N^1.5)

void shellSort(std::vector<int>& arr) 
{
    std::size_t n = arr.size();
    std::size_t knuth{};
    // knuth GAP is better than n/2 GAP
    for (;knuth < n/3;)
        knuth = 3 * knuth + 1; // better gap
    // 从 gap = n/2 开始，逐渐减小到 1
    for (std::size_t gap = n / 2; gap > 0; gap /= 2) // if you want to use knuth here, you just need modify the third parameter as gap /= 3
    {
        // 对每个 gap 进行插入排序
        for (std::size_t i = gap; i < n; ++i)
        {
            int temp = arr[i]; // pop out
            std::size_t j = i; // blank = i

            // 向前按 gap 步长插入排序    // THE FIRST IS DETERMINED BY THE OUTER LOOP AND THE FOLLOWING ARE DETERMINED BY THE INDER LOOP
            while (j >= gap && arr[j - gap] > temp) // <4,0> <5,1> <6,2> <7,3> GAP=4 ; <2,0> <3,1> <4,2,0> <5,3,1> <6,4,2,0> <7,5,3,1> GAP=2; <1,0> <2,1,0> <3,2,1,0> ... GAP=1
            {
                arr[j] = arr[j - gap]; // move the greater one to fill the blank
                j -= gap;              // blank jump gap steps
            }

            arr[j] = temp; // insert to the right position
        }

        // 打印当前 gap 排序后的数组
        std::cout << "After gap = " << gap << ": ";
        for (int num : arr)
            std::cout << num << " ";
        std::cout << "\n";
    }
}

int main() {
    std::vector<int> arr = {8, 5, 3, 7, 6, 2, 4, 1};

    std::cout << "Original array:\n";
    for (int num : arr) std::cout << num << " ";
    std::cout << "\n\n";

    shellSort(arr);

    std::cout << "\nSorted array:\n";
    for (int num : arr) std::cout << num << " ";
    std::cout << "\n";

    return 0;
}
