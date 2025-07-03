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



// LC - 3330. Find the Original Typed String I

int possibleStringCount(string word) {
    int n = word.size();

    int count=0;
    for(int i= 1 ; i < n ; i ++){
        if(word[i]==word[i-1])count ++;
    }
    return count + 1;
}



// 2099. Find Subsequence of Length K With the Largest Sum

vector<int> maxSubsequence(vector<int>& nums, int k) {
    int n = nums.size();
    vector<pair<int, int>> indexed;

    // Pair each value with its index
    for (int i = 0; i < n; ++i) {
        indexed.push_back({nums[i], i});
    }

    // Sort descending by value
    sort(indexed.rbegin(), indexed.rend());

    // Pick top k elements (with indices)
    vector<pair<int, int>> selected(indexed.begin(), indexed.begin() + k);

    // Sort selected elements by original index to preserve order
    sort(selected.begin(), selected.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });

    // Extract values
    vector<int> result;
    for (auto& p : selected) {
        result.push_back(p.first);
    }

    return result;
}



// 1498. Number of Subsequences That Satisfy the Given Sum Condition

int numSubseq(vector<int>& nums, int target) {
    int mod = 1e9 + 7;
    int n = nums.size();
    sort(nums.begin(), nums.end());

    // Precompute powers of 2 modulo mod
    vector<int> pow2(n+1, 1);
    for (int i = 1; i <= n; ++i)
        pow2[i] = (pow2[i-1] * 2) % mod;

    int ans = 0;
    int left = 0, right = n-1;

    while (left <= right) {
        if (nums[left] + nums[right] <= target) {
            // Number of possible subsequences formed by choosing any subset of (right-left) middle elements
            ans = (ans + pow2[right - left]) % mod;
            ++left;
        } else {
            --right;
        }
    }

    return ans;
}