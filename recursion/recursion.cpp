#include <bits/stdc++.h>
using namespace std;

// atoi function
string solve(int i ,string s , string ans, vector<char> &digit){
    if(find(digit.begin(),digit.end(),s[i]) == digit.end()){
        return ans;
    }
    if(i == s.size()){
        return ans;
    }
    if(s[i] == ' '){
        return solve(i+1,s,ans,digit);
    }

    return solve(i+1,s,ans+s[i],digit);
}

int myAtoi(string s) {
    vector<char> digit = {'0','1','2','3','4','5','6','7','8','9'};
    if(s[0] == '-' || s[0] == '+'){
        string ans = solve(1,s,"",digit);
    }
}


// pow function
int solve(int n , int x ,int result){
    if(n == 0){
        return result;
    }

    if(n<0){
        result = result / x;
        n++;
        return solve(n,x,result);
    }

        result = result * x;
        n--;
        return solve(n,x,result);
    
}
double myPow(double x, int n) {
    if(x == 0){
        return 0;
    }
    return solve(n,x,1);
}


// sorting a stack using recursion
void solve(stack<int> &s , int x){
    if(s.empty() || s.top() < x){
        s.push(x);
        return;
    }
    int temp = s.top();
    s.pop();
    solve(s,x);
    s.push(temp);

}
void sort(stack<int> &s){
    vector<int> v;
    while(!s.empty()){
        v.push_back(s.top());
        s.pop();
    }
    for(int i = 0; i < v.size(); i++){
        solve(s,v[i]);
    }
}


// generate parenthesis
void solve(string s , int openCount, vector<string> &ans,int n ){
    // if(s.size() == 2*n){
        // ans.push_back(s);
        // return;
    // }
    if(count(s.begin(),s.end(),'(') ==n){
        if(s.size() == 2*n){
            ans.push_back(s);
            return;
        }
        else{
            while(s.size() != 2*n){
                s += ")";
            }
            ans.push_back(s);
            return;
        }
    }

    if(openCount>0 ){
        solve(s+"(",openCount+1,ans,n);
        solve(s+")",openCount-1,ans,n);
    }
    else{
        solve(s+"(",openCount+1,ans,n);
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> ans;
    solve("",0,ans,n);
    return ans;
}



// better string

// using recursion
void generateSubsequences(const std::string &str, int index, std::string current, std::unordered_set<std::string> &subsequences) {
    if (index == str.size()) {
        subsequences.insert(current);  // Insert the current subsequence into the set
        return;
    }
    generateSubsequences(str, index + 1, current, subsequences);
    generateSubsequences(str, index + 1, current + str[index], subsequences);
}
    
int countDistinctSubsequences(const std::string &str) {
    std::unordered_set<std::string> subsequences;
    generateSubsequences(str, 0, "", subsequences);
    return subsequences.size();  // The number of unique subsequences
}

string betterString(std::string str1, std::string str2) {
        int count1 = countDistinctSubsequences(str1);
        int count2 = countDistinctSubsequences(str2);
        
        return (count1 >= count2) ? str1 : str2;
}




// number of subsequences with sum k
int solve(int i , int target , int arr[], int n){
    if(i == n){
        if(target == 0) return 1;
        else return 0;
    }

    int include =0;
    int exclude = 0;
    if(arr[i] <= target) include = solve(i+1, target-arr[i], arr,n);

    exclude =  solve(i+1, target, arr, n);

    return include + exclude;
}
int perfectSum(int arr[], int n, int sum){
    return solve(0, sum , arr, n);
}



// combination sum
void solve(int i , int target , vector<int> &candidates , vector<int>&temp, vector<vector<int>> &result){
    if(target == 0){
        result.push_back(temp);
        return ;
    }
    if(i == candidates.size()){
        return;
    }

    if(target>candidates[i]){
        temp.push_back(candidates[i]);
        solve(i , target-candidates[i],candidates,temp, result);
        temp.pop_back();
    }

    solve(i+1 , target , candidates , temp , result);

}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> temp;
    solve(0,target,candidates,temp,result);
}


// combination sum 2

