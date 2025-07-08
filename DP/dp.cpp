#include<bits/stdc++.h>
using namespace std;
int mod = 1e9 + 7;

// climb stairs
int solve(int n){
    if(n==0 || n==1) return 1;
    return solve(n-1) + solve(n-2);
}
int climbStairs(int n) {
    return solve(n);
}


// geek jump

// using recursion
int solve(int n,vector<int>& height){
    if(n==0) return 0;
    if(n==1) return abs(height[1] - height[0]);

    int oneStep = abs(height[n] - height[n-1]) + solve(n-1,height);
    int twoStep = abs(height[n] - height[n-2]) + solve(n-2,height);
    return min(oneStep,twoStep);
}
int minimumEnergy(vector<int>& height, int n) {
    return solve(n-1,height);
}


// using memoization
int solveMem(int n,vector<int>& height,vector<int>& dp){
    if(n==0) return 0;
    if(n==1) return abs(height[1] - height[0]);
    if(dp[n] != -1) return dp[n];

    int oneStep = abs(height[n] - height[n-1]) + solveMem(n-1,height,dp);
    int twoStep = abs(height[n] - height[n-2]) + solveMem(n-2,height,dp);
    return dp[n] = min(oneStep,twoStep);
}
int minimumEnergy(vector<int>& height, int n) {
    vector<int> dp(n+1,-1);
    return solveMem(n-1,height,dp);
}


// using tabulation
int solveTab(int n,vector<int>& height){
    vector<int> dp(n+1,0);
    dp[1] = abs(height[1] - height[0]);
    for(int i=2;i<=n;i++){
        int oneStep = abs(height[i] - height[i-1]) + dp[i-1];
        int twoStep = abs(height[i] - height[i-2]) + dp[i-2];
        dp[i] = min(oneStep,twoStep);
    }
    return dp[n];
}
int minimumEnergy(vector<int>& height, int n) {
    return solveTab(n-1,height);
}




// using tabulation with space optimization
int solveOptimal(int n , vector<int>& height){
    int prev = 0;
    int curr = abs(height[1] - height[0]);
    int next = 0;
    for(int i=2;i<=n;i++){
        int oneStep = abs(height[i] - height[i-1]) + curr;
        int twoStep = abs(height[i] - height[i-2]) + prev;
        next = min(oneStep,twoStep);
        prev = curr;
        curr = next;
    }
    return curr;
}
int solveTab(int n,vector<int>& height){
    return solveOptimal(n,height);
}


// minimal cost(gfg)

// using recursion
int solve(vector<int>& arr,int n,int k){
    if(n<=0) return 0;
    if(n==1) return abs(arr[1] - arr[0]);

    int ans = INT_MAX;
    for(int i=1;i<=k;i++){
        if(n-i>=0){
            ans = min(ans,abs(arr[n] - arr[n-i]) + solve(arr,n-i,k));
        }
    }
    return ans;
}
int minimizeCost(vector<int>& arr, int& k) {
    return solve(arr,arr.size()-1,k);
}


// using memoization
int solveMem(vector<int>& arr,int n,int k,vector<int>& dp){
    if(n<=0) return 0;
    if(n==1) return abs(arr[1] - arr[0]);
    if(dp[n] != -1) return dp[n];

    int ans = INT_MAX;
    for(int i=1;i<=k;i++){
        if(n-i>=0){
            ans = min(ans,abs(arr[n] - arr[n-i]) + solveMem(arr,n-i,k,dp));
        }
    }
    return dp[n] = ans;
}
int minimizeCost(vector<int>& arr, int& k) {
    vector<int> dp(arr.size(),-1);
    return solveMem(arr,arr.size()-1,k,dp);
}


// using tabulation
int solveTab(vector<int>& arr,int n,int k){
    vector<int> dp(n+1,0);
    dp[1] = abs(arr[1] - arr[0]);
    dp[0] = 0;
    for(int i=2;i<=n;i++){
        for(int j=1;j<=k;j++){
            if(i-j>=0){
                dp[i] = min(dp[i],abs(arr[i] - arr[i-j]) + dp[i-j]);
            }
        }
    }
    return dp[n];
}
int minimizeCost(vector<int>& arr, int& k) {
    return solveTab(arr,arr.size()-1,k);
}



// subset sum problem 


// using recursion
bool solve(vector<int>& arr,int target, int i ){
    if (target == 0) return true;
    if(target < 0 || i >= arr.size()) return false;

    for(int j=i;j<arr.size();j++){
        if(solve(arr,target-arr[j],j+1)) return true;
    }
    return false;
}
bool isSubsetSum(vector<int>arr, int sum){
    return solve(arr,sum,0);
}


// memoization
bool solveMem(vector<int>& arr,int target, int i,vector<vector<int>>& dp){
    if (target == 0) return true;
    if(target < 0 || i >= arr.size()) return false;
    if(dp[i][target] != -1) return dp[i][target];

    for(int j=i;j<arr.size();j++){
        if(solveMem(arr,target-arr[j],j+1,dp)) return dp[i][target] = true;
    }
    return dp[i][target] = false;
}
bool isSubsetSum(vector<int>arr, int sum){
    vector<vector<int>> dp(arr.size(),vector<int>(sum+1,-1));
    return solveMem(arr,sum,0,dp);
}


// using tabulation
bool solveTab(vector<int>& arr  , int sum){
    vector<vector<bool>> dp(arr.size()+1,vector<bool>(sum+1,false));
    for(int i=0;i<=arr.size();i++){
        dp[i][0] = true;
    }

    for(int i = arr.size()-1;i>=0;i--){
        for(int j=1;j<=sum;j++){
            for(int k=i;k<arr.size();k++){
                if(j-arr[k] >= 0) {
                    if(dp[k+1][j-arr[k]]) dp[i][j] = true;
                }
            }
        }
    }
    return dp[0][sum];
}
bool isSubsetSum(vector<int>arr, int sum){
    return solveTab(arr,sum);
}   


// assign cookies

int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(),g.end());
    sort(s.begin(),s.end());
    
    int i=0,j=0;
    while(i<g.size() && j<s.size()){
        if(g[i] <= s[j]){
            i++;
            j++;
        }
        else{
            j++;
        }
    }
    return i;
}


// rod cutting


// using recursion
int solve(int price[],int n){
    if(n==0) return 0;
    int ans = INT_MIN;
    for(int i=1;i<=n;i++){
        ans = max(ans,price[i-1] + solve(price,n-i));
    }
    return ans;
}

int cutRod(int price[], int n) {
    return solve(price,n);
}


// using memoization
int solveMem(int price[],int n,vector<int>& dp){
    if(n==0) return 0;
    if(dp[n] != -1) return dp[n];
    int ans = INT_MIN;
    for(int i=1;i<=n;i++){
        ans = max(ans,price[i-1] + solveMem(price,n-i,dp));
    }
    return dp[n] = ans;
}
int cutRod(int price[], int n) {
    vector<int> dp(n+1,-1);
    return solveMem(price,n,dp);
}


// using tabulation
int solveTab(int price[],int n){
    vector<int> dp(n+1,INT_MIN);
    dp[0] = 0;
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            dp[i] = max(dp[i],price[j-1] + dp[i-j]);
        }
    }
    return dp[n];
}

int cutRod(int price[], int n) {
    return solveTab(price,n);
}





// const in js
// difference between json and javascript object





// unique paths


// using recursion
int solve(int startRow,int startCol,int m , int n , vector<vector<int>>& dir){
    if(startRow == m-1 && startCol == n-1) return 1;

    int numOfPaths = 0;
    for(auto d : dir){
        int x = startRow + d[0];
        int y = startCol + d[1];
        if(x >= 0 && x < m && y >= 0 && y < n){
            numOfPaths += solve(x,y,m,n,dir);
        }
    }
    return numOfPaths;
}

int uniquePaths(int m, int n) {
    vector<vector<int>> dir = {{1, 0}, {0, 1}}; // right, down
    return solve(0,0,m,n,dir);
}


// using memoization
int solve(int startRow,int startCol,int m , int n , vector<vector<int>>& dir, vector<vector<int>>& dp){
    if(startRow == m-1 && startCol == n-1) return 1;
    if(dp[startRow][startCol] != -1) return dp[startRow][startCol];

    int numOfPaths = 0;
    for(auto d : dir){
        int x = startRow + d[0];
        int y = startCol + d[1];
        if(x >= 0 && x < m && y >= 0 && y < n){
            numOfPaths += solve(x,y,m,n,dir);
        }
    }
    return dp[startRow][startCol] = numOfPaths;
}

int uniquePaths(int m, int n) {
    vector<vector<int>> dir = {{1, 0}, {0, 1}}; // right, down
    vector<vector<int>> dp(m,vector<int>(n,-1));
    return solve(0,0,m,n,dir,dp);
}  


// unique paths
// using tabulation

int solveTab(int startRow , int startCol, int m , int n , vector<vector<int>>& dir){
    vector<vector<int>> dp(m,vector<int>(n,0));
    dp[m-1][n-1] = 1;

    for(int row = m-1; row >= 0; row--){
        for(int col = n-1; col >= 0; col--){
            if(row == m-1 && col == n-1) continue; // Skip the bottom-right corner
            int numOfPaths = 0;
            for(auto d : dir){
                int x = row + d[0];
                int y = col + d[1];
                if(x >= 0 && x < m && y >= 0 && y < n){
                    numOfPaths += dp[x][y];
                }
            }
            dp[row][col] = numOfPaths;
        }
    }
    return dp[0][0];
}

int uniquePaths(int m, int n) {
    vector<vector<int>> dir = {{1, 0}, {0, 1}}; // right, down
    return solveTab(0, 0, m, n, dir);
}



// unique paths 2

// using memoization
int solve(int startRow,int startCol,int m , int n , vector<vector<int>>& dir, vector<vector<int>>& obstacleGrid, vector<vector<int>>& dp){
    if(obstacleGrid[0][0] == 1) return 0;
    if(startRow == m-1 && startCol == n-1) return 1;
    if(dp[startRow][startCol] != -1) return dp[startRow][startCol];

    int numOfPaths = 0;
    for(auto d : dir){
        int x = startRow + d[0];
        int y = startCol + d[1];
        if(x >= 0 && x < m && y >= 0 && y < n && obstacleGrid[x][y] == 0){
            numOfPaths += solve(x,y,m,n,dir,obstacleGrid,dp);
        }
    }
    dp[startRow][startCol] = numOfPaths;
    return dp[startRow][startCol];
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();
    vector<vector<int>> dp(m,vector<int>(n,-1));
    vector<vector<int>> dir = {{1, 0}, {0, 1}}; // right, down
    return solve(0,0,m,n,dir,obstacleGrid);
}


// using tabulation
int solveTab(int startRow,int startCol,int m , int n , vector<vector<int>>& dir, vector<vector<int>>& obstacleGrid){
    vector<vector<int>> dp(m,vector<int>(n,0));
    dp[m-1][n-1] = 1;

    for(int row = m-1; row >= 0; row--){
        for(int col = n-1; col >= 0; col--){
            if(row == m-1 && col == n-1) continue; // Skip the bottom-right corner
            int numOfPaths = 0;
            for(auto d : dir){
                int x = row + d[0];  // 1 will be added for right , 0 will be added for down
                int y = col + d[1];  // 0 will be added for right , 1 will be added for down
                if(x >= 0 && x < m && y >= 0 && y < n && obstacleGrid[x][y] == 0){
                    numOfPaths += dp[x][y];
                }
            }
            dp[row][col] = numOfPaths;
        }
    }
    return dp[0][0];
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    if(obstacleGrid[0][0] == 1) return 0;
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();
    vector<vector<int>> dir = {{1, 0}, {0, 1}}; // right, down
    return solveTab(0,0,m,n,dir,obstacleGrid);
}



