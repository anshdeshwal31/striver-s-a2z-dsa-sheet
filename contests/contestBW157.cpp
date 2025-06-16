#include<bits/stdc++.h>
using namespace std;


//  LC - 3556
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


// LC - 3557



int maxSubstrings(string word) {
    if(word.size()<4)return 0;

    int count = 0;
    for (int len = 4; len<=word.size(); len++){
        int i = 0;
        while(i+len<=word.size()){
            if(word.substr(i,len)[0] == word.substr(i,len)[len-1]){
                word.erase(i,len);
                count++;
                i += len;
            }
            else{
                i++;
            }
        }
    }
    return count;
}



int solve(vector<int>&prices,int i , bool Buy ,bool Sell,int& k , int transactions){
    if(transactions==k) return 0;
    if(i==prices.size()-1){
        if(Buy){
            return prices[i];
        }
        if(Sell) return -prices[i];
    }

    int sumBuy = -prices[i]+solve(prices,i+1,1,0,k,transactions+1);
    int sumSell = prices[i]+solve(prices,i+1,0,1,k,transactions);
    int sumNothing = solve(prices,i+1,0,0,k,transactions);

    return max(sumBuy,max(sumSell,sumNothing));
}