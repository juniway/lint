#include <cstdlib>
#include <ctime>
#include "list.hpp"

void FrontBackSplit(ListNode *src, ListNode **front_ref, ListNode **back_ref) {
    *front_ref = src;
    if (src == nullptr || src->next == nullptr) {
        *back_ref = nullptr;
        return;
    }

    ListNode *slow, *fast, *pre;
    slow = fast = src;

    while(fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        pre = slow;
        slow = slow->next;
    }

    pre->next = nullptr;

    *back_ref = slow;
}

ListNode* BuildListFromHead(int n) {
    ListNode dummy;
    dummy.next = nullptr;
    ListNode *cur = &dummy;
    
    for (int i = 0; i < n; ++i) {
        cur->next = new ListNode(std::rand()%100);
        cur = cur->next;
    }

    return dummy.next;
}

// int main(int argc, char *argv[]) {
//     srand(time(nullptr));
//     ListNode *head = BuildListFromHead(std::rand()%15);
//     PrintList(head);
//
//     ListNode *front, *back;
//     FrontBackSplit(head, &front, &back);
//     PrintList(front);
//     PrintList(back);
//     
//     return 0;
// }