// using tabulation with space optimization
int solveOptimal(int startRow,int startCol,int m , int n , vector<vector<int>>& dir, vector<vector<int>>& obstacleGrid){
    vector<int> next(n,0);
    vector<int> curr(n,0);
    next[n-1] = 1;

    for(int row = m-1; row >= 0; row--){
        for(int col = n-1; col >= 0; col--){
            if(row == m-1 && col == n-1) continue; // Skip the bottom-right corner
            int numOfPaths = 0;
            for(auto d : dir){
                int x = row + d[0];  // 1 will be added for right , 0 will be added for down
                int y = col + d[1];  // 0 will be added for right , 1 will be added for down
                if(x >= 0 && x < m && y >= 0 && y < n && obstacleGrid[x][y] == 0){
                    numOfPaths += curr[y];
                }
            }
            curr[col] = numOfPaths;
            next = curr;
        }
    }
    return curr[0];
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    if(obstacleGrid[0][0] == 1) return 0;
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();
    vector<vector<int>> dir = {{1, 0}, {0, 1}}; // right, down
    return solveOptimal(0,0,m,n,dir,obstacleGrid);
}


// house robber

// using recursion
int solve(vector<int> &arr, int i){
    if(i == arr.size()-1) return arr[i];
    if(i >= arr.size()) return 0;

    int include = arr[i] + solve(arr,i+2);
    int exclude = solve(arr,i+1);
    return max(include,exclude);
}
int rob(vector<int>& arr) {
    return solve(arr,0);
}



// house robber 2

// using recursion
int solve(vector<int> &arr, int i, int n){
    if(i == n) return arr[i];
    if(i > n) return 0;

    int include = arr[i] + solve(arr,i+2,n);
    int exclude = solve(arr,i+1,n);
    return max(include,exclude);
}
int rob(vector<int>& arr) {
    if (arr.size() == 0) return 0;
    if (arr.size() == 1) return arr[0];

    int ans1 = solve(arr,0,arr.size()-2);
    int ans2 = solve(arr,1,arr.size()-1);
    return max(ans1,ans2);
}


// longest common subsequence

// using recursion
int solve(string text1, string text2, int i, int j){
    if(i == text1.size() || j == text2.size()) return 0;
    if(text1[i] == text2[j]) return 1 + solve(text1,text2,i+1,j+1);
    
    int choice1 = solve(text1,text2,i+1,j);
    int choice2 = solve(text1,text2,i,j+1);
    return max(choice1,choice2);
}
int longestCommonSubsequence(string text1, string text2) {
    return solve(text1,text2,0,0);
}


// using memoization
int solve(string text1, string text2, int i, int j, vector<vector<int>> &dp){
    if(i == text1.size() || j == text2.size()) return 0;
    if(text1[i] == text2[j]) return 1 + solve(text1,text2,i+1,j+1);
    if(dp[i][j] != -1) return dp[i][j];
    
    int choice1 = solve(text1,text2,i+1,j);
    int choice2 = solve(text1,text2,i,j+1);
    return dp[i][j] = max(choice1,choice2);
}
int longestCommonSubsequence(string text1, string text2) {
    vector<vector<int>> dp(text1.size(),vector<int>(text2.size(),-1));
    return solve(text1,text2,0,0,dp);
}


// using tabulation
int solveTab(string text1, string text2, int i, int j){
    vector<vector<int>> dp(text1.size()+1,vector<int>(text2.size()+1,0));

    for(int i = text1.size()-1;i>=0;i--){
        for(int j = text2.size()-1;j>=0;j--){
            if(text1[i] == text2[j]) dp[i][j] = 1 + dp[i+1][j+1];
            else{
                int choice1 =dp[i+1][j];
                int choice2 = dp[i][j+1];
                dp[i][j] = max(choice1,choice2);
            }
        }
    }
    return dp[0][0];
}
int longestCommonSubsequence(string text1, string text2) {
    return solveTab(text1,text2,0,0);
}
int solveTab(string text1, string text2, int i, int j){
    vector<vector<int>> dp(text1.size()+1,vector<int>(text2.size()+1,0));

    for(int i = text1.size()-1;i>=0;i--){
        for(int j = text2.size()-1;j>=0;j--){
            if(text1[i] == text2[j]) dp[i][j] = 1 + dp[i+1][j+1];
            else{
                int choice1 =dp[i+1][j];
                int choice2 = dp[i][j+1];
                dp[i][j] = max(choice1,choice2);
            }
        }
    }
    return dp[0][0];
}
int longestCommonSubsequence(string text1, string text2) {
    return solveTab(text1,text2,0,0);
}

// using tabulation with space optimization
int solveTab(string text1, string text2, int i, int j){
    vector<int> curr(text2.size()+1,0);
    vector<int> next(text2.size()+1,0);

 
    for(int i = text1.size()-1;i>=0;i--){
        for(int j = text2.size()-1;j>=0;j--){
            if(text1[i] == text2[j]) curr[j] = 1 + next[j+1];
            else{
                int choice1 =next[j];
                int choice2 = curr[j+1];
                curr[j] = max(choice1,choice2);
            }
        }
        next = curr;
    }
    return curr[0];
}
int longestCommonSubsequence(string text1, string text2) {
    return solveTab(text1,text2,0,0);
}



// print all the LCS in lexographical order

// using recursion
void findLCS(string& s, string& t, int i, int j, string current, set<string>& result) {
    if (i == s.length() || j == t.length()) {
        result.insert(current);
        return;
    }

    if (s[i] == t[j]) {
        findLCS(s, t, i + 1, j + 1, current + s[i], result);
    } else {
        findLCS(s, t, i + 1, j, current, result);
        findLCS(s, t, i, j + 1, current, result);
    }
}

vector<string> all_longest_common_subsequences(string s, string t) {
    set<string> result;
    findLCS(s, t, 0, 0, "", result);

    // Find the maximum length LCS
    int maxLen = 0;
    for (const string& seq : result) {
        maxLen = max(maxLen, (int)seq.length());
    }

    vector<string> res;
    for (const string& seq : result) {
        if (seq.length() == maxLen) {
            res.push_back(seq);
        }
    }
    return res;
}


// wrong 
// using memoization
void findLCSMemo(string& s, string& t, int i, int j, string current, set<string>& result, vector<vector<set<string>>>& dp) {
    if (i == s.length() || j == t.length()) {
        result.insert(current);
        return;
    }

    if (dp[i][j].count(current)) return;

    if (s[i] == t[j]) {
        findLCSMemo(s, t, i + 1, j + 1, current + s[i], result, dp);
    } else {
        findLCSMemo(s, t, i + 1, j, current, result, dp);
        findLCSMemo(s, t, i, j + 1, current, result, dp);
    }
    dp[i][j].insert(current);
}

vector<string> all_longest_common_subsequences(string s, string t) {
    set<string> result;
    vector<vector<set<string>>> dp(s.length(), vector<set<string>>(t.length()));
    findLCSMemo(s, t, 0, 0, "", result,dp);
    // Find the maximum length LCS
    int maxLen = 0;
    for (const string& seq : result) {
        maxLen = max(maxLen, (int)seq.length());
    }

    vector<string> res;
    for (const string& seq : result) {
        if (seq.length() == maxLen) {
            res.push_back(seq);
        }
    }
    return res;
}


// length of longest common substring

// using recursion
int solve(int i , int j , string &s1 , string &s2 , int count){
    if(i == s1.size() || j == s2.size()) return count;
    int result = count;
    if(s1[i] == s2[j]) result = solve(i+1,j+1,s1,s2,count+1);
    int choice1 = solve(i+1,j,s1,s2,0);
    int choice2 = solve(i,j+1,s1,s2,0);
    return max(result,max(choice1,choice2));
}

int lcs(string &str1, string &str2){
    return solve(0,0,str1,str2,0);
}

// using memoization
int solve(int i, int j, string &s1, string &s2, int count, vector<vector<vector<int>>> &memo) {
    if (i == s1.size() || j == s2.size()) return count;
    if (memo[i][j][count] != -1) return memo[i][j][count];
    
    int result = count;
    if (s1[i] == s2[j]) 
        result = solve(i+1, j+1, s1, s2, count+1, memo);
    
    int choice1 = solve(i+1, j, s1, s2, 0, memo);
    int choice2 = solve(i, j+1, s1, s2, 0, memo);
    result = max(result, max(choice1, choice2));
    return memo[i][j][count] = result;
}

int lcs(string &str1, string &str2) {
    int m = str1.size(), n = str2.size();
    int maxPossibleLength = min(m, n);
    vector<vector<vector<int>>> memo(m, vector<vector<int>>(n, vector<int>(maxPossibleLength + 1, -1)));
    return solve(0, 0, str1, str2, 0, memo);
}



// wrong
// using tabulation
int solveTab(string &s1, string &s2) {
    int m = s1.size(), n = s2.size();
    int maxPossibleLength = min(m, n);
    vector<vector<vector<int>>> dp(m+1, vector<vector<int>>(n+1, vector<int>(maxPossibleLength+1, 0)));

    for(int i = 0 ; i<=maxPossibleLength; i++){
        dp[m][n][i] = 0;
    }

    for(int i = m-1; i>=0; i--){
        for(int j = n-1; j>=0; j--){
            for(int k=maxPossibleLength;k>=0 ; k--){
                if(s1[i] == s2[j]){
                    dp[i][j][k] = 1 + dp[i+1][j+1][k+1];
                }
                else{
                    dp[i][j][k] = 0;
                }
            }
        }
    }
    return dp[0][0][0];
}

int lcs(string &str1, string &str2) {
    return solveTab(str1, str2);
}


// longest palindromic subsequence

// using recursion
int solve(int i , int j , string s){
    if(i == j) return 1;
    if(i > j) return 0;

    if(s[i] == s[j]) return 2 + solve(i+1,j-1,s);
    int choice1 = solve(i+1,j,s);
    int choice2 = solve(i,j-1,s);
    return max(choice1,choice2);
}
int longestPalindromeSubseq(string s) {
    return solve(0,s.size()-1,s);
}


// using memoization
int solve(int i , int j , string s, vector<vector<int>> &dp){
    if(i == j) return 1;
    if(i > j) return 0;
    if(dp[i][j] != -1) return dp[i][j];

    if(s[i] == s[j]) return dp[i][j] = 2 + solve(i+1,j-1,s,dp);
    int choice1 = solve(i+1,j,s,dp);
    int choice2 = solve(i,j-1,s,dp);
    return dp[i][j] = max(choice1,choice2);
}
int longestPalindromeSubseq(string s) {
    vector<vector<int>> dp(s.size(),vector<int>(s.size(),-1));
    return solve(0,s.size()-1,s,dp);
}


// wrong
// using tabulation
int solveTab(string s,int i , int j){
    vector<vector<int>> dp(s.size(),vector<int>(s.size(),0));
    for(int i=0;i<s.size();i++){
        dp[i][i] = 1;
    }

    for(int i=s.size()-1;i>=0;i--){
        for(int j=0;j<s.size();j++){
            if(s[i] == s[j] && j-1>=0) return dp[i][j] = 2 + dp[i+1][j-1];
            int choice1 = dp[i+1][j];
            int choice2 = dp[i][j-1];
            dp[i][j] = max(choice1,choice2);   
        }
    }
    return dp[0][s.size()-1];
}
int longestPalindromeSubseq(string s) {
    return solveTab(s,0,s.size()-1);
}







// minimum insertions to make a string palindrome

// using recursion
// wrong
int solve(string s1 , string s2 , int i , int j){
    if(i == s1.size() && j == s2.size()) return 0;
    if(i == s1.size()) return s2.size() - j;
    if(j == s2.size()) return s1.size() - i;

    if(s1[i] == s2[j]) return solve(s1,s2,i+1,j+1);
    int choice1 = 1 + solve(s1,s2,i+1,j);
    int choice2 = 1 + solve(s1,s2,i,j+1);
    return min(choice1,choice2);
}
int minInsertions(string s) {
    string reversedString = s;
    reverse(reversedString.begin(),reversedString.end());
    return solve(s,reversedString,0,0);
}


