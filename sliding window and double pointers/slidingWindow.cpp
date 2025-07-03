#include<bits/stdc++.h>
using namespace std;


// longest substring without repeating characters
bool checkRepeating(string s,int start,int end){
    unordered_set<char> st;
    for(int i=start;i<=end;i++){
        if(st.find(s[i]) != st.end()) return true;
        st.insert(s[i]);
    }
    return false;
}

int lengthOfLongestSubstring(string s) {
    if(s.size() == 0) return 0;
    int maxi = 0;
    int i=0,j=0;
    int ans = 0;

    while(j<s.size()){
        if(!checkRepeating(s,i,j)){
            ans = j-i+1;
            maxi = max(maxi,ans);
            j++;
        }
        else{
            while(checkRepeating(s,i,j)){
                i++;
            }
        }
    }
    return maxi;
}


// length of longest subarray with at most sum at most k
int maxSumSubarray(vector<int>& nums, int k) {
    int l=0,r=0;
    int sum = 0;
    int maxLen = 0;
    while(r<nums.size()){
        if(sum+ nums[r] <= k){
            sum += nums[r];
            maxLen = max(maxLen,r-l+1);
            r++;
        }
        else{
            sum -= nums[l];
            l++;
        }
    }
    return maxLen;
}


// total fruit
int totalFruit(vector<int>& fruits) {
    unordered_map<int,int> mp;
    int left = 0, right = 0, maxLen = 0;

    while(right < fruits.size()-1){
        right++;
        mp[fruits[right]]++;

        while(mp.size() > 2){
            mp[fruits[left]]--;
            if(mp[fruits[left]] == 0) mp.erase(fruits[left]);
            left++;
        }
        maxLen = max(maxLen,right-left+1);
    }
    return maxLen;
}


// longest ones
int longestOnes(vector<int>& nums, int k) {
    int l=0,r=0;
    int maxLen = 0;

    while(r<nums.size()-1){
        r++;
        if(nums[r] == 0) k--;

        while(k<0){
            if(nums[l] == 0) k++;
            l++;
        }
        maxLen = max(maxLen,r-l+1);
    }    
    return maxLen;
}


// longest repeating character replacement
int characterReplacement(string s, int k) {
    if(s.size() == 1) return 1;

    int l=0,r=1;
    int maxLen = 1;

    while(r<s.size()){
        if(s[r] != s[r-1]) k--;

        while(k<0){
            if(s[l] != s[l+1]) k++;
            l++;
        }
        maxLen = max(maxLen,r-l+1);
        r++;
    }
    return maxLen;
}

int characterReplacement(string s, int k) {
    int l=0,r=0;
    int maxLen = 0;

    while(r<s.size()){
        if(s[r] != s[l]) {
            if(k == 0){
                while(s[l] == s[l+1]) l++;
                l++;
            }
            else k--;
        }
        maxLen = max(maxLen,r-l+1);
        r++;
        {
            if(s[r] != s[l]) {
                if(k == 0){
                    while(s[l] == s[l+1]) l++;
                    l++;
                }
                else k--;
            }
            maxLen = max(maxLen,r-l+1);
            r++;
        }
    }
}



// binary subarrays with sum
int numSubarraysWithSum(vector<int>& nums, int goal) {
    int sum = 0;
    int l = 0, r = 0;
    int count = 0;

    while(r<nums.size()-1){
        if(sum == goal) count++;
        r++;
        sum += nums[r];
        while(sum >= goal){
            sum -= nums[l];
            l++;
            if(sum == goal) count++;
        }
    }
    return count;
}



// LC - 3. Longest Substring Without Repeating Characters

int lengthOfLongestSubstring(string s) {
    set<char> st;
    int n = s.size();
    int left = 0;
    int ans = 0;

    for (int right = 0; right < n; ++right) {
        // If s[right] already in set, shrink window from left until it's removed
        while (st.find(s[right]) != st.end()) {
            st.erase(s[left]);
            ++left;
        }

        st.insert(s[right]);
        ans = max(ans, right - left + 1);
    }
    return ans;
}



// LC- 1004. Max Consecutive Ones III

int longestOnes(vector<int>& nums, int k) {
        
    int right = 0;
    int left = 0;
    int ans = 0;
    for(int right = 0; right<nums.size();right++){
        while(nums[right]==0 && k<=0){
            if(nums[left]==0)k++;
            left++;
        }

        if(nums[right]==0)k--;
        ans = max(ans , right - left +1);
    }
}



//  LC  - 904. Fruit Into Baskets

 int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> count;
        int left = 0;
        int maxFruits = 0;

        for (int right = 0; right < fruits.size(); ++right) {
            count[fruits[right]]++;

            // If more than 2 types, shrink window from left
            while (count.size() > 2) {
                count[fruits[left]]--;
                if (count[fruits[left]] == 0)
                    count.erase(fruits[left]);
                ++left;
            }

            maxFruits = max(maxFruits, right - left + 1);
        }

        return maxFruits;
    }