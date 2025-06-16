#include <bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node* left;
    Node* right;
    Node(int val){
        data = val;
        left = NULL;
        right = NULL;
    }
};

class TreeNode{
    public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val){
        val = val;
        left = NULL;
        right = NULL;
    }
};

// finding minimum element in a binary search tree
int minValue(Node* root){
    if(root == NULL) return -1;
    while(root->left != NULL){
        root = root->left;
    }
    return root->data;
}



// searching an element in a binary search tree
TreeNode* searchBST(TreeNode* root, int val) {
    if(root == NULL) return NULL;
    if(root->val == val) return root;
    if(root->val > val) return searchBST(root->left, val);
    return searchBST(root->right, val);
}




// LC 98
bool solve(TreeNode* root){
    if(!root || (!root->left && !root->right)) return true;

    // both left and right exist
    if(root->left && root->right){
        return root->left->val<root->val && root->right->val > root->val && solve(root->left) && solve(root->right);
    }

    // only left exists
    else if (root->left){
        return root->left->val<root->val && solve(root->left);
    }

    // only right exists
    else{
        return root->right->val > root->val && solve(root->right);
    }

}
bool isValidBST(TreeNode* root) {
    return solve(root);   
}


// LC 700
TreeNode* solve(TreeNode* root, int val){
    if(!root) return NULL ;
    if(root->val  == val) return root;
    if(root->val > val){
        return solve(root->left , val);
    }
    else{
        return solve(root->right , val);
    }
}
TreeNode* searchBST(TreeNode* root, int val) {
    return solve(root, val);
}



// LC 1008
int helper(int val, vector<int> &inorder){
    auto it = find(inorder.begin()  , inorder.end() , val);
    return distance(inorder.begin() , it);
}
TreeNode* solve(vector<int>& preorder , vector<int>&inorder){
    if(preorder.size()==1){
        TreeNode* temp = new TreeNode(preorder[0]);
        return temp;
    }
    TreeNode* root= new TreeNode(preorder[0]);
    int len = helper(root->val , inorder);
    
    root->left = solve(preorder.begin()+1 , preorder.begin()+len+1, inorder);
    root->right = solve(preorder.begin()+len+2 , preorder.end(),inorder);
    return root;
}
TreeNode* bstFromPreorder(vector<int>& preorder) {
    vector<int> inorder = preorder;
    sort(inorder.begin() , inorder.end());

}


class Node {
    public: 
    Node* next;
    int val;
    Node(int val){
        this->next = nullptr;
        this->val = val;
    }
};


// LC 173 - binary search tree iterator

// LC 99 - recover binary search tree
