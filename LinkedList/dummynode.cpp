#include <iostream>
#include "common.h"

using namespace std;

Node *insert(Node *root, Node *node) {
    Node dummy;
    dummy.next = root;
    if (root == nullptr) {
        dummy.next = node;
        return dummy.next;
    }

    Node *prev = &dummy;
    Node *cur = prev->next;
    while(cur && cur->data < node->data) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == nullptr) {
        prev->next = node;
    } else {
        Node *next = cur->next;
        prev->next = node;
        node->next = next;
    }

    return dummy.next;
}

int main() {
    Node node1;
    node1.data = 9;
    Node* pNode = insert(nullptr, &node1);
    cout << "Node: " << pNode->data << endl;
}