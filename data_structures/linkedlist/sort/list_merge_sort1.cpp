#include <random>
#include "list.hpp"

ListNode* SortedMerge(ListNode *a, ListNode *b) {
    ListNode dummy;
    dummy.next = nullptr;
    ListNode *tail = &dummy;


    while(true) {
        if (a == nullptr) {
            tail->next = b;
            break;
        } else if (b == nullptr) {
            tail->next = a;
            break;
        } else {
            if(a->data <= b->data) {
                MoveNode(&(tail->next), &a);
            } else {
                MoveNode(&(tail->next), &b);
            }
            tail = tail->next;
        }
    }

    return dummy.next;
}

void MergeSort(ListNode **head_ref) {
    ListNode *a, *b;
    a = b = nullptr;

    ListNode *head = *head_ref;
    if (head == nullptr || head->next == nullptr){
        return;
    }

    FrontBackSplit(head, &a, &b);
    MergeSort(&a);
    MergeSort(&b);

    *head_ref = SortedMerge(a, b);

}

ListNode *BuildListFront(std::random_device& seed, int(f)(int)) {
    ListNode *head = nullptr;

    std::mt19937 gen(seed());
    std::uniform_int_distribution<int> distn(1, 10);

    int n = distn(gen);
    for (int i = 0; i < n; i++){
        Push(&head, f(i));
    }

    return head;
}

void testSortedMerge() {
    std::random_device seed;
    ListNode *a = BuildListFront(seed, [](int i){return i*2;});
    ListNode *b = BuildListFront(seed, [](int i){return i*2+1;});
    PrintList(a);
    PrintList(b);

    ListNode *res = SortedMerge(a, b);
    PrintList(res);
}

void testMergeSort() {
    std::random_device seed;
    ListNode *a = BuildListFront(seed, [](int i){return i*2;});
    PrintList(a);

    MergeSort(&a);
    PrintList(a);
}

int main(int argc, char *argv[]) {
    // testSortedMerge();
    testMergeSort();
    return 0;
}
