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

// no need too loops
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