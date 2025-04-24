#include <bits/stdc++.h>
using namespace std;

class TreeNode{
    public:
    TreeNode* left;
    TreeNode* right;

    TreeNode(){
        this->left  = nullptr;
        this->right = nullptr;
    }
};



// LC 543 - diameter of a binary tree
pair<int , int> solve(TreeNode* root){
    if(!root) return {0, 0};

    pair<int , int > leftCall = solve(root->left);
    pair<int , int > rightCall = solve(root->right);

    int diameter =  max(max(leftCall.first, rightCall.first),leftCall.second + rightCall.second+1);
    return {diameter, max(leftCall.second,rightCall.second)+1};
}

int diameterOfBinaryTree(TreeNode* root) {
    pair<int, int> ans = solve(root);
    return ans.first - 1; // subtracted 1 because diameter is the number of edges not the number of nodes
}