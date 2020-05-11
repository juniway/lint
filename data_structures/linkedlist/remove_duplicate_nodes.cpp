// leetcode 82. Remove Duplicates from Sorted List II

ListNode* deleteDuplicates(ListNode* head) {
    ListNode dummy;
    dummy.next = head;
    ListNode *prev = &dummy, *cur = prev->next;


    while(cur) {
        bool isDuplicated = false;
        while(cur->next && cur->val == cur->next->val) {
            isDuplicated = true;
            ListNode *tmp = cur;
            cur = cur->next;
            delete tmp;
            continue;
        }

        if (isDuplicated) {
            ListNode *tmp = cur;
            cur = cur->next;
            delete tmp;
            continue;
        }

        prev->next = cur;
        prev = prev->next;
        cur = cur->next;
    }

    prev->next = cur;
    return dummy.next;
}