// method 1 
// using recursion 
int solve(string& s, int left, int right) {
    if (left >= right) return 0;
    
    if (s[left] == s[right]) return solve(s, left + 1, right - 1);
    
    return 1 + min(solve(s, left + 1, right), solve(s, left, right - 1));
}

int minInsertions(string s) {
    return solve(s, 0, s.length() - 1);
}


// using memoization
int solveMem(string& s, int left, int right,vector<vector<int>>& dp) {
    if (left >= right) return 0;
    if (dp[left][right] != -1) return dp[left][right];
    
    if (s[left] == s[right]) return solveMem(s, left + 1, right - 1,dp);
    
    dp[left][right] = 1 + min(solveMem(s, left + 1, right,dp), solveMem(s, left, right - 1,dp));
    return dp[left][right];
}

int minInsertions(string s) {
    vector<vector<int>> dp(s.length(),vector<int>(s.length(),-1));
    return solveMem(s, 0, s.length() - 1,dp);
}

int solveTab(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) {
                dp[i][j] = dp[i+1][j-1];
            } else {
                dp[i][j] = 1 + min(dp[i+1][j], dp[i][j-1]);
            }
        }
    }
    return dp[0][n-1];
}

int minInsertions(string s) {
    return solveTab(s);
}


// using tabulation
int solveTab(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) {
                dp[i][j] = dp[i+1][j-1];
            } else {
                dp[i][j] = 1 + min(dp[i+1][j], dp[i][j-1]);
            }
        }
    }
    return dp[0][n-1];
}

int minInsertions(string s) {
    return solveTab(s);
}


// using tabulation with space optimization
int solveTab(string s) {
    int n = s.size();
    vector<int> curr(n, 0);
    vector<int> next(n, 0);

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) {
                curr[j] = next[j-1];
            } else {
                curr[j] = 1 + min(next[j], curr[j-1]);
            }
        }
        next = curr;
    }
    return curr[n-1];
}

int minInsertions(string s) {
    return solveTab(s);
}


// delete operation for two string 

// using recursion
int solve(int i , int j , string word1, string word2){
    if(i == word1.size() && j == word2.size()) return 0;
    if(i == word1.size()) return word2.size() - j;
    if(j == word2.size()) return word1.size() - i;

    if(word1[i] == word2[j]) return solve(i+1,j+1,word1,word2);
    int choice1 = 1 + solve(i+1,j,word1,word2);
    int choice2 = 1 + solve(i,j+1,word1,word2);
    return min(choice1,choice2);
}
int minDistance(string word1, string word2) {
    return solve(0,0,word1,word2);
}


// using memoization
int solve(int i , int j , string word1, string word2, vector<vector<int>>& dp){
    if(i == word1.size() && j == word2.size()) return 0;
    if(i == word1.size()) return word2.size() - j;
    if(j == word2.size()) return word1.size() - i;
    if(dp[i][j] != -1) return dp[i][j];

    if(word1[i] == word2[j]) return dp[i][j] = solve(i+1,j+1,word1,word2,dp);
    int choice1 = 1 + solve(i+1,j,word1,word2,dp);
    int choice2 = 1 + solve(i,j+1,word1,word2,dp);
    return dp[i][j] = min(choice1,choice2);
}
int minDistance(string word1, string word2) {
    vector<vector<int>> dp(word1.size(),vector<int>(word2.size(),-1));
    return solve(0,0,word1,word2,dp);
}


// using tabulation 
int solveTab(string word1, string word2){
    vector<vector<int>> dp(word1.size()+1,vector<int>(word2.size()+1,0));

    for(int i = 0; i <= word1.size(); i++) dp[i][word2.size()] = word1.size() - i;
    for(int j = 0; j <= word2.size(); j++) dp[word1.size()][j] = word2.size() - j;

    for(int i = word1.size()-1;i>=0;i--){
        for(int j = word2.size()-1;j>=0;j--){
            if(word1[i] == word2[j]) dp[i][j] = dp[i+1][j+1];
            else{
                int choice1 = 1 + dp[i+1][j];
                int choice2 = 1 + dp[i][j+1];
                dp[i][j] = min(choice1,choice2);
            }
        }
    }
    return dp[0][0];
}
int minDistance(string word1, string word2) {
    return solveTab(word1,word2);
}


// using tabulation with space optimization
int solveOptimal(string word1, string word2){
    vector<int> curr(word2.size()+1,0);
    vector<int> next(word2.size()+1,0);

    for(int j = 0; j <= word2.size(); j++) next[j] = word2.size() - j;

    for(int i = word1.size()-1;i>=0;i--){
        curr[word2.size()] = word1.size() - i;
        for(int j = word2.size()-1;j>=0;j--){
            if(word1[i] == word2[j]) curr[j] = next[j+1];
            else{
                int choice1 = 1 + next[j];
                int choice2 = 1 + curr[j+1];
                curr[j] = min(choice1,choice2);
            }
        }
        next = curr;
    }
    return curr[0];
}
int minDistance(string word1, string word2) {
    return solveOptimal(word1,word2);
}


// shortest common supersequence

// using recursion
string scs(const string& str1, const string& str2, int i, int j) {
    if (i == str1.length()) return str2.substr(j);
    if (j == str2.length()) return str1.substr(i);
    
    if (str1[i] == str2[j]) return str1[i] + scs(str1, str2, i+1, j+1);
    
    // Characters don't match, try both possibilities
    string includeStr1 = str1[i] + scs(str1, str2, i+1, j);
    string includeStr2 = str2[j] + scs(str1, str2, i, j+1);
    
    if(includeStr1.length() < includeStr2.length()) return includeStr1;
    return includeStr2;
}
string shortestCommonSupersequence(string str1, string str2) {
    return scs(str1, str2, 0, 0);
}


// using memoization
string scs(const string& str1, const string& str2, int i, int j, vector<vector<string>>& dp) {
    if (i == str1.length()) return str2.substr(j);
    if (j == str2.length()) return str1.substr(i);
    if (dp[i][j] != "") return dp[i][j];
    
    if (str1[i] == str2[j]) return str1[i] + scs(str1, str2, i+1, j+1,dp);
    
    // Characters don't match, try both possibilities
    string includeStr1 = str1[i] + scs(str1, str2, i+1, j,dp);
    string includeStr2 = str2[j] + scs(str1, str2, i, j+1,dp);
    
    if(includeStr1.length() < includeStr2.length()) return dp[i][j] = includeStr1;
    return dp[i][j] = includeStr2;
}
string shortestCommonSupersequence(string str1, string str2) {
    vector<vector<string>> dp(str1.length(), vector<string>(str2.length(), ""));
    return scs(str1, str2, 0, 0,dp);
}


// using tabulation(still giving tle)
string solveTab(string str1, string str2) {
   vector<vector<string>> dp(str1.size() + 1, vector<string>(str2.size() + 1, ""));

    for(int j = 0; j <= str2.size(); j++) dp[str1.size()][j] = str2.substr(j);
    for(int i = 0; i <= str1.size(); i++) dp[i][str2.size()] = str1.substr(i);

    for(int i = str1.size() - 1; i >= 0; i--) {
        for(int j = str2.size() - 1; j >= 0; j--) {
            if(str1[i] == str2[j]) dp[i][j] = str1[i] + dp[i+1][j+1];
            else {
                string includeStr1 = str1[i] + dp[i+1][j];
                string includeStr2 = str2[j] + dp[i][j+1];
                if(includeStr1.length() < includeStr2.length()) dp[i][j] = includeStr1;
                else dp[i][j] = includeStr2;
            }
        }
    }
    return dp[0][0];
}
string shortestCommonSupersequence(string str1, string str2) {
    return solveTab(str1, str2);
}


// method 2
string solveTab(string str1, string str2) {

    int m = str1.size(), n = str2.size();

    // finding the length of LCS
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    // Fill the dp table with LCS length
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Backtracking to construct the Shortest Common Supersequence
    string result;
    int i = m-1, j = n-1;

    while (i > 0 && j > 0) {
        if (str1[i] == str2[j]) {
            result += str1[i];
            i--, j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            result += str1[i];
            i--;
        } else {
            result += str2[j ];
            j--;
        }
    }

    // Add remaining characters from either string
    while (i > 0) result += str1[i-- - 1];
    while (j > 0) result += str2[j-- - 1];

    // Reverse the result to get the correct sequence
    reverse(result.begin(), result.end());
    return result;

}

string shortestCommonSupersequence(string str1, string str2) {
    return solveTab(str1, str2);
}


// longest increasing subsequence

// using recursion
int solve(int prevIndex ,int currIndex , vector<int> &nums){
    if(currIndex == nums.size()) return 0;

    if(prevIndex == -1 || nums[currIndex] > nums[prevIndex]){
        int include = 1 + solve(currIndex,currIndex+1,nums);
        int exclude = solve(prevIndex,currIndex+1,nums);
        return max(include,exclude);
    }

    return solve(prevIndex,currIndex+1,nums);
}
int lengthOfLIS(vector<int>& nums) {
    return solve(-1,0,nums);
}


// using memoization
int solveMem(int prevIndex ,int currIndex , vector<int> &nums,vector<vector<int>> &dp){
    if(currIndex == nums.size()) return 0;
    if(dp[prevIndex+1][currIndex] != -1) return dp[prevIndex+1][currIndex];

    if(prevIndex == -1 || nums[currIndex] > nums[prevIndex]){
        int include = 1 + solveMem(currIndex,currIndex+1,nums,dp);
        int exclude = solveMem(prevIndex,currIndex+1,nums,dp);
        return dp[prevIndex+1][currIndex] = max(include,exclude);
    }

    return dp[prevIndex+1][currIndex] = solveMem(prevIndex,currIndex+1,nums,dp);
}
int lengthOfLIS(vector<int>& nums) {
    vector<vector<int>> dp(nums.size(),vector<int>(nums.size(),-1));
    return solveMem(-1,0,nums,dp);
}


// longest increasing subsequence
// using tabulation
int solveTab(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

    for(int i = n ; i>=0;i--){
        for(int j = n-1;j>=0;j--){
            if(i == 0 || nums[j]>nums[i-1]){
                int include = 1 + dp[j][j+1];
                int exclude = dp[i][j+1];
                dp[i][j] = max(include,exclude);
            }
            else{
                dp[i][j] = dp[i][j+1];
            }
        }
    }
    return dp[0][0];
}
int lengthOfLIS(vector<int>& nums) {
    return solveTab(nums);
}



// printing the longest increasing subsequence(codestudio)
// using recursion
vector<int> solve(int prevIndex ,int currIndex , vector<int> &nums,vector<int> &ans){
    if(currIndex == nums.size()) return ans;

    if(prevIndex == -1 || nums[currIndex] > nums[prevIndex]){
        ans.push_back(nums[currIndex]);
        vector<int> include = solve(currIndex,currIndex+1,nums,ans);
        ans.pop_back();
        vector<int> exclude = solve(prevIndex,currIndex+1,nums,ans);
        if(include.size() > exclude.size()) return include;
        return exclude;
    }

    return solve(prevIndex,currIndex+1,nums,ans);
}
vector<int> printingLongestIncreasingSubsequence(vector<int> nums, int n) {
    vector<int> ans;
    return solve(-1,0,nums,ans);
}



// ninja training


// using recursion
int solve(int index , int exclude , vector<vector<int>> &points){
    if(index < 0) return 0; 

    int maxi = INT_MIN;
    for(int i = 0; i < 3; i++){
        if(exclude != -1){
            if(i != exclude){
                maxi = max(maxi,points[index][i] + solve(index-1,i,points));
            }
        }
        else{
            maxi = max(maxi,points[index][i] + solve(index-1,i,points));
        }
    }
    return maxi;
}

