#include <iostream>
#include <functional>
#include <array>
#include <vector>
#include <iomanip>
#include <algorithm>
#define INITIAL_VALUE 200000

// Find the maximum benefit 


bool checkDecreasing(const std::vector<int>& arr)
{
    int count{1};
    for (auto end{arr.end()};;--end)
    {
        auto min{std::min_element(arr.begin(), end)};
        if(min == arr.end() - count)
        {
            ++count;
            if(min != arr.begin())
                continue;
            else
                return true;
        }
        else
            return false;
    }
}

int getMaxValue(std::vector<int>& arr)
{
    if(checkDecreasing(arr))
    {
        std::cout << "Data Monotonically Decreasing.\n";
        int maxv{arr[1] - arr[0]};
        for (size_t i = 1; i < std::size(arr)-1; ++i) // because we need use index(i+1) so our i can't beyond <size() - 2>, aka i < size - 1
        {
            int cur_result{arr[i + 1] - arr[i]};
            if(cur_result > maxv)
                maxv = cur_result;
        }
        return maxv;
    }
    else
    {
        for (int maxv{};;)
        {
            auto min{std::min_element(arr.begin(), arr.end())};

            if (min == arr.end() - 1)
            {
                arr.erase(min);
                continue;
            }
            else    
            {
                auto max{std::max_element(min, arr.end(), [](int a, int b)
                                        { return a < b; })};

                maxv = (*max) - (*min);

                return maxv;
            }
        }
    }
}

int main()
{
    // constexpr std::array data{std::to_array({6, 5, 3, 1, 3, 4, 3})};
    // std::vector data{6, 5, 3, 1, 3, 4, 3};
    // std::vector data2{3, 4, 3, 2};
    // std::vector data3{8, 5, 4, 1};

    // int maxv {getMaxValue(data)};
    // int maxv2{getMaxValue(data2)};
    // int maxv3{getMaxValue(data3)};

    // std::cout << "Max Value:" << std::right << std::setw(3) << maxv << '\n';
    // std::cout << "Max Value:" << std::right << std::setw(3) << maxv2 << '\n';
    // std::cout << "Max Value:" << std::right << std::setw(3) << maxv3 << '\n';

    // answer
    int n;
    std::cout << "How many values you got: ";
    std::cin >> n;
    int maxValue{-INITIAL_VALUE};
    // int minValue{};
    for (int i{0},value{},min{}; i < n; ++i)
    {
        std::cout << "Value#" << i + 1 << ": ";
        std::cin >> value;
        if(i == 0)
        {    
            min = value;
            continue;
        }
        maxValue = std::max(maxValue, value - min);
        min = std::min(min, value);
    }
    std::cout << "Max Value:" << maxValue << '\n';

    return 0;
}