void solve(int i , int target , vector<int> &candidates , vector<int>&temp, vector<vector<int>> &result){
    if(target == 0){
        result.push_back(temp);
        return ;
    }
    if(i == candidates.size()){
        return;
    }

    if((target>=candidates[i] && i != 0 && candidates[i] != candidates[i-1]) || (i == 0 && target>=candidates[i])){
        temp.push_back(candidates[i]);
        solve(i+1 , target-candidates[i],candidates,temp, result);
        temp.pop_back();
    }

    solve(i+1 , target , candidates , temp , result);

}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());  
    vector<vector<int>> result;
    vector<int> temp;
    solve(0,target,candidates,temp,result);
    return result;
}


    int minimumEffortPath(vector<vector<int>>& heights) {
        int rows = heights.size();
        int cols = heights[0].size();
        
        // Create a priority queue storing {effort, {x, y}}
        priority_queue<pair<int, pair<int, int>>, 
                      vector<pair<int, pair<int, int>>>, 
                      greater<pair<int, pair<int, int>>>> pq;
        
        // Create a distance matrix initialized with infinity
        vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
        
        // Directions: right, down, left, up
        vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        // Start from (0,0) with effort 0
        dist[0][0] = 0;
        pq.push({0, {0, 0}});
        
        while(!pq.empty()) {
            int effort = pq.top().first;
            int x = pq.top().second.first;
            int y = pq.top().second.second;
            pq.pop();
            
            // If we reached the target
            if(x == rows-1 && y == cols-1) 
                return effort;
            
            // If we found a better path to current cell
            if(effort > dist[x][y]) 
                continue;
            
            // Check all 4 directions
            for(auto& dir : dirs) {
                int newX = x + dir.first;
                int newY = y + dir.second;
                
                if(newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                    // Calculate new effort as max of current effort and 
                    // absolute difference between current and next cell
                    int newEffort = max(effort, 
                        abs(heights[x][y] - heights[newX][newY]));
                    
                    // If we found a better path to next cell
                    if(newEffort < dist[newX][newY]) {
                        dist[newX][newY] = newEffort;
                        pq.push({newEffort, {newX, newY}});
                    }
                }
            }
        }
        return 0;
    }







    int minimumEffortPath(vector<vector<int>>& heights) {
        int rows = heights.size();
        int cols = heights[0].size();
        
        // Create a priority queue storing {effort, {x, y}}
        priority_queue<pair<int, pair<int, int>>, 
                      vector<pair<int, pair<int, int>>>, 
                      greater<pair<int, pair<int, int>>>> pq;
        
        // Create a distance matrix initialized with infinity
        vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
        
        // Directions: right, down, left, up
        vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        // Start from (0,0) with effort 0
        dist[0][0] = 0;
        pq.push({0, {0, 0}});
        
        while(!pq.empty()) {
            int effort = pq.top().first;
            int x = pq.top().second.first;
            int y = pq.top().second.second;
            pq.pop();
            
            // If we reached the target
            if(x == rows-1 && y == cols-1) 
                return effort;
            
            // If we found a better path to current cell
            if(effort > dist[x][y]) 
                continue;
            
            // Check all 4 directions
            for(auto& dir : dirs) {
                int newX = x + dir.first;
                int newY = y + dir.second;
                
                if(newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                    // Calculate new effort as max of current effort and 
                    // absolute difference between current and next cell
                    int newEffort = max(effort, 
                        abs(heights[x][y] - heights[newX][newY]));
                    
                    // If we found a better path to next cell
                    if(newEffort < dist[newX][newY]) {
                        dist[newX][newY] = newEffort;
                        pq.push({newEffort, {newX, newY}});
                    }
                }
            }
        }
        return 0;
    }



// LC 46 - permutations


// method 1 - O(N) S.C. - of map
void solve(unordered_map<int,bool>& mp , vector<int> & temp , vector<vector<int>> & result) {
    if(temp.size() ==  mp.size()) result.push_back(temp);

    for(auto &x:mp){
        if(x.second == false){
            x.second = true;
            temp.push_back(x.first);
            solve(mp,temp , result);
            x.second = false;
            temp.pop_back();
        }
    }

}

vector<vector<int>> permute(vector<int>& nums) {
    unordered_map<int, bool> mp;
    vector<int> temp;

    for(int num:nums){
        mp[num] = false;
    }

    vector<vector<int>> result;
    solve(mp , temp , result);
    return result;
}


// method 2 - more space optimized
void solve( int index , vector<int> & nums , vector<vector<int>> & result) {
    if(index == nums.size()){
        result.push_back(nums);
        return;
    }

    for(int i = index ; i < nums.size(); i++){
        swap(nums[index], nums[i]);
        solve(index+1 , nums, result);
        swap(nums[index], nums[i]); // backtracking
    }

}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> result;
    solve(0 , nums , result);
    return result;
}



