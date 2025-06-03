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


// ninja's training - https://www.naukri.com/code360/problems/ninja-s-training_3621003

// using recursion
int solve(int i , int exclude , int n , vector<vector<int>>& points){
    if(i>=n) return 0;

    int maxSum = INT_MIN;
    for(int j = 0 ; j < n ; j++){
        if(j!=exclude){
            int sum = points[i][j] + solve(i+1,j,n,points);
            maxSum = max(maxSum,sum);
        }
    }
    return maxSum;
}

int ninjaTraining(int n, vector<vector<int>> &points){
    return solve(0,-1,points.size(),points);
}


// using memoization 
int solveMem(int i , int exclude , int n , vector<vector<int>>& points,vector<vector<int>>& dp){
    if(i>=n) return 0;
    if(dp[i][exclude+1]!=-1)return dp[i][exclude+1];

    int maxSum = INT_MIN;
    for(int j = 0 ; j < points[0].size() ; j++){
        if(j!=exclude){
            int sum = points[i][j] + solveMem(i+1,j,n,points,dp);
            maxSum = max(maxSum,sum);
        }
    }
    return dp[i][exclude+1] = maxSum;
}

int ninjaTraining(int n, vector<vector<int>> &points){
    vector<vector<int>> dp(n,vector<int>(points[0].size()+1,-1));
    return solveMem(0,-1,points.size(),points,dp);
}


// using tabulation
int solveTab(vector<vector<int>>& points){
    int n = points.size();
    vector<vector<int>> dp(n+1,vector<int>(points[0].size()+1,0));
    
    for(int i = n-1 ; i >=0 ; i--){
        for(int k = points[0].size()-1; k>=-1; k--){
            int maxSum = INT_MIN;
            for(int j = 0 ; j < points[0].size() ; j++){
                if(j!=k){
                    int sum = points[i][j] + dp[i+1][j+1];
                    maxSum = max(maxSum,sum);
                }
            }
            dp[i][k+1] = maxSum; 
        }
    }
    return dp[0][0];
}

int ninjaTraining(int n, vector<vector<int>> &points){
    return solveTab(points);
}


// tabulation using space optimization
int solveOptimal(vector<vector<int>>& points){
    int n = points.size();
    vector<vector<int>> dp(n+1,vector<int>(points[0].size()+1,0));
    vector<int> next(points.size()+1,0);
    vector<int> current(points.size()+1,0);
    
    for(int i = n-1 ; i >=0 ; i--){
        for(int k = points[0].size()-1; k>=-1; k--){
            int maxSum = INT_MIN;
            for(int j = 0 ; j < points[0].size() ; j++){
                if(j!=k){
                    int sum = points[i][j] + next[j+1];
                    maxSum = max(maxSum,sum);
                }
            }
            current[k+1] = maxSum; 
        }
        next = current;
    }
    return current[0];
}

int ninjaTraining(int n, vector<vector<int>> &points){
    return solveOptimal(points);
}