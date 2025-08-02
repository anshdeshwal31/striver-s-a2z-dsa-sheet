#include <bits/stdc++.h>
using namespace std;


// selection sort
void selectionSort(vector<int>& arr, int n){

    for(int i = n-1; i>=1;i--){
        int maxi = i;
        for(int j =i ; j>=0;j--){
            if(arr[j] > arr[maxi]){
                maxi = j;
            }
        }
        swap(arr[i],arr[maxi]);
    }
}


// bubble sort
void bubbleSort(vector<int>& arr, int n){
    for(int i = n-1 ; i>=1;i--){
        for(int j = 0;j<=i-1;j--){
            if(arr[j] > arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }

}


// insertion sort
void insertionSort(vector<int>& arr, int n){
    for(int i = 1;i<n;i++){
        int key = arr[i];
        int j = i-1;
        while(j>=0 && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}


// merge sort
void mergeSortedArray(std::vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
        
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int p = 0; p < k; p++) arr[left + p] = temp[p];
}

void solve(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        solve(arr, left, mid);
        solve(arr, mid + 1, right);
        mergeSortedArray(arr, left, mid, right);
    }
}

void mergeSort(vector<int>& arr,int n ) {
    solve(arr, 0, arr.size() - 1);
} 


// quick sort
int partition(vector<int> &arr, int start, int end) {
    int pivot = arr[start];
    int lessCount = 0;

    for(int i=start+1; i<=end; i++) {
        if(arr[i] <= pivot) {
            lessCount++;
        }
    }

    int pivotIndex = start + lessCount;
    swap(arr[start], arr[pivotIndex]);

    int i = start;
    int j = end;

    while(i<pivotIndex && j>pivotIndex) {
        while(arr[i] <= pivot) {
            i++;
        }

        while(arr[j] > pivot) {
            j--;
        }

        if(i<pivotIndex && j>pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    } 

    return pivotIndex;
}

void quickSort(vector<int> &arr, int start, int end) {
    if(start >= end) {
        return;
    }

    int p = partition(arr, start, end);

    quickSort(arr, start, p-1);
    quickSort(arr, p+1, end);
}
