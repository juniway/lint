// http://blog.csdn.net/otuhacker/article/details/10366563
既然两个指针都是从前往后遍历，那么链表值进行交换就简单了。
找到支点后，支点左边和支点右边进行子问题递归，就回到快排原来的思路上去了。
代码如下：

struct Node{
    int data;
    Node* next;
    Node() = default;
    Node(int _dat, Node* pNext = nullptr) : data(_dat) , next(pNext) {}
};

Node* GetPartion(Node* pBegin, Node* pEnd) {
    int pivot = pBegin->data;
    Node* p = pBegin;
    Node* q = p->next;

    while(q != pEnd){
        if(q->data < pivot){
            p = p->next;
            swap(p->data, q->data);
        }
        q = q->next;
    }
    swap(p->data, pBegin->data);
    return p;
}

void QuickSort(Node* pBeign, Node* pEnd){
    if(pBeign != pEnd){
        Node* partion = GetPartion(pBeign, pEnd);
        QuickSort(pBeign,partion);
        QuickSort(partion->next,pEnd);
    }
}