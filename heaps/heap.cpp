#include<bits/stdc++.h>
using namespace std;

  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };

//  codestudio : build min heap 
void heapify(vector<int>& arr, int n, int i) {
    int leftChildIndex = 2 * i + 1;
    int rightChildIndex = 2 * i + 2;
    int largest = i;

    // Check if left child exists and is greater than the root
    if (leftChildIndex < n && arr[leftChildIndex] > arr[largest]) {
        largest = leftChildIndex;
    }

    // Check if right child exists and is greater than the largest so far
    if (rightChildIndex < n && arr[rightChildIndex] > arr[largest]) {
        largest = rightChildIndex;
    }

    // If the largest is not the root, swap and continue heapifying
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

vector<int> buildHeap(vector<int> arr, int n){
    for (int i= n/2-1; i>=0;i--){
        heapify(arr, n , i);
    }
    return arr;
}



// check if the array represents max heap
bool solve(int arr[] , int n , int i ){
    if(i>=n/2) return true;

    int leftChildIndex = 2 * i + 1;
    int rightChildIndex = 2 * i + 2;

    if(rightChildIndex<n){
        return arr[i]>arr[leftChildIndex] && arr[i]>arr[rightChildIndex];
    }
    else{
        if(leftChildIndex<n){
            return arr[i]>arr[leftChildIndex];
        }
        else{
            return true;
        }
    }
}
bool isMaxHeap(int arr[], int n){
    for (int i = n/2-1; i >=0; i--){
        if (!solve(arr , n , i )){
            return false;
        }
    }
    return true;
}




// LC 215

int findKthLargest(vector<int>& nums, int k) {
    priority_queue<vector<int>,greater<int>> pq;
    for (int   i = 0;   i< k;i  ++){
        pq.push(nums[i]);
    }

    for(int i = k ; i<nums.size();i++){
        if(nums[i]>pq.top()) {
            pq.push(nums[i]);
        }  
    }

    return pq.top();
}



// LC 23
struct CompareNodes {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    int k  = lists.size();
    priority_queue<ListNode*,vector<ListNode*>,CompareNodes> pq;
    for (int  i = 0; i < k; i++){
        pq.push(lists[i]);
    }
    
    ListNode*  ansListHead = new ListNode(-1);
    ListNode* tempNode = new ListNode();
    ansListHead->next = tempNode;
    while(!pq.empty()){
        ListNode* temp = pq.top();
        int tempVal = temp->val;

        tempNode->val = temp->val;
        tempNode->next = new ListNode(tempVal);
        tempNode = tempNode->next;
        
        if(temp->next) pq.push(temp->next);
    }

    ListNode* newHead = ansListHead->next;
    ansListHead->next = nullptr;
    delete  ansListHead;
    
    return newHead;
}



// LC 846 
bool isNStraightHand(vector<int>& hand, int groupSize) {
    priority_queue<greater<int>, vector<int>> pq;
    for(int& card:hand) pq.push(card);

    while(!pq.empty()){
        int top = -1;
        int count = groupSize;
        while(count--){
            if(top == -1 && )
        }
        
    }
}


