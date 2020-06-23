// 0～n-1中缺失的数字

// 难度：简单

// Tags:
// array | binary search

// 一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0～n-1之内。在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字。

//  

// 示例 1:

// 输入: [0,1,3]
// 输出: 2
// 示例 2:

// 输入: [0,1,2,3,4,5,6,7,9]
// 输出: 8

#include <vector>
#include <iostream>

using namespace std;

int missingNumber(vector<int> &nums);

void TestMissingNumber()
{
    vector<int> nums{1};
    int result = missingNumber(nums);
    cout << "result is " << result << endl;
}

int missingNumber(vector<int> &nums)
{
    if (nums.empty())
        return -1;

    if (nums.size() == 1 && nums[0] == 0) // handle for input {0}
        return 1;

    int begin = 0, end = nums.size() - 1, middle;

    while (begin < end)
    {
        middle = (begin + end) / 2;
        if (middle == nums[middle])
            begin = middle + 1;
        else
            end = middle;
    }

    return begin;
}