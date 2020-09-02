#include <iostream>
#include <vector>
#include <stack>
#include "../tree.hpp"
using namespace std;

vector<int> postorderNary(Node *root) {
    vector<int> res;
    stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        root = s.top();
        res.push_back(root->data);
        if (root->left) s.push(root->left);
        if (root->right) s.push(root->right);
        s.pop();
    }

    reverse(res.begin(), res.end());
    return res;
}

vector<int> postorderNary1(Node *root) {
    vector<int> res;
    stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        root = s.top();
        res.push_back(root->data);
        if (root->left) s.push(root->left);
        if (root->right) s.push(root->right);
        s.pop();
    }

    reverse(res.begin(), res.end());
    return res;
}
