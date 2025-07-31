#include <bits/stdc++.h>
using namespace std;


// check k-th bit - https://www.geeksforgeeks.org/problems/check-whether-k-th-bit-is-set-or-not-1587115620/1

bool checkKthBit(int n, int k) {
    int temp = 1;
    temp<<k;

    if(n&temp) return true;
    else return false;
}



// check odd or even - https://www.geeksforgeeks.org/problems/odd-or-even3618/1

bool isEven(int n) {
    if(n&1) return false;
    else return true;
}



// LC - 231 - power of two 

bool isPowerOfTwo(int n) {
        if (n <= 0) return false;
        return (n & (n - 1)) == 0;
}