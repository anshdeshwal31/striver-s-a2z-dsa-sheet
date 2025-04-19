#include <bits/stdc++.h>
using namespace std;

class ListNode{
public:
    ListNode* next;
    int val;
    ListNode(int val){
        this->next = nullptr;
        this->val = val;
    }
};



// LC 328 - odd even linked list
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



// LC 2- add two numbers
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;
    int carry = 0;
    
    while (l1 || l2 || carry) {
        int sum = carry;
        
        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }
        
        if (l2) {
            sum += l2->val;
            l2 = l2->next;
        }
        
        carry = sum / 10;
        current->next = new ListNode(sum % 10);
        current = current->next;
    }
    
    ListNode* result = dummy->next;
    delete dummy;
    return result;
}