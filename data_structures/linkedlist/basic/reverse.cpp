#include <iostream>
#include "list.hpp"
using namespace std;

// 1. use pre and cur
ListNode* reverseList(ListNode *head) {
    ListNode *pre = nullptr, *cur = head;
    while (cur->next) {
        ListNode *tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }

    if (head != nullptr)
        head->next = cur;

    return pre;
}

// 2. using dummy node
ListNode* reverseList2(ListNode *head) {
    ListNode dummy; dummy.next = head;
    ListNode *pre = &dummy, *cur = head;
    while (cur && cur->next) {
        ListNode *next = cur->next->next;
        cur->next->next = pre->next;
        pre->next = cur->next;
        cur->next = next;
    }

    return dummy.next;
}

// 3. using ref
void reverseList3(ListNode **head_ref) {
    ListNode *result = nullptr;
    ListNode *cur = *head_ref;
    ListNode *next = cur;

    while(cur) {
        next = cur->next;
        cur->next = result;
        result = cur;
        cur = next;
    }

    *head_ref = result;
}

// 4. using ref + MoveNode
void reverseList4(ListNode **head_ref) {
    ListNode *result = nullptr;
    ListNode *cur = *head_ref;
    while (cur != nullptr) {
        MoveNode(&result, &cur);
    }

    *head_ref = result;
}


// 5. Back-Middle-Front strategy
// nullptr 1 -> 2 -> 3
//  back  mid  front
void reverseList5(ListNode **head_ref) {
    if (*head_ref != nullptr) {
        ListNode *mid = *head_ref;
        ListNode *front = mid->next;
        ListNode *back = nullptr;
        while(true) {
            mid->next = back;
            if (front == nullptr) break;
            back = mid;
            mid = front;
            front = front->next;
        }
        *head_ref = mid;
    }
}

ListNode* buildList() {
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    // head->next->next->next = new ListNode(4);
    // head->next->next->next->next = new ListNode(5);
    return head;
}

int main(int argc, char *argv[]) {
    ListNode *head = buildList();
    PrintList(head);
    PrintList(reverseList2(head));
    return 0;
}
