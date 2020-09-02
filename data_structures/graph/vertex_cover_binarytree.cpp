#include <iostream>
#include <unordered_map>
#include "../binarytree/tree.hpp"
using namespace std;

// Binary Tree's Vertext Cover
// recursive
int findVertextCoverBinaryTree(Node *root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 0;

    // include root
    int include = 1 + findVertextCoverBinaryTree(root->left) + findVertextCoverBinaryTree(root->right);
    int exclude = 0;
    if (root->left)
        exclude += 1 + findVertextCoverBinaryTree(root->left->left) + findVertextCoverBinaryTree(root->left->right);
    if (root->right)
        exclude += 1 + findVertextCoverBinaryTree(root->right->left) + findVertextCoverBinaryTree(root->right->right);
    return min(include, exclude);
}

// memoization
int findVertextCoverBinaryTree(Node *root, unordered_map<Node*, int> m) {
    if (root == nullptr) return 0;
    if (m[root] != 0) return m[root];
    int include = 1 + findVertextCoverBinaryTree(root->left) + findVertextCoverBinaryTree(root->right);
    int exclude = 0;
    if (root->left)
        exclude += 1 + findVertextCoverBinaryTree(root->left->left) + findVertextCoverBinaryTree(root->left->right);
    if (root->right)
        exclude += 1 + findVertextCoverBinaryTree(root->right->left) + findVertextCoverBinaryTree(root->right->right);
    m[root] = min(include, exclude);
    return m[root];
}

void testFindVertextCoverBinaryTree() {
    Node *root = new Node(20);
    root->left = new Node(8);
    root->left->left = new Node(4);
    root->left->right = new Node(12);
    root->left->right->left = new Node(10);
    root->left->right->right = new Node(14);
    root->right = new Node(22);
    root->right->right = new Node(25);

    unordered_map<Node*, int> m;
    // cout << findVertextCoverBinaryTree(root) << endl;
    cout << findVertextCoverBinaryTree(root, m) << endl;
}

int main(int argc, char *argv[]) {
    testFindVertextCoverBinaryTree();
    return 0;
}
