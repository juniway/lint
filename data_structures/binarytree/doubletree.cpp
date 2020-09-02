#include <algorithm>
#include <array> 
#include "tree.hpp"

void doubleTree(Node *root) {
    if (root == nullptr) return;
    doubleTree(root->left);
    doubleTree(root->right);

    Node *tmp = root->left;
    root->left = new Node(root->data);
    root->left->left = tmp;
}

bool sameTree(Node *rt1, Node *rt2) {
    if (rt1 == nullptr && rt2 == nullptr) return true;
    else if ((rt1 == nullptr && rt2 != nullptr) || (rt1 != nullptr && rt2 == nullptr)) return false;
    else {
        return rt1->data == rt2->data && sameTree(rt1->left, rt2->left) && sameTree(rt1->right, rt2->right);
    }
}

int countTrees(int n) {
    if (n <= 1) return 1;
    else {
        int sum = 0;
        int left, right, root;
        for (root = 1; root <= n; root++) {
            left = countTrees(root - 1);
            right = countTrees(n - root);
            sum += left * right;
        }

        return sum;
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

Node* BuildTree1() {
    Node *root = nullptr;
    constexpr int n = 8;
    std::array<int, n> a = {21, 8, 22, 14, 17, 10, 15, 1};
    for (auto i: a) {
        Insert(&root, i);
    }
    PrintBst(root);

    return root;
}

void TestDoubleTree() {
    Node *root = BuildTree();
    doubleTree(root);
    PrintBst(root);
}

void TestSameTree() {
    Node *root1 = BuildTree();
    Node *root2 = BuildTree1();
    cout << std::boolalpha << sameTree(root1, root2) << "\n";
}

void TestCountTree() {
    for (int i = 0; i < 10; i++) {
        std::cout << "count: " << countTrees(i) << "\n";
    }
}

int main(int argc, char *argv[]) {
    // TestDoubleTree();
    // TestSameTree();
    TestCountTree();
    return 0;
}
