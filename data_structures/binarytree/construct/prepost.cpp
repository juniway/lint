#include <iostream>
#include <vector>
#include "../tree.hpp"

using namespace std;

Node* constructFromPrePost(vector<int>& pre, vector<int>& post, int L, int R, int postIndex) {
    if (postIndex < 0 || L > R) return nullptr;
    Node *head = new Node(post[postIndex]);
    if (L == R) return head;

    int M;
    for (M = L; M < pre.size(); M++)
        if (pre[M] == post[postIndex - 1]) break;
    head->left = constructFromPrePost(pre, post, L + 1, M - 1, postIndex - 1 - (R - M) - 1);
    head->right = constructFromPrePost(pre, post, M, R, postIndex - 1);
    return head;
}

Node* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    return constructFromPrePost(pre, post, 0, post.size() - 1, post.size() - 1);
}

void testConstrucPrePost() {
    vector<int> pre {1, 2, 4, 5, 3, 6, 7};
    vector<int> post {4, 5, 2, 6, 7, 3, 1};
    constructFromPrePost(pre, post);
}

int main(int argc, char *argv[]) {
    testConstrucPrePost();
    return 0;
}
