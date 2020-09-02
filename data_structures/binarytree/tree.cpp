#include "tree.hpp"

bool Lookup(Node *root, int key) {
    while(root != nullptr) {
        if (root->data == key) return true;
        else if (root->data > key) root = root->left;
        else root = root->right;
    }
    return false;
}

bool LookupRec(Node *root, int key) {
    if (root == nullptr) return false;
    if (key == root->data) return true;
    else if (key < root->data) {
        return Lookup(root->left, key);
    } else {
        return Lookup(root->right, key);
    }
}

int main(int argc, char *argv[]) {
    Node *root = BuildBst(10);
    PrintBst(root);
    cout << Height(root) << "\n";
    cout << std::boolalpha << Lookup(root, 10) << "\n";
    return 0;
}
