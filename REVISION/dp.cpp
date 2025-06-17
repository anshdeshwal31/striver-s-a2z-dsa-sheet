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


int solve(int i , int j , int n , int m ){
    if(i==n-1 && j==m-1) return 0;

    int choice1 = 0;
    int choice2 = 0;
    if(i+1<n){
         choice1 = 1+ solve(i+1,j,n,m);
    }
    if(j+1<m){
         choice2 = 1+ solve(i,j+1,n,m);
    }
    return choice1+choice2;
}


// LC - 931. Minimum Falling Path Sum 

// using recursion
int solve(int row , int col , int rowSize , int colSize, vector<vector<int>>& matrix){
    if(row == rowSize) return 0;

    int choice1 = INT_MAX;
    int choice2 = INT_MAX;
    int choice3 = INT_MAX;

    if(col-1>=0) choice1 = solve(row+1,col-1,rowSize,colSize,matrix);

    choice2 = solve(row+1,col,rowSize,colSize,matrix);

    if(col+1<colSize) choice3 = solve(row+1,col+1,rowSize,colSize,matrix);

    return matrix[row][col] + min(choice1,min(choice2,choice3));
 }

int minFallingPathSum(vector<vector<int>>& matrix) {
    int rowSize = matrix.size();
    int colSize = matrix[0].size();

    int minAns = INT_MAX;
    for(int j = 0 ; j < colSize; j++){
        minAns = min(solve(0,j,rowSize,colSize,matrix),minAns);
    }
    return minAns;
}



// rod cutting - https://www.geeksforgeeks.org/problems/rod-cutting0840/1

// using recursion

int solve(int n, vector<int>& price) {
    // base case: rod length zero means no price
    if (n == 0) return 0;

    int ans = 0;
    // try all possible first cuts from 1 to n
    for (int i = 1; i <= n; i++) {
        int cutPrice = price[i-1]; // price for cutting length i
        int remainingPrice = solve(n - i, price); // solve for remaining rod
        ans = max(ans, cutPrice + remainingPrice); // maximize the total
    }

    return ans;
}

int cutRod(vector<int>& price) {
    int n = price.size();
    return solve(n, price);
}



// LC - 1143. Longest Common Subsequence

//  print LCS - https://www.naukri.com/code360/problems/print-longest-common-subsequence_8416383


// using recursion
void solve(int i , int j ,string& s1, string& s2,int len, int& ans){
    if(i==s1.size() && j == s2.size()) return;

    if(s1[i]==s2[j]){
        len++;
        ans = max(ans,len);
        solve(i+1,j+1,s1,s2,len,ans);
    }
    else{
        len = 0;
        solve(i+1,j , s1,s2,len,ans); 
        solve(i,j+1 , s1,s2,len,ans); 
    }
}

int longestCommonSubstr(string& s1, string& s2) {
    // your code here
    int ans = 0;
    solve(0,0,s1,s2,0,ans);
    return ans;
}


// using memoization
void solveMem(int i , int j ,string& s1, string& s2,int len, int& ans){
    if(i==s1.size() && j == s2.size()) return;

    if(s1[i]==s2[j]){
        len++;
        ans = max(ans,len);
        solveMem(i+1,j+1,s1,s2,len,ans);
    }
    else{
        len = 0;
        solveMem(i+1,j , s1,s2,len,ans); 
        solveMem(i,j+1 , s1,s2,len,ans); 
    }
}

int longestCommonSubstr(string& s1, string& s2) {
    // your code here
    int ans = 0;
    solveMem(0,0,s1,s2,0,ans);
    return ans;
}


// longest common substring -https://www.geeksforgeeks.org/problems/longest-common-substring1452/1

// using recursion 
class Solution {
public:
    int solve(int i, int j, string& s1, string& s2, int& ans) {
        if(i == s1.size() || j == s2.size()) return 0;

        int res = 0;
        if(s1[i] == s2[j]){
            res = 1 + solve(i+1, j+1, s1, s2, ans);
            ans = max(ans, res);
        }

        // Explore other possibilities independently — don't chain len
        solve(i+1, j, s1, s2, ans);
        solve(i, j+1, s1, s2, ans);

        return res;
    }

