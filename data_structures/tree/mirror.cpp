#include <array>
#include "tree.hpp"

void inverse(Node *root) {
    if (root == nullptr) return;
    if (root->left == nullptr) {
        root->left = root->right;
        root->right = nullptr;
    } else if (root->right == nullptr) {
        root->right = root->left;
        root->left = nullptr;
    } else {
        inverse(root->right);
        inverse(root->left);
        Node *tmp = root->left;
        root->left = root->right;
        root->right = tmp;
    }
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

void TestInverse() {
    Node *root = BuildTree();
    inverse(root);
    PrintBst(root);
}

int main(int argc, char *argv[]) {
    TestInverse();
    return 0;
}
