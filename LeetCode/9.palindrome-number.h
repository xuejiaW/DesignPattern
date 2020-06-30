// 回文数

// 难度：简单

// Tags:
// math

// 判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。

// 示例 1:

// 输入: 121
// 输出: true
// 示例 2:

// 输入: -121
// 输出: false
// 解释: 从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。
// 示例 3:

// 输入: 10
// 输出: false
// 解释: 从右向左读, 为 01 。因此它不是一个回文数。
// 进阶:

// 你能不将整数转为字符串来解决这个问题吗？

#include "debug.h"
#include <string>

bool isPalindrome(int x);

void TestIsPalindrome()
{
    bool result = isPalindrome(10);
    cout << result << endl;
}

// // Version: string
// bool isPalindrome(int x)
// {
//     if (x < 0)
//         return false;

//     string num = to_string(x);
//     int left = 0, right = num.size() - 1;
//     while (left <= right)
//     {
//         if (num[left] != num[right])
//             return false;
//         left++;
//         right--;
//     }
//     return true;
// }

// // Version: revert number
bool isPalindrome(int x)
{
    // This method should care about the zero situation
    if (x < 0 || (x % 10 == 0 && x != 0))
        return false;

    int halfRevertNum = 0;
    while (x > halfRevertNum)
    {
        halfRevertNum *= 10;
        halfRevertNum += x % 10;
        x /= 10;
    }

    // oven digit situation and odd digit situation
    return x == halfRevertNum || x == halfRevertNum / 10;
}