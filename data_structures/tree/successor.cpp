#include <iostream>
#include "tree.hpp"

using std::cout;

Node *Successor(Node *root, int key) {
    Node *cur = root;
    Node *parent = root;
    while(cur != nullptr) {
        if (key == cur->data){
            cur = cur->right;
            while(cur != nullptr) {
                parent = cur;
                cur = cur->left;
            }
        } else if (key < cur->data) {
            parent = cur;
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    
    return parent;
}

void TestSuccessor() {
    Node *root = nullptr;
    Insert(&root, 20);
    Insert(&root, 8);
    Insert(&root, 12);
    Insert(&root, 22);
    Insert(&root, 4);
    Insert(&root, 10);
    Insert(&root, 14);

    Node *succ = Successor(root, 14);
    cout << succ->data << "\n";
    succ = Successor(root, 8);
    cout << succ->data << "\n";
    succ = Successor(root, 10);
    cout << succ->data << "\n";
}

// int main(int argc, char *argv[]) {
//     TestSuccessor();
//     return 0;
// }
