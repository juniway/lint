#include <iostream>
#include "common.h"

using namespace std;

void Print(ListNode *p) {
    while(p != nullptr) {
        cout << p->data << " " ;
        p = p->next;
    }
    cout << endl;
}

// 要点是：使用 prev 和 cur 两个游标
ListNode* ReverseLinkedList(ListNode *root) {
    ListNode *head = root;
    ListNode *prev = root;
    ListNode *tmp = root->next;
    while (tmp) {
        ListNode *next = tmp->next;
        tmp->next = prev;
        prev = tmp;
        tmp = next;
    }
    head->next = NULL;
    return prev;
}

ListNode* ReverseList(ListNode* pHead){
    ListNode* pReversedHead = nullptr;
    ListNode* pNode = pHead;
    ListNode* pPrev = nullptr;

    while(pNode != nullptr){
        ListNode* pNext = pNode->m_pNext;
        if(pNext == nullptr){
            pReversedHead = pNode;
        }
        pNode->m_pNext = pPrev;
        pPrev = pNode;
        pNode = pNext;
    }

    return pReversedHead;
}

ListNode* ReversedList(ListNode* pHead){
    std::stack<ListNode*> st;
    while(pHead != nullptr){
        st.push(pHead);
        pHead = pHead->m_pNext;
    }

    pHead = st.top();
    ListNode* cur = pHead;

    while(true){
        st.pop();
        if(st.empty()){
            cur->next = nullptr;
            return pHead;
        }
        cur->next = st.top();
    }
}

// 创建一条长度为 N 的链表，技巧是：在头部建一个 fake head。
extern Node* CreateLinkedList();
// Node* CreateLinkedList() {
//     Node *dummy = new Node();
//     Node *prev = dummy;
//     for (int i = 0; i < 10; ++i) {
//         Node *pNode = new Node();
//         pNode->data = i;
//         pNode->next = nullptr;
//         prev->next = pNode;
//         prev = pNode;
//     }
//     prev = dummy->next;
//     delete dummy;
//     return prev;
// }

int main() {
    Node* root = CreateLinkedList();
    Print(root);
    Node *res = ReverseLinkedList(root);
    Print(res);
    delete root;
    delete res;
}