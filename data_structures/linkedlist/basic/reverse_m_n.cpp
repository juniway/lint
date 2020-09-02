// Leetcode 92. Reverse Linked List II
#include <iostream>
#include "list.hpp"

using namespace std;

ListNode* reverseBetween(ListNode* head, int m, int n) {
    ListNode dummy; ListNode *pre = &dummy, *cur;
    dummy.next = head;
    for (int i = 0; i < m - 1; i++) {
        pre = pre->next;
    }
    cur = pre->next;
    for (int i = 0; i < n - m; i++) {
        ListNode* temp = pre->next;
        pre->next = cur->next;
        cur->next = cur->next->next;
        pre->next->next = temp;
    }
    return dummy.next;
}
