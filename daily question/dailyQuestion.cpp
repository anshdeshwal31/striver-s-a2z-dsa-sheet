#include<bits/stdc++.h>
using namespace std;



//LC 386 - lexigraphical numbers

// using recursion

void dfs(int cur, int n, vector<int>& res) {
    if (cur > n) return;

    if(cur!=0)res.push_back(cur);

    cur *= 10;
    for (int i = 0; i <= 9; i++) {
        if(cur==0  && i==0)continue;
        dfs(cur + i, n, res);
    }
}

vector<int> lexicalOrder(int n) {
    vector<int> res;
    dfs(0,n,res);
    return res;
}
