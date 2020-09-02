#include <iostream>
#include <vector>
#include <stack>
#include "../tree.hpp"
using namespace std;

void pre_order(Node *root) {
    stack<Node*> s;
    while(root || !s.empty()) {
        if (root) {
            cout << root->data << " ";
            s.push(root);
            root = root->left;
        } else {
            root = s.top() -> right;
            s.pop();
        }
    }
    cout << endl;
}

vector<int> preorder(Node *root) {
    if (root == nullptr) return {};
    vector<int> res;
    stack<Node*> s;
    s.push(root);
    while(!s.empty()) {
        root = s.top();
        s.pop();
        res.push_back(root->data);
        if (root->right) s.push(root->right);
        if (root->left) s.push(root->left);
    }
    return res;
}

vector<int> preorder1(Node *root) {
    vector<int> res;
    stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        root = s.top(); s.pop();
        if (root != nullptr) {
            res.push_back(root->data);
            s.push(root->right);
            s.push(root->left);
        }
    }

    return res;
}

void testPreorder() {
    Node *root = BuildSimpleBST();
    auto res = preorder1(nullptr);
    for (auto v : res) cout << v << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    testPreorder();
    return 0;
}