    int longestCommonSubstr(string &s1, string &s2) {
        int ans = 0;
        solve(0, 0, s1, s2, ans);
        return ans;
    }
};


// using memoization 

class Solution {
public:
    int solve(int i, int j, string& s1, string& s2, int& ans, vector<vector<int>> &dp) {
        if(i == s1.size() || j == s2.size()) return 0;

        if(dp[i][j] != -1) return dp[i][j];

        int res = 0;
        if(s1[i] == s2[j]){
            res = 1 + solve(i+1, j+1, s1, s2, ans, dp);
            ans = max(ans, res);
        }

        // Explore other paths independently (not chaining res here)
        solve(i+1, j, s1, s2, ans, dp);
        solve(i, j+1, s1, s2, ans, dp);

        return dp[i][j] = res;
    }

    int longestCommonSubstr(string &s1, string &s2) {
        int ans = 0;
        int n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        solve(0, 0, s1, s2, ans, dp);
        return ans;
    }
};



// LC - 1312. Minimum Insertion Steps to Make a String Palindrome

// using recursion
int solve(int i , int j , string& s){
    if(i>=j) return 0;

    if(s[i]==s[j]){
        return solve(i+1, j-1, s);
    }
    int call1 = 1+ solve(i+1 ,j ,s);
    int call2 = 1+ solve(i,j-1,s);
    return min(call1,call2);
}

int minInsertions(string s) {
    int n  = s.size();
    return solve(0,n-1,s);
}


// using memoization
int solveMem(int i , int j , string& s,vector<vector<int>>& dp){
    if(i>=j) return 0;
    if(dp[i][j]!=-1) return dp[i][j];

    if(s[i]==s[j]){
        return solveMem(i+1, j-1, s,dp);
    }
    int call1 = 1+ solveMem(i+1 ,j ,s,dp);
    int call2 = 1+ solveMem(i,j-1,s,dp);
    return dp[i][j] = min(call1,call2);
}

int minInsertions(string s) {
    int n = s.size();
    vector<vector<int>> dp(n,vector<int>(n,-1));
    return solveMem(0,n-1,s,dp);
}



// LC - 583. Delete Operation for Two Strings

// using recursion

int solve(int i , int j , string word1, string word2){
    if(i == word1.size()) return word2.size()-j;
    if(j == word2.size()) return word1.size()-i;
    
    if(word1[i]== word2[j]) return solve(i+1,j+1,word1,word2);

    int deleteFrom1 = 1+ solve(i+1,j,word1,word2);
    int deleteFrom2 = 1+ solve(i,j+1,word1,word2);
    return min(deleteFrom1,deleteFrom2);
}

int minDistance(string word1, string word2) {
    return solve(0,0,word1,word2);
}


// LC - 1092. Shortest Common Supersequence 

// using recursion

string shortestSupersequence(int i, int j, string& str1, string& str2) {
    if(i == str1.size()) return str2.substr(j); // if str1 ends, take rest of str2
    if(j == str2.size()) return str1.substr(i); // if str2 ends, take rest of str1

    if(str1[i] == str2[j]) {
        // If both characters match, include it once and move both
        return str1[i] + shortestSupersequence(i+1, j+1, str1, str2);
    } else {
        // Else, try both options: take str1[i] or str2[j]
        string option1 = str1[i] + shortestSupersequence(i+1, j, str1, str2);
        string option2 = str2[j] + shortestSupersequence(i, j+1, str1, str2);

        // Return the shorter one
        return (option1.size() < option2.size()) ? option1 : option2;
    }
}

string shortestCommonSupersequence(string str1, string str2) {
    return shortestSupersequence(0, 0, str1, str2);
}




// LC - 115 Distinct subsequences

// using recursion

int countSubsequences(string s, string t, int i, int j) {
    if (j == t.size()) return 1;
    if (i == s.size()) return 0;

    if (s[i] == t[j]) {
        return countSubsequences(s, t, i + 1, j + 1) 
               + countSubsequences(s, t, i + 1, j);
    } else {
        return countSubsequences(s, t, i + 1, j);
    }
}

int numDistinct(string s, string t) {
    return countSubsequences(s, t, 0, 0);
}