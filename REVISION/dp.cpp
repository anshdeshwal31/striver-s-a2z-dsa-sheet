#include<bits/stdc++.h>
using namespace std;


// frog jump - https://www.geeksforgeeks.org/problems/geek-jump/1
// using recursion
int solve(int i , vector<int>& height){
    if(i==1) return height[1]- height[0];
    if(i==0) return 0;

    int choice1 = solve(i-1,height) + abs(height[i] - height[i-1]);
    int choice2 = solve(i-2,height) + abs(height[i] - height[i-2]);
    return min(choice1,choice2);
}

int minCost(vector<int>& height) {
    return solve(height.size(),height);
}


// using memoization
int solveMem(int i , vector<int>& height, vector<int>& memo){
    if(i==1) return abs(height[1]- height[0]);
    if(i==0) return 0;
    if(memo[i]!=-1)return memo[i];

    int choice1 = solveMem(i-1,height,memo) + abs(height[i] - height[i-1]);
    int choice2 = solveMem(i-2,height,memo) + abs(height[i] - height[i-2]);
    return memo[i] = min(choice1,choice2);
}

int minCost(vector<int>& height){
    int n = height.size();
    vector<int>memo(n,-1);
    return solveMem(n-1,height,memo);
}


// using tabulation
int solveTab(vector<int>& height){
    int n = height.size();
    vector<int> dp(n,INT_MAX);
    dp[0] = 0;
    dp[1] = abs(height[1]- height[0]);
    
    for(int i = 2 ; i < n ; i++){
        int choice1 = dp[i-1] + abs(height[i] - height[i-1]);
        int choice2 = dp[i-2] + abs(height[i] - height[i-2]);
        dp[i] = min(choice1,choice2); 
    }
    return dp[n-1];
}

int minCost(vector<int>& height){
    return solveTab(height);
}


// tabulation with space optimization
int solveOptimal(vector<int>& height){
    int n = height.size();
    int prev2 = 0;
    int prev1 = abs(height[1]- height[0]);
    int curr = 0;
    
    for(int i = 2 ; i < n ; i++){
        int choice1 = prev1 + abs(height[i] - height[i-1]);
        int choice2 = prev2 + abs(height[i] - height[i-2]);
        curr = min(choice1,choice2); 
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}

int minCost(vector<int>& height){
    return solveOptimal(height);
}