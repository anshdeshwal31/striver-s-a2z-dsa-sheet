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




// LC - 424. Longest Repeating Character Replacement

int characterReplacement(string s, int k) {
        int n = s.size();
        int left = 0, maxCount = 0, ans = 0;
        vector<int> count(26, 0);

        for (int right = 0; right < n; ++right) {
            count[s[right] - 'A']++;
            maxCount = max(maxCount, count[s[right] - 'A']);

            // If window has more than k chars to replace, shrink from left
            while (right - left + 1 - maxCount > k) {
                count[s[left] - 'A']--;
                ++left;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }



// LC - 930. Binary Subarrays With Sum

int numSubarraysWithSum(vector<int>& nums, int goal) {
    unordered_map<int, int> mp;
    mp[0] = 1; // prefix sum 0 appears once initially
    int sum = 0;
    int count = 0;

    for (int right = 0; right < nums.size(); right++) {
        sum += nums[right];

        if (mp.count(sum - goal))
            count += mp[sum - goal];

        mp[sum]++;
    }

    return count;
}



// LC - 1248. Count Number of Nice Subarrays

    // using prefix sum
    int numberOfSubarrays(vector<int>& nums, int k) {
        unordered_map<int, int> countMap;
        countMap[0] = 1; // base case
        int oddCount = 0, result = 0;

        for (int num : nums) {
            if (num % 2 != 0) oddCount++;

            if (countMap.count(oddCount - k))
                result += countMap[oddCount - k];

            countMap[oddCount]++;
        }

        return result;
    }


    // using two-pointers and sliding window

    int atMost(vector<int>& nums, int k) {
        int left = 0, res = 0;
        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] % 2 != 0) k--;

            while (k < 0) {
                if (nums[left] % 2 != 0) k++;
                left++;
            }

            res += right - left + 1;
        }
        return res;
    }

    int numberOfSubarrays(vector<int>& nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);
    }


    
// LC - 1358. Number of Substrings Containing All Three Characters

int numberOfSubstrings(string s) {
        int n = s.size();
        int count = 0;
        int left = 0;
        unordered_map<char, int> freq;

        for (int right = 0; right < n; ++right) {
            freq[s[right]]++;

            // When all three characters are present in the window
            while (freq['a'] > 0 && freq['b'] > 0 && freq['c'] > 0) {
                // Add all substrings starting from left to n-1
                count += n - right;
                freq[s[left]]--;
                left++;
            }
        }
        return count;
    }




    // LC - 1423. Maximum Points You Can Obtain from Cards 

    int maxScore(vector<int>& cardPoints, int k) {

        int right = 0;
        int n = cardPoints.size();
        if(k==n) return accumulate(cardPoints.begin(),cardPoints.end(),0);
        int minSum= INT_MAX;
        int sum = 0;
        int left = 0;
        
        for(right =0 ; right < n; right ++){
            sum+=cardPoints[right];
            if(right>=n-k-1){
                minSum = min(sum , minSum);
                sum-=cardPoints[left++];
            }
        }
        return accumulate(cardPoints.begin(),cardPoints.end(),0) - minSum;
    }


    
    
    //  Longest Substring with At Most K Distinct Characters - https://www.naukri.com/code360/problems/distinct-characters_2221410

int kDistinctChars(int k, string &str){
    int n  = str.size();
    int left = 0; 
    int right = 0;
    unordered_map<char,int>mp;
    int ans = 0;

    for(int right = 0 ; right<n; right++){
        mp[str[right]]++;
        while(mp.size()>k){
            mp[str[left]]--;
            if(mp[str[left]]==0) mp.erase(str[left]);
            left++;
        }
        ans = max(ans,right-left+1);
        // cout<<ans<<" "<<endl;
    }
    return ans;
}

