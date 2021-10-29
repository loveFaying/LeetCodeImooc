#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

// 209. Minimum Size Subarray Sum
// https://leetcode.com/problems/minimum-size-subarray-sum/description/
class Solution {
public:
    // 暴力解法
    // 该方法在 Leetcode 中会超时！
    // 时间复杂度: O(n^3)
    // 空间复杂度: O(1)
    int minSubArrayLen(int s, vector<int>& nums) {

        assert(s > 0);

        int res = nums.size() + 1;
        for(int l = 0 ; l < nums.size() ; l ++)
            for(int r = l ; r < nums.size() ; r ++){
                int sum = 0;
                for(int i = l ; i <= r ; i ++)
                    sum += nums[i];
                if(sum >= s)
                    res = min(res, r - l + 1);
            }

        if(res == nums.size() + 1)
            return 0;

        return res;
    }

    // 优化暴力解
    // 时间复杂度: O(n^2)
    // 空间复杂度: O(n)
    int minSubArrayLen2(int s, vector<int>& nums) {

        assert(s > 0);

        // sums[i]存放nums[0...i-1]的和
        vector<int> sums(nums.size() + 1, 0);
        for(int i = 1 ; i <= nums.size() ; i ++)
            sums[i] = sums[i-1] + nums[i-1];

        int res = nums.size() + 1;
        for(int l = 0 ; l < nums.size() ; l ++)
            for(int r = l ; r < nums.size() ; r ++){
                // 使用sums[r+1] - sums[l] 快速获得nums[l...r]的和
                if(sums[r+1] - sums[l] >= s)
                    res = min(res, r - l + 1);
            }

        if(res == nums.size() + 1)
            return 0;

        return res;
    }

    // 滑动窗口的思路
    // 时间复杂度: O(n)
    // 空间复杂度: O(1)
    int minSubArrayLen3(int s, vector<int>& nums) {

        assert(s > 0);

        int l = 0 , r = -1; // nums[l...r]为我们的滑动窗口
        int sum = 0;
        int res = nums.size() + 1;

        while(l < nums.size()){   // 窗口的左边界在数组范围内,则循环继续

            if(r + 1 < nums.size() && sum < s)
                sum += nums[++r];
            else // r已经到头 或者 sum >= s
                sum -= nums[l++];

            if(sum >= s)
                res = min(res, r - l + 1);
        }

        if(res == nums.size() + 1)
            return 0;
        return res;
    }

    // 另外一个滑动窗口的实现, 仅供参考
    // 时间复杂度: O(n)
    // 空间复杂度: O(1)
    int minSubArrayLen4(int s, vector<int>& nums) {

        assert(s > 0);

        int l = 0 , r = -1; // [l...r]为我们的窗口
        int sum = 0;
        int res = nums.size() + 1;

        while(r + 1 < nums.size()){   // 窗口的右边界无法继续扩展了, 则循环继续

            while(r + 1 < nums.size() && sum < s)
                sum += nums[++r];

            if(sum >= s)
                res = min(res, r - l + 1);

            while(l < nums.size() && sum >= s){
                sum -= nums[l++];
                if(sum >= s)
                    res = min(res, r - l + 1);
            }
        }

        if(res == nums.size() + 1)
            return 0;
        return res;
    }

    // 二分搜索
    // 扩展main2的方法。对于每一个l, 可以使用二分搜索法搜索r
    //
    // 时间复杂度: O(nlogn)
    // 空间复杂度: O(n)
    int minSubArrayLen5(int s, vector<int>& nums) {

        assert(s > 0);

        // sums[i]存放nums[0...i-1]的和
        vector<int> sums(nums.size() + 1, 0);
        for(int i = 1 ; i <= nums.size() ; i ++)
            sums[i] = sums[i-1] + nums[i-1];

        int res = nums.size() + 1;
        for(int l = 0 ; l < (int)nums.size() - 1 ; l ++){

            auto r_bound = lower_bound(sums.begin(), sums.end(), sums[l] + s);
            if(r_bound != sums.end()){
                int r = r_bound - sums.begin();
                res = min(res, r - l);
            }
        }

        if(res == nums.size() + 1)
            return 0;

        return res;
    }
};

int main() {

    int nums[] = {2, 3, 1, 2, 4, 3};
    vector<int> vec(nums, nums + sizeof(nums)/sizeof(int));
    vector<int> vec2(nums, nums + sizeof(nums)/sizeof(int));
    vector<int> vec3(nums, nums + sizeof(nums)/sizeof(int));
    vector<int> vec4(nums, nums + sizeof(nums)/sizeof(int));
    vector<int> vec5(nums, nums + sizeof(nums)/sizeof(int));
    
    int s = 7;

    cout << Solution().minSubArrayLen(s, vec) << endl;
    cout << Solution().minSubArrayLen2(s, vec2) << endl;
    cout << Solution().minSubArrayLen3(s, vec3) << endl;
    cout << Solution().minSubArrayLen4(s, vec4) << endl;
    cout << Solution().minSubArrayLen5(s, vec5) << endl;

    return 0;
}