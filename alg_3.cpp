#include <iostream>
#include <vector>
// Insertion Sort


int main()
{
    std::vector arr{4, 2, 7, 1, 3};
    for (std::size_t index{1},blank{}; index < std::size(arr); ++index) // pop-out -> move -> insertion
    {
        int temp{arr[index]}; // pop the value we want to compare out first,
        blank = index; // and this position is empty
        // for (std::size_t pre_move{blank-1}; ; --pre_move) // start to compare the elements before the empty place
        // {
        //     if (arr[pre_move] > temp) // if the element is bigger
        //     {
        //         arr[blank] = arr[pre_move]; // this element moves to the right (fill the empty)
        //         --blank; // and blank goes to the left naturally
        //     }
        //     if (blank == 0 || pre_move == 0) // if the blank reaches the left edge or the element we just compared is the most left element in the array
        //         break;                       // which means no value for comparing left, so we break the loop
        // }
        for (; blank > 0 && arr[blank-1] > temp;) // if the blank didn't reach the very left and the number before the blank is bigger than our value
        {
            arr[blank] = arr[blank-1]; // move the value ahead to occupy the blank (move the to the right)
            --blank; // blank move to the left side
        }
        arr[blank] = temp; // insert the value that we popped out at the very begining to the blank
        // Go to the next round
    }
    
    for(auto num:arr)
        std::cout << num << ' ';
    std::cout << '\n';

    return 0;
}
