#include "common.h"
#include <vector>

ListNode* mergetTwoLists(ListNode *ph1, ListNode *ph2) {
    ListNode *pCur = nullptr;
    ListNode *pHead = nullptr;
    if (ph1 == nullptr) {
        return ph2;
    } else if (ph2 == nullptr) return ph1;
    else {
        if (ph1->data < ph2->data) {
            pHead = ph1;
            ph1 = ph1->next;
        } else {
            pHead = ph2;
            ph2 = ph2->next;
        }

        pCur = pHead;
        while(ph1 != nullptr && ph2 != nullptr) {
            if(ph1->data <= ph2->data) {
                pCur->next = ph1;
                ph1 = ph1->next;
            } else {
                pCur->next = ph2;
                ph2 = ph2->next;
            }
            pCur = pCur->next;
        }
        if(ph1 == nullptr) {
            pCur->next = ph2;
        } else if(ph2 == nullptr){
            pCur->next = ph1;
        }
        return pHead;
    }
}

ListNode* mergeTwoListRecursive(ListNode *ph1, ListNode *ph2) {
    ListNode *newHead = nullptr;
    if (ph1 == nullptr) return ph2;
    else if (ph2 == nullptr) return ph1;
    else {
        if (ph1->data < ph2->data) {
            newHead = ph1;
            newHead->next = mergeTwoListRecursive(ph1->next, ph2);
        } else {
            newHead = ph2;
            newHead->next = mergeTwoListRecursive(ph1, ph2->next);
        }
        return newHead;
    }
}

void deleteNodeO1(ListNode *head, ListNode *toDelete) {
    if (toDelete == nullptr) return;
    if (toDelete->next != nullptr) {
        toDelete->data = toDelete->next->data;
        toDelete->next = toDelete->next->next;
        delete toDelete->next;
        toDelete = nullptr;
    } else {
        ListNode *p = head;
        while(p != nullptr && p->next != toDelete) {
            p = p->next;
        }
        delete toDelete;
        p->next = nullptr;
        toDelete = nullptr;
    }
}

void printListFromTail(ListNode *head, vector<int> &res) {
    ListNode *p = head;
    if (p != nullptr) {
        if(p->next != nullptr) {
            printListFromTail(p->next, res);
        }
        res.push_back(p->data);
    }
}
