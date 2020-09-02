#include <cstdlib>
#include <ctime>
#include "list.hpp"

// split the node front back in halves
// split operation can be used to do merge sort
void FrontBackSplit(ListNode *src, ListNode **front_ref, ListNode **back_ref) {
    // if len is less than 2, handle separately
    if (src == nullptr || src->next == nullptr) {
        *front_ref = src;
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

void FrontBackSplit(Node* source, Node** frontRef, Node** backRef){
    // if length is less than 2, handle separately
    if (source == NULL || source->next == NULL){
        *frontRef = source;
        *backRef = NULL;
        return;
    }

    Node* slow = source;
    Node* fast = source->next;

    // Advance 'fast' two nodes, and advance 'slow' one node
    while (fast != NULL){
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // 'slow' is before the midpoint in the list, so split it in two at that point.
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
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


// reference: 
// https://www.techiedelight.com/merge-sort-singly-linked-list/