int ninjaTraining(int n, vector<vector<int>> &points){
    return solve(n-1,-1,points);
}


// using memoization
int solveMem(int index , int exclude , vector<vector<int>> &points, vector<vector<int>> &dp){
    if(index < 0) return 0; 
    if(dp[index][exclude+1] != -1) return dp[index][exclude+1];

    int maxi = INT_MIN;
    for(int i = 0; i < 3; i++){
        if(exclude != -1){
            if(i != exclude){
                maxi = max(maxi,points[index][i] + solveMem(index-1,i,points,dp));
            }
        }
        else{
            maxi = max(maxi,points[index][i] + solveMem(index-1,i,points,dp));
        }
    }
    dp[index][exclude+1] = maxi;
    return maxi;
}

int ninjaTraining(int n, vector<vector<int>> &points){
    vector<vector<int>> dp(n,vector<int>(4,-1));
    return solveMem(n-1,-1,points,dp);
}


// wrong 
// using tabulation
int solveTab(int n, vector<vector<int>> &points){
    vector<vector<int>> dp(points.size(),vector<int>(4,0));
    for(int row = 0; row < points.size(); row++){
        for(int col = -1 ; col < 3; col++){

            int maxi = INT_MIN;
            for(int i = 0; i < 3; i++){
                if(col != -1){
                    if(i != col){
                        maxi = max(maxi,points[row][col] + dp[row-1][col+1]);
                    }
                }
                else{
                    maxi = max(maxi,points[row][col] + dp[row-1][col+1]);
                }
            }
            dp[row][col+1] = maxi;

        }
    }
    return dp[n-1][0];
}
int ninjaTraining(int n, vector<vector<int>> &points){
    return solveTab(n,points);
}



// leetcode 64 - minimum path sum

// using recursion
int solve(int i , int j, int rowSize , int colSize  , vector<vector<int>> &grid){
    if(i == rowSize-1 && j == colSize-1) return grid[i][j];
    
    if(i+1 < rowSize && j+1 < colSize){
        // move down
        int down  = solve(i+1,j,rowSize,colSize,grid);

        // move right
        int right = solve(i,j+1,rowSize,colSize,grid);

        return grid[i][j] + min(down,right);
    }

    if(i+1 < rowSize) return grid[i][j] + solve(i+1,j,rowSize,colSize,grid);

    return grid[i][j] + solve(i,j+1,rowSize,colSize,grid);
}
int minPathSum(vector<vector<int>>& grid) {
    return solve(0,0,grid.size(),grid[0].size(),grid);
}


// using memoization
int solveMem(int i , int j, int rowSize , int colSize  , vector<vector<int>> &grid, vector<vector<int>> &dp){
    if(i == rowSize-1 && j == colSize-1) return grid[i][j];
    if(dp[i][j] != -1) return dp[i][j];
    
    if(i+1 < rowSize && j+1 < colSize){
        // move down
        int down  = solveMem(i+1,j,rowSize,colSize,grid,dp);

        // move right
        int right = solveMem(i,j+1,rowSize,colSize,grid,dp);

        return dp[i][j] = grid[i][j] + min(down,right);
    }

    if(i+1 < rowSize) {
        return dp[i][j] = grid[i][j] + solveMem(i+1,j,rowSize,colSize,grid,dp);
    }
    return dp[i][j] = grid[i][j] + solveMem(i,j+1,rowSize,colSize,grid,dp);
}
int minPathSum(vector<vector<int>>& grid) {
    vector<vector<int>> dp(grid.size(),vector<int>(grid[0].size(),-1));
    return solveMem(0,0,grid.size(),grid[0].size(),grid,dp);
}


// using tabulation
int solveTab(vector<vector<int>>& grid) {
    int rowSize = grid.size();
    int colSize = grid[0].size();
    vector<vector<int>> dp(rowSize, vector<int>(colSize, 0));
    dp[rowSize-1][colSize-1] = grid[rowSize-1][colSize-1];

    for(int i = rowSize-2; i >= 0; i--) {
        for (int j = colSize-2; j >= 0; j--) {

            if(i+1 < rowSize && j+1 < colSize){
                // move down
                int down  = solveMem(i+1,j,rowSize,colSize,grid,dp);

                // move right
                int right = solveMem(i,j+1,rowSize,colSize,grid,dp);

                return dp[i][j] = grid[i][j] + min(down,right);
            }

            if(i+1 < rowSize) {
                return dp[i][j] = grid[i][j] + solveMem(i+1,j,rowSize,colSize,grid,dp);
            }
            return dp[i][j] = grid[i][j] + solveMem(i,j+1,rowSize,colSize,grid,dp);
        }
    }
}  

int minPathSum(vector<vector<int>>& grid) {
    return solveTab(grid);
}

// triangle - leetcode 120

// using recursion
int solve(int i ,int  j ,vector<vector<int>>& triangle){
    if(i == triangle.size()) return 0;
    
    int justBelow = solve(i+1,j,triangle);  
    int justBelowRight = solve(i+1,j+1,triangle);
    return triangle[i][j] + min(justBelow,justBelowRight);
}
int minimumTotal(vector<vector<int>>& triangle) {
    return solve(0,0,triangle);
}


// using memoization
int solveMem(int i ,int  j ,vector<vector<int>>& triangle, vector<vector<int>> &dp){
    if(i == triangle.size()) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    
    int justBelow = solveMem(i+1,j,triangle,dp);  
    int justBelowRight = solveMem(i+1,j+1,triangle,dp);
    return dp[i][j] = triangle[i][j] + min(justBelow,justBelowRight);
}
int minimumTotal(vector<vector<int>>& triangle) {
    int rowSize = triangle.size();
    int colSize = triangle[rowSize-1].size();
    vector<vector<int>> dp(rowSize,vector<int>(colSize,-1));
    return solveMem(0,0,triangle,dp);
}


// using  tabulation 
int solveTab(vector<vector<int>>& triangle) {
    int rowSize = triangle.size();
    vector<vector<int>> dp(rowSize, vector<int>(rowSize, 0));
    
    // Initialize the bottom row
    for (int j = 0; j < rowSize; j++) {
        dp[rowSize-1][j] = triangle[rowSize-1][j];
    }
    
    // Bottom-up DP
    for (int i = rowSize - 2; i >= 0; i--) {
        for (int j = i; j >= 0; j--) {
            dp[i][j] = triangle[i][j] + min(dp[i+1][j], dp[i+1][j+1]);
        }
    }
    
    return dp[0][0];
}

int minimumTotal(vector<vector<int>>& triangle) {
    return solveTab(triangle);
}


// using tabulation with space optimization
int solveOptimal(vector<vector<int>>& triangle) {
    int rowSize = triangle.size();
    int colSize = triangle[rowSize-1].size();
    vector<int> next(colSize, 0);
    vector<int> curr(colSize, 0);

    for(int j = 0; j < colSize; j++) {
        next[j] = triangle[colSize-1][j];
    }

    for (int i = colSize - 2; i >= 0; i--) {
        for (int j = i; j >= 0; j--) {
            curr[j] = triangle[i][j] + min(next[j], next[j+1]);
        }
        next = curr;
    }
    curr[0];
}
int minimumTotal(vector<vector<int>>& triangle) {
    return solveOptimal(triangle);
}



// perfect sum problem

// using recursion
int solve(int i, int n, int sum, int arr[]){
    if(i>n) return 0;
    if(sum == 0) return 1;
    
    int ans = 0;
    if(arr[i] <= sum){
        int include = solve(i+1,n,sum-arr[i],arr);
        ans += include;
    }
    int exclude = solve(i+1,n,sum,arr);
    ans += exclude;
    return ans;
}

int perfectSum(int arr[], int n, int sum){
    return solve(0,n,sum,arr);
}


// using memoization
int solve(int i, int n, int sum, int arr[], vector<vector<int>> &dp){
    if(i>n) return 0;
    if(sum == 0) return 1;
    if(dp[i][sum] != -1) return dp[i][sum];
    
    int ans = 0;
    if(arr[i] <= sum){
        int include = solve(i+1,n,sum-arr[i],arr,dp);
        ans += include;
    }
    int exclude = solve(i+1,n,sum,arr,dp);
    ans += exclude;
    return dp[i][sum] = ans;
}

int perfectSum(int arr[], int n, int sum){
    vector<vector<int>> dp(n+1,vector<int>(sum+1,-1));
    return solve(0,n,sum,arr,dp);
}



    
// using recursion

int solve(int i, int n, int sum, int arr[]){
    if(i == n) {
        return (sum == 0) ? 1 : 0;
    }
    
    int exclude = solve(i+1, n, sum, arr);
    int include = 0;
    if(arr[i] <= sum){
        include = solve(i+1, n, sum-arr[i], arr);
    }
    return (exclude + include) % mod;
}

int perfectSum(int arr[], int n, int sum){
    return solve(0, n, sum, arr);
}


// using memoization
int solve(int i, int n, int sum, int arr[], vector<vector<int>> &dp){
    if(i == n) {
        return (sum == 0) ? 1 : 0;
    }
    if(dp[i][sum] != -1) return dp[i][sum];
    
    int exclude = solve(i+1, n, sum, arr, dp);
    int include = 0;
    if(arr[i] <= sum){
        include = solve(i+1, n, sum-arr[i], arr, dp);
    }
    return dp[i][sum] = (exclude + include) % mod;
}
int perfectSum(int arr[], int n, int sum){
    vector<vector<int>> dp(n+1, vector<int>(sum+1, -1));
    return solve(0, n, sum, arr, dp);
}


// using tabulation
int solveTab(int i, int n, int sum, int arr[]){
    vector<vector<int>> dp(n+1, vector<int>(sum+1, 0));
    for(int i = 0; i <= n; i++) dp[i][0] = 1;

    for(int i = n-1; i >= 0; i--){
        for(int j = 1; j <= sum; j++){
            int exclude = dp[i+1][j];
            int include = 0;
            if(arr[i] <= j){
                include = dp[i+1][j-arr[i]];
            }
            dp[i][j] = (exclude + include) % mod;
        }
    }
    return dp[0][sum];

}
int perfectSum(int arr[], int n, int sum){
    return solveTab(0, n, sum, arr);
}


// using tabulation with space optimization
int solveOptimal(int i , int n , int sum , int arr[]){
    vector<int > next(sum+1,0);
    vector<int > curr(sum+1,0);
    next[0] = 1;

    for(int i = n-1; i >= 0; i--){
        next[0] = 1;
        for(int j = 1; j <= sum; j++){
            int exclude = next[j];
            int include = 0;
            if(arr[i] <= j){
                include = next[j-arr[i]];
            }
            curr[j] = (exclude + include) % mod;
        }
        next = curr;
    }
    return curr[sum];
}

int perfectSum(int arr[], int n, int sum){
    return solveOptimal(0, n, sum, arr);
}



// coin change

// using recursion

int solve(vector<int> &coins, int i  , int amount){
    if(amount == 0) return 0;
    else if(i<0) return INT_MAX;
    
    int include = INT_MAX;
    if(coins[i] <= amount ){
        int temp = solve(coins,i,amount-coins[i]);

        if(temp != INT_MAX) include = 1 + temp;
    }
    int exclude = solve(coins,i-1,amount);
    return min(include,exclude);
}
int coinChange(vector<int> &coins, int amount) {
    int n = coins.size();
    int ans = solve(coins,n-1,amount);
    return ans == INT_MAX ? -1 : ans;
}


