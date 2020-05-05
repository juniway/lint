#include <iostream>
#include <stack>
#include "list.hpp"

// 要点是：使用 prev 和 cur 两个游标
ListNode* ReverseList(ListNode *root) {
    ListNode *head = root;
    ListNode *prev = root;
    ListNode *tmp = root->next;
    while (tmp) {
        ListNode *next = tmp->next;
        tmp->next = prev;
        prev = tmp;
        tmp = next;
    }
    head->next = NULL;
    return prev;
}

ListNode* ReverseList1(ListNode* pHead){
    ListNode* pReversedHead = nullptr;
    ListNode* pNode = pHead;
    ListNode* pPrev = nullptr;

    while(pNode != nullptr){
        ListNode* pNext = pNode->next;
        if(pNext == nullptr){
            pReversedHead = pNode;
        }
        pNode->next = pPrev;
        pPrev = pNode;
        pNode = pNext;
    }

    return pReversedHead;
}

ListNode* ReversedList2(ListNode* pHead){
    std::stack<ListNode*> st;
    while(pHead != nullptr){
        st.push(pHead);
        pHead = pHead->next;
    }

    pHead = st.top();
    ListNode* cur = pHead;

    while(true){
        st.pop();
        if(st.empty()){
            cur->next = nullptr;
            return pHead;
        }
        cur->next = st.top();
    }
}

void Reverse(ListNode **head_ref) {
    ListNode *result = nullptr;
    ListNode *cur = *head_ref;
    ListNode *next = cur;

    while(cur != nullptr) {
        next = cur->next;
        cur->next = result;
        result = cur;
        cur = next;
    }

    *head_ref = result;
}

void Reverse2(ListNode **head_ref) {
    ListNode *result = nullptr;
    ListNode *cur = *head_ref;
    while (cur != nullptr) {
        MoveNode(&result, &cur);
    }

    *head_ref = result;
}

// Back-Middle-Front strategy
// nullptr 1 -> 2 -> 3
//  back  mid  front
void Reverse3(ListNode **head_ref) {
    if (*head_ref != nullptr) {
        ListNode *mid = *head_ref;
        ListNode *front = mid->next;
        ListNode *back = nullptr;
        while(true) {
            mid->next = back;
            if (front == nullptr) break;
            back = mid;
            mid = front;
            front = front->next;
        }
        *head_ref = mid;
    }
}

int main() {
}
