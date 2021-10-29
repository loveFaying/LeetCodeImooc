#include <iostream>
#include <vector>

using namespace std;

/// 198. House Robber
/// https://leetcode.com/problems/house-robber/description/
class Solution {

private:
    /*rob*/
    // memo[i] 表示考虑抢劫 nums[i...n) 所能获得的最大收益
    vector<int> memo;

    // 考虑抢劫nums[index...nums.size())这个范围的所有房子
    int tryRob(const vector<int> &nums, int index){

        if(index >= nums.size())
            return 0;

        if(memo[index] != -1)
            return memo[index];

        int res = 0;
        for(int i = index ; i < nums.size() ; i ++)
            res = max(res, nums[i] + tryRob(nums, i + 2));
        memo[index] = res;
        return res;
    }

    /*rob3*/
    // memo[i] 表示考虑抢劫 nums[0...i] 所能获得的最大收益

    // 考虑抢劫nums[0...index]这个范围的所有房子
    int tryRob3(const vector<int> &nums, int index){

        if(index < 0)
            return 0;

        if(memo[index] != -1)
            return memo[index];

        int res = 0;
        for(int i = 0 ; i <= index ; i ++)
            res = max(res, nums[i] + tryRob3(nums, i - 2));
        memo[index] = res;
        return res;
    }

    /*rob5*/
    // memo[i] 表示考虑抢劫 nums[0...i] 所能获得的最大收益
    // 考虑抢劫nums[index...nums.size())这个范围的所有房子
    int tryRob5(const vector<int> &nums, int index){

        if(index >= nums.size())
            return 0;

        if(memo[index] != -1)
            return memo[index];

        // 或者当前房子放弃, 从下一个房子开始考虑
        // 或者抢劫当前的房子, 从i+2以后的房子开始考虑
        return memo[index] = max(tryRob5(nums, index + 1),
                                 nums[index] + tryRob5(nums, index + 2));
    }

    /*rob7*/
    // memo[i] 表示考虑抢劫 nums[0...i] 所能获得的最大收益

    // 考虑抢劫nums[0...index]这个范围的所有房子
    int tryRob7(const vector<int> &nums, int index){

        if(index < 0)
            return 0;

        if(memo[index] != -1)
            return memo[index];

        // 或者当前房子放弃, 考虑[0...index-1]的所有房子
        // 或者抢劫当前的房子, 考虑[0...index-2]的所有房子
        return memo[index] = max(tryRob7(nums, index - 1),
                                 nums[index] + tryRob7(nums, index - 2));
    }

public:
    /// 记忆化搜索
    /// 时间复杂度: O(n^2)
    /// 空间复杂度: O(n)
    int rob(vector<int>& nums) {

        memo.clear();
        for(int i = 0 ; i < nums.size() ; i ++)
            memo.push_back(-1);
        return tryRob(nums, 0);
    }

    /// 动态规划
    /// 时间复杂度: O(n^2)
    /// 空间复杂度: O(n)
    int rob2(vector<int>& nums) {

        int n = nums.size();

        if(n == 0)
            return 0;

        // memo[i] 表示考虑抢劫 nums[i...n) 所能获得的最大收益
        vector<int> memo(n, 0);
        memo[n - 1] = nums[n - 1];
        for(int i = n - 2 ; i >= 0 ; i --)
            for (int j = i; j < n; j++)
                memo[i] = max(memo[i],
                              nums[j] + (j + 2 < n ? memo[j + 2] : 0));

        return memo[0];
    }

    /// 记忆化搜索, 改变状态定义
    /// 时间复杂度: O(n^2)
    /// 空间复杂度: O(n)
    int rob3(vector<int>& nums) {

        memo.clear();
        for(int i = 0 ; i < nums.size() ; i ++)
            memo.push_back(-1);
        return tryRob3(nums, nums.size() - 1 );
    }

    /// 动态规划, 改变状态定义
    /// 时间复杂度: O(n^2)
    /// 空间复杂度: O(n)
    int rob4(vector<int>& nums) {

        int n = nums.size();
        if( n == 0 )
            return 0;

        // memo[i] 表示考虑抢劫 nums[0...i] 所能获得的最大收益
        vector<int> memo(n, 0);
        memo[0] = nums[0];
        for(int i = 1 ; i < n ; i ++)
            for (int j = i; j >= 0; j--)
                memo[i] = max(memo[i],
                              nums[j] + (j - 2 >= 0 ? memo[j - 2] : 0));

        return memo[n-1];
    }

    /// 记忆化搜索, 优化状态转移
    /// 时间复杂度: O(n)
    /// 空间复杂度: O(n)
    int rob5(vector<int>& nums) {

        memo.clear();
        for(int i = 0 ; i < nums.size() ; i ++)
            memo.push_back(-1);
        return tryRob5(nums, 0);
    }

    /// 动态规划, 优化状态转移
    /// 时间复杂度: O(n)
    /// 空间复杂度: O(n)
    int rob6(vector<int>& nums) {

        int n = nums.size();

        if(n == 0)
            return 0;

        // memo[i] 表示考虑抢劫 nums[i...n) 所能获得的最大收益
        vector<int> memo(n, 0);
        memo[n - 1] = nums[n - 1];
        for(int i = n - 2 ; i >= 0 ; i --)
            // 或者当前房子放弃, 从下一个房子开始考虑
            // 或者抢劫当前的房子, 从i+2以后的房子开始考虑
            memo[i] = max(memo[i + 1],
                          nums[i] + (i + 2 < n ? memo[i + 2] : 0));

        return memo[0];
    }

    /// 记忆化搜索, 改变状态定义, 优化转移方程
    /// 时间复杂度: O(n)
    /// 空间复杂度: O(n)
    int rob7(vector<int>& nums) {

        memo.clear();
        for(int i = 0 ; i < nums.size() ; i ++)
            memo.push_back(-1);
        return tryRob7(nums, nums.size() - 1 );
    }

    /// 动态规划, 改变状态定义, 优化转移方程
    /// 时间复杂度: O(n)
    /// 空间复杂度: O(n)
    int rob8(vector<int>& nums) {

        int n = nums.size();
        if( n == 0 )
            return 0;

        // memo[i] 表示考虑抢劫 nums[0...i] 所能获得的最大收益
        vector<int> memo(n, 0);
        memo[0] = nums[0];
        for(int i = 1 ; i < n ; i ++)
            memo[i] = max(memo[i - 1],
                          nums[i] + (i - 2 >= 0 ? memo[i - 2] : 0));

        return memo[n-1];
    }
};

int main() {

    int nums[] = {2, 1};
    vector<int> vec(nums, nums + sizeof(nums)/sizeof(int));

    cout << Solution().rob(vec) << endl;
    cout << Solution().rob2(vec) << endl;
    cout << Solution().rob3(vec) << endl;
    cout << Solution().rob4(vec) << endl;
    cout << Solution().rob5(vec) << endl;
    cout << Solution().rob6(vec) << endl;
    cout << Solution().rob7(vec) << endl;
    cout << Solution().rob8(vec) << endl;

    return 0;
}