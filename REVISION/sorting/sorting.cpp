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