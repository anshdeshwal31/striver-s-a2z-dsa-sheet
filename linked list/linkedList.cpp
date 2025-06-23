#include <bits/stdc++.h>  
using namespace std;


class ListNode{
    public:
        int val;
        ListNode* next;

    ListNode(int x){
        this->next = NULL;
        this->val = x;
    }
};

class ListNode{
    public:
        int val;
        ListNode* next;
        ListNode* prev;

    ListNode(int x){
        this->next = NULL;
        this->prev = NULL;
        this->val = x;
    }
};

ListNode* oddEvenList(ListNode* head) {
    ListNode* tempOdd = head;
    ListNode* tempEven = head->next;
    ListNode* evenHead = tempEven;

    while(tempOdd && tempEven){
        tempEven->next = tempEven->next->next;
        tempOdd->next = tempOdd->next->next;

        tempEven = tempEven->next;
        tempOdd = tempOdd->next;
    }

    tempOdd->next = evenHead;
    return head;
}

ListNode* oddEvenList(ListNode* head) {
    if (!head || !head->next) return head; // Handle edge cases
    
    ListNode* tempOdd = head;
    ListNode* tempEven = head->next;
    ListNode* evenHead = tempEven;  // Save the starting point of the even list
    
    while (tempEven && tempEven->next) {
        tempOdd->next = tempOdd->next->next;
        tempOdd = tempOdd->next;
        
        tempEven->next = tempEven->next->next;
        tempEven = tempEven->next;
    }
    
    tempOdd->next = evenHead;  // Connect odd list with even list
    return head;
}


// Insertion in a doubly linked list
Node* insert(int k, int val, Node *head) {
    if(!head) return new Node(val);
    if(k == 0){
        Node* newNode = new Node(val);
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        return head;
    }

    Node* temp = head;
    int count = 0;
    while(count < k){
        temp = temp->next;
        count++;
    }

    Node* newNode = new Node(val);
    newNode->next = temp->next;
    newNode->prev = temp;
    if(temp->next != NULL) temp->next->prev = newNode;
    temp->next = newNode;
}


// deletion in a doubly linked list
void deleteNode(Node* &head, int pos) {
    if(!head) return;
    if(!head->next && pos == 0){
        delete head;
        head = NULL;
    }

    if(pos == 0){
        Node* toDelete = head;
        head = head->next;
        head->prev = NULL;
        toDelete->next = NULL;
        delete toDelete;
    }
    int count = 0;
    Node* temp = head;
    while(count < pos-1 && temp){
        temp = temp->next;
        count++;
    }
    Node* toDelete = temp->next;    
    temp -> next = temp->next->next;
    if(temp->next != NULL) temp->next->prev = temp;
    toDelete->next = NULL;
    toDelete->prev = NULL;
    delete toDelete;
}



// reverse a doubly linked list
void solve(DLLNode* temp){
    if(!temp->next){
        DLLNode* prev = temp->prev;
        temp->next = prev;
        temp->prev = NULL;
        return;
    }

    DLLNode* prev = temp->prev;
    temp->prev = solve(temp->next);
    temp->next = prev;
}
DLLNode* reverseDLL(DLLNode* head) {
    if(!head) return NULL;
    DLLNode* temp = head;
    while(temp->next){
        temp = temp->next;
    }
    solve(head);
    return temp;
}



// middle of a linked list

ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}



// reverse a linked list

// iterative solution
ListNode* reverseList(ListNode* head) {
    if(!head) return NULL;
    if(!head->next) return head;

    ListNode* prev = NULL;
    ListNode* curr = head;
    ListNode* next = head->next;
    while(curr){
        curr->next = prev;
        prev = curr;
        curr = next;
        if(next) next = next->next;
    }
    return prev;
}

// recursive solution
void solve(ListNode* prev , ListNode* curr ){
    if(!curr) return;
    solve(curr,curr->next);
    curr->next = prev;
}
ListNode* reverseList(ListNode* head) {
    if(!head) return NULL;
    if(!head->next) return head;

    ListNode* temp = head;
    while(temp->next){
        temp = temp->next;
    }
    solve(NULL,head);
    head = temp;
    return head;
}


// linked list cycle
bool hasCycle(ListNode *head) {
    if(!head) return false;
    ListNode* slow = head;
    ListNode* fast = head;

    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) return true;
    }
    return false;
}


// linked list cycle II

ListNode* detectCycle(ListNode* head) {
    if(!head) return nullptr;
    ListNode* slow = head;
    ListNode* fast = head;

    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) break;
    }

    if(slow!=fast) return nullptr;

    slow = head;
    while(true){
        slow = slow->next;
        fast = fast->next;
        if(slow==fast) return slow;
    }
    return nullptr;
}


