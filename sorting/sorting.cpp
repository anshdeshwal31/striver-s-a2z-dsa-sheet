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
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++; 
            swap(arr[i], arr[j]); 
        }
    }
    swap(arr[i + 1], arr[high]);  
    return i + 1; 
}


void solve(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  
        solve(arr, low, pi - 1);  
        solve(arr, pi + 1, high); 
    }
}
vector<int> quickSort(vector<int> arr){
    int n = arr.size();
    solve(arr, 0, n - 1);
    return arr;
}