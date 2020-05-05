#ifndef COMMON_H
#define COMMON_H

struct ListNode {
    int data;
    ListNode *next;
    ListNode() = default;
    ListNode(int a, ListNode *next = nullptr) : data(a), next(next) {}
};

ListNode* Create(int n, int(f)(int));
void Destroy(ListNode **head);
void PrintList(ListNode *head);
void Push(ListNode **head_ref, int new_data);
void Delete(ListNode **head_ref, int new_data);

void FrontBackSplit(ListNode*, ListNode**, ListNode**);
void MoveNode(ListNode**, ListNode**);

#endif
