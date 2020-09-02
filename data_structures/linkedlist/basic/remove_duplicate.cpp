// Leetcode 83
Node *deleteDuplicates(Node *head) {
    if (head == nullptr) {
        return head;
    }

    Node* dummy = head;
    Node *cur = head;
    while(cur != nullptr) {
        Node *tmp = cur->next;
        while(tmp && tmp->data == cur->data) {
            Node *tp = tmp->next;
            delete tmp;
            tmp = tp;
        }
        cur->next = tmp;
        cur = cur->next;
    }
    return dummy;
}

// no need two loops
ListNode *deleteDuplicates1(ListNode *head) {
    if (head == nullptr) {
        return head;
    }

    ListNode* dummy = head;
    ListNode *prev = head, *cur = prev->next;
    while(cur != nullptr) {
        if (prev->val == cur->val) {
            prev->next = cur->next;
            delete cur;
        } else {
            prev = cur;
        }
        cur = cur->next;
    }
    return dummy;
}


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


void removeDupFromSorted(ListNode **head) {
    ListNode dummy;
    dummy.next = *head;
    ListNode *pre = &dummy;
    ListNode *cur = pre->next;
    while(cur != nullptr) {
        if (cur->data == pre->data) {
            pre->next = cur->next;
            delete cur;
            cur = pre->next;
        } else {
            pre = cur;
            cur = cur->next;
        }
    }
}

