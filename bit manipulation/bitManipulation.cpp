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



    // swap two numbers 

    // method 1 - https://www.geeksforgeeks.org/problems/swap-two-numbers3844/1
    pair<int, int> get(int a, int b) {
        a = a + b;
        b = a - b;
        a = a - b;
        return {a, b};
    }
    
    // method 2
    pair<int, int> get(int a, int b) {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
        return {a, b};
    }



    // LC - 29. Divide Two Integers
    
    int divide(int dividend, int divisor) {
    // Handle overflow
    if (dividend == INT_MIN && divisor == -1)
        return INT_MAX;

    // Determine the sign
    bool negative = (dividend < 0) ^ (divisor < 0);

    // Convert both numbers to long long and work with positives
    long long a = abs((long long)dividend);
    long long b = abs((long long)divisor);
    long long result = 0;

    // Subtract divisor multiples using bit shifts
    while (a >= b) {
        long long temp = b, multiple = 1;
        while ((temp << 1) <= a) {
            temp <<= 1;
            multiple <<= 1;
        }
        a -= temp;
        result += multiple;
    }

    return negative ? -result : result;
    }



    // 2220. Minimum Bit Flips to Convert Number
    int minBitFlips(int start, int goal) {
        int xored = start ^ goal;
        int count = 0;
        while (xored) {
            count += xored & 1;
            xored >>= 1;
        }
        return count;
    }



    // LC - 136. Single Number

    int singleNumber(vector<int>& nums) {
        int result = 0;
        for(int i = 0 ; i < nums.size();i++){
            result^=nums[i];
        }
        return result ;
    }



    // LC 78 - subsets

    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int total = 1 << n;  // 2^n subsets
        vector<vector<int>> result;

        for (int mask = 0; mask < total; ++mask) {
            vector<int> subset;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    subset.push_back(nums[i]);
                }
            }
            result.push_back(subset);
        }

        return result;
    }