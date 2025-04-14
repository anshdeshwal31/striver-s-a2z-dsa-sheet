#include <bits/stdc++.h>
using namespace std;

// LC 35 - search insert position 
int searchInsert(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    
    return left; // left is the insert position
}



// floor and ceil in a sorted array
// codestudio - https://www.naukri.com/code360/problems/ceiling-in-a-sorted-array_1825401 
int findFloor(vector<int> &v, int n, int target) {
    int low = 0, high = n - 1;
    int result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (v[mid] == target) return mid;
        else if (v[mid] < target) {
            result = mid;
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return result;
}


int ceil(int x, vector<int> &arr){
    int low = 0, high = arr.size() - 1;
    int result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) return mid;
        else if (arr[mid] < x) {
            low = mid + 1;
        }
        else {
            result = mid;
            high = mid - 1;
        }
    }
    return result;
}