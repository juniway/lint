#include "list.hpp"

ListNode* SortedIntersect(ListNode *a, ListNode *b){
    ListNode dummy;
    dummy.next = nullptr;
    ListNode *tail = &dummy;

    while(a != nullptr && b != nullptr) {
        if (a->data == b->data) {
            Push(&(tail->next), a->data);
            tail = tail->next;
            a = a->next;
            b = b->next;
        } else if (a->data < b->data) {
            a = a->next;
        } else {
            b = b->next;
        }
    }

    return dummy.next;
}

ListNode* SortedIntersect1(ListNode *a, ListNode *b) {
    ListNode *result = nullptr;
    ListNode **tail_ref = &result;

    while(a != nullptr && b != nullptr) {
        if (a->data == b->data) {
            Push(tail_ref, a->data);
            tail_ref = &((*tail_ref)->next);
            a = a->next;
            b = b->next;
        } else if (a->data < b->data) {
            a = a->next;
        } else {
            b = b->next;
        }
    }

    return result;
}
