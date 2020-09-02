#include <iostream>
#include <vector>
#include <stack>
#include "../tree.hpp"
using namespace std;

void in_order(Node *root) {
    stack<Node*> s;
    while(!s.empty() || root != nullptr) {
        if(root != nullptr){
            s.push(root);
            root = root->left;
        }
        else {
            Node *tmp = s.top();
            cout << tmp->data << " ";
            s.pop();
            root = tmp->right;
        }
    }
    cout << endl;
}

vector<int> inorder(Node *root) {
    if (root == nullptr) return {};
    vector<int> res;
    stack<Node*> s;
    s.push(root);
    while(!s.empty()) {
        root = s.top();
        if(root->left != nullptr) {
            s.push(root->left);
            root->left = nullptr;
        } else {
            res.push_back(root->data);
            s.pop();
            if (root->right)
                s.push(root->right);
        }
    }

    return res;
}

void testInorder() {
    Node *root = nullptr;
    Insert(&root, 5);
    Insert(&root, 9);
    Insert(&root, 3);
    Insert(&root, 7);
    Insert(&root, 2);
    Insert(&root, 4);
    in_order(root);
    // auto res = inorder(root);
    //
    // for (auto x : res) cout << x << " ";
    // cout << endl;
}

int main(int argc, char *argv[]) {
    testInorder();
    return 0;
}
