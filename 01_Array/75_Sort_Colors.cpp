#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// 75. Sort Colors
// https://leetcode.com/problems/sort-colors/description/
class Solution {
public:
    // 计数排序的思路
    // 对整个数组遍历了两遍
    // 时间复杂度: O(n)
    // 空间复杂度: O(k), k为元素的取值范围
    void sortColors(vector<int> &nums) {

        int count[3] = {0};    // 存放0, 1, 2三个元素的频率
        for(int i = 0 ; i < nums.size() ; i ++){
            assert(nums[i] >= 0 && nums[i] <= 2);
            count[nums[i]] ++;
        }

        int index = 0;
        for(int i = 0 ; i < count[0] ; i ++)
            nums[index++] = 0;
        for(int i = 0 ; i < count[1] ; i ++)
            nums[index++] = 1;
        for(int i = 0 ; i < count[2] ; i ++)
            nums[index++] = 2;

        // 小练习: 自学编写计数排序算法
    }

    // 三路快速排序的思想
    // 对整个数组只遍历了一遍
    // 时间复杂度: O(n)
    // 空间复杂度: O(1)
    void sortColors2(vector<int> &nums) {

        int zero = -1;          // [0...zero] == 0
        int two = nums.size();  // [two...n-1] == 2
        for(int i = 0 ; i < two ; ){
            if(nums[i] == 1)
                i ++;
            else if (nums[i] == 2)
                swap( nums[i] , nums[--two]);
            else{ // nums[i] == 0
                assert(nums[i] == 0);
                swap(nums[++zero] , nums[i++]);
            }
        }
    }
};

int main() {

    int nums[] = {2, 2, 2, 1, 1, 0};
    vector<int> vec = vector<int>(nums, nums + sizeof(nums)/sizeof(int));
    vector<int> vec2 = vector<int>(nums, nums + sizeof(nums)/sizeof(int));

    Solution().sortColors(vec);
    Solution().sortColors(vec2);

    for(int i = 0 ; i < vec.size() ; i ++)
        cout << vec[i] << " ";
    cout << endl;

    for(int i = 0 ; i < vec2.size() ; i ++)
        cout << vec2[i] << " ";
    cout << endl;
    return 0;
}
