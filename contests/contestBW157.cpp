#include<bits/stdc++.h>
using namespace std;

    bool isPrime(int n){
        if(n<=1)return false;
        if(n==2) return true;
        if(n%2==0) return false;
        for(int i = 3;i<n;i+=2){
            if(n%i==0) return false;
        }
        return true;
    }
    
    long long sumOfLargestPrimes(string s) {
        int n = s.size();
        set<int>minHeap;
        for(int i = 0; i <n ; i ++){
            for(int j = n-1 ; j>=i ; j--){
                int num = stoi(s.substr(i,j-i+1));   
                if(isPrime(num)){
                    // cout<< num<<endl;
                    if(minHeap.size()<3 && minHeap.find(num)==minHeap.end()){
                        minHeap.insert(num);
                    }
                    else{
                        if(*minHeap.begin()<num && minHeap.find(num)==minHeap.end()){
                            minHeap.erase(*minHeap.begin());
                            minHeap.insert(num);
                        }
                    }
                }
            }
        }
        int sum = 0;
        // cout<<"first value in the minHeap "<<*minHeap.begin();
        while(!minHeap.empty()){
            // cout<<"wassup"<<endl;
            // cout<<*minHeap.begin();
            sum+=(*minHeap.begin());
            minHeap.erase(*minHeap.begin());
        }
        return sum;
    }