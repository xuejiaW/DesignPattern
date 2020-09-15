// 正则表达式匹配

// 难度：困难

// Tags
// string | dynamic-programming

// 给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

// '.' 匹配任意单个字符
// '*' 匹配零个或多个前面的那一个元素
// 所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

// 说明:

// s 可能为空，且只包含从 a-z 的小写字母。
// p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。

// 示例 1:
// 输入:
// s = "aa"
// p = "a"
// 输出: false
// 解释: "a" 无法匹配 "aa" 整个字符串。

// 示例 2:
// 输入:
// s = "aa"
// p = "a*"
// 输出: true
// 解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。

// 示例 3:
// 输入:
// s = "ab"
// p = ".*"
// 输出: true
// 解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。

// 示例 4:
// 输入:
// s = "aab"
// p = "c*a*b"
// 输出: true
// 解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。

// 示例 5:
// 输入:
// s = "mississippi"
// p = "mis*is*p*."
// 输出: false

#include "parser.h"
#include "debug.h"

bool isMatch(string s, string p)
{
    int sSize = s.size(), pSize = p.size();

    vector<vector<int>> dp(sSize + 1, vector<int>(pSize + 1, 0));
    dp[0][0] = 1;
    for (int i = 0; i <= sSize; ++i)
    {
        for (int j = 1; j <= pSize; ++j)
        {
            if (p[j - 1] == '.')
                dp[i][j] = i != 0 && dp[i - 1][j - 1];
            else if (p[j - 1] == '*')
                // match zero || (match one)
                dp[i][j] = dp[i][j - 2] || (i != 0 && (dp[i - 1][j]) && (p[j - 2] == '.' || s[i - 1] == p[j - 2]));
            else
                dp[i][j] = i != 0 && dp[i - 1][j - 1] && s[i - 1] == p[j - 1];
        }
    }

    return dp[sSize][pSize];
}
