#include <bits/stdc++.h>
using namespace std;


class node{
    public:
    int data;
    node* left;
    node* right;
    node(int val){
        data = val;
        left = NULL;
        right = NULL;
    }
};
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


// creation of binary tree from level order traversal

// using iterative approach
void create_tree(node* root, vector<int> &vec){
    queue<node*> q;
    node* temp = root;
    int i = 1;
    q.push(temp);

    while(i < vec.size()){
        temp = q.front();
        q.pop();
        
        node* left = new node(vec[i++]);
        node* right = i < vec.size() ? new node(vec[i++]) : NULL;
        temp->left = left;
        temp->right = right;
        q.push(left);
        if (right) q.push(right);
    }
}


// using recursive approach
void solve(queue<node*> &q , vector<int> &vec,int &i){
    if(i == vec.size()) return;

    node* temp = q.front();
    q.pop();
    node* left = new node(vec[i++]);
    temp->left = left;
    q.push(left);
    if(i < vec.size()) {
        node* right = new node(vec[i++]);
        temp->right = right;
        q.push(right);
    }
    solve(q,vec,i);
}
void create_tree(node* root, vector<int> &vec){
    queue<node*> q;
    q.push(root);
    int i = 1;
    solve(q,vec,i);
}


// balanced binary tree
pair<int,bool> solve(TreeNode* root){
    if(root == NULL) return {0,true};
    pair<int,bool> left = solve(root->left);
    pair<int,bool> right = solve(root->right);

    if(left.second == false || right.second == false) return {0,false};
    if(abs(left.first - right.first) > 1) return {0,false};

    return {max(left.first,right.first) + 1,true};
}
bool isBalanced(TreeNode* root){
    return solve(root).second;
}


// maximum path sum 
int solve(TreeNode* root){
    // if(root == NULL) return 0;
    if(root->left == NULL && root->right == NULL) return root->val;
    int leftSum = solve(root->left);
    int rightSum = solve(root->right);
    int currSum = leftSum + rightSum + root->val;
    return max({leftSum,rightSum,currSum,root->val});
}
int maxPathSum(TreeNode* root) {
    return solve(root);
}

int solve(TreeNode* root){
    if(root->left == NULL && root->right == NULL) return root->val;
    if(root->left == NULL){
        int rightSum = solve(root->right);
        int currSum = rightSum + root->val;
        return max({rightSum,currSum,root->val});
    }
    if(root->right == NULL){
        int leftSum = solve(root->left);
        int currSum = leftSum + root->val;
        return max({leftSum,currSum,root->val});
    }
    int left = solve(root->left);
    int right = solve(root->right);
    int leftSum = left + root->val;
    int rightSum = right + root->val;
    int currSum = left + right + root->val;
    return max({leftSum,rightSum,currSum,left,right,root->val});
}


// maximum width of binary tree
int solve(TreeNode* root){
    queue<pair<TreeNode*,int>> q;
    int index = 0;
    q.push({root,i});
    int maxWidth = 0;
    int minIndex = 0;

    while(!q.empty()){
        int size = q.size();
        
        for(int i = 0; i < size; i++){
        }
    }
            
}



// binary tree paths
void solve(TreeNode* root , string path , vector<string> &ans){
    if(!root->left && !root->right){
        path += to_string(root->val);
        ans.push_back(path);
        return;
    }

    if(root->left) solve(root->left,path + to_string(root->val) + "->",ans);
    if(root->right) solve(root->right,path + to_string(root->val) + "->",ans);
}
vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> ans;
    solve(root,"",ans);
    return ans;
}


//check children sum property 
bool solve(Node* root){
    if(root == NULL) return true;
    if(root->left == NULL && root->right == NULL) return true;
    
    bool leftCall = solve(root->left);
    bool rightCall = solve(root->right);
    int currentSum = 0;
    if(root->left) currentSum += root->left->data;
    if(root->right) currentSum += root->right->data;
    return leftCall && rightCall && (currentSum == root->data);
}
int isSumProperty(Node *root){
    return solve(root);
}



