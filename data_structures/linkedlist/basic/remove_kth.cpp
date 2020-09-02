#include <iostream>
#include "list.hpp"

using namespace std;

ListNode* removeKth1(ListNode *head, int k) {
    if (head == nullptr || k < 0) return head;

    ListNode dummy;
    dummy.next = head;
    ListNode *pre = &dummy, *cur = dummy.next;
    while (cur) {
        if (--k == -1) {
            pre->next = cur->next;
            delete cur;
            cur = nullptr;
            break;
        }
        pre = cur;
        cur = cur->next;
    }

    if (k > -1) {
        // idempotent operation, so we simply print a message
        cout << "length is less than " << k << ".\n";
    }

    return dummy.next;
}

ListNode* removeKth(ListNode *head, int k) {
    if (head == nullptr || k < 0) return head;
    ListNode *pre = nullptr, *cur = head;
    while (cur) {
        if (--k == -1) {
            if (cur == head) {
                ListNode *tmp = cur;
                cur = cur->next;
                head = cur;
                delete tmp;
            } else {
                pre->next = cur->next;
                delete cur;
                cur = nullptr;
            }
            break;
        }
        pre = cur;
        cur = cur->next;
    }

    if (k > -1) {
        // idempotent operation, so we simply print a message
        cout << "length is less than " << k << ".\n";
    }

    return head;
}

ListNode* removeKth4(ListNode *head, int k) {
    ListNode **cur = &head;
    while (*cur) {
        if (--k == -1) {
            *cur = (*cur)->next;
            break;
        }
        cur = &((*cur)->next);
    }

    return head;
}
ListNode* removeKth2(ListNode *head, int k) {
    if (head == nullptr || k < 0) return head;

    ListNode *tmp = head;
    if (k == 0) {
        head = head->next;
        delete tmp;
    } else {
        while (tmp) {
            if (--k == 0) {
                ListNode *p = tmp->next;
                tmp->next = tmp->next->next;
                tmp = tmp->next;
                delete p;
                break;
            }
            tmp = tmp->next;
        }

        if (k > 0) {
            cout << "length is less than " << k << ".\n";
        }
    }

    return head;
}

ListNode *removeMiddle(ListNode *head) {
    if (head == nullptr) return head;

    ListNode **slow, *fast;
    slow = &head, fast = head->next;
    while(fast && fast->next) {
        slow = &((*slow)->next);
        fast = fast->next->next;
    }

    if(*slow != nullptr)
        *slow = (*slow)->next;

    return head;
}

void testRemove() {
    ListNode *head = nullptr;
    Push(&head, 4);
    Push(&(head->next), 5);
    Push(&(head->next->next), 1);
    Push(&(head->next->next->next), 9);
    PrintList(head);
    // PrintList(removeKth3(head, 3));
    PrintList(removeMiddle(head));
}

int main(int argc, char *argv[]) {
    testRemove();
    return 0;
}

