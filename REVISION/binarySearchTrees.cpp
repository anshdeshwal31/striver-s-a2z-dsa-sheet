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


// LC - 1008. Construct Binary Search Tree from Preorder Traversal
//METHOD 1
TreeNode* buildBST(vector<int>& preorder, int& index, int min, int max) {
    if (index >= preorder.size() || preorder[index] < min || preorder[index] > max) {
        return nullptr;
    }
    
    TreeNode* root = new TreeNode(preorder[index++]);
    
    root->left = buildBST(preorder, index, min, root->val);
    root->right = buildBST(preorder, index, root->val, max);
    
    return root;
}

TreeNode* bstFromPreorder(vector<int>& preorder) {
    int index = 0;
    return buildBST(preorder, index, INT_MIN, INT_MAX);
}


// METHOD 2
TreeNode* build(vector<int>& preorder, vector<int>& inorder, int preStart, int preEnd, int inStart, int inEnd) {
    if (preStart > preEnd || inStart > inEnd) return nullptr;

    // The first element in preorder is the root.
    int rootVal = preorder[preStart];
    TreeNode* root = new TreeNode(rootVal);

    // Find the index of root in inorder to split left/right subtrees.
    int inIndex = inStart; // Start searching from inStart.
    while (inorder[inIndex] != rootVal) {
        inIndex++;
    }

    // Calculate the size of the left subtree.
    int leftSize = inIndex - inStart;

    // Recursively build left and right subtrees.
    root->left = build(preorder, inorder, preStart + 1, preStart + leftSize, inStart, inIndex - 1);

    root->right = build(preorder, inorder, preStart + leftSize + 1, preEnd, inIndex + 1, inEnd);

    return root;
}

TreeNode* bstFromPreorder(vector<int>& preorder) {
    vector<int> inorder = preorder;
    sort(inorder.begin() , inorder.end());
    return build(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
}
    