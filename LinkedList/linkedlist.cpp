#include <iostream>
#include "common.h"

using namespace std;

Node *insert(Node *root, Node *node) {
    Node dummy(-1);
    dummy.next = root;
    if (root == nullptr) {   // 1. 把 prev 和 cur 前移一位即可免去这步判断
        dummy.next = node;
        return dummy.next;
    }

    Node *prev = &dummy, *cur = prev->next;
    while(cur && node != nullptr && node->data > cur->data) {
        prev = cur;
        cur = cur ->next;
    }

    if (cur == nullptr) {  // 2. 把 prev 和 cur 前移一位即可免去这步判断
        prev->next = node;
    } else {
        // Node *next = cur->next;
        prev->next = node;
        node->next = cur;
    }

    return prev;
}

// 改进：把 prev 和 cur 的位置前移一位，可以避免判断 head 是否为空
Node *insert1(Node *root, Node *node) {
    Node dummy(-1);
    dummy.next = root;

    Node *prev = nullptr;
    Node *cur = &dummy;
    while (cur && node->data > cur->data) { // 第一次必然成功, prev 会变成 dummy
        prev = cur;
        cur = cur->next;
    }
    prev->next = node;  // prev 不可能为空
    node->next = cur;
    return dummy.next;
}

Node *delete1(Node* root, int key) {
    Node dummy(-1);
    dummy.next = root;
    Node *prev = &dummy, *cur = dummy.next;
    while (cur && cur->data != key) {
        prev = cur;
        cur = cur->next;
    }
    prev->next = cur->next;
    if (cur != nullptr)
        delete cur;
    cur = nullptr;

    return dummy.next;
}

void delete2(Node* node) {
    if (node == nullptr) {
        return;
    }

    if (node->next != nullptr) {
        Node *tmp = node->next;
        node->data = node->next->data;
        node->next = node->next->next;
        delete tmp;
        tmp = nullptr;
    } else {
        delete node;
        node = nullptr;
    }
}

Node *find(Node *head, int key) {
    while(head) {
        if (head->data == key) {
            return head;
        }
        head = head->next;
    }
    return head;
}

int main(int args, char **argv) {
    Node *head = Create(10);
    Print(head);
    Node *node = insert1(head, new Node(7));
    Print(node);

    // node = delete1(head, 7);
    // Print(node);

    Node *node1 = find(head, 8);
    delete2(node1);
    Print(head);

    Destroy(&head);
    if (head == nullptr) {
        cout << "OK!\n";
    } else {
        cout << "Failed!\n";
    }
}