// using memoization
int solve(vector<int> &coins, int i  , int amount, vector<vector<int>> &dp){
    if(amount == 0) return 0;
    else if(i<0) return INT_MAX;

    if(dp[i][amount] != -1) return dp[i][amount];
    
    int include = INT_MAX;
    if(coins[i] <= amount ){
        int temp = solve(coins,i,amount-coins[i]);

        if(temp != INT_MAX) include = 1 + temp;
    }
    int exclude = solve(coins,i-1,amount);
    return dp[i][amount] = min(include,exclude);
}
int coinChange(vector<int> &coins, int amount) {
    int n = coins.size();
    vector<vector<int>> dp(n,vector<int>(amount+1,-1));
    int ans = solve(coins,n-1,amount,dp);
    return ans == INT_MAX ? -1 : ans;
}


// using tabulation
int solveTab(vector<int> &coins, int amount){
    int n = coins.size();
    vector<vector<int>> dp(n+1,vector<int>(amount+1,INT_MAX));
    for(int i = 0; i < n; i++) dp[i][0] = 0;

    for(int i = 0; i <= n-1; i++){
        for(int j = 1; j <= amount; j++){
            int include = INT_MAX;
            if(coins[i] <= j ){
                int temp = dp[i][j-coins[i]];

                if(temp != INT_MAX) include = 1 + temp;
            }
            if(i-1 >= 0) dp[i][j] = min(include,dp[i-1][j]);
            else dp[i][j] = include;
        }
    }
    return dp[n-1][amount] == INT_MAX ? -1 : dp[n-1][amount];
}

int coinChange(vector<int> &coins, int amount) {
    return solveTab(coins,amount);
}  


// using tabulation with space optimization
int solveOptimal(vector<int> &coins, int amount){
    int n = coins.size();
    vector<int> prev(amount+1,INT_MAX);
    vector<int> curr(amount+1,INT_MAX);
    curr[0] = 0;

    for(int i = 0; i <= n-1; i++){
        curr[0] = 0;
        for(int j = 1; j <= amount; j++){
            int include = INT_MAX;
            if(coins[i] <= j ){
                int temp = curr[j-coins[i]];

                if(temp != INT_MAX) include = 1 + temp;
            }
            if(i-1 >= 0) curr[j] = min(include,prev[j]);
            else curr[j] = include;
        }
        prev = curr;
    }
    return curr[amount] == INT_MAX ? -1 : curr[amount];
}

int coinChange(vector<int> &coins, int amount) {
    return solveOptimal(coins,amount);
}  



// largest divisible subset


// using recursion
vector<int> solve(vector<int> &nums, int idx, int prev) {
    if (idx == nums.size()) return {};

    // Option 1: Exclude nums[idx]
    vector<int> exclude = solve(nums, idx + 1, prev);

    // Option 2: Include nums[idx] if divisible
    vector<int> include;
    if (prev == -1 || nums[idx] % nums[prev] == 0) {
        include = solve(nums, idx + 1, idx);
        include.push_back(nums[idx]);
    }

    // Return the larger subset
    return (include.size() > exclude.size()) ? include : exclude;
}
vector<int> largestDivisibleSubset(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    return solve(nums, 0, -1);   
}


// using memoization
vector<int> findSubset(int idx, int prev, vector<int>& nums, vector<vector<vector<int>>>& dp) {
    if (idx == nums.size()) return {};
    if (!dp[idx][prev + 1].empty()) return dp[idx][prev + 1];
    
    vector<int> exclude = findSubset(idx + 1, prev, nums, dp);
    
    vector<int> include;
    if (prev == -1 || nums[idx] % nums[prev] == 0) {
        include = findSubset(idx + 1, idx, nums, dp);
        include.push_back(nums[idx]);
    }
    
    // Store the larger subset in the memoization table
    dp[idx][prev + 1] = (include.size() > exclude.size()) ? include : exclude;
    return dp[idx][prev + 1];
}

vector<int> largestDivisibleSubset(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return {};
    sort(nums.begin(), nums.end());
    
    // Memoization table: sdp[i][j] stores the largest subset starting at index i with nums[j] as the previous element.
    // We use prev = -1 to signify no previous element.
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n + 1));
    
    vector<int> result = findSubset(0, -1, nums, dp);
    // Since the result is built backward, reverse it to get the correct order
    reverse(result.begin(), result.end());
    return result;
}


// using tabulation
vector<int> solveTab(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return {};
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n + 1));

    for(int i = n-1; i >0 ; i--){
        for(int j = n-1 ; j >= -1; j--){
            // Option 1: Exclude nums[idx]
            vector<int> exclude = dp[i][j+1];
            // Option 2: Include nums[idx] if divisible
            vector<int> include;
            if (j == -1 || nums[i] % nums[j] == 0) {
                include  = dp[i+1][idx+1];
                include.push_back(nums[idx]);
            }
            dp[i][j+1] = (include.size() > exclude.size()) ? include : exclude;
        }
    }
    return dp[0][0];
}
vector<int> largestDivisibleSubset(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    return solveTab(nums);
}


// distinct subsequences

// using recursion

int solve(string s, string t , int i , int j){
    if(j>=t.size()) return 1;
    if(i>=s.size()) return 0;

    int include = 0 , exclude = 0;
    if(s[i] == t[j]){
        include = solve(s,t,i+1,j+1);
    }
    exclude = solve(s,t,i+1,j);

    return include + exclude;
}
int numDistinct(string s, string t) {
    return solve(s,t,0,0);
}


// using memoization 
int solveMem(string s, string t , int i , int j, vector<vector<int>> &dp){
    if(j>=t.size()) return 1;
    if(i>=s.size()) return 0;
    if(dp[i][j] != -1) return dp[i][j];

    int include = 0 , exclude = 0;
    if(s[i] == t[j]){
        include = solveMem(s,t,i+1,j+1,dp);
    }
    exclude = solveMem(s,t,i+1,j,dp);

    return dp[i][j] = include + exclude;
}
int numDistinct(string s, string t) {
    vector<vector<int>> dp(s.size(),vector<int>(t.size(),-1));
    return solveMem(s,t,0,0, dp);
}


// using tabulation 

int solveTab(string s , string t) {
    vector<vector<long long>> dp(s.size() + 1, vector<long long>(t.size() + 1, 0));

    for (int i = 0; i <= s.size(); i++) 
        dp[i][t.size()] = 1;  // Last column initialization

    for (int i = s.size() - 1; i >= 0; i--) {
        for (int j = t.size() - 1; j >= 0; j--) {
            long long include = 0, exclude = 0;  // Changed to long long
            if (s[i] == t[j]) {
                include = dp[i + 1][j + 1];
            }
            exclude = dp[i + 1][j];
            dp[i][j] = include + exclude;  // Ensure this is long long
        }
    }
    return dp[0][0];
}
int numDistinct(string s, string t) {
    return solveTab(s,t);
}

// using tabulation with space optimization

int solveOptimal(string s , string t){
    vector<long long> next(t.size()+1,0);
    vector<long long> curr(t.size()+1,0);

    for(int i = s.size()-1; i >= 0; i--){
        next[t.size()] = 1;
        for(int j = t.size()-1; j >= 0; j--){
            long long include = 0 , exclude = 0;
            if(s[i] == t[j]){
                include = next[j+1];
            }
            exclude = next[j];
            curr[j] = include + exclude;
        }
        next = curr;
    }
    return next[0];
}
int numDistinct(string s, string t) {
    return solveOptimal(s,t);
}



// target sum


// using recursion
int solve(int i , int target , vector<int> &nums){
    if(i >= nums.size()){
        return target == 0 ? 1 : 0;
    }
    int add = solve(i+1,target-nums[i],nums);
    int subtract = solve(i+1,target+nums[i],nums);
    return add + subtract;
}
    
int findTargetSumWays(vector<int>& nums, int target) {
    return solve(0,target,nums);
}


// using memoization
int solveMem(int i , int target , vector<int> &nums, vector<vector<int>> &dp){
    if(i >= nums.size()){
        return target == 0 ? 1 : 0;
    }
    if(dp[i][target+1000] != -1) return dp[i][target+1000];
    int add = solveMem(i+1,target-nums[i],nums,dp);
    int subtract = solveMem(i+1,target+nums[i],nums,dp);
    return dp[i][target+1000] = add + subtract;
}
    
int findTargetSumWays(vector<int>& nums, int target) {
    vector<vector<int>> dp(nums.size(),vector<int>(2001,-1));
    return solveMem(0,target,nums,dp);
}


int solveMem(int i, int target, vector<int>& nums, vector<vector<int>>& dp) {
    if (target < -1000 || target > 1000) {
        return 0; // Handle out of bounds
    }

    if (i >= nums.size()) {
        return target == 0 ? 1 : 0;
    }

    if (dp[i][target + 1000] != -1) 
        return dp[i][target + 1000];

    int add = solveMem(i + 1, target - nums[i], nums, dp);
    int subtract = solveMem(i + 1, target + nums[i], nums, dp);
    return dp[i][target + 1000] = add + subtract;
}

int findTargetSumWays(vector<int>& nums, int target) {
    vector<vector<int>> dp(nums.size(), vector<int>(2001, -1));
    return solveMem(0, target, nums, dp);
}



// matrix chain multiplication
// using tabulation
int solveTab(int arr[], int i, int j, int N){
    vector<vector<int>> dp(N, vector<int>(N, 0));

    for(int i = N-1; i >= 1; i--){
        for(int j = i+1; j <= N-1; j++){
            int mini = INT_MAX;
            for(int k = i; k<= j-1; k++){
                int ans = dp[i][k] + dp[k+1][j] + arr[i-1]*arr[k]*arr[j];
                mini = min(mini,ans);
            } 
            dp[i][j] = mini;
        }
    }
    return dp[1][N-1];
}

int matrixMultiplication( int N,int arr[]){
    return solveTab(arr,1,N-1,N);
}



// minimum cost to cut a stick

// using recursion
int solve(int start, int end, const vector<int>& cuts) {
    if (end - start <= 1) return 0;

    int minCost = INT_MAX;
    for (int i = start + 1; i < end; ++i) {
        int cost = cuts[end] - cuts[start] + solve(start, i, cuts) + solve(i, end, cuts);  
        minCost = min(minCost, cost);
    }
    return minCost;
}

int minCost(int n, vector<int>& cuts) {
    cuts.push_back(0);
    cuts.push_back(n);

    sort(cuts.begin(), cuts.end());
    return solve(0, cuts.size() - 1, cuts);
}


// using memoization
int solveMem(int start, int end, const vector<int>& cuts, vector<vector<int>>& dp) {
    if (end - start <= 1) return 0;
    if(dp[start][end] != -1) return dp[start][end];

    int minCost = INT_MAX;
    for (int i = start + 1; i < end; i++) {
        int cost = cuts[end] - cuts[start] + solveMem(start, i, cuts,dp) + solveMem(i, end, cuts,dp);  
        minCost = min(minCost, cost);
    }
    return dp[start][end] = minCost;
}

int minCost(int N, vector<int>& cuts) {
    cuts.push_back(0);
    cuts.push_back(N);
    int n = cuts.size();
    sort(cuts.begin(), cuts.end());
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return solveMem(0, cuts.size() - 1, cuts,dp);
}


// using tabulation
int solveTab(int n , vector<int>& cuts){
    vector<vector<int>> dp(n,vector<int>(n , 0));

    for(int i = n-1; i >= 0; i--){
        for(int j = i+2; j < n; j++){
            int mini = INT_MAX;
            for(int k = i+1; k < j; k++){
                int cost = cuts[j] - cuts[i] + dp[i][k] + dp[k][j];
                mini = min(mini,cost);
            }
            dp[i][j] = mini;
        }
    }
    return dp[0][n-1];
}

int minCost(int n, vector<int>& cuts) {
    cuts.push_back(0);
    cuts.push_back(n);
    sort(cuts.begin(), cuts.end());
    return solveTab(cuts.size(),cuts);
}



// burst balloons