// binary tree maximum path sum
int solve(TreeNode* root){
    if(root->left == NULL && root->right == NULL) return root->val;

    int leftSum = solve(root->left);
    int rightSum = solve(root->right);
    if(root->val<0) return max(root->val,leftSum,rightSum);

    // if(root->left && root->right&& root->left->val > 0 && root->right->val > 0){
    //     return max({left , right , root->val + root->left->val + root->right->val+root->left->val});
    // }
    // else if(root->left  && root->left->val > 0){
    //     return max({left , right , root->val + root->left->val});
    // }
    // else if(root->right && root->right->val > 0){
    //     return max({left , right , root->val + root->right->val});
    // }
    // else{
    //     return max({left , right , root->val});
    // }
    if(root->left && root->right ){
        if(root->left->val > 0 && root->right->val > 0){
            return max({left , right , root->val + root->left->val + root->right->val});
        }
        else if(root->left->val > 0){
            return max({left , right , root->val + root->left->val});
        }
        else if(root->right->val > 0){
            return max({left , right , root->val + root->right->val});
        }
        else{
            return max({left , right , root->val});
        }
    }
    else if(root->left ){
        if(root->left->val > 0){
            return max({left , right , root->val + root->left->val});
        }
        else{
            return max({left , right , root->val});
        }
    }
    else (root->right ){
        if(root->right->val > 0){
            return max({left , right , root->val + root->right->val});
        }
        else{
            return max({left , right , root->val});
        }
    }

}

int maxPathSum(TreeNode* root) {
    return solve(root);
}


// binary tree maximum path sum
int solve(TreeNode* root){
    if(root->left == NULL && root->right == NULL) return root->val;

    int left = solve(root->left);
    int right = solve(root->right);
    if(root->val<0) return max(root->val, max(left,right));

    if(root->left && root->right ){
        if(root->left->val > 0 && root->right->val > 0){
            return max(root->right->val + root->val + root->left->val, max(left,right));
        }
        else if(root->left->val > 0){
            // return max({left , right , root->val + root->left->val});
            return max(root->left->val + root->val, max(left,right));
        }
        else if(root->right->val > 0){
            return max((root->right->val + root->val), max(left,right));
        }
        else{
            return max((root->val), max(left,right));
        }
    }
    else if(root->left ){
        if(root->left->val > 0){
            return max((root->left->val + root->val), max(left,right));
        }
        else{
            return max((root->val), max(left,right));
        }
    }
    else (root->right ){
        if(root->right->val > 0){
            return max((root->right->val + root->val), max(left,right));
        }
        else{
            return max((root->val), max(left,right));
        }
    }

}

int maxPathSum(TreeNode* root) {
    return solve(root);
}



