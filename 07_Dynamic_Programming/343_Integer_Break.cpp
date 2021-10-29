#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

/// 343. Integer Break
/// https://leetcode.com/problems/integer-break/description/
class Solution {

private:
    /* integerBreak */
    int max3(int a, int b, int c){
        return max(a, max(b, c));
    }

    // 将n进行分割(至少分割两部分), 可以获得的最大乘积
    int breakInteger(int n){

        if(n == 1)
            return 1;

        int res = -1;
        for(int i = 1 ; i <= n - 1 ; i ++)
            res = max3(res, i * (n - i), i * breakInteger(n - i));
        return res;
    }

    /* integerBreak2 */
    // 将n进行分割(至少分割两部分), 可以获得的最大乘积
    vector<int> memo;

    int breakInteger2(int n){

        if(n == 1)
            return 1;

        if(memo[n] != -1)
            return memo[n];

        int res = -1;
        for(int i = 1 ; i <= n - 1 ; i ++)
            res = max3(res, i * (n - i) , i * breakInteger2(n - i));
        memo[n] = res;
        return res;
    }

public:

    /// 暴力搜索
    /// 在Leetcode中提交这个版本的代码会超时! (Time Limit Exceeded)
    /// 时间复杂度: O(n^n)
    /// 空间复杂度: O(n)
    int integerBreak(int n) {
        assert(n >= 1);
        return breakInteger(n);
    }

    /// 记忆化搜索
    /// 时间复杂度: O(n^2)
    /// 空间复杂度: O(n)
    int integerBreak2(int n) {
        assert(n >= 1);
        memo.clear();
        for(int i = 0 ; i < n + 1 ; i ++)
            memo.push_back(-1);
        return breakInteger2(n);
    }

    /// 动态规划
    /// 时间复杂度: O(n^2)
    /// 空间复杂度: O(n)
    int integerBreak3(int n) {

        assert(n >= 1);

        // memo[i] 表示将数字i分割(至少分割成两部分)后得到的最大乘积
        vector<int> memo(n + 1, -1);

        memo[1] = 1;
        for(int i = 2 ; i <= n ; i ++)
            // 求解memo[i]
            for(int j = 1 ; j <= i - 1 ; j ++)
                memo[i] = max3(memo[i], j * (i - j), j * memo[i - j]);

        return memo[n];
    }
};

int main() {

    cout << Solution().integerBreak(2) << endl;
    cout << Solution().integerBreak(10) << endl;

    cout << Solution().integerBreak2(2) << endl;
    cout << Solution().integerBreak2(10) << endl;

    cout << Solution().integerBreak3(2) << endl;
    cout << Solution().integerBreak3(3) << endl;
    cout << Solution().integerBreak3(4) << endl;
    cout << Solution().integerBreak3(10) << endl;

    return 0;
}