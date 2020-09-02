#include <iostream>
#include "list.hpp"

using namespace std;

ListNode* removeNthFromEnd(ListNode *head, int n) {
    ListNode dummy;
    dummy.next = head;
    ListNode *p1 = &dummy, *p2 = &dummy;
    for (int i = 0; i <= n; i++) {
        p1 = p1->next;
    }

    while(p1 != nullptr) {
        p1 = p1->next;
        p2 = p2->next;
    }

    ListNode *entry = p2->next;
    p2->next = p2->next->next;
    delete entry;

    return dummy.next;
}