// using recursion
int solve(int i, int j, vector<int> &nums) {
    if (i > j) return 0;
    int maxCoins = INT_MIN;
    
    for (int k = i; k <= j; k++) {
        int coins = nums[i - 1] * nums[k] * nums[j + 1];
        int remainingCoins = solve(i, k - 1, nums) + solve(k + 1, j, nums);
        maxCoins = max(maxCoins, coins + remainingCoins);
    }
    return maxCoins;
}

int maxCoins(vector<int> &nums) {
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    int n = nums.size();
    return solve(1, n-2, nums);
}


// using memoization
int solveMem(int i, int j, vector<int> &nums, vector<vector<int>> &dp) {
    if (i > j) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    int maxCoins = INT_MIN;
    
    for (int k = i; k <= j; k++) {
        int coins = nums[i - 1] * nums[k] * nums[j + 1];
        int remainingCoins = solveMem(i, k - 1, nums,dp) + solveMem(k + 1, j, nums,dp);
        maxCoins = max(maxCoins, coins + remainingCoins);
    }
    return dp[i][j] = maxCoins;
}

int maxCoins(vector<int> &nums) {
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return solveMem(1, n-2, nums, dp);
}


// using tabulation 
int solveTab(int i , int j , vector<int>& nums){
    int n = nums.size();
    vector<vector<int>> dp(n,vector<int>(n,0));

    for(int i = n-1;i >= 1; i--){
        for(int j = i; j<=n-2;j++){
            int maxCoins = INT_MIN;
            
            for (int k = i; k <= j; k++) {
                int coins = nums[i - 1] * nums[k] * nums[j + 1];
                int remainingCoins = dp[i][k-1] + dp[k+1][j];
                maxCoins = max(maxCoins, coins + remainingCoins);
                dp[i][j] = maxCoins;
            }

        }
    }
    return dp[1][n-2];
}
int maxCoins(vector<int>& nums) {
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    return solveTab(1,nums.size()-2,nums);
}


// using tabulation with space optimization
int solveOptimal(int i , int j , vector<int>& nums){
    int n = nums.size();
    vector<vector<int>> dp(n,vector<int>(n,0));

    for(int i = n-1;i >= 1; i--){
        for(int j = i; j<=n-2;j++){
            int maxCoins = INT_MIN;
            
            for (int k = i; k <= j; k++) {
                int coins = nums[i - 1] * nums[k] * nums[j + 1];
                int remainingCoins = dp[i][k-1] + dp[k+1][j];
                maxCoins = max(maxCoins, coins + remainingCoins);
            }
            dp[i][j] = maxCoins;

        }
    }
    return dp[1][n-2];
}
int maxCoins(vector<int>& nums) {
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    return solveOptimal(1,nums.size()-2,nums);
}




// LC 221

// using recursion
int solve(vector<vector<char>>& matrix, int i, int j, int &maxi) {
    if(i >= matrix.size() || j >= matrix[0].size())
        return 0;
        
    int right = solve(matrix, i, j+1, maxi);
    int diagnol = solve(matrix, i+1, j+1, maxi);
    int down = solve(matrix, i+1, j, maxi);
    
    if(matrix[i][j] == '1') {
        int ans = 1 + min(right, min(diagnol, down));
        maxi = max(maxi, ans);
        return ans;
    }
    else {
        return 0;
    }
}

int maximalSquare(vector<vector<char>>& matrix) {
    int maxi= 0;
    int n = matrix.size();
    int m = matrix[0].size();
    solve(matrix, 0, 0, maxi);
    return maxi*maxi;
}


// using memoization 
int solveMem(vector<vector<char>>& matrix, int i, int j, int &maxi,vector<vector<int>> &dp) {
    if(i >= matrix.size() || j >= matrix[0].size())
        return 0;
    if(dp[i][j] != -1) return dp[i][j]; 
        
    int right = solveMem(matrix, i, j+1, maxi,dp);
    int diagnol = solveMem(matrix, i+1, j+1, maxi,dp);
    int down = solveMem(matrix, i+1, j, maxi,dp);
    
    if(matrix[i][j] == '1') {
        int ans = 1 + min(right, min(diagnol, down));
        maxi = max(maxi, ans);
        return dp[i][j] = ans;
    }
    else {
        return dp[i][j] = 0;
    }
}

int maximalSquare(vector<vector<char>>& matrix) {
    int maxi= 0;
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> dp(n,vector<int>(m,-1));

    solveMem(matrix, 0, 0, maxi,dp);
    return maxi*maxi;
}


// using tabulation
void solveTab(vector<vector<char>> &matrix,int &maxi){
    int n = matrix.size();
    int m  = matrix[0].size();
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));

    for(int i = n-1;i>=0;i--){
        for (int  j  = m-1; j  >=0; j--){
            int right = dp[i][j+1];
            int diagonal = dp[i+1][j+1];
            int down = dp[i][j+1];

            if(matrix[i][j] == '1') {
                int ans = 1 + min(right, min(diagonal, down));
                maxi = max(maxi, ans);
                dp[i][j] = ans;
            }
        }
        
    }
}

int maximalSquare(vector<vector<char>>& matrix) {
    int maxi= 0;
    solveTab(matrix,maxi);
    return maxi*maxi;
}



// LC 121

// using recusion
int solve(int index, bool canBuy, vector<int>& prices) {
    if(index >= prices.size()) return 0;
    
    int doNothing = solve(index + 1, canBuy, prices);
    int doSomething = 0;
    
    if(canBuy) {
        doSomething = -prices[index] + solve(index + 1, false, prices);
    } else {
        doSomething = prices[index];
    }
    
    return max(doNothing, doSomething);
}
int maxProfit(vector<int>& prices) {
    return solve (0,true , prices);
}


// using memoizaiton 
int solveMem(int index, bool canBuy, vector<int>& prices, vector<vector<int>>& dp) {
    // Base case
    if(index >= prices.size()) return 0;
    if(dp[index][canBuy] !=-1) return dp[index][canBuy];

    int doNothing = solveMem(index + 1, canBuy, prices,dp);
    int doSomething = 0;
    
    if(canBuy) {
        doSomething = -prices[index] + solveMem(index + 1, false, prices,dp);
    } else {
        doSomething = prices[index];
    }
    
    return dp[index][canBuy] =  max(doNothing, doSomething);
}
int maxProfit(vector<int>& prices) {
    vector<vector<int>> dp(prices.size(),vector<int>(2,-1));
    return solveMem (0,true , prices,dp);
}


// using tabulation 
int solveTab(vector<int>& prices){
    vector<vector<int>> dp(prices.size(),vector<int>(2,0));
    int n  =prices.size();

    for (int  i = n-1; i >=0; i--)
    {
        for (int  j  = 0; j  <= 1; j ++)
        {
            int doNothing = dp[i+1][j];
            int doSomething = 0;
            
            if(j) {
                doSomething = -prices[i] + dp[i+1][false];
            } else {
                doSomething = prices[i];
            }
            
            dp[i][j] =  max(doNothing, doSomething);

        }
        
    }
    return dp[0][1];
}

int maxProfit(vector<int>& prices) {
    return solveTab(prices);
}


// tabulation with space optimization 
int solveTab(vector<int>& prices){
    vector<int> next(2,0);
    vector<int> curr(2,0);
    int n  =prices.size();

    for (int  i = n-1; i >=0; i--)
    {
        for (int  j  = 0; j  <= 1; j ++)
        {
            int doNothing = next[j];
            int doSomething = 0;
            
            if(j) {
                doSomething = -prices[i] + next[false];
            } else {
                doSomething = prices[i];
            }
            curr[j] =  max(doNothing, doSomething);
        }
        next = curr;   
    }
    return curr[1];
}

int maxProfit(vector<int>& prices) {
    return solveTab(prices);
}



// LC 122

// using recursion 
int solve(int index , bool canBuy , vector<int> & prices){
    if(index >= prices.size()) return 0;

    // do nothing 
    int profitWhenDidNothing = solve(index+1,canBuy,prices);

    int profitWhenDidSomething = 0;

    // when you are not holding any stock and buying a stock 
    if(canBuy){
        profitWhenDidSomething -= prices[index];
        profitWhenDidSomething += solve(index+1, false,prices);
    }
    // when you are holding a stock  and selling that stock
    else{
        profitWhenDidSomething += prices[index];
        profitWhenDidSomething += solve(index+1,true,prices);
    }

    return max(profitWhenDidNothing,profitWhenDidSomething);
}
int maxProfit(vector<int>& prices) {
    return solve(0,true, prices);
}


// using memoization  
int solveMem(int index , bool canBuy , vector<int> & prices, vector<vector<int>>&dp){
    if(index >= prices.size()) return 0;
    if(dp[index][canBuy]!=-1)return dp[index][canBuy];

    // do nothing 
    int profitWhenDidNothing = solveMem(index+1,canBuy,prices,dp);

    int profitWhenDidSomething = 0;

    // when you are not holding any stock and buying a stock 
    if(canBuy){
        profitWhenDidSomething -= prices[index];
        profitWhenDidSomething += solveMem(index+1, false,prices,dp);
    }
    // when you are holding a stock  and selling that stock
    else{
        profitWhenDidSomething += prices[index];
        profitWhenDidSomething += solveMem(index+1,true,prices,dp);
    }

    return dp[index][canBuy] =  max(profitWhenDidNothing,profitWhenDidSomething);
}
int maxProfit(vector<int>& prices) {
    vector<vector<int>> dp(prices.size(),vector<int>(2,-1));
    return solveMem(0,true, prices,dp);
}


// usign tabulation 
int solveTab(vector<int>& prices){
    int n = prices.size();
    vector<vector<int>> dp(prices.size()+1,vector<int>(2,0));
    for (int  i = n-1; i >=0; i--){
        for (int  j  = 0; j  <= 1; j ++){
            int profitWhenDidNothing = dp[i+1][j];

            int profitWhenDidSomething = 0;

            // when you are not holding any stock and buying a stock 
            if(j){
                profitWhenDidSomething -= prices[i];
                profitWhenDidSomething += dp[i+1][0];
            }
            // when you are holding a stock  and selling that stock
            else{
                profitWhenDidSomething += prices[i];
                profitWhenDidSomething += dp[i+1][1];
            }

            dp[i][j] = max(profitWhenDidNothing,profitWhenDidSomething);
        }
    }
    return dp[0][1];
}
int maxProfit(vector<int>& prices) {
    return solveTab(prices);
}


// tabulation with space optimization 
int solveTab(vector<int>& prices){
    int n = prices.size();
    vector<int> next(n+1,0);
    vector<int> curr(n+1,0);

    for (int  i = n-1; i >=0; i--){
        for (int  j  = 0; j  <= 1; j ++){
            int profitWhenDidNothing = next[j];

            int profitWhenDidSomething = 0;

            // when you are not holding any stock and buying a stock 
            if(j){
                profitWhenDidSomething -= prices[i];
                profitWhenDidSomething += next[0];
            }
            // when you are holding a stock  and selling that stock
            else{
                profitWhenDidSomething += prices[i];
                profitWhenDidSomething += next[1];
            }

            curr[j] = max(profitWhenDidNothing,profitWhenDidSomething);
        }
        next = curr;
    }
    return curr[1];
}
int maxProfit(vector<int>& prices) {
    return solveTab(prices);
}



// LC 123

// usign recursioon
int solve(int index , bool canBuy , vector<int> & prices,int& k){
    if(index >= prices.size() || k==0) return 0;

    // do nothing 
    int profitWhenDidNothing = solve(index+1,canBuy,prices,k);

    int profitWhenDidSomething = 0;

    // when you are not holding any stock and buying a stock 
    if(canBuy){
        profitWhenDidSomething -= prices[index];
        profitWhenDidSomething += solve(index+1,false,prices,k);
    }
    // when you are holding a stock  and selling that stock
    else{
        k--;
        profitWhenDidSomething += prices[index];
        profitWhenDidSomething += solve(index+1,true,prices,k);
    }

    return max(profitWhenDidNothing,profitWhenDidSomething);
}
int maxProfit(vector<int>& prices) {
    int k = 2;
    return solve(0,true,prices,k);
}


