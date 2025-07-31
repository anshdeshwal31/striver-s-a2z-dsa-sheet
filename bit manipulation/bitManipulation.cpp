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


// Number of 1 bits - https://www.geeksforgeeks.org/problems/set-bits0143/1

    int setBits(int n) {
        int count = 0;
        while (n > 0) {
            if (n & 1) count++;  // Check if the LSB is set
            n = n >> 1;          // Shift right to check the next bit
        }
        return count;
    }


        
    int setBit(int n) {
        // Write Your Code here

        if(n&1){
            n = n>>1;
        }
        else{
            n = n|1;
        }
        
    }


    // set the rightmost unset bit - https://www.geeksforgeeks.org/problems/set-the-rightmost-unset-bit4436/1

    int setBit(int n) {
        int k = 1;
        while (1) {
            if ((k & n) == 0) {
                n = n | k;
                return n;
            }
            k = k << 1; // Left shift to move to next bit
        }
    }