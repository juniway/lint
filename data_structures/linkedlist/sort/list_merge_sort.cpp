#include "list.hpp"
#include <ctime>
#include <cstdlib>

ListNode* merge(ListNode *l, ListNode *r) {
    if (l == nullptr) return r;
    else if(r == nullptr) return l;

    ListNode *result= new ListNode();
    ListNode *p = result;
    while (l != nullptr && r != nullptr) {
        if (l->data < r->data) {
            result->next = l;
            result = l;
            l = l->next;
        } else {
            result->next = r;
            result = r;
            r = r->next;
        }
    }
    if (l != nullptr)  result->next = l;
    if (r != nullptr)  result->next = r;

    result = p->next;
    delete p;
    return result;
}

// split the list in half
void split(ListNode *head, ListNode *&l, ListNode *&r) {
    if (head == nullptr || head->next == nullptr) {
        l = head;
        r = nullptr;
        return;
    }

    ListNode *slow = head, *fast = head->next;
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
    }
    l = head;
    r = slow->next;
    slow->next = nullptr;
}

void mergeSort(ListNode *&head) {
    if (head == nullptr || head->next == nullptr) return;
    ListNode *l, *r;
    split(head, l, r);
    mergeSort(l);
    mergeSort(r);
    head = merge(l, r);
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
    return 0;
}