// usign memoization 
int solveMem(int index , bool canBuy , vector<int> & prices,int& k, vector<vector<vector<int>>> dp){
    if(index >= prices.size() || k==0) return 0;
    if(dp[index][canBuy][k] !=-1) return dp[index][canBuy][k];

    // do nothing 
    int profitWhenDidNothing = solveMem(index+1,canBuy,prices,k,dp);

    int profitWhenDidSomething = 0;

    // when you are not holding any stock and buying a stock 
    if(canBuy){
        profitWhenDidSomething -= prices[index];
        profitWhenDidSomething += solveMem(index+1,false,prices,k,dp);
    }
    // when you are holding a stock  and selling that stock
    else{
        k--;
        profitWhenDidSomething += prices[index];
        profitWhenDidSomething += solveMem(index+1,true,prices,k,dp);
    }

    dp[index][canBuy][k] = max(profitWhenDidNothing,profitWhenDidSomething);
}
int maxProfit(vector<int>& prices) {
    int k = 2;
    vector<vector<vector<int>>> dp(prices.size(),vector<vector<int>>(2,vector<int>(k+1,-1)));
    return solveMem(0,true,prices,k,dp);
}


// usign tabulation
int solveTab(vector<int>& prices) {
    int n = prices.size();
    int k = 2; // Maximum transactions allowed
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int>(k+1, 0))); // Initialize dp to 0

    for (int i = n-1; i >= 0; i--) {
        for (int j = 0; j <= 1; j++) {
            for (int l = 1; l <= k; l++) { // Start from 1, as at least 1 transaction is needed
                // Do nothing
                int profitWhenDidNothing = dp[i+1][j][l];
                int profitWhenDidSomething = 0;

                // When you are not holding any stock and decide to buy
                if (j) {
                    profitWhenDidSomething = -prices[i] + dp[i+1][0][l];
                }
                // When you are holding a stock and decide to sell
                else {
                    profitWhenDidSomething = prices[i] + dp[i+1][1][l-1]; // Use l-1 for completed transaction
                }

                dp[i][j][l] = max(profitWhenDidNothing, profitWhenDidSomething);
            }
        }
    }

    return dp[0][1][k]; // Maximum profit starting from 0th day, canBuy=true, with k transactions
}

int maxProfit(vector<int>& prices) {
    return solveTab(prices);
}

// i love you more than i love anyone else,you have melted my heart which noone could . when i talk you just listen; when i'm mad you never argue .i wanna sleep and cuddle with you but i'm afraid that i might strangle for you too gentle .i offer you my soul untouched like those red roses. you are unlike any other,i'm in love with your dark skin. and sorry i do get mad at you sometimes and it's always for no reason but you know that i never mean it for underlying that madness is love,pure love .even in those moments you are patient beyond belief and tolerate a madman like me . why do you do all that? i could never figure that out. you are the only one i can confide in, my love.you mean everything to me;i feel content when i'm just with you in my room alone.there is no lust inbetween us,lust doesn't let you love to the fullest , it pollutes; doesn't it babe? i have always been too afraid to love anyone, i have always thought is it worth the risk and effort ? but i didn't put effort to love you and there is not risk with you , even death can't break us apart for i'm gonna die first and "if the tree falls and i don't hear the sound , did the tree the really fall" .you are mine and just mine ;am i possesive? for you , i'm and i know that you don't mind it.





// chocolate pickup - https://www.naukri.com/code360/problems/ninja-and-his-friends_3125885

// using recursion

int solve(int row, int col1, int col2, int r, int c, vector<vector<int>>& grid) {
    // Out of bounds
    if (col1 < 0 || col1 >= c || col2 < 0 || col2 >= c) return -1e9;

    // Base case: last row
    if (row == r) {
       return 0;
    }

    int maxChoco = 0;
    for (int d1 = -1; d1 <= 1; d1++) {
        for (int d2 = -1; d2 <= 1; d2++) {
            int newCol1 = col1 + d1;
            int newCol2 = col2 + d2;

            int current = (col1 == col2) ? grid[row][col1] : grid[row][col1] + grid[row][col2];
            int next = solve(row + 1, newCol1, newCol2, r, c, grid);

            maxChoco = max(maxChoco, current + next);
        }
    }

    return maxChoco;
}

int maximumChocolates(int r, int c, vector<vector<int>> &grid) {
    return solve(0, 0, c - 1, r, c, grid);
}


// using memoization 
int solve(int row, int col1, int col2, int r, int c, vector<vector<int>>& grid, vector<vector<vector<int>>> &dp) {
    if (col1 < 0 || col1 >= c || col2 < 0 || col2 >= c) return -1e9;
    if (row == r) return 0;
    if (dp[row][col1][col2] != -1) return dp[row][col1][col2];

    int current = (col1 == col2) ? grid[row][col1] : grid[row][col1] + grid[row][col2];
    int maxChoco = 0;
    for (int d1 = -1; d1 <= 1; d1++) {
        for (int d2 = -1; d2 <= 1; d2++) {
            int newCol1 = col1 + d1;
            int newCol2 = col2 + d2;

            int next = solve(row + 1, newCol1, newCol2, r, c, grid, dp);

            maxChoco = max(maxChoco, current + next);
        }
    }

    return dp[row][col1][col2] = maxChoco;
}

int maximumChocolates(int r, int c, vector<vector<int>> &grid) {
    vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(c, -1)));
    return solve(0, 0, c - 1, r, c, grid, dp);
}


// using tabulation
int maximumChocolates(int r, int c, vector<vector<int>> &grid) {
    // +1 for the base case row (row == r)
    vector<vector<vector<int>>> dp(r + 1, vector<vector<int>>(c, vector<int>(c, 0)));


    for (int row = r - 1; row >= 0; row--) {
        for (int col1 = c - 1; col1 >= 0; col1--) {
            for (int col2 = 0; col2 <= c-1; col2++) {
                int maxChoco = 0;
                
                int currChoco = (col1 == col2)? grid[row][col1]: grid[row][col1] + grid[row][col2];

                for (int d1 = -1; d1 <= 1; d1++) {
                    for (int d2 = -1; d2 <= 1; d2++) {
                        int newCol1 = col1 + d1;
                        int newCol2 = col2 + d2;

                        if (newCol1 >= 0 && newCol1 < c && newCol2 >= 0 && newCol2 < c) {
                            maxChoco = max(maxChoco, dp[row + 1][newCol1][newCol2]);
                        }
                    }
                }

                dp[row][col1][col2] = currChoco + maxChoco;
            }
        }
    }

    return dp[0][0][c - 1];
}


// using tabulation with space optimization
int maximumChocolates(int r, int c, vector<vector<int>> &grid) {
    // +1 for the base case row (row == r)
    vector<vector<int>>currVector(c, vector<int>(c, 0));
    vector<vector<int>>nextVector(c, vector<int>(c, 0));

    for (int row = r - 1; row >= 0; row--) {
        for (int col1 = c - 1; col1 >= 0; col1--) {
            for (int col2 = 0; col2 <= c-1; col2++) {
                int maxChoco = 0;
                
                int currChoco = (col1 == col2)? grid[row][col1]: grid[row][col1] + grid[row][col2];

                for (int d1 = -1; d1 <= 1; d1++) {
                    for (int d2 = -1; d2 <= 1; d2++) {
                        int newCol1 = col1 + d1;
                        int newCol2 = col2 + d2;

                        if (newCol1 >= 0 && newCol1 < c && newCol2 >= 0 && newCol2 < c) {
                            maxChoco = max(maxChoco, nextVector[newCol1][newCol2]);
                        }
                    }
                }

                currVector[col1][col2] = currChoco + maxChoco;
            }
        }
        nextVector = currVector;
    }

    return currVector[0][c - 1];
}



// LC - 2035. Partition Array Into Two Arrays to Minimize Sum Difference

// using recursion

int solve(int index, int count, int sum, int n, int totalSum, vector<int>& nums) {
    // Base case: we've selected n elements
    if (count == n) {
        int otherSum = totalSum - sum;
        return abs(sum - otherSum);
    }

    // End of array
    if (index == nums.size()) return INT_MAX;

    // Option 1: pick current element
    int pick = solve(index + 1, count + 1, sum + nums[index], n, totalSum, nums);

    // Option 2: skip current element
    int notPick = solve(index + 1, count, sum, n, totalSum, nums);

    return min(pick, notPick);
}

int minimumDifference(vector<int>& nums) {
    int totalSum = accumulate(nums.begin(), nums.end(), 0);
    int n = nums.size() / 2;
    return solve(0, 0, 0, n, totalSum, nums);
}


int solve2(int child , int cookie ,vector<int>& g, vector<int>& s ){
    if(child>=g.size()|| cookie>=s.size()) return 0;

    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    if(g[child]<=s[cookie]){
        choice1 = 1+ solve2(child+1,cookie+1,g,s);
    }

    choice2 = solve2(child+1,cookie,g,s);
    choice3 = solve2(child, cookie+1,g,s);

    return max(choice1,max(choice2,choice3));
}

int findContentChildren(vector<int>& g, vector<int>& s) {
    return solve2(0,0,g,s);
}



// LC - 494. Target Sum

// using recursion

int solve3(int i , int sum , vector<int>& nums, int target){
    if(i==nums.size()){
        if(sum == target) return 1;
        return 0;
    } 

    int addChoice = solve3(i+1,sum+nums[i],nums, target);
    int subtractChoice = solve3(i+1,sum-nums[i],nums , target);

    return addChoice+subtractChoice;
}
int findTargetSumWays(vector<int>& nums, int target) {
    return solve3(0,0,nums, target);
}

// using memoization
int solve3(int i, int sum, vector<int>& nums, int target, unordered_map<string, int>& dp) {
    if (i == nums.size()) {
        return (sum == target) ? 1 : 0;
    }

    string key = to_string(i) + "," + to_string(sum);
    if (dp.find(key) != dp.end()) return dp[key];

    int addChoice = solve3(i+1, sum + nums[i], nums, target, dp);
    int subtractChoice = solve3(i+1, sum - nums[i], nums, target, dp);

    return dp[key] = addChoice + subtractChoice;
}

int findTargetSumWays(vector<int>& nums, int target) {
    unordered_map<string, int> dp;
    return solve3(0, 0, nums, target, dp);
}


/// using tabulation
int solveTab(vector<int>& nums, int target) {
    int n = nums.size();
    int arraySum = accumulate(nums.begin(), nums.end(), 0);

    unordered_map<string, int> dp;

    // Base case initialization at i==n
    for (int s = -arraySum; s <= arraySum; s++) {
        string key = to_string(n) + "," + to_string(s);
        dp[key] = (s == target) ? 1 : 0;
    }

    // Bottom-up tabulation
    for (int i = n-1 ; i >= 0; i--) {
        for (int s = -arraySum; s <= arraySum; s++) {
            string keyAdd = to_string(i + 1) + "," + to_string(s + nums[i]);
            string keySubtract = to_string(i + 1) + "," + to_string(s - nums[i]);

            int addChoice = dp.count(keyAdd) ? dp[keyAdd] : 0;
            int subtractChoice = dp.count(keySubtract) ? dp[keySubtract] : 0;

            string key = to_string(i) + "," + to_string(s);
            dp[key] = addChoice + subtractChoice;
        }
    }

    string ansKey = to_string(0) + "," + to_string(0);
    return dp.count(ansKey) ? dp[ansKey] : 0;
}

int findTargetSumWays(vector<int>& nums, int target) {
    return solveTab(nums, target);
}

int solve(vector<int>& coins , int amount){
    if(amount == 0) return 1;
    if(amount<=0) return 0;
    
    int ans = 0 ;
    for(int i = 0 ; i < coins.size(); i ++){
        ans+=solve(coins , amount-coins[i]);
    }
    return ans;
}

