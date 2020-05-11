#include <cstdlib>
#include <ctime>
#include "list.hpp"

void append(ListNode **head_a, ListNode **head_b){
    ListNode dummy;
    dummy.next = *head_a;
    ListNode *cur = &dummy;
    while(cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = *head_b;
    *head_b = nullptr;
    *head_a = dummy.next;
}

ListNode* BuildListFromTail() {
    int n = std::rand()%10;
    if (n <= 0) return nullptr;

    ListNode *head = nullptr;
    Push(&head, std::rand()%11);
    ListNode *tail = head;

    for (int i = 0; i < n - 1; i++) {
        Push(&(tail->next), std::rand()%100);
        tail = tail->next;
    }

    return head;
}

int main() {
    srand(time(nullptr));
    ListNode *heada = BuildListFromTail();
    PrintList(heada);
    ListNode *headb = BuildListFromTail();
    PrintList(headb);

    append(&heada, &headb);
    PrintList(heada);
}
