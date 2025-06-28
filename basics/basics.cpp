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