#include "tree.hpp"
#include <array>
#include <iostream>

int maxDepthRec(Node *root) {
    if (root == nullptr) return 0;
    return 1 + std::max(maxDepthRec(root->left), maxDepthRec(root->right));
}

int minValue(Node *root) {
    while(root->left != nullptr) {
        root = root->left;
    }
    return root->data;
}

bool hasPathSum(Node *root, int sum) {
    if (root == nullptr) return false;
    if (root->left == nullptr && root->right == nullptr && root->data == sum)
        return true;
    if (hasPathSum(root->left, sum-(root->data)) || hasPathSum(root->right, sum-(root->data)))
        return true;

    return false;
}

bool hasPathSum1(Node *root, int sum) {
    if (root == nullptr) return sum == 0;
    sum = sum - (root->data);
    return hasPathSum1(root->left, sum) || hasPathSum1(root->right, sum);
}

void printArray(int path[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

void printPathsRec(Node *root, int path[], int pathLen) {
    if (root == nullptr) return;
    path[pathLen] = root->data;
    pathLen++;

    if (root->left == nullptr && root->right == nullptr) {
        printArray(path, pathLen);
    } else {
        printPathsRec(root->left, path, pathLen);
        printPathsRec(root->right, path, pathLen);
    }
}

void printAllPaths(Node *root) {
    int path[1000];
    printPathsRec(root, path, 0);
}


template<std::size_t SIZE>
Node* BuildTree(const std::array<int, SIZE> &a) {
    Node *root = nullptr;
    for (auto i : a) {
        Insert(&root, i);
    }
    PrintBst(root);

    return root;
}

void TestMaxDepth() {
    constexpr int n = 8;
    std::array<int, n> a = {20, 8, 22, 14, 17, 10, 15, 1};
    Node *root = BuildTree(a);
    std::cout << maxDepthRec(root) << std::endl;
}

void TestMinValue() {
    constexpr int n = 8;
    std::array<int, n> a = {20, 8, 22, 14, 17, 10, 15, 1};
    Node *root = BuildTree(a);
    std::cout << "Min Value: " << minValue(root) << "\n";
}

void TestHasPathSum() {
    std::array<int, 8> a = {29, 11, 52, 74, 19};
    Node *root = BuildTree(a);
    for (auto i : a) {
        std::cout << i << ": " << std::boolalpha << hasPathSum1(root, i) << "\n";
    }
}

void TestPrintPaths() {
    constexpr int n = 8;
    std::array<int, n> a = {20, 8, 22, 14, 17, 10, 15, 1};
    Node *root = BuildTree(a);
    printAllPaths(root);
}

int main(int argc, char *argv[]) {
    // TestMaxDepth();
    // TestMinValue();
    // TestHasPathSum();
    TestPrintPaths();
    return 0;
}
