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



// LC 34 -Find First and Last Position of Element in Sorted Array
int firstOccurence(vector<int> &v, int n, int target) {
    int left = 0, right = n - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (v[mid] == target) {
            result = mid;
            right = mid - 1;
        }
        else if (v[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return result;
}

int lastOccurence(vector<int> &v, int n, int target) {
    int left = 0, right = n - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (v[mid] == target) {
            result = mid;
            left = mid + 1;
        }
        else if (v[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return result;
}

vector<int> searchRange(vector<int>& nums, int target) {
    int first = firstOccurence(nums, nums.size(), target);
    int last = lastOccurence(nums, nums.size(), target);
    return {first, last};   
}



// LC - 33. Search in Rotated Sorted Array
int search(std::vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (nums[mid] == target) {
            return mid;
        }

        if (nums[low] <= nums[mid]) {
            if (nums[low] <= target && target < nums[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else {
            if (nums[mid] < target && target <= nums[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }

    return -1;
}



// LC 81. Search in Rotated Sorted Array II
bool search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Found target
        if (nums[mid] == target) 
            return true;
            
        // Handle duplicates - skip duplicates from left
        if (nums[left] == nums[mid]) {
            left++;
            continue;
        }
        
        // Left half is sorted
        if (nums[left] < nums[mid]) {
            // Check if target is in the sorted left half
            if (target >= nums[left] && target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        } 
        // Right half is sorted
        else {
            // Check if target is in the sorted right half
            if (target > nums[mid] && target <= nums[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }
    
    return false;
}



// LC 1539. Kth Missing Positive Number
int findKthPositive(vector<int>& arr, int k) {
    int left = 0;
    int right = arr.size() - 1;
    
    // Special case: if k is smaller than first element
    if (k < arr[0]) return k;
    
    // Binary search
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Calculate missing numbers before arr[mid]
        int missing = arr[mid] - (mid + 1);
        
        if (missing < k) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    

    return k + right + 1;
}