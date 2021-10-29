#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

// 3. Longest Substring Without Repeating Characters
// https://leetcode.com/problems/longest-substring-without-repeating-characters/description/

class Solution {
public:
    // 滑动窗口
    // 时间复杂度: O(len(s))
    // 空间复杂度: O(len(charset))
    int lengthOfLongestSubstring(string s) {

        int freq[256] = {0};

        int l = 0, r = -1; //滑动窗口为s[l...r]
        int res = 0;

        // 整个循环从 l == 0; r == -1 这个空窗口开始
        // 到l == s.size(); r == s.size()-1 这个空窗口截止
        // 在每次循环里逐渐改变窗口, 维护freq, 并记录当前窗口中是否找到了一个新的最优值
        while(l < s.size()){

            if(r + 1 < s.size() && freq[s[r+1]] == 0)
                freq[s[++r]] ++;
            else    //r已经到头 || freq[s[r+1]] == 1
                freq[s[l++]] --;

            res = max(res, r-l+1);
        }

        return res;
    }

    // 滑动窗口
    // 时间复杂度: O(len(s))
    // 空间复杂度: O(len(charset))
    int lengthOfLongestSubstring2(string s) {

        int freq[256] = {0};

        int l = 0, r = -1; //滑动窗口为s[l...r]
        int res = 0;

        // 在这里, 循环中止的条件可以是r + 1 < s.size(), 想想看为什么?
        // 感谢课程QQ群 @千千 指出 :)
        while(r + 1 < s.size()){

            if( freq[s[r + 1]] == 0 )
                freq[s[++r]] ++;
            else    //freq[s[r+1]] == 1
                freq[s[l++]] --;

            res = max(res, r - l + 1);
        }

        return res;
    }

    // 滑动窗口的另一个实现, 仅做参考
    // 时间复杂度: O(len(s))
    // 空间复杂度: O(len(charset))
    int lengthOfLongestSubstring3(string s) {

        int freq[256] = {0};

        int l = 0, r = -1;
        int res = 0;

        while(r + 1 < s.size()){

            while(r + 1 < s.size() && freq[s[r + 1]] == 0)
                freq[s[++r]] ++;

            res = max(res, r - l + 1);

            if(r + 1 < s.size()){
                freq[s[++r]] ++;
                assert(freq[s[r]] == 2);
                while(l <= r && freq[s[r]] == 2)
                    freq[s[l++]] --;
            }
        }

        return res;
    }

    // 课程问答区 @yatkun 提出的方法,
    // l每次可以向前跳跃, 而不仅仅是+1
    // 但代价是, 为了获得这个跳跃的位置, 每次需要遍历整个窗口的字符串
    //
    // 时间复杂度: O(len(s)*len(charset))
    // 空间复杂度: O(1)
    int lengthOfLongestSubstring4(string s) {

        int l = 0, r = 0; //滑动窗口为s[l...r]
        int res = 0;

        while(r < s.size()){

            int index = isDuplicateChar(s, l, r);

            // 如果s[r]之前出现过
            // l可以直接跳到s[r+1]之前出现的位置 + 1的地方
            if(index != -1)
                l = index + 1;

            res = max(res, r-l+1);
            r ++;
        }

        return res;
    }

    // 滑动窗口
    // 其中使用last[c]保存字符c上一次出现的位置, 用于在右边界发现重复字符时, 快速移动左边界
    // 使用这种方法, 时间复杂度依然为O(n), 但是只需要动r指针, 实际上对整个s只遍历了一次
    // 相较而言, 之前的方法, 需要移动l和r两个指针, 相对于对s遍历了两次
    //
    // 时间复杂度: O(len(s))
    // 空间复杂度: O(len(charset))
    int lengthOfLongestSubstring5(string s) {

        int last[256];
        memset(last, -1, sizeof(last));

        int l = 0, r = -1; //滑动窗口为s[l...r]
        int res = 0;
        while(r + 1 < s.size()){

            r ++;
            if(last[s[r]] != -1)
                l = max(l, last[s[r]] + 1);

            res = max(res, r - l + 1);
            last[s[r]] = r;
        }

        return res;
    }
private:
    // 查看s[l...r-1]之间是否存在s[r]
    // 若存在,返回相应的索引, 否则返回-1
    int isDuplicateChar(const string& s, int l, int r){
        for(int i = l ; i < r ; i ++)
            if(s[i] == s[r])
                return i;
        return -1;
    }
};

int main() {

    cout << Solution().lengthOfLongestSubstring( "abcabcbb" )<<endl; //3
    cout << Solution().lengthOfLongestSubstring( "bbbbb" )<<endl;    //1
    cout << Solution().lengthOfLongestSubstring( "pwwkew" )<<endl;   //3
    cout << Solution().lengthOfLongestSubstring( "c" )<<endl;        //1
    cout << Solution().lengthOfLongestSubstring( "" )<<endl;         //0

    cout << Solution().lengthOfLongestSubstring2( "abcabcbb" )<<endl; //3
    cout << Solution().lengthOfLongestSubstring2( "bbbbb" )<<endl;    //1
    cout << Solution().lengthOfLongestSubstring2( "pwwkew" )<<endl;   //3
    cout << Solution().lengthOfLongestSubstring2( "c" )<<endl;        //1
    cout << Solution().lengthOfLongestSubstring2( "" )<<endl;         //0

    cout << Solution().lengthOfLongestSubstring3( "abcabcbb" )<<endl; //3
    cout << Solution().lengthOfLongestSubstring3( "bbbbb" )<<endl;    //1
    cout << Solution().lengthOfLongestSubstring3( "pwwkew" )<<endl;   //3
    cout << Solution().lengthOfLongestSubstring3( "c" )<<endl;        //1
    cout << Solution().lengthOfLongestSubstring3( "" )<<endl;         //0

    cout << Solution().lengthOfLongestSubstring4( "abcabcbb" )<<endl; //3
    cout << Solution().lengthOfLongestSubstring4( "bbbbb" )<<endl;    //1
    cout << Solution().lengthOfLongestSubstring4( "pwwkew" )<<endl;   //3
    cout << Solution().lengthOfLongestSubstring4( "c" )<<endl;        //1
    cout << Solution().lengthOfLongestSubstring4( "" )<<endl;         //0

    cout << Solution().lengthOfLongestSubstring5( "abcabcbb" )<<endl; //3
    cout << Solution().lengthOfLongestSubstring5( "bbbbb" )<<endl;    //1
    cout << Solution().lengthOfLongestSubstring5( "pwwkew" )<<endl;   //3
    cout << Solution().lengthOfLongestSubstring5( "c" )<<endl;        //1
    cout << Solution().lengthOfLongestSubstring5( "" )<<endl;         //0

    return 0;
}