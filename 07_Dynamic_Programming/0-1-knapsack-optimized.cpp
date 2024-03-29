#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

/// 背包问题
class Knapsack01{

public:
    /// 动态规划改进: 滚动数组
    /// 时间复杂度: O(n * C) 其中n为物品个数; C为背包容积
    /// 空间复杂度: O(C), 实际使用了2*C的额外空间
    int knapsack01(const vector<int> &w, const vector<int> &v, int C){
        assert(w.size() == v.size() && C >= 0);
        int n = w.size();
        if( n == 0 && C == 0 )
            return 0;

        vector<vector<int>> memo(2, vector<int>(C + 1, 0));

        for(int j = 0 ; j <= C ; j ++)
            memo[0][j] = (j >= w[0] ? v[0] : 0);

        for(int i = 1 ; i < n ; i ++)
            for(int j = 0 ; j <= C ; j ++){
                memo[i % 2][j] = memo[(i-1) % 2][j];
                if(j >= w[i])
                    memo[i % 2][j] = max(memo[i % 2][j], v[i] + memo[(i-1) % 2][j - w[i]]);
            }
        return memo[(n-1) % 2][C];
    }

    int knapsack01_2(const vector<int> &w, const vector<int> &v, int C){
        assert(w.size() == v.size() && C >= 0);
        int n = w.size();
        if(n == 0 || C == 0)
            return 0;

        vector<int> memo(C+1,0);

        for(int j = 0 ; j <= C ; j ++)
            memo[j] = (j >= w[0] ? v[0] : 0);

        for(int i = 1 ; i < n ; i ++)
            for(int j = C ; j >= w[i] ; j --)
                memo[j] = max(memo[j], v[i] + memo[j - w[i]]);

        return memo[C];
    }
};

int main() {

    int n, W;
    cin >> n >> W;

    int v, w;
    vector<int> vs, ws;
    for(int i = 0 ; i < n ; i ++){
        cin >> w >> v;
        vs.push_back(v);
        ws.push_back(w);
    }

    cout << Knapsack01().knapsack01(ws, vs, W) << endl;
    cout << Knapsack01().knapsack01_2(ws, vs, W) << endl;

    return 0;
}