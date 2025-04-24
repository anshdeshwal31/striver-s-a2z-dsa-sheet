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



// queue implementation using array - https://www.naukri.com/code360/problems/queue-using-array-or-singly-linked-list_2099908?leftPanelTabValue=PROBLEM
class Queue {
    public:
        int fFront ;
        int rear;
        vector<int>queueVector;

        Queue() {
            this->fFront = 0;
            this->rear = 0;
            queueVector = vector<int>(10000 , 0);
        }
    
        bool isEmpty() {
            return fFront == rear;
        }
    
        void enqueue(int data) {
            queueVector[rear++] = data; 
        }
    
        int dequeue() {
            if(fFront == rear) return -1;
            return queueVector[fFront ++ ];
        }
        
        int front() {
            if(fFront == rear) return -1;
            return queueVector[fFront];
        }

    };



    // Queue implementation using linked list - https://www.geeksforgeeks.org/problems/implement-queue-using-linked-list/1
    struct QueueNode
{
    int data;
    QueueNode *next;
    QueueNode(int a)
    {
        data = a;
        next = NULL;
    }
};

struct MyQueue {
    QueueNode *front;
    QueueNode *rear;
    void push(int);
    int pop();
    MyQueue() {front = rear = NULL;}
}; 

void  push(int x){
    if(!rear){
        rear = new QueueNode(x);
        front = rear;
        return ;
    } 
    rear->next = new QueueNode(x);
    rear = rear->next;
    return;
        // Your Code
}

//Function to pop front element from the queue.
int pop()
{
    if(!front ) return -1;
    int val = front -> data;
    front = front ->next;
    if (!front) rear = NULL;
    return val;
        // Your Code       
}


// stack implementation using linked list - https://www.geeksforgeeks.org/problems/implement-stack-using-linked-list/1

class MyStack {
    private:
        StackNode* top;
    
    public:
        MyStack() {
            top = NULL;
        }
    
        void push(int x) {
            StackNode* newNode = new StackNode(x);
            newNode->next = top;
            top = newNode;
        }
    
        int pop() {
            if (top == NULL) return -1;
            int popped = top->data;
            StackNode* temp = top;
            top = top->next;
            delete temp;
            return popped;
        }
};
    


// LC 20 - valid parenthesis
bool isValid(string s) {
    stack<char> st;
    
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '{' || s[i] == '(' || s[i] == '[') {
            st.push(s[i]);
        }
        else if (s[i] == ')') {
            if(st.empty() || st.top() != '(') {
                return false;
            }
            st.pop();
        }
        else if (s[i] == '}') {
            if(st.empty() || st.top() != '{') {
                return false;
            }
            st.pop();
        }
        else if (s[i] == ']') {
            if(st.empty() || st.top() != '[') {
                return false;
            }
            st.pop();
        }
    }
    return st.empty();
}


// LC 155 - Min Stack 

// method 1 
class MinStack {
    stack < pair < int, int >> st;
  
    public:
      void push(int x) {
        int min;
        if (st.empty()) {
          min = x;
        } else {
          min = std::min(st.top().second, x);
        }
        st.push({x,min});
      }
  
    void pop() {
      st.pop();
    }
  
    int top() {
      return st.top().first;
    }
  
    int getMin() {
      return st.top().second;
    }
  };


//   method 2 
class MinStack {
    private:
        stack<int> st;
        stack<int> minSt;
    
    public:
        MinStack() {
        }
    
        void push(int val) {
            st.push(val);
            if (minSt.empty() || val <= minSt.top()) {
                minSt.push(val);
            }
        }
    
        void pop() {
            if (st.top() == minSt.top()) {
                minSt.pop();
            }
            st.pop();
        }
    
        int top() {
            return st.top();
        }
    
        int getMin() {
            return minSt.top();
        }
};

    

// LC 496 - next greater element
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {

    stack<int> st;
    int n = nums2.size();
    unordered_map<int , int > mp;
    st.push(nums2[n-1]);
    mp[nums2[n-1]] =  -1;

    for(int i = n-2;i>=0;i--){
        int element = nums2[i];
        while(!st.empty() && st.top()<=element){
            st.pop();
        } 

        if(!st.empty()){
            mp[element] = st.top();
        }
        else{
            mp[element] = -1;
        }
        st.push(element);
    }

    vector<int>ans;
    for(int el:nums1){
        ans.push_back(mp[el]);
    }
    return ans;
}