#include <bits/stdc++.h>
using namespace std;


// insertion sort 
void insertionSort(vector<int>& arr) {
    // code here
    int n = arr.size();
    for (int i = 0; i <= n - 1; i++) {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            int temp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = temp;
            j--;
        }
    }
} 



// merge sort
void merge(vector<int>& arr , int mid){
    vector<int>v1;
    vector<int>v2;

    for(int i = 0 ; i<=mid;i++)v1.push_back(arr[i]);
    for(int i = mid+1 ; i<arr.size() ; i++)v2.push_back(arr[i]);

    int i =0 , j=0 , k =0;
    while(i<v1.size() && j<v2.size()){
        if(v1[i] < v2[j]) arr[k++] = v1[i++];
        else arr[k++] = v2[j++];
    }

    while(i<v1.size()) arr[k++] = v1[i++];
    while(j<v2.size()) arr[k++] = v2[j++];
    
}

void mergeSort(vector<int>& arr , int l , int r){
    if(l>=r) return;

    int mid = (l+r)/2;

    mergeSort(arr , l , mid);
    mergeSort(arr , mid+1 , r);

    merge(arr , mid);
}


// quick sort 

int partition(vector<int> &arr, int start, int end) {
    int pivot = arr[start];
    int lessCount = 0;

    for(int i=start+1; i<=end; i++) {
        if(arr[i] <= pivot) lessCount++;
    }

    int pivotIndex = start + lessCount;
    swap(arr[start], arr[pivotIndex]);

    int i = start;
    int j = end;

    while(i<pivotIndex && j>pivotIndex) {
        while(arr[i] <= pivot) i++;
        while(arr[j] > pivot)  j--;

        if(i<pivotIndex && j>pivotIndex) swap(arr[i++], arr[j--]);
    } 

    return pivotIndex;
}

void quickSort(vector<int> &arr, int start, int end) {
    if(start >= end)return;

    int p = partition(arr, start, end);

    quickSort(arr, start, p-1);
    quickSort(arr, p+1, end);
}



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