int change(int amount, vector<int>& coins) {
    
}


// LC 518 - coin change 2
// using recursion
int solve2(int i , vector<int>& coins , int amount){
    if(i==coins.size()) return 0;
    if(amount == 0) return 1;
    if(amount<=0) return 0;

    int take = solve2(i,coins , amount -coins[i]);
    int skip = solve2(i+1, coins , amount);
    return take + skip;

}
int change(int amount, vector<int>& coins) {
    return solve2(0, coins , amount);
}

// using memoization
int solve2(int i, vector<int>& coins, int amount, vector<vector<int>>& dp) {
    if (i == coins.size()) return (amount == 0) ? 1 : 0;
    if (amount < 0) return 0;

    if (dp[i][amount] != -1) return dp[i][amount];

    int take = solve2(i, coins, amount - coins[i], dp);
    int skip = solve2(i + 1, coins, amount, dp);

    return dp[i][amount] = take + skip;
}

int change(int amount, vector<int>& coins) {
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1, -1));
    return solve2(0, coins, amount, dp);
}




// unbounded knapsack with duplicate items - https://www.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1

int solve(int i, vector<int>& val, vector<int>& wt, int capacity, int n) {
    // Base Case: no more items or no capacity
    if (i == n || capacity == 0) return 0;

    // If we can pick current item
    if (wt[i] <= capacity) {
        // Two choices: pick it (stay at i) or skip
        int pick = val[i] + solve(i, val, wt, capacity - wt[i], n);
        int notPick = solve(i + 1, val, wt, capacity, n);
        return max(pick, notPick);
    }
    else {
        // Can't pick this item, move to next
        return solve(i + 1, val, wt, capacity, n);
    }
}
int knapSack(vector<int>& val, vector<int>& wt, int capacity) {
        int n = val.size();
        return solve(0, val, wt, capacity, n);
}


// LC - 516. Longest Palindromic Subsequence

//  using recursion
int solve(int i, int j, string& s, vector<vector<int>>& dp) {
    if (i > j) return 0;
    if (i == j) return 1;

    if (dp[i][j] != -1) return dp[i][j]; 

    if (s[i] == s[j])
        return dp[i][j] = 2 + solve(i+1, j-1, s, dp);
    else
        return dp[i][j] = max(solve(i+1, j, s, dp), solve(i, j-1, s, dp));
    }
    
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, -1)); 
        return solve(0, n-1, s, dp);
}




// LC - 72. Edit Distance

// using recursion 

int solve(int i ,int j , string word1 , string word2 ){
    if(i==word1.size()) return word2.size()-j;
    if(j == word2.size()) return word1.size()-i;
    
    
    if(word1[i]==word2[j]) return solve(i+1,j+1,word1 , word2);

    int insert  = 1 + solve(i , j+1 , word1 , word2);
    int deleteChar = 1+ solve(i+1 ,j , word1 , word2);
    int replace = 1+solve(i+1 , j+1 , word1 , word2);

    return min({insert , deleteChar , replace});
}
int minDistance(string word1, string word2) {
    return solve(0 , 0 , word1 , word2);
}


// using tabulation 

    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();

        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

        // Base cases:
        // When word1 is exhausted, insert remaining word2 characters
        for (int j = 0; j <= n; ++j) dp[m][j] = n - j;

        // When word2 is exhausted, delete remaining word1 characters
        for (int i = 0; i <= m; ++i) dp[i][n] = m - i;

        // Fill DP table from bottom-right to top-left
        for (int i = m-1; i >= 0; --i) {
            for (int j = n-1; j >= 0; --j) {
                if (word1[i] == word2[j]) {
                    dp[i][j] = dp[i+1][j+1]; // no operation
                } else {
                    int insertOp  = 1 + dp[i][j+1];
                    int deleteOp  = 1 + dp[i+1][j];
                    int replaceOp = 1 + dp[i+1][j+1];

                    dp[i][j] = min({insertOp, deleteOp, replaceOp});
                }
            }
        }

        return dp[0][0];
    }




    // LC - 44. Wildcard Matching

    // using recursion  

    bool isMatch(string s, string p) {
        return match(0, 0, s, p);
    }

    bool match(int i, int j, string &s, string &p) {
        if (i == s.size() && j == p.size())
            return true;

        // Pattern ended but string still left
        if (j == p.size())
            return false;

        // String ended but pattern still left
        if (i == s.size()) {
            for (int k = j; k < p.size(); ++k)
                if (p[k] != '*') return false;
            return true;
        }

        if (p[j] == s[i] || p[j] == '?')
            return match(i+1, j+1, s, p);

        if (p[j] == '*') {
            return match(i, j+1, s, p) || match(i+1, j, s, p);
        }

        // Characters don't match and no wildcard
        return false;
    }

     bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, -1));
        return match(0, 0, s, p, dp);
    }


     // using tabulation 
        bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));

        dp[m][n] = true;

        for (int j = n-1; j >= 0; --j)
            dp[m][j] = (p[j] == '*') && dp[m][j+1];

        for (int i = m-1; i >= 0; --i) {
            for (int j = n-1; j >= 0; --j) {
                if (p[j] == s[i] || p[j] == '?')
                    dp[i][j] = dp[i+1][j+1];
                else if (p[j] == '*')
                    dp[i][j] = dp[i][j+1] || dp[i+1][j];
                else
                    dp[i][j] = false;
            }
        }

        return dp[0][0];
    }



// LC - 121. Best Time to Buy and Sell Stock

// without recursion 
 
int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;
    
    for(int price : prices) {
        minPrice = min(minPrice, price);
        maxProfit = max(maxProfit, price - minPrice);
    }
    return maxProfit;
}


// using recursion 

int solve(int index, bool canBuy, vector<int>& prices) {
    // Base case
    if(index >= prices.size()) return 0;
    
    int doNothing = solve(index + 1, canBuy, prices);
    int doSomething = 0;
    
    if(canBuy) {
        doSomething = -prices[index] + solve(index + 1, false, prices);
    } else {
        doSomething = prices[index];
    }
    
    return max(doNothing, doSomething);
}
int maxProfit(vector<int>& prices) {
    return solve (0,true , prices);
}




// LC - 123. Best Time to Buy and Sell Stock III

    // usign recursioon
int solve(int index , bool canBuy , vector<int> & prices,int k){
    if(index >= prices.size() || k==0) return 0;

    // do nothing 
    int profitWhenDidNothing = solve(index+1,canBuy,prices,k);

    int profitWhenDidSomething = 0;

    // when you are not holding any stock and buying a stock 
    if(canBuy){
        profitWhenDidSomething -= prices[index];
        profitWhenDidSomething += solve(index+1,false,prices,k);
    }
    // when you are holding a stock  and selling that stock
    else{
        // k--;
        profitWhenDidSomething += prices[index];
        profitWhenDidSomething += solve(index+1,true,prices,k-1);
        // k++;
    }

    return max(profitWhenDidNothing,profitWhenDidSomething);
}
int maxProfit(vector<int>& prices) {
    int k = 2;
    return solve(0,true,prices,k);
}


int solveTab(vector<int>& prices){
    int k = 2;
    int n = prices.size();
    vector<vector<vector<int>>>dp(n+1,vector<vector<int>>(2,vector<int>(k+1,0)));
    
    for(int i = n-1; i>=0; i--){
        for(int j = 0; j<=1; j++){
            for(int l = 1; l<=k;l++){
                // do nothing 
                int profitWhenDidNothing = dp[i+1][j][l];
                
                int profitWhenDidSomething = 0;
                
                // when you are not holding any stock and buying a stock 
                if(j){
                    profitWhenDidSomething -= prices[i];
                    profitWhenDidSomething += dp[i+1][0][l];
                }
                // when you are holding a stock  and selling that stock
                else{
                    // k--;
                    profitWhenDidSomething += prices[i];
                    profitWhenDidSomething += dp[i+1][1][l-1];
                    // k++;
                }
                
                dp[i][j][l] = max(profitWhenDidNothing,profitWhenDidSomething);
                
            }
        }
    }

    return dp[0][1][k];
}

int maxProfit(vector<int>& prices){
    return solveTab(prices);
}


// tabulation using space optimization 

int solveOptimal(vector<int>& prices){
    int k = 2;
    int n = prices.size();
    vector<vector<vector<int>>>dp(n+1,vector<vector<int>>(2,vector<int>(k+1,0)));
    vector<vector<int>>next(2,vector<int>(k+1,0));
    vector<vector<int>>curr(2,vector<int>(k+1,0));
    
    for(int i = n-1; i>=0; i--){
        for(int j = 0; j<=1; j++){
            for(int l = 1; l<=k;l++){
                // do nothing 
                int profitWhenDidNothing = next[j][l];
                
                int profitWhenDidSomething = 0;
                
                // when you are not holding any stock and buying a stock 
                if(j){
                    profitWhenDidSomething -= prices[i];
                    profitWhenDidSomething += next[0][l];
                }
                // when you are holding a stock  and selling that stock
                else{
                    // k--;
                    profitWhenDidSomething += prices[i];
                    profitWhenDidSomething += next[1][l-1];
                    // k++;
                }
                
                curr[j][l] = max(profitWhenDidNothing,profitWhenDidSomething);
                
            }
        }
        next = curr;
    }

    return curr[1][k];
}

int maxProfit(vector<int>& prices){
    return solveOptimal(prices);
}




// LC - 309. Best Time to Buy and Sell Stock with Cooldown

// using recursion

    int solve(int i, bool canBuy, vector<int>& prices) {
    if (i >= prices.size()) return 0;

    int profit = 0;

    if (canBuy) {
        // Either buy today or skip
        int buy = -prices[i] + solve(i + 1, false, prices);
        int skip = solve(i + 1, true, prices);
        profit = max(buy, skip);
    } else {
        // Either sell today (with cooldown) or skip
        int sell = prices[i] + solve(i + 2, true, prices);
        int skip = solve(i + 1, false, prices);
        profit = max(sell, skip);
    }

    return profit;
}

int maxProfit(vector<int>& prices) {
    return solve(0, true, prices);
}

// using tabulation 

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> dp(n + 2, vector<int>(2, 0));

    for (int i = n - 1; i >= 0; --i) {
        dp[i][1] = max(-prices[i] + dp[i+1][0],
                       dp[i+1][1]);

        dp[i][0] = max(prices[i] + dp[i+2][1],
                       dp[i+1][0]);
    }

    return dp[0][1];
}



// LC - 714. Best Time to Buy and Sell Stock with Transaction Fee

// using recursion 
    int solve(int i, bool canBuy, vector<int>& prices, int fee) {
    if (i >= prices.size()) return 0;

    int profit = 0;

    if (canBuy) {
        // Either buy today or skip
        int buy = -prices[i] + solve(i + 1, false, prices, fee);
        int skip = solve(i + 1, true, prices, fee);
        profit = max(buy, skip);
    } else {
        // Either sell today (pay fee) or skip
        int sell = prices[i] - fee + solve(i + 1, true, prices, fee);
        int skip = solve(i + 1, false, prices, fee);
        profit = max(sell, skip);
    }

    return profit;
}

int maxProfit(vector<int>& prices, int fee) {
    return solve(0, true, prices, fee);
}

// using tabulation 

int maxProfit(vector<int>& prices, int fee) {
    int n = prices.size();
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));

    for (int i = n - 1; i >= 0; --i) {
        // If can buy today
        dp[i][1] = max(
            -prices[i] + dp[i + 1][0],  // Buy
            dp[i + 1][1]                // Skip
        );

        // If holding a stock (can sell)
        dp[i][0] = max(
            prices[i] - fee + dp[i + 1][1], // Sell (pay fee)
            dp[i + 1][0]                    // Skip
        );
    }

    return dp[0][1];  // starting from day 0 with canBuy=true
}
