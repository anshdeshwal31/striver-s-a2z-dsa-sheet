#include <bits/stdc++.h>
using namespace std;


// stack implementation using array - https://www.naukri.com/code360/problems/stack-implementation-using-array_3210209?leftPanelTabValue=PROBLEM
class Stack {
    
    public:
        int stackTop;
        vector<int> stackVector;
        Stack(int capacity) {
            stackVector = vector<int> (capacity,0);
            this->stackTop = 0;
        }
    
        void push(int num) {
            if(stackTop == stackVector.size()) return ;

            stackVector[stackTop++] = num;
            return;
        }
    
        int pop() {
            if(stackTop == 0) return -1;
            return stackVector[stackTop--];
        }
        
        int top() {
            if(stackTop==0) return -1;
            return stackVector[stackTop-1];
        }
        
        int isEmpty() {
            return stackTop == 0;
        }
        
        int isFull() {
            return stackTop == stackVector.size();
        }
        
};