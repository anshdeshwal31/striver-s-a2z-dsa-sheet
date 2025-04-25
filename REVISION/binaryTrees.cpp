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



// LC - 105. Construct Binary Tree from Preorder and Inorder Traversal
TreeNode* constructTree(vector<int>& preorder, int preStart, int preEnd, vector<int> &inorder, int inStart, int inEnd, map<int,int>& mp) {
    if (preStart > preEnd || inStart > inEnd) return NULL;

    TreeNode* root = new TreeNode(preorder[preStart]);
    int elem = mp[root -> val];
    int nElem = elem - inStart;

    root -> left = constructTree(preorder, preStart + 1, preStart + nElem, inorder,
    inStart, elem - 1, mp);
    root -> right = constructTree(preorder, preStart + nElem + 1, preEnd, inorder, 
    elem + 1, inEnd, mp);

    return root;
}

TreeNode* buildTree(vector < int > & preorder, vector < int > & inorder) {
  int preStart = 0, preEnd = preorder.size() - 1;
  int inStart = 0, inEnd = inorder.size() - 1;

  map < int, int > mp;
  for (int i = inStart; i <= inEnd; i++) {
    mp[inorder[i]] = i;
  }

  return constructTree(preorder, preStart, preEnd, inorder, inStart, inEnd, mp);
}