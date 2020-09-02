#include <iostream>
#include "tree.hpp"

using namespace std;

// DFS: preorder
void dfs(Node *root, int level, int& maxLevel, Node*& deepnode) {
    if (root == nullptr) return;
    if (maxLevel < level) {
        maxLevel = level;
        deepnode = root;
    }
    dfs(root->left, level + 1, maxLevel, deepnode);
    dfs(root->right, level + 1, maxLevel, deepnode);
}

Node* deepestNode(Node *root) {
    Node *deepnode;
    int maxLevel = -1;
    dfs(root, 0, maxLevel, deepnode);
    cout << "maxLevel: " << maxLevel << endl;
    return deepnode;
}

void testDeepestNode() {
    Node *root = nullptr;
    Insert(&root, 6);
    Insert(&root, 9);
    Insert(&root, 4);
    Insert(&root, 13);
    Insert(&root, 8);
    Insert(&root, 7);

    Node *deep = deepestNode(root);
    cout << "Deepest Node: " << deep->data << endl;
}

int main(int argc, char *argv[]) {
    testDeepestNode();
    return 0;
}
