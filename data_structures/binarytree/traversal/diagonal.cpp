#include <iostream>
#include <queue>
#include <map>
#include "../tree.hpp"

using namespace std;

void printDiagonal(Node *node, int diagonal, multimap<int, int>& map) {
    if (node == nullptr) return;
    map.insert(pair<int,int>(diagonal, node->data));
    printDiagonal(node->left, diagonal + 1, map);
    printDiagonal(node->right, diagonal, map);
}

void printDiagonal(Node *root) {
    multimap<int, int> dv_map;
    printDiagonal(root, 0, dv_map);
    int tmp = 0;
    for (auto dv: dv_map) {
        auto d = dv.first, v = dv.second;
        if (d != tmp) {
            cout << endl;
            tmp = d;
        }
        cout << v << " ";
    }
    cout << endl;
}

vector<int> printDiagonal1(Node *root) {
    queue<Node*> q;
    while (root) { // enqueue all right nodes
        q.push(root);
        root = root->right;
    }

    Node *sentinel = new Node(-1);
    q.push(sentinel);

    vector<int> res;
    while(q.size() != 1) {
        Node *tmp = q.front();
        q.pop();
        if (tmp != sentinel) {
            res.push_back(tmp->data);
            Node *node = tmp->left;
            while (node) { // enqueue all right nodes of node
                q.push(node);
                node = node->right;
            }
        } else {
            q.push(sentinel);
        }
    }

    return res;
}

Node* createBinaryTree() {
    Node *root = new Node(10);
    root->left = new Node(11);
    root->right = new Node(12);
    root->left->left = new Node(13);
    root->left->right = new Node(14);
    root->right->left = new Node(15);
    root->right->right = new Node(16);

    return root;
}

Node* createBinaryTree1() {
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    root->left->left->left = new Node(8);
    root->left->left->right = new Node(9);
    root->right->left->left = new Node(10);
    root->right->left->right = new Node(11);
    root->right->right->right = new Node(12);
    root->right->right->right->left = new Node(13);
    root->right->right->right->right = new Node(14);

    return root;
}

void testDiagonal() {
    auto root = createBinaryTree();
    printDiagonal(root);

    auto res = printDiagonal1(createBinaryTree1());
    for (auto v : res) cout << v << " "; cout << endl;
}

int main(int argc, char *argv[]) {
    testDiagonal();
    return 0;
}
