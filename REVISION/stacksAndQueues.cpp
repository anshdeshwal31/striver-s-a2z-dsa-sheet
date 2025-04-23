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