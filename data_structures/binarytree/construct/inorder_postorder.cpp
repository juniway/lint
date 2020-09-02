#include <iostream>
#include <vector>
#include <unordered_map>
#include "../tree.hpp"
using namespace std;

Node* buildTree(vector<int>& inorder, vector<int>& postorder, int L, int R, int postIndex) {
    if (postIndex > R || L > R) return nullptr;

    Node* head = new Node(postorder[postIndex]);
    if (L == R) return head;

    int M;
    for (M = L; M <= R; M++)
        if (inorder[M] == head->data) break;

    head->left = buildTree(inorder, postorder, L, M - 1, postIndex - 1 - R + M);
    head->right = buildTree(inorder, postorder, M + 1, R, postIndex - 1);

    return head;
}

Node *buildTree(vector<int>& inorder, vector<int>& postorder, int L, int R, int postIndex, unordered_map<int, int> m) {
    if (L > R) return nullptr;
    Node * head = new Node(postorder[postIndex]);
    if (L == R) return head;

    int M = m[head->data];
    head->left = buildTree(inorder, postorder, L, M - 1, postIndex - 1 - (R - M), m);
    head->right = buildTree(inorder, postorder, M + 1, R, postIndex - 1, m);

    return head;
}

TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post, int L, int R, int postIndex) {
    if (postIndex < 0 || L > R) return nullptr;
    TreeNode *head = new TreeNode(post[postIndex]);
    if (L == R) return head;

    int M;
    for (M = L; M < pre.size(); M++)
        if (pre[M] == post[postIndex - 1]) break;
    head->left = constructFromPrePost(pre, post, L + 1, M - 1, postIndex - 1 - (R - M));
    head->right = constructFromPrePost(pre, post, M + 1, R, postIndex - 1);
    return head;
}

TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    return constructFromPrePost(pre, post, 0, post.size() - 1, post.size() - 1);
}

Node* buildTree(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int, int> m;
    for (int i = 0; i < inorder.size(); i++) {
        m[inorder[i]] = i;
    }
    return buildTree(inorder, postorder, 0, inorder.size() - 1, inorder.size() - 1, m);
}

void testBuildTree() {
    // vector<int> inorder {9, 3, 15, 20, 7};
    // vector<int> postorder {9, 15, 7, 20, 3};
    vector<int> inorder {-1};
    vector<int> postorder {-1};

    buildTree(inorder, postorder);
}

int main(int argc, char *argv[]) {
    testBuildTree();
    return 0;
}
