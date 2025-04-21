#include <bits/stdc++.h>
using namespace std;


// LC 8 - string to integer 

// recursive solution 
void solve(int i, string s, string& temp) {
    if (i == s.length()) return;

    if (temp == "" && s[i] == ' ') {
        solve(i + 1, s, temp);
        return;
    }

    // Add optional '+' or '-' sign only once
    if (temp == "" && (s[i] == '+' || s[i] == '-')) {
        temp += s[i];
        solve(i + 1, s, temp);
        return;
    }

    if (s[i] >= '0' && s[i] <= '9') {
        temp += s[i];
        solve(i + 1, s, temp);
        return;
    }

    return;
}

int myAtoi(string s) {
    string temp = "";
    solve(0, s, temp);

    if (temp == "" || temp == "+" || temp == "-") return 0;

    try {
        return stoi(temp);
    } catch (...) {
        return (temp[0] == '-') ? INT_MIN : INT_MAX;
    }
}


// iterative solution
int myAtoi(string s) {
    int i = 0, n = s.length();
    while (i < n && s[i] == ' ') i++;  // Skip leading spaces

    int sign = 1;
    if (i < n && (s[i] == '+' || s[i] == '-')) {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }

    long result = 0;
    while (i < n && isdigit(s[i])) {
        result = result * 10 + (s[i] - '0');

        // Clamp to INT range
        if (sign == 1 && result > INT_MAX) return INT_MAX;
        if (sign == -1 && -result < INT_MIN) return INT_MIN;

        i++;
    }

    return sign * result;
}



// LC 22 - generate parenthesis
void backtrack(int open, int close, int n, string current, vector<string>& result) {
    if (current.length() == 2 * n) {
        result.push_back(current);
        return;
    }

    if (open < n) {
        backtrack(open + 1, close, n, current + '(', result);
    }

    if (close < open) {
        backtrack(open, close + 1, n, current + ')', result);
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> result;
    backtrack(0, 0, n, "", result);
    return result;
}


// LC 39 - combination sum 
void solve(int i , vector<int>&candidates , int target , vector<int>temp, vector<vector<int>>& ans){
    if(target<0)return;
    if(target==0){
        ans.push_back(temp);
        return;
    }
    if(i==candidates.size()) return;

    solve(i+1 , candidates, target , temp , ans);
    temp.push_back(candidates[i]);
    solve(i,candidates , target-candidates[i] , temp , ans);
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> ans;
    vector<int> temp;
    solve(0 , candidates , target , temp , ans);
    return ans;
}



// LC 216 - combination sum 3
void solve(int i , int k , int n  , vector<vector<int>>& ans , vector<int> temp){
    if(k==0){
        if(n==0){
            ans.push_back(temp);
            return;
        }
        return;
    }

    for(int j = i ; j <= 9 ; j ++){
        temp.push_back(j);
        solve(j+1 , k-1 , n-j , ans , temp);
        temp.pop_back();
    }
}

vector<vector<int>> combinationSum3(int k, int n) {
    vector<vector<int>> ans;
    vector<int> temp;
    solve(1 , k , n , ans , temp);
    return ans;
}