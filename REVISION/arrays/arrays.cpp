#include <bits/stdc++.h>
using namespace std;


// LC 1752 - check if the array is sorted and rotated 
class Solution {
    public:
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
    
    };