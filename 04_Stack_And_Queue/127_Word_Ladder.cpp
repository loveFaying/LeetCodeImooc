/// Source : https://leetcode.com/problems/word-ladder/description/
/// Author : liuyubobobo
/// Time   : 2017-11-21

#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {

public:
    /// BFS
    /// Time Complexity: O(n*n)
    /// Space Complexity: O(n)
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

        int end = find(wordList.begin(), wordList.end(), endWord) - wordList.begin();
        if(end == wordList.size())
            return 0;

        int begin = find(wordList.begin(), wordList.end(), beginWord) - wordList.begin();
        if(begin == wordList.size())
            wordList.push_back(beginWord);

        int n = wordList.size();

        vector<vector<bool>> g(n, vector<bool>(n, false));
        for(int i = 0 ; i < wordList.size() ; i ++)
            for(int j = 0 ; j < i ; j ++)
                g[i][j] = g[j][i] = similar(wordList[i], wordList[j]);

        // bfs
        queue<int> q;
        vector<int> step(n, 0);

        q.push(begin);
        step[begin] = 1;
        while(!q.empty()){
            int cur = q.front();
            q.pop();

            for(int i = 0 ; i < n ; i ++)
                if(step[i] == 0 && g[cur][i]){
                    if(i == end)
                        return step[cur] + 1;
                    step[i] = step[cur] + 1;
                    q.push(i);
                }
        }

        return 0;
    }

    /// BFS
    /// Using set to store all the words and erase visited word eagerly.
    /// Time Complexity: O(n*n)
    /// Space Complexity: O(n)
    int ladderLength2(string beginWord, string endWord, vector<string>& wordList) {

        unordered_set<string> wordSet(wordList.begin(), wordList.end());

        // bfs
        queue<pair<string, int>> q;
        q.push(make_pair(beginWord, 1));
        if(wordSet.find(beginWord) != wordSet.end())
            wordSet.erase(beginWord);

        vector<string> visited;

        while(!q.empty()){
            string curWord = q.front().first;
            int curStep = q.front().second;
            q.pop();

            visited.clear();
            for(string word: wordSet)
                if(similar(word, curWord)){
                    if(word == endWord)
                        return curStep + 1;
                    q.push(make_pair(word, curStep + 1));
                    visited.push_back(word);
                }

            for(string word: visited)
                wordSet.erase(word);
        }

        return 0;
    }

    /// Bi-directional BFS
    /// Time Complexity: O(n*n)
    /// Space Complexity: O(n)
    int ladderLength3(string beginWord, string endWord, vector<string>& wordList) {

        int end = find(wordList.begin(), wordList.end(), endWord) - wordList.begin();
        if(end == wordList.size())
            return 0;

        int begin = find(wordList.begin(), wordList.end(), beginWord) - wordList.begin();
        if(begin == wordList.size())
            wordList.push_back(beginWord);

        int n = wordList.size();

        vector<vector<bool>> g(n, vector<bool>(n, false));
        for(int i = 0 ; i < wordList.size() ; i ++)
            for(int j = 0 ; j < i ; j ++)
                g[i][j] = g[j][i] = similar(wordList[i], wordList[j]);


        // bi-derectional-bfs
        vector<int> step_s(n, 0);
        vector<int> step_t(n, 0);

        queue<int> queue_s;
        queue<int> queue_t;

        queue_s.push(begin);
        step_s[begin] = 1;

        queue_t.push(end);
        step_t[end] = 1;
        while(!queue_s.empty() && !queue_t.empty()){

            int cur_s = queue_s.front();
            queue_s.pop();

            int cur_t = queue_t.front();
            queue_t.pop();

            for(int i = 0 ; i < wordList.size() ; i ++)
                if(step_s[i] == 0 && g[cur_s][i]){
                    step_s[i] = step_s[cur_s] + 1;
                    queue_s.push(i);
                }

            for(int i = 0 ; i < wordList.size() ; i ++)
                if(step_t[i] == 0 && g[cur_t][i]){
                    step_t[i] = step_t[cur_t] + 1;
                    queue_t.push(i);
                }

            // check intersection
            int res = INT_MAX;
            for(int i = 0 ; i < wordList.size() ; i ++)
                if(step_s[i] != 0 && step_t[i] != 0)
                    res = min(res, step_s[i] + step_t[i] - 1);

            if(res != INT_MAX)
                return res;
        }

        return 0;
    }

    /// Bi-directional BFS
    /// No need to calculate all pairs similarity
    /// Time Complexity: O(n*n)
    /// Space Complexity: O(n)
    int ladderLength4(string beginWord, string endWord, vector<string>& wordList) {

        if(find(wordList.begin(), wordList.end(), endWord) == wordList.end())
            return 0;

        // bi-derectional bfs
        unordered_map<string, int> step_s;
        unordered_map<string, int> step_t;

        queue<string> queue_s;
        queue<string> queue_t;

        queue_s.push(beginWord);
        step_s[beginWord] = 1;

        queue_t.push(endWord);
        step_t[endWord] = 1;
        while(!queue_s.empty() && !queue_t.empty()){

            string sWord = queue_s.front();
            queue_s.pop();

            string tWord = queue_t.front();
            queue_t.pop();

            for(string word: wordList){
                if(step_s.find(word) == step_s.end() && similar(word, sWord)){
                    step_s[word] = step_s[sWord] + 1;
                    queue_s.push(word);
                }

                if(step_t.find(word) == step_t.end() && similar(word, tWord)){
                    step_t[word] = step_t[tWord] + 1;
                    queue_t.push(word);
                }
            }

            // check intersection
            int res = INT_MAX;
            for(string word: wordList)
                if(step_s.find(word) != step_s.end() && step_t.find(word) != step_t.end())
                    res = min(res, step_s[word] + step_t[word] - 1);

            if(res != INT_MAX)
                return res;
        }

        return 0;
    }

private:
    bool similar(const string& word1, const string& word2){

        assert(word1 != "" && word1.size() == word2.size() && word1 != word2);

        int diff = 0;
        for(int i = 0 ; i < word1.size() ; i ++)
            if(word1[i] != word2[i]){
                diff ++;
                if(diff > 1)
                    return false;
            }
        return true;
    }
};

int main() {

    vector<string> vec1 = {"hot","dot","dog","lot","log","cog"};
    string beginWord1 = "hit";
    string endWord1 = "cog";
    cout << Solution().ladderLength(beginWord1, endWord1, vec1) << endl;
    // 5

    // ---

    vector<string> vec2 = {"a","b","c"};
    string beginWord2 = "a";
    string endWord2 = "c";
    cout << Solution().ladderLength2(beginWord2, endWord2, vec2) << endl;
    // 2

    // ---

    vector<string> vec3 = {"most","fist","lost","cost","fish"};
    string beginWord3 = "lost";
    string endWord3 = "cost";
    cout << Solution().ladderLength3(beginWord3, endWord3, vec3) << endl;
    // 2

    // ---

    vector<string> vec4 = {"hot","dot","dog","lot","log"};
    string beginWord4 = "hit";
    string endWord4 = "cog";
    cout << Solution().ladderLength4(beginWord4, endWord4, vec4) << endl;
    // 0

    return 0;
}