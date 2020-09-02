#include <iostream>
#include <vector>
#include "../tree.hpp"

using namespace std;


Node* bstFromPreorder(vector<int>& preorder, int L, int R) {
    if (L > R) return nullptr;
    Node *head = new Node(preorder[L]);
    if (L == R) return head;
    int M = L;
    for(int i = L + 1; i <= R; i++)
        if (preorder[i] < preorder[L])
            M = i;
    head->left = bstFromPreorder(preorder, L + 1, M);
    head->right = bstFromPreorder(preorder, M + 1, R);

    return head;
}

Node* bstFromPreorder(vector<int>& preorder) {
    return bstFromPreorder(preorder, 0, preorder.size() - 1);
}

void testPre() {
    vector<int> pre{8, 5, 1, 7, 10, 12};
    bstFromPreorder(pre);
}

int main(int argc, char *argv[]) {
    testPre();
    return 0;
}