// array leaders
vector<int> leaders(vector<int>& arr) {
    vector<int> leaders;int maxi = -1;
    for(int i = arr.size()-1; i>=0 ; i--){
        if(arr[i] >= maxi) leaders.push_back(arr[i]);
        // if(arr[i] >= maxi) leaders.insert(leaders.begin(),arr[i]);
        maxi = max(maxi, arr[i]);
    }
    reverse(leaders.begin(), leaders.end());
    return leaders;
}


// LC 90 subsets 2 
void solve(vector<int>&nums, vector<int> & temp , vector<vector<int>>&ans, int index){
    ans.push_back(temp);
    for(int i = index ; i<nums.size();i++){
        if(i>index && nums[i]==nums[i-1]) continue;

        temp.push_back(nums[i]);
        solve(nums,temp , ans , i+1);
        temp.pop_back();
    }
    
}

vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(),nums.end());
    vector<int> temp;
    vector<vector<int>> ans;
    int index = 0;
    solve(nums,temp,ans,index);
    return ans;
        
}



// LC 216 combination sum 3

void solve(int num , vector<int>&temp , vector<vector<int>>&ans,int sum ,int k){
    if(sum == 0 && k == 0) ans.push_back(temp);
    else if(num>9 || k!=0 ) return;

    if(num<sum){
        temp.push_back(num);
        solve(num+1,temp,ans,sum-num,k-1);
        temp.pop_back();
    }
    solve(num+1,temp,ans,sum,k);

}

vector<vector<int>> combinationSum3(int k, int n) {
    vector<int> temp;
    vector<vector<int>> ans;
    solve(1,temp,ans,n,k);
    return ans;
}



// LC 17 
void solve(int index , string digits , string tempStr, unordered_map<int, string> &mp,vector<string> & result){
    if(index>=digits.size()){
        result.push_back(tempStr);
    }
    for (int i = index ; i<tempStr.size();i++){
        for(int j = 0;j<mp[i].size();j++){
            tempStr.push_back(mp[i][j]);
            solve(index+1,digits,tempStr,mp,result);
            tempStr.pop_back();
        }
    }
} 



vector<string> letterCombinations(string digits) {
    unordered_map <int , string> mp = {
        {2,"abc"},
        {3,"def"},
        {4,"ghi"},
        {5,"jkl"},
        {6,"mno"},
        {7,"pqrs"},
        {8,"tuv"},
        {9,"wxyz"}
    };

    vector<string> result;
    string tempStr;
    int index = 0;
    solve(index , digits, tempStr,mp,result);
    return result;     
}



// Rat in a maze 
void solve(vector<vector<int>>&matrix , vector<vector<int>>& visited , int i , int j , string temp, vector<string>& ans){

    if(i==matrix.size()-1 && j == matrix[0].size() -1 ){
        ans.push_back(temp);
        return;
    }

    // UP   
    if(i-1>=0 && matrix[i-1][j] == 1 && visited[i-1][j] == 0){
        visited[i-1][j] = 1;
        solve(matrix, visited , i-1,j,temp+'U', ans);
        visited[i-1][j] = 0;
    }

    // DOWN
    if(i+1<matrix.size() && matrix[i+1][j] == 1 && visited[i+1][j] == 0){
        visited[i+1][j] = 1;
        solve(matrix, visited , i+1,j,temp+'D', ans);
        visited[i-1][j] = 0;
    }

    // LEFT
    if(j-1>0 && matrix[i][j-1] == 1 && visited[i][j-1] == 0){
        visited[i][j-1] = 1;
        solve(matrix, visited , i,j-1,temp+'L', ans);
        visited[i][j-1] = 0;
    }

    // RIGHT
    if(j+1<matrix[0].size() && matrix[i][j+1] == 1 && visited[i][j+1] == 0){
        visited[i][j+1] = 1;
        solve(matrix, visited , i,j+1,temp+'R', ans);
        visited[i][j+1] = 0;
    }
}



// Lc 139 word break 
bool solve(int start , int end  , string s , vector<string>& wordDict){
    auto it = find (wordDict.begin(), wordDict.end(),s);

    if(it != wordDict.end()) return true;

    for(int i = start ; i<=end ; i++){
        if(solve(start, i , s.substr(start , i ),wordDict)) return true;
    }
    return false;
}