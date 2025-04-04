#include <bits/stdc++.h>
using namespace std;


// LC 1752 - check if the array is sorted and rotated 
bool check(vector<int>& nums) {
    int count = 0;
    int n = nums.size();

    for(int i=1; i<n; i++) {  // when the array both sorted and rotated
        if(nums[i-1] > nums[i]) {
            count++;
        }
    }

    if(nums[n-1] > nums[0]) { // when the array is sorted and not rotated
        count++;
    }

    return count <= 1;
}


// LC 26 - remove duplicates from sorted array 
int removeDuplicates(vector<int>& nums) {
    int n = nums.size();
    
    if (n <= 1) return n;
    
    int j = 1; 
    
    for(int i = 1; i < n; i++) {
        if(nums[i] != nums[i-1]) {
            nums[j++] = nums[i]; 
        }
    }
    
    return j; 
}



// LC 169 majority element 

// using boyer moore voting algo 
int majorityElement(vector<int>& nums) {
    int candidate = nums[0];
    int count = 1;
    
    for(int i = 1; i < nums.size(); i++) {
        if(count == 0) {
            candidate = nums[i];
            count = 1;
        }
        else if(nums[i] == candidate) {
            count++;
        }
        else {
            count--;
        }
    }
    
    return candidate;
}


// LC 53 - Maximum subarray 
// kadane's algo 

int maxSubArray(vector<int>& nums) {
    int sum = 0;
    int maxSum = INT_MIN;
    for(int i = 0; i<nums.size(); i++){
        maxSum = max(sum , maxSum);
        if(sum<0) sum = nums[i];
        else sum+=nums[i];
    }
    return max(sum , maxSum);
}



// longest subarray with sum k 
// https://practice.geeksforgeeks.org/problems/longest-sub-array-with-sum-k0809/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=longest-sub-array-with-sum-k

int getLongestSubarray(vector<int>& a, int k) {
    int n = a.size();

    map<int, int> preSumMap;
    int sum = 0;
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];

        if (sum == k) {
            maxLen = max(maxLen, i + 1);
        }

        // calculate the sum of remaining part i.e. x-k:
        int rem = sum - k;

        //Calculate the length and update maxLen:
        if (preSumMap.find(rem) != preSumMap.end()) {
            int len = i - preSumMap[rem];
            maxLen = max(maxLen, len);
        }

        if (preSumMap.find(sum) == preSumMap.end()) {
            preSumMap[sum] = i;
        }
    }

    return maxLen;
}
