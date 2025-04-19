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