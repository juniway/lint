#include <iostream>
#include "list.hpp"
using namespace std;

bool isPalindrome(ListNode* head) {
    if(head == nullptr) return true;
    ListNode *slow=head, *fast = head->next;
    while(fast != nullptr && fast->next!=nullptr){
        fast=fast->next->next;
        slow=slow->next;
    }
    ListNode *p = slow->next, *pre = nullptr;
    slow->next = nullptr;
    while(p != nullptr){
        ListNode *tmp = p->next;
        p->next = pre;
        pre = p;
        p = tmp;
    }

    while(head != nullptr && pre != nullptr){
        if(head->data != pre->data) return false;
        head = head->next;
        pre = pre->next;
    }
    return true;
}

void testIsPalindrome() {
    ListNode *head = nullptr;
    Push(&head, 3);
    Push(&(head->next), 4);
    Push(&(head->next->next), 3);
    PrintList(head);
    cout << boolalpha << isPalindrome(head) << endl;
}

int main(int argc, char *argv[]) {
    testIsPalindrome();
    return 0;
}
