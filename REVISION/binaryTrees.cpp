#include <bits/stdc++.h>
using namespace std;

class TreeNode{
    public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val){
        this->left  = nullptr;
        this->right = nullptr;
        this->val = val;
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



// LC 124 - binary tree maximum path sum
int solve(TreeNode* root, int& maxSum) {
    if (root == NULL) return 0;
    
    int leftSum = max(0, solve(root->left, maxSum));
    int rightSum = max(0, solve(root->right, maxSum));
    
    maxSum = max(maxSum, leftSum + rightSum + root->val);
    
    return max(leftSum, rightSum) + root->val;
}

int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    solve(root, maxSum);
    return maxSum;
}


