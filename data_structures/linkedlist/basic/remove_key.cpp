#include <iostream>
#include "list.hpp"

using namespace std;

ListNode* removeWithKey(ListNode *head, int key) {
    ListNode **cur = &head;
    while(*cur && (*cur)->data != key) {
        cur = &((*cur)->next);
    }

    if (*cur != nullptr)
        *cur = (*cur)->next;

    return head;
}

void testRemove() {
    ListNode *head = nullptr;
    Push(&head, 3);
    Push(&(head->next), 4);
    Push(&(head->next->next), 7);
    PrintList(head);
    PrintList(removeWithKey(head, 4));
}

int main(int argc, char *argv[]) {
    testRemove();
    return 0;
}
