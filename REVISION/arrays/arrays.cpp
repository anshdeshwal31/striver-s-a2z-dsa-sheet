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