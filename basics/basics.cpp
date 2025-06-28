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
