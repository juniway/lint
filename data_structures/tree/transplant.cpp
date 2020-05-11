#include <array>
#include "tree.hpp"

using std::array;

Node *findKey(Node *root, int key) {
    while(root != nullptr) {
        if (root->data == key) break;
        else if (root->data > key) root = root->left;
        else root = root->right;
    }

    return root;
}

Node *parent(Node *root, Node *node) {
    if (root == nullptr || node == nullptr) return nullptr;
    else if(root->left == node || root->right == node) return root;
    else {
        if (root->data < node->data) return parent(root->right, node);
        else return parent(root->left, node);
    }
}

Node *parent1(Node* root, Node *node) {
    if (root == nullptr || node == nullptr) return nullptr;
    while(root != nullptr && root->left != node && root->right != node) {
        if(root->data > node->data) root = root->left;
        else root = root->right;
    }
    return root;
}

void transplant(Node *root, Node *u, Node *v) {
    Node *p = parent(root, u);
    if (p == nullptr) root = v;
    else if (p->left == u) {
        p->left = v;
    } else {
        p->right = v;
    }
}

Node* findMin(Node *node) {
    while(node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* successor(Node *root, Node *node) {
    Node *cur, *pre = nullptr;
    cur = root;

    while (cur != nullptr) {
        if (cur == node) break;
        else if (cur->data < node->data) {
            cur = cur->right;
        } else {
            pre = cur;
            cur = cur->left;
        }
    }

    if (cur != nullptr && cur->right != nullptr) {
        pre = findMin(cur->right);
    }

    return pre;
}

void delNode(Node *root, Node *node) {
    if (root == nullptr || node == nullptr) return;
    if (node->left == nullptr) {
        transplant(root, node, node->right);
    } else if (node->right == nullptr) {
        transplant(root, node, node->left);
    } else {
        Node *succ = successor(root, node);
        if (node->right == succ) {
            transplant(root, succ, succ->right);
            succ->right = node->right;
        } else {
            succ ->right = node->right;
            Node *p = parent(root, succ);
            p->left = succ->right;
        }
        transplant(root, node, succ);
        succ->left = node->left;
    }

    delete node;
    node = nullptr;
}

void TestParent() {
    constexpr int n = 3;

    Node *root = nullptr;
    array<int, n> a = {10, 8, 15};
    for (int i = 0; i < n; i++) {
        Insert(&root, a[i]);
    }

    for (auto i : a) {
        Node *prt = parent1(root, findKey(root, i));
        if (prt == nullptr) {
            printf("%d's parent is %s\n", i, "nullptr");
        } else {

            printf("%d's parent is %d\n", i, prt->data);
        }
    }
}

void TestTransplant() {
    constexpr int n = 8;

    Node *root = nullptr;
    array<int, n> a = {20, 8, 12, 22, 4, 10, 14, 21};
    for (int i = 0; i < n; i++) {
        Insert(&root, a[i]);
    }
    
    PrintBst(root);
    transplant(root, findKey(root, 8), findKey(root, 12));
    PrintBst(root);
}

void TestSuccessor() {
    constexpr int n = 8;

    Node *root = nullptr;
    array<int, n> a = {20, 8, 12, 22, 4, 10, 14, 21};
    for (int i = 0; i < n; i++) {
        Insert(&root, a[i]);
    }

    PrintBst(root);

    for (auto i : a){
        Node *succ = successor(root, findKey(root, i));
        if (succ != nullptr) {
            printf("%d's successor is %d\n", i, succ->data);
        } else {
            printf("%d's successor is %s\n", i, "nullptr");
        }
    }
    
}

void TestDelNode() {
    constexpr int n = 8;

    Node *root = nullptr;
    array<int, n> a = {20, 8, 12, 22, 4, 10, 14, 21};
    for (int i = 0; i < n; i++) {
        Insert(&root, a[i]);
    }
    PrintBst(root);
    delNode(root, findKey(root, 8));
    PrintBst(root);
    
}

void TestDelNode1() {
    constexpr int n = 9;

    Node *root = nullptr;
    array<int, n> a = {20, 8, 24, 4, 12, 21, 29, 10, 23};
    for (int i = 0; i < n; i++) {
        Insert(&root, a[i]);
    }
    PrintBst(root);
    delNode(root, findKey(root, 21));
    PrintBst(root);
    
}

int main(int argc, char *argv[]) {
    TestParent();
    // TestTransplant();
    // TestSuccessor();
    // TestDelNode1();
    return 0;
}
