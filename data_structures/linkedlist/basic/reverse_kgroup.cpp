ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode *cur = head;
    int K = k;
    while (K > 0) {
        if (cur == nullptr) return head;
        cur = cur->next;
        K--;
    }

    ListNode *pre = reverseKGroup(cur, k);
    while(K++ < k) {
        ListNode *next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }

    return pre;
}

ListNode* reverseKGroup1(ListNode* head, int k) {
    int n = 0;
    for (auto i = head; i != nullptr; i = i->next, n++);

    ListNode dummy;
    dummy.next = head;
    for (ListNode *prev = &dummy, *cur = head; n >= k; n -= k) {
        for (int i = 1; i < k; i++) {
            ListNode *next = cur->next->next;
            cur->next->next = prev->next;
            prev->next = cur->next;
            cur->next = next;
        }
        prev = cur;
        cur = cur->next;
    }
    return dummy.next;
}
