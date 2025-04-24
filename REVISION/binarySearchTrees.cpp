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



// LC 450 -  delete node in a BST 
int minVal(TreeNode* root) {
    if(root == NULL) {
        return -1;
    }

    TreeNode* temp = root;
    while(temp->left) {
        temp = temp->left;
    }

    return temp->val;
}

TreeNode* deleteNode(TreeNode* root, int data) {
    if(root == NULL) {
        return root;
    }

    if(root->val == data) {
        
        // 0 Child
        if(root->left==NULL && root->right==NULL) {
            delete root;
            return NULL;
        }

        // 1 Child
        // Left Child
        if(root->left!=NULL && root->right==NULL) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        // Right Child
        if(root->left==NULL && root->right!=NULL) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }

        // 2 Child
        if(root->left!=NULL && root->right!=NULL) {
            int mini = minVal(root->right);
            root->val = mini;
            root->right = deleteNode(root->right, mini);
            return root;
        }
    }
    else if(data > root->val) {
        root->right = deleteNode(root->right, data);
        return root;
    } 
    else{
        root->left = deleteNode(root->left, data);
        return root;
    }
    return root;
}


// LC- 235. Lowest Common Ancestor of a Binary Search Tree
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // Base case: if root is null or equals either target node
    if (!root || root == p || root == q) {
        return root;
    }
    
    int curr = root->val;
    int val1 = p->val;
    int val2 = q->val;
    
    // Case 1: Both values are smaller than current - LCA must be in left subtree
    if (val1 < curr && val2 < curr) {
        return lowestCommonAncestor(root->left, p, q);
    }
    
    // Case 2: Both values are larger than current - LCA must be in right subtree
    if (val1 > curr && val2 > curr) {
        return lowestCommonAncestor(root->right, p, q);
    }
    
    // Case 3: Values lie on different sides (or one equals current)
    // Current node is the LCA
    return root;
}