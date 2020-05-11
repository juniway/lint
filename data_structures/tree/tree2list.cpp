#include <array>
#include "tree.hpp"

void join(Node *a, Node *b) {
    a->right = b;
    b->left = a;
}

Node *append(Node *a, Node *b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    Node *aLast, *bLast;
    aLast = a->left;
    bLast = b->left;

    join(aLast, b);
    join(bLast, a);

    return a;
}

Node *tree2List(Node *root) {
    Node *aList, *bList;
    if (root == nullptr) return nullptr;
    aList = tree2List(root->left);
    bList = tree2List(root->right);
    
    // make root itself as a cycly doubly linked list
    root->left = root;
    root->right = root;

    aList = append(aList, root);
    aList = append(aList, bList);

    return aList;
}

Node* BuildTree() {
    Node *root = nullptr;
    std::array<int, 8> a{3, 9, 4, 13, 11, 7, 6, 5};
    for (auto i : a) {
        Insert(&root, i);
    }
    return root;
}

void printList(Node *head, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << head->data << " ";
        head = head->right;
    }
    std::cout << "\n";
}

void TestTree2List() {
    Node *root = BuildTree();
    PrintBst(root);
    Node *lst = tree2List(root);
    printList(lst, 8);
}

int main(int argc, char *argv[]) {
    TestTree2List();
    return 0;
}
