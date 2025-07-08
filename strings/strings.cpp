#include <bits/stdc++.h>
using namespace std;


// reverse words in string
string reverseWords(string s) {
    string ans = "";
    string temp = "";
    for(int i = s.size()-1; i >= 0; i--) {
        if(s[i] != ' ') {
            temp += s[i];
            if(i == 0) {
                if(temp.size() > 0) {
                    reverse(temp.begin(), temp.end());
                    ans += temp;
                    temp = "";
                }
            }
        }
        else{
            if(temp.size() > 0) {
                reverse(temp.begin(), temp.end());
                if(i==0) {
                    ans += temp;
                }
                else{
                    ans += temp + " ";
                    temp = "";
                }
            }
        }
    }
    return ans;
}



// LC 1781


// wrong code 
class Solution {
public:
    int beautySum(string s) {
        int n = s.length();
        int sum = 0;
        
        for(int i = 0; i < n; i++) {
            vector<int> freq(26, 0);
            int maxFreq = 0; 
            int minFreq = INT_MAX; 
            for(int j = i; j < n; j++) {
                freq[s[j] - 'a']++;
                
                maxFreq = max(maxFreq,freq[s[j] - 'a']);
                minFreq = min(minFreq,freq[s[j] - 'a']);

                sum += (maxFreq - minFreq);
            }
        }
        return sum;
    }
};



// LC 1781
class Solution {
public:
    int beautySum(string s) {
        int n = s.length();
        int sum = 0;
        
        for(int i = 0; i < n; i++) {
            vector<int> freq(26, 0);
            for(int j = i; j < n; j++) {
                freq[s[j] - 'a']++;
                
                // Find max frequency directly
                int maxFreq = 0;
                int minFreq = INT_MAX;
                for(int f : freq) {
                    maxFreq = max(maxFreq, f);
                    if(f>0)minFreq = min(minFreq, f);
                }
                
                sum += (maxFreq - minFreq);
            }
        }
        return sum;
    }
};




// LC - 921. Minimum Add to Make Parentheses Valid

// O(n) space complexity 

int minAddToMakeValid(string s) {
    stack<char>st;
    for(int i = 0 ; i < s.size(); i ++){
        if(s[i]=='('){
            st.push(s[i]);
        }
        else{
            if(!st.empty() && st.top()=='(') st.pop();
            else st.push(')');
        }
    }
    return st.size();
}

// O(1) space complexity

int minAddToMakeValid(string s) {
    int open = 0;  // number of unmatched '('
    int moves = 0; // number of insertions needed

    for (char c : s) {
        if (c == '(') {
            open++;  // one more '(' to match later
        } else { // c == ')'
            if (open > 0) {
                open--;  // matched with an earlier '('
            } else {
                moves++; // no '(' available, so need one '(' insertion
            }
        }
    }

    moves += open; // any remaining '(' need closing ')'

    return moves;
}