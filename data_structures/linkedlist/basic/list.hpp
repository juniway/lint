#include <iostream>

#ifndef COMMON_H
#define COMMON_H

struct ListNode {
    int data;
    ListNode *next;
    ListNode() = default;
    ListNode(int a, ListNode *next = nullptr) : data(a), next(next) {}
};

ListNode* Create(int n, int(f)(int));
void Destroy(ListNode **head);
void PrintList(ListNode *head);
void Push(ListNode **head_ref, int new_data);
void Delete(ListNode **head_ref, int new_data);

void FrontBackSplit(ListNode*, ListNode**, ListNode**);
void MoveNode(ListNode**, ListNode**);

// Implementations

inline ListNode* Create(int n, int(f)(int)) {
    ListNode dummy;
    ListNode *cur = &dummy;
    for(int i = 0; i < n; ++i) {
        ListNode *tmp = new ListNode(f(i));
        cur->next = tmp;
        cur = tmp;
    }
    return dummy.next;
}

inline void Push(ListNode **head_ref, int data) {
    ListNode *node = new ListNode(data);
    node->next = *head_ref;
    *head_ref = node;
}

inline void Delete(ListNode **head_ref, int key) {
    ListNode *pre, *cur;
    pre = cur = *head_ref;
    while(true) {
        if(cur->data != key) {
            // pre = cur;
            // cur = cur->next;
        }
    }

    if(cur != nullptr) {
        pre->next = cur->next;
        delete cur;
    }

}

// 用二级指针的目的是用于验证链表确实被删除，因为一旦删除之后，head 返回出去就是 nullptr
inline void Destroy(ListNode **head) {
    ListNode *cur = *head;
    while(cur != nullptr) {
        ListNode *tmp = cur->next;
        delete cur;
        cur = tmp;
    }
    *head = cur;
}

inline void PrintList(ListNode *head) {
    while(head != nullptr) {
        std::cout << head->data << " ";
        head=head->next;
    }
    std::cout << "\n";
}
#endif
