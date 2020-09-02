// merge two sorted list

// 1. recursive 
Node* SortedMerge(struct Node* a, struct Node* b){
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    Node* result = nullptr;
    if (a->data <= b->data) {
        result = a;
        result->next = SortedMerge(a->next, b);
    } else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }

    return result;
}

ListNode* shuffleMerge(ListNode *head1, ListNode *head2){
    ListNode dummy;
    ListNode *p = &dummy;
    dummy.next = nullptr;

    while(true) {
        if(head1 == nullptr) {p->next = head2 ;break;}
        else if(head2 == nullptr) {p->next = head1; break;}
        else {
            p->next = head1;
            p = p->next;
            head1 = head1->next;

            p->next = head2;
            p = p->next;
            head2 = head2->next;
        }
    }
    return dummy.next;
}

// with dummy
ListNode *mergeTwoLists(ListNode *ph1, ListNode *ph2) {
   ListNode dummy;
   dummy.next = nullptr;
   ListNode *p = &dummy;

   while(true) {
       if(ph1 == nullptr) {p->next = ph2; break;}
       else if(ph2 == nullptr) {p->next = ph1; break;}
       else {
           if(ph1->data < ph2->data) {
               p->next = ph1;
               ph1 = ph1->next;
               p = p->next;
           } else {
               p->next = ph2;
               ph2 = ph2->next;
               p = p->next;
           }
       }
   }

   return dummy.next;
}


// without dummy
ListNode* mergetTwoLists(ListNode *ph1, ListNode *ph2) {
    ListNode *pCur = nullptr;
    ListNode *pHead = nullptr;
    if (ph1 == nullptr) {
        return ph2;
    } else if (ph2 == nullptr) return ph1;
    else {
        if (ph1->data < ph2->data) {
            pHead = ph1;
            ph1 = ph1->next;
        } else {
            pHead = ph2;
            ph2 = ph2->next;
        }

        pCur = pHead;
        while(ph1 != nullptr && ph2 != nullptr) {
            if(ph1->data <= ph2->data) {
                pCur->next = ph1;
                ph1 = ph1->next;
            } else {
                pCur->next = ph2;
                ph2 = ph2->next;
            }
            pCur = pCur->next;
        }
        if(ph1 == nullptr) {
            pCur->next = ph2;
        } else if(ph2 == nullptr){
            pCur->next = ph1;
        }
        return pHead;
    }
}

