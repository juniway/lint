
void insertSorted(ListNode **head, int val) {
    ListNode dummy;
    dummy.next = *head;
    ListNode *p = &dummy;
    ListNode *cur = p->next;
    while(cur != nullptr && val > cur->data) {
        p = cur;
        cur = cur->next;
    }

    ListNode *node = new ListNode(val);
    node->next = cur;
    p->next = node;
}

void SortedInsert(ListNode **head_ref, ListNode *node) {
    ListNode dummy;
    dummy.next = *head_ref;
    ListNode *cur = &dummy;
    while(cur->next != nullptr && cur->next->data < node->data) {
        cur = cur->next;
    }

    node->next = cur->next;
    cur->next = node;

    *head_ref = dummy.next;
}

ListNode *insert(ListNode *root, ListNode *node) {
    ListNode dummy;
    dummy.next = root;
    if (root == nullptr) {
        dummy.next = node;
        return dummy.next;
    }

    ListNode *prev = &dummy;
    ListNode *cur = prev->next;
    while(cur && cur->data < node->data) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == nullptr) {
        prev->next = node;
    } else {
        ListNode *next = cur->next;
        prev->next = node;
        node->next = next;
    }

    return dummy.next;
}


void append(ListNode **head_a, ListNode **head_b){
    ListNode dummy;
    dummy.next = *head_a;
    ListNode *cur = &dummy;
    while(cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = *head_b;
    *head_b = nullptr;
    *head_a = dummy.next;
}