// find the length of the loop in a linked list
int countNodesinLoop(Node *head) {
    Node* slow = head;
    Node* fast = head;

    // Phase 1: Detect if there is a cycle
    while (fast && fast->next) {
        slow = slow->next;          
        fast = fast->next->next;    
        if (slow == fast) break;     // Cycle detected
    }

    if (slow != fast) return 0;     // No cycle found

    // Phase 2: Count the number of nodes in the cycle
    int count = 1;
    Node *temp = slow;
    while(temp->next != slow){
        count++;
        temp = temp->next;
    }
    return count;
}



// 328
ListNode* oddEvenList(ListNode* head) {
        if(!head || !head->next)return head;

        ListNode* evenHead = head->next;
        ListNode* temp1 = head;
        ListNode* temp2 = head->next;   

        while(temp2&&temp2->next){
            temp1->next = temp2->next;
            temp1 = temp1->next;
            temp2->next =  temp2->next->next;
            temp2  = temp2->next;
        }
        temp1->next = evenHead;

        return head;
}


// LC 19
ListNode* removeNthFromEnd(ListNode* head, int n) {
    int len = 0;
    ListNode* temp = head;
    while(temp){
        len++;
        temp = temp->next;
    }

    int k = len -n;
    
    temp = head;
    while(k>1){
        temp = temp->next;
        k--;
    }

    ListNode * nodeToDelete = temp->next;
    if(temp->next)temp->next = temp->next->next;
    nodeToDelete->next = NULL;
    delete nodeToDelete;
    return head;
}



// LC 2095
ListNode* deleteMiddle(ListNode* head) {
    if(!head)return head;
    ListNode* slow = head;
    ListNode* fast = head;
    while(fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }        
    ListNode* nodeToDelete = slow->next;
    slow->next = slow->next->next;
    delete nodeToDelete;
    return head;

} 


// Reverse a doubly linked list 
ListNode* reverseDLL(ListNode* head) {
    // Your code here
    if(!head || head->next) return head;
    ListNode* temp = head;
    ListNode* tempNext = head->next;

    while(temp){
        tempNext = temp->next;
        temp->next = temp->prev;
        temp->prev = tempNext;
        temp  = temp->prev;
        if(temp->next) head = temp;
    }
    return head;
}




// LC 2 add two numbers
void solve(ListNode* temp1, ListNode* temp2, int & carry ){
    if(!temp1 || !temp2) return ;

    solve(temp1->next ,temp2->next, carry);

    int sum = temp1->val + temp2->val + carry;
    temp1->val = sum%10;
    carry = sum/10;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if(!l1) return l2;
    else if (!l2) return l1;
    
    int len1 =0;
    int len2 = 0;
    ListNode* temp1 = l1; 
    ListNode* temp2 = l2; 

    while(temp1){
        len1++;
        temp1 = temp1->next;
    }
    while(temp2){
        len2++;
        temp2 = temp2->next;
    }
    
    temp1 = l1;
    temp2 = l2;
    int carry = 0;

    if(len1>len2){
        while(len1!=len2){
        temp1 = temp1->next;
        len1--;
        }
        solve(temp1, temp2,carry);
    }
    else{
        while(len1!=len2){
            temp2 = temp2->next;
            len2++;
        }
        solve(temp2 , temp1, carry);
    }
}



// delete all the occurences of a key in DLL - https://www.geeksforgeeks.org/problems/delete-all-occurrences-of-a-given-key-in-a-doubly-linked-list/1

    void deleteAllOccurOfX(struct Node** head_ref, int x) {
        Node* curr = *head_ref;

        while (curr != NULL) {
            // If current node contains x
            if (curr->data == x) {
                // If current node is head
                if (curr == *head_ref) {
                    *head_ref = curr->next;
                    if (*head_ref != NULL) {
                        (*head_ref)->prev = NULL;
                    }
                    delete curr;
                    curr = *head_ref;
                }
                // If current node is not head
                else {
                    Node* nextNode = curr->next;
                    curr->prev->next = curr->next;
                    if (curr->next != NULL) {
                        curr->next->prev = curr->prev;
                    }
                    delete curr;
                    curr = nextNode;
                }
            }
            else {
                curr = curr->next;
            }
        }
    }



// find pairs with given sum in a DLL - https://www.geeksforgeeks.org/problems/find-pairs-with-given-sum-in-doubly-linked-list/1



// Remove duplicates from a sorted DLL - https://www.geeksforgeeks.org/problems/remove-duplicates-from-a-sorted-doubly-linked-list/1




// LC 25 - reverse nodes in k-group

// using recursion
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k == 1) return head;

        // Check if there are at least k nodes remaining
        ListNode* temp = head;
        int count = 0;
        while (temp && count < k) {
            temp = temp->next;
            count++;
        }

        if (count < k) return head;  // not enough nodes, leave as-is

        // Reverse k nodes
        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* next = nullptr;
        count = 0;

        while (curr && count < k) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
            count++;
        }

        // Recursively reverse the next part of the list
        if (next)
            head->next = reverseKGroup(next, k);

        return prev;  // new head after reversing this group
    }
};
