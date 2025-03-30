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



