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

// using iteration

vector<int> lexicalOrder(int n) {
    vector<int> res;
    int currNum = 1;

    for (int i = 0; i < n; i++) {
        res.push_back(currNum);

        if (currNum * 10 <= n) {
            currNum *= 10;
        } else {
            while (currNum % 10 == 9 || currNum >= n) {
                currNum /= 10;
            }
            currNum += 1;
        }
    }

    return res;
}



// LC 440 -  K-th Smallest in Lexicographical Order

// // using recursion 
// int dfs(int cur, int n , int& k ){
//     if(cur>n)return 0;
//     if(cur!=0)k--;
//     if(k==0) return cur;

//     int ans;
//     for(int i = 0; i <=9; i++){
//         if(cur==0  && i==0)continue;
//         ans = max(ans,dfs(cur*10+i,n,k));
//     }
//     return ans;
// }


// int findKthNumber(int n, int k) {
//     int ans;
//     return dfs(0,n,k);
// }

int findKthNumber(int n, int k) {
    int currNum = 1;
    k--; // starting from 1, so first number is 1st lex num

    while (k > 0) {
        long steps = 0, first = currNum, last = currNum;
        
        // count number of numbers in the lex range [first, last] <= n
        while (first <= n) {
            steps += min((long)n, last) - first + 1;
            first *= 10;
            last = last * 10 + 9;
        }

        if (steps <= k) {
            currNum++;  // move to next sibling
            k -= steps;
        } else {
            currNum *= 10; // move to first child
            k--;
        }
    }

    return currNum;
}