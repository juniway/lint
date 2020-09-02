#include <iostream>
#include "common.h"

ListNode *CreateList() {
    ListNode *root = new ListNode(5);
    root->next = new ListNode(4);
    root->next->next = new ListNode(8);
    root->next->next->next = new ListNode(11);
    root->next->next->next->next = new ListNode(2);
    return root;
}

class Solution {
public:
    ListNode* insertionSortList(ListNode *head) {
        if(head == nullptr || head->next == nullptr) return head;
        ListNode *dummy = new ListNode(0);
        ListNode *cur = head;
        while(cur != nullptr) { // 依次遍历每个节点
            ListNode *pre = dummy;
            while(pre->next != nullptr && pre->next->val < cur->val) // 遍历已排序的那部分链表
                pre = pre->next;

            ListNode *temp = cur->next;
            cur->next = pre->next;
            pre->next = cur;
            cur = temp;
        }
        return dummy->next;
    }
};

int main() {
    ListNode *root = CreateList();
    PrintList(root);
    Solution sol;
    ListNode *res = sol.insertionSortList(root);
    PrintList(res);
}
