#include<bits/stdc++.h>
using namespace std;

  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };

//  codestudio : build min heap 
void heapify(vector<int>& arr, int n, int i) {
    int leftChildIndex = 2 * i + 1;
    int rightChildIndex = 2 * i + 2;
    int largest = i;

    // Check if left child exists and is greater than the root
    if (leftChildIndex < n && arr[leftChildIndex] > arr[largest]) {
        largest = leftChildIndex;
    }

    // Check if right child exists and is greater than the largest so far
    if (rightChildIndex < n && arr[rightChildIndex] > arr[largest]) {
        largest = rightChildIndex;
    }

    // If the largest is not the root, swap and continue heapifying
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

vector<int> buildHeap(vector<int> arr, int n){
    for (int i= n/2-1; i>=0;i--){
        heapify(arr, n , i);
    }
    return arr;
}



// check if the array represents max heap
bool solve(int arr[] , int n , int i ){
    if(i>=n/2) return true;

    int leftChildIndex = 2 * i + 1;
    int rightChildIndex = 2 * i + 2;

    if(rightChildIndex<n){
        return arr[i]>arr[leftChildIndex] && arr[i]>arr[rightChildIndex];
    }
    else{
        if(leftChildIndex<n){
            return arr[i]>arr[leftChildIndex];
        }
        else{
            return true;
        }
    }
}
bool isMaxHeap(int arr[], int n){
    for (int i = n/2-1; i >=0; i--){
        if (!solve(arr , n , i )){
            return false;
        }
    }
    return true;
}




// LC 215

int findKthLargest(vector<int>& nums, int k) {
    priority_queue<vector<int>,greater<int>> pq;
    for (int   i = 0;   i< k;i  ++){
        pq.push(nums[i]);
    }

    for(int i = k ; i<nums.size();i++){
        if(nums[i]>pq.top()) {
            pq.push(nums[i]);
        }  
    }

    return pq.top();
}



// LC 23
struct CompareNodes {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    int k  = lists.size();
    priority_queue<ListNode*,vector<ListNode*>,CompareNodes> pq;
    for (int  i = 0; i < k; i++){
        pq.push(lists[i]);
    }
    
    ListNode*  ansListHead = new ListNode(-1);
    ListNode* tempNode = new ListNode();
    ansListHead->next = tempNode;
    while(!pq.empty()){
        ListNode* temp = pq.top();
        int tempVal = temp->val;

        tempNode->val = temp->val;
        tempNode->next = new ListNode(tempVal);
        tempNode = tempNode->next;
        
        if(temp->next) pq.push(temp->next);
    }

    ListNode* newHead = ansListHead->next;
    ansListHead->next = nullptr;
    delete  ansListHead;
    
    return newHead;
}



// LC - 355. Design Twitter

class Twitter {
    int time;
    unordered_map<int, unordered_set<int>> followees;
    unordered_map<int, vector<pair<int, int>>> tweets;

public:
    Twitter() {
        time = 0;
    }

    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({time++, tweetId});
    }

    vector<int> getNewsFeed(int userId) {
        priority_queue<pair<int, int>> pq;  // max-heap on time

        // Add user's own tweets
        for (auto &t : tweets[userId]) {
            pq.push(t);
        }

        // Add tweets of followees
        for (auto &f : followees[userId]) {
            for (auto &t : tweets[f]) {
                pq.push(t);
            }
        }

        // Get top 10 recent tweets
        vector<int> res;
        int cnt = 0;
        while (!pq.empty() && cnt < 10) {
            res.push_back(pq.top().second);
            pq.pop();
            cnt++;
        }
        return res;
    }

    void follow(int followerId, int followeeId) {
        if (followerId == followeeId) return;
        followees[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        followees[followerId].erase(followeeId);
    }
};



// minimum cost to cut ropes - https://www.geeksforgeeks.org/problems/minimum-cost-of-ropes-1587115620/1



// LC - 703. Kth Largest Element in a Stream



int solve(int i , int j , int time , vector<vector<int>>& waitCost ,int m , int n, vector<vector<vector<int>>>&dp ){
    if(i==m-1 && j ==n-1) return m*n;
    if(i>=m)return INT_MAX;
    if(j>=n) return INT_MAX;
    if(dp[i][j][time]!=-1)return dp[i][j][time];


    if(time%2==0){
        return dp[i][j][time] = waitCost[i][j] + solve(i,j,time+1,waitCost ,  m ,  n,dp);
    }

    int moveDown = solve(i+1,j,time+1,waitCost,m,n,dp);
    int moveRight = solve(i,j+1,time+1,waitCost,m,n,dp);

    return dp[i][j][time] =  min(moveDown,moveRight)+ (i+1)*(j+1);
}

    long long minCost(int m, int n, vector<vector<int>>& waitCost) {
        vector<vector<vector<int>>>dp(m,vector<vector<int>>(n,vector<int>(2*m*n+1,-1)));
        return solve(0,0,1,waitCost , m,n,dp);
    }
    
    
    
    int solveTab ( vector<vector<int>>&waitCost , int m , int n){
        vector<vector<vector<int>>>dp(m,vector<vector<int>>(n,vector<int>(2*m*n+1,-1)));
        
        for(int i = 0 ; i < 2*m*n+1; i++){
            dp[m-1][n-1][i] = m*n;
        }
        
        for(int i = m-1; i >= 0 ; i--){
            for(int j = n-1 ; j>=0; j--){
                for(int time = 2*m*n-1 ; time>=0 ; time--){
                    if(time%2==0){
                        dp[i][j][time] = waitCost[i][j] + dp[i][j][time+1];
                    }
                    
                    int moveDown = dp[i+1][j][time+1];
                    int moveRight = dp[i][j+1][time+1];
                    
                    dp[i][j][time] =  min(moveDown,moveRight)+ (i+1)*(j+1);
                }   
            }
        }
        return dp[0][0][1];
    }
    
    long long minCost(int m, int n, vector<vector<int>>& waitCost) {
        return solveTab(waitCost ,m ,n);
    }


    int dfs(int i , int time ,vector<int>&visited , unordered_map<int , vector<vector<int>>>&adjList){
        int mini = INT_MAX;
        visited[i]=true;
        for(auto& neigh: adjList[i] ){
            if(!visited[neigh[0]]){
                int tempTime;
                if(time>=neigh[2] && time <=neigh[3]){
                    tempTime = time+1;
                }
                else if(time<neigh[2]){
                    tempTime = neigh[2]+1;
                }
                else{
                    continue;
                }
                int recursiveCall = dfs(neigh[0],tempTime , visited,adjList);
                mini = min(mini ,recursiveCall);
            }
        }
        return mini;
    }

    int minTime(int n, vector<vector<int>>& edges) {
        unordered_map<int , vector<vector<int>>> adjList;

        for(auto &i: edges){
            adjList[i[0]].push_back({i[1],i[2],i[3]});  // neighbouring node , start time , end time 
        }

        vector<int>visited(n,0);
        return dfs(0,0,visited , adjList);
    }


    #include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int dfs(int i , int time ,vector<int>&visited , unordered_map<int , vector<vector<int>>>&adjList){
        int mini = INT_MAX;
        visited[i]=true;
        for(auto& neigh: adjList[i] ){
            if(!visited[neigh[0]]){
                int tempTime;
                if(time>=neigh[2] && time <=neigh[3]){
                    tempTime = time+1;
                }
                else if(time<neigh[2]){
                    tempTime = neigh[2]+1;
                }
                else{
                    continue;
                }
                int recursiveCall = dfs(neigh[0],tempTime , visited,adjList);
                mini = min(mini ,recursiveCall);
            }
        }
        return mini;
    }

    int minTime(int n, vector<vector<int>>& edges) {
        unordered_map<int , vector<vector<int>>> adjList;

        for(auto &i: edges){
            adjList[i[0]].push_back({i[1],i[2],i[3]});  // neighbouring node , start time , end time 
            // cout<<" "<< adjList[i[0]][0][0]<< " "<<adjList[i[0]][0][1]<<" " << adjList[i[0]][0][2]<<" ";
        }
        
        vector<int>visited(n,0);
        return dfs(0,0,visited , adjList);
    }
};



