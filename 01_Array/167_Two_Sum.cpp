#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// 167. Two Sum II - Input array is sorted
// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/
//
class Solution {
public:
    // 暴力枚举法
    // 时间复杂度: O(n^2)
    // 空间复杂度: O(1)
    vector<int> twoSum(vector<int>& numbers, int target) {

        assert(numbers.size() >= 2);
        // assert(isSorted(numbers));

        for(int i = 0 ; i < numbers.size() ; i ++)
            for(int j = i+1 ; j < numbers.size() ; j ++)
                if(numbers[i] + numbers[j] == target){
                    int res[2] = {i+1, j+1};
                    return vector<int>(res, res+2);
                }

        throw invalid_argument("the input has no solution");
    }

    // 二分搜索法
    // 时间复杂度: O(nlogn)
    // 空间复杂度: O(1)
    vector<int> twoSum2(vector<int>& numbers, int target) {

        assert(numbers.size() >= 2);
        // assert(isSorted(numbers));

        for(int i = 0 ; i < numbers.size() - 1 ; i ++){
            int j = binarySearch(numbers, i+1, numbers.size()-1, target - numbers[i]);
            if(j != -1){
                int res[2] = {i+1, j+1};
                return vector<int>(res, res+2);
            }
        }

        throw invalid_argument("the input has no solution");
    }

    // 对撞指针
    // 时间复杂度: O(n)
    // 空间复杂度: O(1)
    vector<int> twoSum3(vector<int>& numbers, int target) {

        assert(numbers.size() >= 2);
        // assert(isSorted(numbers));

        int l = 0, r = numbers.size() - 1;
        while(l < r){

            if(numbers[l] + numbers[r] == target){
                int res[2] = {l+1, r+1};
                return vector<int>(res, res+2);
            }
            else if(numbers[l] + numbers[r] < target)
                l ++;
            else // numbers[l] + numbers[r] > target
                r --;
        }

        throw invalid_argument("the input has no solution");
    }

private:

    int binarySearch(const vector<int> &nums, int l, int r, int target){

        assert(l >= 0 && l < nums.size());
        assert(r >= 0 && r < nums.size());

        while(l <= r){

            int mid = l + (r - l)/2;
            if(nums[mid] == target)
                return mid;
            if(target > nums[mid])
                l = mid + 1;
            else
                r = mid - 1;
        }

        return -1;
    }

    bool isSorted(const vector<int>& numbers){
        for(int i = 1 ; i < numbers.size() ; i ++)
            if(numbers[i] < numbers[i-1])
                return false;
        return true;
    }
};

int main() {

    int nums[] = {2, 7, 11, 15};
    vector<int> vec(nums, nums + sizeof(nums) / sizeof(int));
    vector<int> vec2(nums, nums + sizeof(nums) / sizeof(int));
    vector<int> vec3(nums, nums + sizeof(nums) / sizeof(int));
    int target = 9;

    vector<int> res = Solution().twoSum(vec, target);
    vector<int> res2 = Solution().twoSum(vec2, target);
    vector<int> res3 = Solution().twoSum(vec3, target);

    for(int i = 0 ; i < res.size() ; i ++)
        cout << res[i] << " ";
    cout << endl;

    for(int i = 0 ; i < res2.size() ; i ++)
        cout << res2[i] << " ";
    cout << endl;

    for(int i = 0 ; i < res2.size() ; i ++)
        cout << res2[i] << " ";
    cout << endl;

    return 0;
}