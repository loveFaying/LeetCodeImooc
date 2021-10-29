#include <iostream>
#include <vector>

using namespace std;

/// 70. Climbing Stairs
/// https://leetcode.com/problems/climbing-stairs/description/
class Solution {

private:
    vector<int> memo;

    int calcWays(int n){

        if(n == 0 || n == 1)
            return 1;

        if(memo[n] == -1)
            memo[n] = calcWays(n - 1) + calcWays(n - 2);

        return memo[n];
    }

public:

    /// 记忆化搜索
    /// 时间复杂度: O(n)
    /// 空间复杂度: O(n)
    int climbStairs(int n) {

        memo = vector<int>(n + 1, -1);
        return calcWays(n);
    }

    /// 动态规划
    /// 时间复杂度: O(n)
    /// 空间复杂度: O(n)
    int climbStairs2(int n) {

        vector<int> memo(n + 1, -1);
        memo[0] = 1;
        memo[1] = 1;
        for(int i = 2 ; i <= n ; i ++)
            memo[i] = memo[i - 1] + memo[i - 2];
        return memo[n];
    }
};

int main() {

    cout << Solution().climbStairs(10) << endl;
    cout << Solution().climbStairs2(10) << endl;

    return 0;
}