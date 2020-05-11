#include <stack>
#include <queue>
#include <iostream>
#include "tree.hpp"

using std::stack;
using std::queue;

// left > root > right
queue<Node*> InOrder(Node *root) {
    stack<Node*> s;
    queue<Node*> q;
    Node *cur = root;
    
    while(!s.empty() || cur != nullptr) {
        if (cur != nullptr) {
            s.push(cur);
            cur = cur->left;
        } else {
            Node *tmp = s.top();
            q.push(tmp);
            s.pop();
            if(tmp->right != nullptr) {
                cur = tmp->right;
            }
        }
    }

    cout << "q.size() = " << q.size() << "\n";

    return q;
}

// right > left > root
queue<Node*> PostOrder(Node *root) {
    stack<Node*> s;
    queue<Node*> q;
    Node *cur = root, *visited = nullptr;

    while(!s.empty() || cur != nullptr) {
        if (cur != nullptr) {
            s.push(cur);
            cur = cur->left;
        } else {
            Node *tmp = s.top();
            if (tmp->right != nullptr && tmp->right != visited) {
                cur = tmp->right;
            } else {
                q.push(tmp);
                visited = tmp;
                s.pop();
            }
        }
    }

    return q;
}

void InOrderRec(Node *root, queue<Node*> & q) {
    if (root == nullptr) return;
    if (root->left != nullptr) InOrderRec(root->left, q);
    q.push(root);
    if (root->right != nullptr) InOrderRec(root->right, q);
}

void PostOrderRec(Node *root, queue<Node*> & q) {
    if (root == nullptr) return;
    if (root->right != nullptr) PostOrderRec(root->right, q);
    if (root->left != nullptr) PostOrderRec(root->left, q);
    q.push(root);
}

queue<Node*> PreOrder(Node *root) {
    if (root == nullptr) return queue<Node*>();
    queue<Node*> q;
    stack<Node*> s;
    s.push(root);
    while(!s.empty()) {
        Node *tmp = s.top();
        s.pop();
        q.push(tmp);
        if(tmp->right != nullptr) s.push(tmp->right);
        if(tmp->left != nullptr) s.push(tmp->left);
    }

    return q;
}

queue<Node*> PostOrder2(Node *root) {
    if(root == nullptr) return queue<Node*>();
    stack<Node*> s, s1;
    s.push(root);
    while(!s.empty()) {
        Node *tmp = s.top();
        s.pop();
        s1.push(tmp);
        if (tmp->left != nullptr) s.push(tmp->left);
        if (tmp->right != nullptr) s.push(tmp->right);
    }
    
    queue<Node*> q;
    while(!s1.empty()) {
        q.push(s1.top());
        s1.pop();
    }
    return q;
}

void PrintQueue(queue<Node*> q) {
    while(!q.empty()) {
        cout << q.front()->data << " ";
        q.pop();
    }

    cout << "\n";
}

void TestInOrder() {
    Node *root = BuildBst(12);
    PrintBst(root);
    auto q = InOrder(root);
    PrintQueue(q);
}

void TestInOrderRec() {
    Node *root = BuildBst(12);
    PrintBst(root);
    queue<Node*> q;
    InOrderRec(root, q);
    PrintQueue(q);
}

void TestPostOrder() {
    Node *root = BuildBst(12);
    PrintBst(root);
    auto q = PostOrder(root);
    PrintQueue(q);
}

void TestPostOrderRec() {
    Node *root = BuildBst(12);
    PrintBst(root);
    queue<Node*> q;
    PostOrderRec(root, q);
    PrintQueue(q);
}

void TestPreOrder() {
    Node *root = BuildBst(5);
    PrintBst(root);
    queue<Node*> q = PreOrder(root);
    PrintQueue(q);
}

void TestPreOrder2() {
    Node *root = BuildBst(5);
    PrintBst(root);
    queue<Node*> q = PostOrder2(root);
    PrintQueue(q);
}

int main(int argc, char *argv[]) {
    // TestPostOrder();
    // TestInOrderRec();
    // TestPostOrderRec();
    // TestPreOrder();
    TestPreOrder2();
    return 0;
}
