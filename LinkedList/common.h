#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() {}
    ListNode(int a) : val(a), next(nullptr) {}
};

ListNode* Create(int n) {
    ListNode dummy;
    ListNode *cur = &dummy;
    for(int i = 0; i < n; ++i) {
        std::cout << i << std::endl;
        ListNode *tmp = new ListNode(i*2);
        cur->next = tmp;
        cur = tmp;
    }
    return dummy.next;
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
        std::cout << head->val << " ";
        head=head->next;
    }
    std::cout << "\n";
}

#endif
