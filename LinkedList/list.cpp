#include "list.hpp"
#include <iostream>

using std::cout;

ListNode* Create(int n, int(f)(int)) {
    ListNode dummy;
    ListNode *cur = &dummy;
    for(int i = 0; i < n; ++i) {
        ListNode *tmp = new ListNode(f(i));
        cur->next = tmp;
        cur = tmp;
    }
    return dummy.next;
}

void Push(ListNode **head_ref, int data) {
    ListNode *node = new ListNode(data);
    node->next = *head_ref;
    *head_ref = node;
}

void Delete(ListNode **head_ref, int key) {
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

void Destroy(ListNode **head) { // 用二级指针的目的是用于验证链表确实被删除，因为一旦删除之后，head 返回出去就是 nullptr
    ListNode *cur = *head;
    while(cur != nullptr) {
        ListNode *tmp = cur->next;
        delete cur;
        cur = tmp;
    }
    *head = cur;
}


void PrintList(ListNode *head) {
    while(head != nullptr) {
        std::cout << head->data << " ";
        head=head->next;
    }
    std::cout << "\n";
}

