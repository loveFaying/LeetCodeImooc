#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 279. Perfect Squares
// https://leetcode.com/problems/perfect-squares/description/
// 该方法会导致 Time Limit Exceeded 或者 Memory Limit Exceeded
class Solution {
public:
    // 时间复杂度: O(2^n)
    // 空间复杂度: O(2^n)
    int numSquares(int n) {

        queue<pair<int, int>> q;
        q.push(make_pair(n, 0));
        while(!q.empty()){
            int num = q.front().first;
            int step = q.front().second;
            q.pop();

            if(num == 0)
                return step;

            for(int i = 1 ; num - i*i >= 0 ; i ++)
                q.push(make_pair(num - i * i, step + 1));
        }

        throw invalid_argument("No Solution.");
    }

    // 使用visited数组,记录每一个入队元素
    //
    // 时间复杂度: O(n)
    // 空间复杂度: O(n)
    int numSquares2(int n) {

        queue<pair<int, int>> q;
        q.push(make_pair(n, 0));

        vector<bool> visited(n+1, false);
        visited[n] = true;

        while(!q.empty()){
            int num = q.front().first;
            int step = q.front().second;
            q.pop();

            if(num == 0)
                return step;

            for(int i = 1; num - i * i >= 0; i ++)
                if(!visited[num - i * i]){
                    q.push(make_pair(num - i * i, step + 1));
                    visited[num - i * i] = true;
                }
        }

        throw invalid_argument("No Solution.");
    }

    // 进一步优化
    //
    // 时间复杂度: O(n)
    // 空间复杂度: O(n)
    int numSquares3(int n) {

        if(n == 0)
            return 0;

        queue<pair<int, int>> q;
        q.push(make_pair(n, 0));

        vector<bool> visited(n + 1, false);
        visited[n] = true;

        while(!q.empty()){
            int num = q.front().first;
            int step = q.front().second;
            q.pop();

            for(int i = 1; num - i * i >= 0; i ++){
                int a = num - i * i;
                if(!visited[a]){
                    if(a == 0) return step + 1;
                    q.push(make_pair(a, step + 1));
                    visited[a] = true;
                }
            }
        }

        throw invalid_argument("No Solution.");
    }

};

int main() {

    cout << Solution().numSquares(12) << endl;
    cout << Solution().numSquares(13) << endl;

    cout << Solution().numSquares2(12) << endl;
    cout << Solution().numSquares2(13) << endl;

    cout << Solution().numSquares3(12) << endl;
    cout << Solution().numSquares3(13) << endl;
    

    return 0;
}