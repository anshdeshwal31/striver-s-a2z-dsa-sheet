#include <bits/stdc++.h>
using namespace std;

double fractionalKnapsack(vector<int>& val, vector<int>& wt, int capacity) {
    map<int,int>rate;
    for(int i = 0 ; i <val.size();i++){
        int perKgPrice = val[i]/wt[i];
        rate[perKgPrice] = i;
    }

    double ans = 0;
    for(auto r:rate){
        if(!capacity) return ans;

        if(capacity>=wt[r.second]){
            ans+=val[r.first];
            capacity-=wt[r.second];
        }
        else{
            ans+=(r.first*capacity);
        }
    }

}


// LC - 678. Valid Parenthesis String
bool checkValidString(string s) {
    int low = 0, high = 0;

    for (char ch : s) {
        if (ch == '(') {
            low++;
            high++;
        } else if (ch == ')') {
            low--;
            high--;
        } else { // ch == '*'
            low--;      // if * is ')'
            high++;     // if * is '('
        }

        if (high < 0) return false; // too many ')'
        if (low < 0) low = 0;       // we can't have negative open brackets
    }

    return low == 0;
}
