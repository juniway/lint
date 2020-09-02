void deleteNode(ListNode *head, ListNode *toDelete) {
    if (toDelete == nullptr) return;
    if (toDelete->next != nullptr) {
        toDelete->data = toDelete->next->data;
        toDelete->next = toDelete->next->next;
        delete toDelete->next;
        toDelete = nullptr;
    } else {
        ListNode *p = head;
        while(p != nullptr && p->next != toDelete) {
            p = p->next;
        }
        delete toDelete;
        p->next = nullptr;
        toDelete = nullptr;
    }
}
