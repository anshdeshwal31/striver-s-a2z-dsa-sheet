#include <bits/stdc++.h>
using namespace std;


// LC 796 - rotate string 

// brute force
bool rotateString(string s, string goal) {
    if (s.size() != goal.size()) return false;
    if (s.empty() && goal.empty()) return true;
    
    for (int i = 0; i < s.size(); i++) {
        string temp = "";
        for (int j = 0; j < s.size(); j++) {
            temp.push_back(s[(j+i) % s.size()]);
        }
        if (temp == goal) return true;
    }
    return false;
}


// optimal
bool rotateString(string s, string goal) {
    return s.size() == goal.size() && (s + s).find(goal);
}



// LC 5 - longest palindromic substring
string longestPalindrome(string s) {
    int n = s.length();
    if (n == 0) return "";

    int start = 0, maxLen = 1;

    for (int center = 0; center < n; ++center) {
        // Odd length palindrome
        int l = center, r = center;
        while (l >= 0 && r < n && s[l] == s[r]) {
            if (r - l + 1 > maxLen) {
                start = l;
                maxLen = r - l + 1;
            }
            l--; r++;
        }

        // Even length palindrome
        l = center, r = center + 1;
        while (l >= 0 && r < n && s[l] == s[r]) {
            if (r - l + 1 > maxLen) {
                start = l;
                maxLen = r - l + 1;
            }
            l--; r++;
        }
    }

    return s.substr(start, maxLen);
}