#include "list.hpp"
#include <random>
#include <iostream>

void MoveNode(ListNode **dest_ref, ListNode **src_ref) {
    if (*src_ref == nullptr) return;
    ListNode *tmp = (*src_ref)->next;
    (*src_ref)->next = *dest_ref;
    *dest_ref = *src_ref;

    *src_ref = tmp;
}

void AlternatingSplit(ListNode *src, ListNode **l1_ref, ListNode **l2_ref) {
    ListNode *a = nullptr;
    ListNode *b = nullptr;

    ListNode *cur = src;
    while(cur != nullptr) {
        MoveNode(&a, &cur);
        if (cur != nullptr) 
            MoveNode(&b, &cur);
    }
    *l1_ref = a;
    *l2_ref = b;
}

void AlternatingSplit0(ListNode *src, ListNode **l1_ref, ListNode **l2_ref) {
    ListNode dm1, dm2;
    dm1.next = dm2.next = nullptr;
    ListNode *tail1 = &dm1;
    ListNode *tail2 = &dm2;

    ListNode *cur = src;
    while(cur != nullptr) {
        MoveNode(&(tail1->next), &cur);
        tail1 = tail1->next;
        if (cur != nullptr) {
            MoveNode(&(tail2->next), &cur);
            tail2 = tail2->next;
        }
    }
    *l1_ref = dm1.next;
    *l2_ref = dm2.next;
}

void AlternatingSplit1(ListNode *src, ListNode **l1_ref, ListNode **l2_ref) {
    ListNode dummy1;
    dummy1.next = *l1_ref;
    ListNode *tail1 = &dummy1;

    ListNode dummy2;
    dummy2.next = *l2_ref;
    ListNode *tail2 = &dummy2;

    ListNode *cur = src;
    while(cur != nullptr) {
        tail1->next = cur;
        tail1 = tail1->next;
        cur = cur->next;
        if (cur != nullptr) {
            tail2->next = cur;
            tail2 = tail2->next;
            cur = cur->next;
        }
    }

    *l1_ref = dummy1.next;
    *l2_ref = dummy2.next;
}

ListNode *BuildListFront(std::random_device& seed) {
    ListNode *head = nullptr;

    std::mt19937 gen(seed());
    std::uniform_int_distribution<int> distn(1, 10);
    std::uniform_int_distribution<int> dist(1, 100);

    int n = distn(gen);
    for (int i = 0; i < n; i++){
        Push(&head, dist(gen));
    }

    return head;
}

void testMoveNode() {
    std::random_device seed;
    ListNode *src = BuildListFront(seed);
    ListNode *dest = BuildListFront(seed);
    PrintList(src);
    PrintList(dest);

    MoveNode(&dest, &src);
    PrintList(src);
    PrintList(dest);
}

void testMoveNodeTail() {
    ListNode *head1 = nullptr;
    Push(&head1, 4);
    PrintList(head1);
    PrintList(head1->next);

    ListNode *head2 = nullptr;
    Push(&head2, 9);
    PrintList(head2);

    MoveNode(&(head1->next), &head2);
    PrintList(head1);
    PrintList(head2);
}

void testAlternatingSplit(){
    std::random_device seed;
    ListNode *src = BuildListFront(seed);
    PrintList(src);

    ListNode *l1{nullptr}, *l2(nullptr);
    AlternatingSplit0(src, &l1, &l2);
    std::cout << "L1: ";
    PrintList(l1);
    std::cout << "L2: ";
    PrintList(l2);
}

int main(int argc, char *argv[]) {
    // testAlternatingSplit();
    testMoveNodeTail();
    return 0;
}
