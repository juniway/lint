#include <iostream>
#include <queue>
#include "tree.hpp"

using namespace std;

// bfs
int deepestLeavesSum0(Node *root) {
    if (root == nullptr) return 0;
    int sum = 0;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        sum = 0;
        while (n--) {
            Node *nd = q.front();
            q.pop();
            sum += nd->data;
            if (nd->left) q.push(nd->left);
            if (nd->right) q.push(nd->right);
        }
    }

    return sum;
}

// bfs + vector
int deepestLeavesSum(Node *root) {
    if (root == nullptr) return 0;
    int sum;
    vector<Node*> q;
    q.push_back(root);
    while(!q.empty()) {
        sum = 0;
        vector<Node*> q1;
        for (auto x : q) {
            sum += x->data;
            if (x->left) q1.push_back(x->left);
            if (x->right) q1.push_back(x->right);
        }
        swap(q, q1);
    }
    return sum;
}

// dfs
int getDepth(Node *root) {
    if (root == nullptr) return 0;
    return 1 + max(getDepth(root->left), getDepth(root->right));
}

void findSum(Node *root, int maxDepth, int currentDepth, int &sum) {
    if (root == nullptr) return;
    if (currentDepth == maxDepth)
        sum += root->data;
    findSum(root->left, maxDepth, currentDepth + 1, sum);
    findSum(root->right, maxDepth, currentDepth + 1, sum);
}

int deepestSum(Node *root) {
    int sum = 0;
    int maxDepth = getDepth(root);
    findSum(root, maxDepth, 1, sum);
    return sum;
}

// dfs 2
void findSum1(Node *root, int& maxDepth, int currentDepth, int &sum) {
    if (root == nullptr) return;

    if (currentDepth > maxDepth) {
        sum = 0;
        maxDepth = currentDepth;
    }

    if (currentDepth == maxDepth) {
        sum += root->data;
    }

    findSum1(root->left, maxDepth, currentDepth + 1, sum);
    findSum1(root->right, maxDepth, currentDepth + 1, sum);
}

int deepestSum1(Node *root) {
    int sum = 0, maxDepth = 1, currentDepth = 1;
    findSum1(root, maxDepth, currentDepth, sum);
    return sum;
}

void testDeepestLeavesSum() {
    Node *root = nullptr;
    Insert(&root, 6);
    Insert(&root, 4);
    Insert(&root, 9);
    Insert(&root, 8);
    Insert(&root, 7);
    Insert(&root, 13);
    Insert(&root, 10);

    cout << deepestLeavesSum(root) << endl;
    cout << deepestLeavesSum1(root) << endl;
    cout << deepestSum(root) << endl;
    cout << deepestSum1(root) << endl;
}

int main(int argc, char *argv[]) {
    testDeepestLeavesSum();
    return 0;
}