// binary tree zigzag level order traversal
vector<vector<int>> zigzagLevelOrder(TreeNode* root){
    if(root == NULL) return {};
    vector<vector<int>> ans;
    queue<TreeNode*> q;
    bool leftToRight = true;
    q.push(root);
    vector<int> temp;

    while(!q.empty()){
        int size = q.size();
        for(int i = 0; i < size; i++){
            if(leftToRight){
                TreeNode* node = q.front();
                q.pop();
                temp.push_back(node->val);
                if(node->right) q.push(node->right);
                if(node->left) q.push(node->left);
            }
            else{
                TreeNode* node = q.front();
                q.pop();
                temp.push_back(node->val);
                // temp.insert(temp.begin(),node->val);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        ans.push_back(temp);
        temp.clear();
    }
    return ans;
}



// boundary traversal of binary tree
void leftPart(TreeNode<int>* root, vector<int>& v) {
    if(root == NULL || (root->left == NULL && root->right == NULL)) 
        return;
    
    v.push_back(root->data);
    
    if(root->left != NULL) 
        leftPart(root->left, v);
    else 
        leftPart(root->right, v);
}

void leafNodes(TreeNode<int>* root, vector<int>& v) {
    if(root == NULL) 
        return;
    if(root->left == NULL && root->right == NULL)
        v.push_back(root->data);
    
    leafNodes(root->left, v);
    leafNodes(root->right, v);
}

void rightPart(TreeNode<int>* root, vector<int>& v) {
    if(root == NULL || (root->left == NULL && root->right == NULL))
        return;

    if(root->right != NULL) 
        rightPart(root->right, v);
    else
        rightPart(root->left, v);

    v.push_back(root->data);
}

vector<int> traverseBoundary(TreeNode<int> *root) {
    vector<int> v;
    if(root == NULL) return v;
    
    v.push_back(root->data);
    if(root->left == NULL && root->right == NULL) return v;

    leftPart(root->left, v);
    leafNodes(root, v);
    rightPart(root->right, v);
    
    return v;
}


// top view of a binary tree
void solve(TreeNode* root , int index , map<int, int> &mp){
    if(root == NULL) return;

    if(mp.find(index) == mp.end()) mp[index] = root->val;

    solve(root->left,index-1,mp);
    solve(root->right,index+1,mp);
}
vector<int> getTopView(TreeNode *root){
    map<int,int> mp;
    solve(root,0,mp);

    vector<int> ans;
    for(auto x : mp){
        ans.push_back(x.second);
    }
    return ans;
}


// count complete tree nodes(leetcode 222)
void countNodes(TreeNode* root , int &count){
    if(root == NULL) return;
    count++;
    countNodes(root->left,count);
    countNodes(root->right,count);
}
int countNodes(TreeNode* root) {
    int count = 0;
    countNodes(root,count);
    return count;
}



// right view of binary tree
vector<int> rightSideView(TreeNode* root) {
    
}


// amount of time taken to burn a tree
TreeNode* findNode(TreeNode* root , int start){
    if(root == NULL) return NULL;
    if(root->val == start) return root;

    TreeNode* left = findNode(root->left,start);
    TreeNode* right = findNode(root->right,start);
    return left ? left : right;
}
void parentMapping(TreeNode* root , unordered_map<TreeNode*,TreeNode*> &mp){
    if(root == NULL) return;
    if(root->left) mp[root->left] = root;
    if(root->right) mp[root->right] = root;
    parentMapping(root->left,mp);
    parentMapping(root->right,mp);
}
int levelOrderTraversal(TreeNode* root , int start , unordered_map<TreeNode*,TreeNode*> &mp, unordered_map<TreeNode*,bool> &visited){
    queue<TreeNode*> q;
    q.push(root);
    visited[root] = true;
    int time = 0;
    while(!q.empty()){
        int size = q.size();
        for(int i = 0; i < size; i++){
            TreeNode* node = q.front();
            q.pop();
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
            if(mp.find(node) != mp.end()) q.push(mp[node]);
        }
        time++;
    }
    return time;
}
int amountOfTime(TreeNode* root, int start) {
    unordered_map<TreeNode*,TreeNode*> mp;
    parentMapping(root,mp);
    return levelOrderTraversal(root,start,mp);
}



// construct binary tree from inorder and postorder traversal
TreeNode* solve(vector<int> &inorder , vector<int> &postorder, int inStart , int inEnd , int postStart , int postEnd , unordered_map<int,int> &mp){
    if(inStart > inEnd || postStart > postEnd) return NULL;

    TreeNode* root = new TreeNode(postorder[postEnd]);
    int inorderIndex = mp[root->val];
    int leftSubtreeSize = inorderIndex - inStart;

    root->left = solve(inorder,postorder,inStart,inStart + leftSubtreeSize-1 , postStart , postEnd - leftSubtreeSize - 1,mp);
    root->right = solve(inorder,postorder,inStart+ inorderIndex+1,inEnd,postEnd - leftSubtreeSize,postEnd-1,mp);
    return root;
}
    

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int,int> mp;  
    for(int i = 0; i < inorder.size(); i++) mp[inorder[i]] = i;

    return solve(inorder,postorder,0,inorder.size()-1,0,postorder.size()-1,mp);
}



// LC 297 


// Encodes a tree to a single string.
string serialize(TreeNode* root) {
    string ans;
    queue<TreeNode*>q;
    q.push(root);
    
    while(!q.empty()){
        TreeNode* temp = q.front();
        ans += to_string(temp->val);
        q.pop();
        q.push(temp->left);
        q.push(temp->right);
    }
    return ans;
}

// Decodes your encoded data to tree.

void solve(int index , string s , queue<TreeNode*> q){
    if(index)
}
TreeNode* deserialize(string data) {
    
}

class Solution {
public:
    // Function to perform iterative Morris
    // inorder traversal of a binary tree
    vector<int> getInorder(TreeNode* root) {
        // Vector to store the
        // inorder traversal result
        vector<int> inorder;
        // Pointer to the current node,
        // starting from the root
        TreeNode* cur = root;
        
        // Loop until the current
        // node is not NULL
        while (cur != NULL) {
            // If the current node's
            // left child is NULL
            if (cur->left == NULL) {
                // Add the value of the current
                // node to the inorder vector
                inorder.push_back(cur->val);
                // Move to the right child
                cur = cur->right;
            } else {
                // If the left child is not NULL,
                // find the predecessor (rightmost node
                // in the left subtree)
                TreeNode* prev = cur->left;
                while (prev->right && prev->right != cur) {
                    prev = prev->right;
                }
                
                // If the predecessor's right child
                // is NULL, establish a temporary link
                // and move to the left child
                if (prev->right == NULL) {
                    prev->right = cur;
                    cur = cur->left;
                } else {
                    // If the predecessor's right child
                    // is already linked, remove the link,
                    // add current node to inorder vector,
                    // and move to the right child
                    prev->right = NULL;
                    inorder.push_back(cur->val);
                    cur = cur->right;
                }
            }
        }
        
        // Return the inorder
        // traversal result
        return inorder;
    }
};



// LC-94

// inorder traversal using morris traversal
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> inorder;
        TreeNode* cur = root;
        
        while (cur != NULL) {

            if (cur->left == NULL) {
                inorder.push_back(cur->val);
                cur = cur->right;
            } 
            else {
                // If the left child is not NULL,
                // find the predecessor (rightmost node
                // in the left subtree)
                TreeNode* prev = cur->left;
                while (prev->right && prev->right != cur) {
                    prev = prev->right;
                }
                
                if (prev->right == NULL) {
                    prev->right = cur;
                    cur = cur->left;
                } else {
                    prev->right = NULL;
                    inorder.push_back(cur->val);
                    cur = cur->right;
                }
            }
        }
        
        return inorder;
    }



// preorder traversal using morris traversal

vector<int> preorderTraversal(TreeNode* root) {
    TreeNode* curr = root;

    vector<int>preOrder;

    while(curr){
        if(!curr->left){
            preOrder.push_back(curr->val);
            curr = curr->right;
        }  
        else{
            preOrder.push_back(curr->val);

            TreeNode* temp = curr->left;
            while(temp->right && temp->right!=curr->right){
                temp = temp->right;
            }
            if(!temp->right){
                temp->right = curr->right;
            }
            else{
                temp->right=nullptr;
            }
        } 
    }
    return preOrder;
}


void solve(TreeNode* root , queue<TreeNode*>& q){
    if(!root) return ;
    q.push(root);
    solve(root->left,q);
    solve(root->right,q);
}

void flatten(TreeNode* root) {
    queue<TreeNode*>q;
    solve(root , q);

    TreeNode* node = q.front();
    q.pop();
    while(!q.empty()){
        node->left = nullptr;
        node->right = q.front();
        node = q.front();
        q.pop();
    }

}