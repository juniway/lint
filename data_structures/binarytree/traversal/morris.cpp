#include <iostream>
#include <array>
#include "tree.hpp"

using std::cout;
using std::array;

Node *findMax(Node *node) {
    while(node->right != nullptr) {
        node = node->right;
    }

    return node;
}

Node *predecessor(Node *root, Node *node) {
    Node *cur, *pred = nullptr;
    cur = root;
    while (cur != nullptr) {
        if (cur == node) break;
        else if (cur->data > node->data) {
            pred = cur;
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    if (cur != nullptr && cur->left != nullptr) {
        pred = findMax(node->left);
    }

    return pred;
}

void morris(Node *root) {
    if (root == nullptr) return;
    Node *cur, *pre = nullptr;
    cur = root;

    while (cur != nullptr) {
        if (cur->left == nullptr){
            cout << cur->data << " ";
            cur = cur->right;
        } else {
            pre = cur->left;
            while (pre->right != nullptr && pre->right != cur)
                pre = pre->right;

            if (pre->right == nullptr) {
                pre->right = cur;
                cur = cur->left;
            } else {
                pre->right = nullptr;
                cout << cur->data << " ";
                cur = cur->right;
            }
        }
    }

    cout << "\n";
}

Node* BuildTree() {
    Node *root = nullptr;
    constexpr int n = 8;
    std::array<int, n> a = {20, 8, 22, 14, 17, 10, 15, 1};
    for (auto i: a) {
        Insert(&root, i);
    }
    PrintBst(root);

    return root;
}

void TestMorris() {
    Node *root = BuildTree();
    morris(root);
}

int main(int argc, char *argv[]) {
    TestMorris();
    return 0;
}
