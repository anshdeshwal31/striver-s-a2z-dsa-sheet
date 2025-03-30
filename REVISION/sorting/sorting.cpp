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