// Maximum Sum Combination- https://www.geeksforgeeks.org/problems/maximum-sum-combination/1

vector<int> topKSumPairs(vector<int>& a, vector<int>& b, int k) {
    int n = a.size();

    // Sort both arrays in descending order
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());

    // Max-heap: pair<sum, pair<index in a, index in b>>
    priority_queue<pair<int, pair<int, int>>> maxHeap;

    // Set to keep track of visited index pairs
    set<pair<int, int>> visited;

    // Initial pair (0, 0)
    maxHeap.push({a[0] + b[0], {0, 0}});
    visited.insert({0, 0});

    vector<int> result;

    while (k-- && !maxHeap.empty()) {
        auto top = maxHeap.top();
        maxHeap.pop();

        int sum = top.first;
        int i = top.second.first;
        int j = top.second.second;

        result.push_back(sum);

        // Next pair: (i+1, j)
        if (i + 1 < n && visited.find({i + 1, j}) == visited.end()) {
            maxHeap.push({a[i + 1] + b[j], {i + 1, j}});
            visited.insert({i + 1, j});
        }

        // Next pair: (i, j+1)
        if (j + 1 < n && visited.find({i, j + 1}) == visited.end()) {
            maxHeap.push({a[i] + b[j + 1], {i, j + 1}});
            visited.insert({i, j + 1});
        }
    }

    return result;
}