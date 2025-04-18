#include <bits/stdc++.h>
using namespace std;

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