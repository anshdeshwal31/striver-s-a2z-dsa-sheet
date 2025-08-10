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



    // find XOR of numbers from L to R -  https://www.geeksforgeeks.org/problems/find-xor-of-numbers-from-l-to-r/1
    
    int xorTill(int n) {
        if (n % 4 == 0) return n;
        else if (n % 4 == 1) return 1;
        else if (n % 4 == 2) return n + 1;
        else return 0;
    }

    int findXOR(int l, int r) {
        return xorTill(r) ^ xorTill(l - 1);
    }



    // LC - 260. Single Number III
    
    vector<int> singleNumber3(vector<int>& nums) {
        int xorAll = 0;
        
        // Step 1: XOR of all elements gives a ^ b
        for (int n : nums) {
            xorAll ^= n;
        }

        // Step 2: Find a set bit in xorAll (rightmost set bit)
        int diff_bit = 1;
        while ((xorAll & diff_bit) == 0) {
            diff_bit <<= 1;
        }

        // Step 3: Divide elements into two groups based on that bit
        int a = 0, b = 0;
        for (int n : nums) {
            if (n & diff_bit)
                a ^= n;
            else
                b ^= n;
        }

        return {a, b};
    }



    // print all prime factors of a number 

    vector<int> primeFac(int n) {
        vector<int> res;

        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                res.push_back(i);  // Unique prime factor found
                while (n % i == 0) {
                    n /= i;  // Remove all multiples of i from n
                }
            }
        }

        if (n > 1) {
            res.push_back(n);  // Remaining n is a prime factor
        }

        return res;
    }/



    // print all divisors of a number

    void print_divisors(int n) {
        vector<int> smallDivisors;
        vector<int> largeDivisors;

        for (int i = 1; i * i <= n; ++i) {
            if (n % i == 0) {
                smallDivisors.push_back(i);
                if (i != n / i) {
                    largeDivisors.push_back(n / i);
                }
            }
        }

        // Print smaller divisors (in ascending order)
        for (int d : smallDivisors) {
            cout << d << " ";
        }

        // Print larger divisors (in reverse order for ascending output)
        reverse(largeDivisors.begin(), largeDivisors.end());
        for (int d : largeDivisors) {
            cout << d << " ";
        }

        // cout << endl;
    }



    // LC 204 - count primes

int countPrimes(int n) {
    if (n <= 2) return 0; // No primes less than 2
    
    vector<bool> isPrime(n, true);
    isPrime[0] = isPrime[1] = false; // 0 and 1 are not prime
    
    for (int i = 2; i * i < n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    return count(isPrime.begin(), isPrime.end(), true);
}



// prime factorization of a number - https://takeuforward.org/plus/dsa/problems/prime-factorisation-of-a-number

vector<int> getPrimeFactors(int num, vector<int>& spf) {
    vector<int> factors;
    while (num > 1) {
        factors.push_back(spf[num]);
        num /= spf[num];
    }
    return factors;
}

vector<vector<int>> primeFactorization(vector<int>& queries) {
    int maxVal = *max_element(queries.begin(), queries.end());
    
    // Step 1: Precompute smallest prime factors (spf)
    vector<int> spf(maxVal + 1);
    for (int i = 0; i <= maxVal; i++) spf[i] = i;
    
    for (int i = 2; i * i <= maxVal; i++) {
        if (spf[i] == i) { // i is prime
            for (int j = i * i; j <= maxVal; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
    
    // Step 2: Get factors for each query
    vector<vector<int>> result;
    for (int q : queries) {
        result.push_back(getPrimeFactors(q, spf));
    }
    return result;
}




// LC - 50. Pow(x, n)

double myPow(double x, int n) {
    long long N = n; // use long long to handle INT_MIN
    if (N < 0) {
        x = 1 / x;
        N = -N;
    }
    
    double result = 1.0;
    while (N > 0) {
        if (N % 2 == 1) { // if odd
            result *= x;
        }
        x *= x;
        N /= 2;
    }
    return result;
}