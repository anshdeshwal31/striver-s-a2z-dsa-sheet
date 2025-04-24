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
