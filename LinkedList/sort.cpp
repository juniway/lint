// 单链表 merge sort
Node* merge(Node *l, Node *r) {
    if (l == NULL) return r;
    else if(r == NULL) return l;

    Node *result= new Node();
    Node *p = result;
    while (l != NULL && r != NULL) {
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
    if (l != NULL)  result->next = l;
    if (r != NULL)  result->next = r;

    result = p->next;
    delete p;
    return result;
}

由于链表不能随机读取，于是把链表分成两个部分的工作比数组要复杂一些。这里是使用了快慢指针的方法，快慢两个指针初始化为链表头部，快指针移动的步长为2，慢指针的步长为1，于是快指针到达链表尾部的时候，慢指针刚好到达中间，于是可以根据这点把链表分为两个部分。

注意要把左边链表的最后一个节点的next值设为空，否则就没有达到切成两个链表的效果。

void split(Node *head, node *&l, Node *&r) {
    if (head == NULL || head->next == NULL) {
        l = head;
        r = NULL;
        return;
    }

    Node *slow = head, *fast = head->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
                  }
    }
    l = head;
    r = slow->next;
    slow->next = NULL;
}

下面就是归并排序的主函数。把链表切成左右两部分，递归地对两部分排好序，然后再归并起来得到最终排好序的链表。

void mergeSort(node *&head) {
    if (head == NULL || head->next == NULL) return;
    node *l, *r;
    split(head, l, r);
    mergeSort(l);
    mergeSort(r);
    head = merge(l, r);
}