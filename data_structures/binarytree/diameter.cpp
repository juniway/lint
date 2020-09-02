#include <iostream>
#include <vector>
#include "tree.hpp"
using namespace std;

int height(Node *root) {
    if (root == nullptr) return -1;
    if (root->left == nullptr && root->right == nullptr) return 0;
    return 1 + max(height(root->left), height(root->right));
}

int diameter(Node *root) {
    if (root == nullptr) return 0;
    int lheight = height(root->left);
    int rheight = height(root->right);
    int ldiameter = diameter(root->left);
    int rdiameter = diameter(root->right);
    return max(lheight + rheight + 1, max(diameter(root->left), diameter(root->right)));
}

int depth(Node *root) {
    if (root == nullptr) return 0;
    int L = depth(root->left);
    int R = depth(root->right);
    ans = max(ans, L + R + 1);
    return max(L, R) + 1;
}

int diameter(Node *root) {
    int ans = 1;
    depth(root);
    return ans - 1;
}
