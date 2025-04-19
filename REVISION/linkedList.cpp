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