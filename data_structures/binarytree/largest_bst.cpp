#include "tree.hpp"
using namespace std;

int size(Node* root) {
    if (root == nullptr) return 0;
    return 1 + size(root->left) + size(root->right);
}

bool isBst(Node *root, int left, int right) {
    if (root == nullptr) return true;
    if (root->data < left || root->data > right) return false;
    return isBst(root->left, left, root->data) && isBst(root->right, root->data, right);

}

bool isBst(Node *root) {
    return isBst(root, INT_MIN, INT_MAX);
}

// recursive
// Time: O(n^2)
// Space: O(h)

struct BstNode {
    int size, minVal, maxVal;
    BstNode(int size, int minv, int maxv) :
        size(size), minVal(minv), maxVal(maxv) {}
};

BstNode* findBstNode(Node *root) {
    if (root == nullptr) return new BstNode(0, INT_MIN, INT_MAX);
    BstNode *left = findBstNode(root->left);
    BstNode *right = findBstNode(root->right);
    BstNode *node ;
    if ((root->left == nullptr || left->maxVal < root->data) &&
            (root->right == nullptr || left->minVal > root->data)) {
        int minv = root->left ? left->minVal:root->data;
        int maxv = root->right ? right->maxVal:root->data;
        int size = left->size + right->size + 1;
        node =  new BstNode(size, minv, maxv);
    } else {
        node = new BstNode(max(left->size, right->size), INT_MIN, INT_MAX);

    }
    delete(left), delete(right);

    return node;
}

int largestBst(Node *root) {
    // if (isBst(root)) return size(root);
    // return max(largestBst(root->left), largestBst(root->right));
    return findBstNode(root)->size;
}


// bottom up

