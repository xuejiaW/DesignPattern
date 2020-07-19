// 缺失的第一个正数

// 难度：困难

// Tags
// array

// 给你一个未排序的整数数组，请你找出其中没有出现的最小的正整数。

// 输入: [1,2,0]
// 输出: 3

// 示例 2:
// 输入: [3,4,-1,1]
// 输出: 2

// 示例 3:
// 输入: [7,8,9,11,12]
// 输出: 1

// 提示：
// 你的算法的时间复杂度应为O(n)，并且只能使用常数级别的额外空间。

#include "parser.h"
#include "debug.h"

int firstMissingPositive(vector<int> &nums);

void TestFirstMissing()
{
    vector<int> nums{1, 2, 0};
    cout << "result is " << firstMissingPositive(nums);
}

int firstMissingPositive(vector<int> &nums)
{
    int numsSize = nums.size();

    for (int i = 0; i != numsSize; ++i)
    {
        while (nums[i] > 0 && nums[i] <= numsSize && nums[i] != nums[nums[i] - 1])
            swap(nums[i], nums[nums[i] - 1]);
    }

    for (int i = 0; i != numsSize; ++i)
    {
        if (nums[i] != i + 1)
            return (i + 1);
    }

    return numsSize + 1;
}
