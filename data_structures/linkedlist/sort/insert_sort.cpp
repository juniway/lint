#include <cstdlib>
#include <ctime>
#include "list.hpp"

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

void InsertSort(ListNode **head_ref) {
    ListNode *res = nullptr;
    ListNode *next;
    ListNode *cur = *head_ref;
    while(cur != nullptr) {
        next = cur->next;
        SortedInsert(&res, cur);
        cur = next;
    }
    *head_ref = res;
}

ListNode* BuildFromTail() {
    std::srand(std::time(nullptr));
    int x = std::rand()%10;

    ListNode *head = nullptr;
    Push(&head, x);

    ListNode *tail = head;
    for (int i = 0; i < 5; i++) {
        Push(&(tail->next), (std::rand()+i)%100);
        tail = tail->next;
    }

    return head;
}

int main(int argc, char *argv[]) {
    // ListNode *head = Create(10, [](int i){return i*2;});
    ListNode *head = BuildFromTail();
    PrintList(head);
    InsertSort(&head);
    PrintList(head);
    return 0;
}
