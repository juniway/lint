#include "list.hpp"
#include <iostream>

ListNode* getKth(ListNode *head, int k) {
    ListNode *pre, *cur;
    pre = cur = head;
    for (int i = 0; i < k; i++) {
        if (cur != nullptr) cur = cur->next;
        else return nullptr;
    }

    while(cur != nullptr) {
        pre = pre->next;
        cur = cur->next;
    }

    return pre;
}

ListNode *DummyKth(ListNode *head, int k) {
    ListNode *pre, *cur;
    pre = cur = head;
    for (int i = 0; i < k; i++) {
        if(cur != nullptr) cur = cur->next;
        // else 
    }

    while(cur != nullptr) {
        cur = cur->next;
        pre = pre->next;
    }

    while(pre->next != nullptr) {
        ListNode *tmp = pre->next;
        pre->next = tmp->next;
        delete tmp;
    }

    return head;
}

void getall(ListNode *head, int n) {
    for(int i = 0; i <= n; i++) {
        ListNode *p = getKth(head, i);
        if (p != nullptr)
            printf("%dth node has data: %d\n", i , p->data);
    }
}

void insertSorted(ListNode **head, int val) {
    ListNode dummy;
    dummy.next = *head;
    ListNode *p = &dummy;
    ListNode *cur = p->next;
    while(cur != nullptr && val > cur->data) {
        p = cur;
        cur = cur->next;
    }

    ListNode *node = new ListNode(val);
    node->next = cur;
    p->next = node;
}

void deleteList(ListNode **head_ref) {
    ListNode *cur = *head_ref;
    ListNode *next = cur->next;

    while(cur!= nullptr) {
        next = cur->next;
        delete cur;
        cur = next;
    }

    *head_ref = nullptr;
}

int PopHead(ListNode **head_ref) {
    ListNode *head = *head_ref;
    assert(head != nullptr);
    int val = head->data;
    *head_ref = head->next;
    delete head;

    return val;
}

void SortedInsert(ListNode **head_ref, ListNode *node) {
    ListNode dummy;
    dummy.next = *head_ref;
    ListNode *cur = &dummy;
    while(cur->next != nullptr && cur->next->data < node->data) {
        cur = cur->next;
    }

    node->next = cur->next;
    cur->next = node;

    *head_ref = dummy.next;
}

int main() {
    ListNode *head = Create(10, [](int i){return i*2;});
    PrintList(head);
    // getall(head, 7);
    PrintList(DummyKth(head, 2));
    // insertSorted(&head, 3);
    // PrintList(head);
    // insertSorted(&head, 9);
    // PrintList(head);
    // insertSorted(&head, 4);
    // PrintList(head);
    //
    // removeDupFromSorted(&head);
    // PrintList(head);
    //
    // ListNode *headx = Create(5, [](int i){i = i*3+4; return i; });
    // PrintList(headx);
    // // ListNode *res = shuffleMerge(head, headx);
    // // PrintList(res);
    //
    // ListNode *meg = mergeTwoLists(head, headx);
    // PrintList(meg);
}
