#include <bits/stdc++.h>
using namespace std;

 int reverse(int x) {
    long long ans = 0 ;
    while(x>0){
        if(ans>INT_MAX || ans < INT_MIN) return 0;
        int lastDigit = x%10;
        ans*10 +lastDigit;
        x=x/10;
    }    
    return ans;
}


// count digits - https://www.geeksforgeeks.org/dsa/program-count-digits-integer-3-different-methods/


// GCD of two numbers - https://www.geeksforgeeks.org/problems/gcd-of-two-numbers3459/1

int findGcd(int a, int b) {
    while(a > 0 && b > 0) {
        if(a > b) {
            a = a % b;
        }
        else {
            b = b % a; 
        }
    }
    if(a == 0) {
        return b;
    }
    return a;
}



// check armstrong number - https://www.geeksforgeeks.org/problems/armstrong-numbers2727/1



// print all divisors - https://www.geeksforgeeks.org/problems/all-divisors-of-a-number/1


void print_divisors(int n) {
    vector<int> small, large;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            small.push_back(i);
            if (i != n / i) large.push_back(n / i);
        }
    }
    for (int d : small) cout << d << " ";
    for (int i = large.size() - 1; i >= 0; i--) cout << large[i] << " ";
    cout << endl;
}



// check prime number - https://www.geeksforgeeks.org/problems/prime-number2314/1  

bool isPrime(int n) {
    if (n <= 1) return false;
    int sqrtn = (int)sqrt(n);
    for (int i = 2; i <= sqrtn; i++) {
        if (n % i == 0) return false;
    }
    return true;
}