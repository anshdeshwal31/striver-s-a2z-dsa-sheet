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