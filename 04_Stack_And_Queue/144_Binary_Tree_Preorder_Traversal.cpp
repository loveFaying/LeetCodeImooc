#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

using namespace std;

/// 144. Binary Tree Preorder Traversal
/// https://leetcode.com/problems/binary-tree-preorder-traversal/description/
/// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:

    /// 二叉树的前序遍历
    /// 时间复杂度: O(n), n为树的节点个数
    /// 空间复杂度: O(h), h为树的高度
    vector<int> preorderTraversal(TreeNode* root) {

        vector<int> res;
        __preorderTraversal(root, res);
        return res;
    }

    /// 非递归的二叉树的前序遍历
    /// 时间复杂度: O(n), n为树的节点个数
    /// 空间复杂度: O(h), h为树的高度
    vector<int> preorderTraversal2(TreeNode* root) {

        vector<int> res;
        if(root == NULL)
            return res;

        stack<Command> stack;
        stack.push(Command("go", root));
        while(!stack.empty()){
            Command command = stack.top();
            stack.pop();

            if(command.s == "print")
                res.push_back(command.node->val);
            else{
                assert(command.s == "go");
                if(command.node->right)
                    stack.push(Command("go",command.node->right));
                if(command.node->left)
                    stack.push(Command("go",command.node->left));
                stack.push(Command("print", command.node));
            }
        }
        return res;
    }

private:

    struct Command{
        string s;   // go, print
        TreeNode* node;
        Command(string s, TreeNode* node): s(s), node(node){}
    };


    void __preorderTraversal(TreeNode* node, vector<int> &res){

        if(node){
            res.push_back(node->val);
            __preorderTraversal(node->left, res);
            __preorderTraversal(node->right, res);
        }
    }
};

int main() {

    return 0;
}
