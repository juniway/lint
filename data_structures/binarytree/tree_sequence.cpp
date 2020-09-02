#include <iostream>
#include <deque>
#include <vector>
#include "tree.hpp"
using namespace std;

void printVector(vector<int>& v) {
    for (auto x : v) cout << x << " ";
    cout << endl;
}

class Solution {
public:
    vector<vector<int>> BSTSequences(Node* root) {
        if (!root) return {{}};
        deque<Node*> q;
        q.push_back(root);
        vector<int> buf;
        vector<vector<int> > ans;
        Inner(q, buf, ans);
        return ans;
    }
    void Inner(deque<Node*> &q, vector<int> &buf, vector<vector<int> > &ans) {
        cout << "~~~~~~~~~~~~~~~~~~~~" << endl;
        if (q.empty()) {
            cout << "q is empty()\n";
            ans.push_back(buf);
            cout << endl;
            return;
        }
        int size = q.size();
        cout << "size: " << size << endl;
        while (size--) {
            Node *r = q.front(); q.pop_front();

            cout << "before push: r->data: " << r->data << endl;
            printVector(buf);
            buf.push_back(r->data);
            cout << "after push: r->data: " << r->data << endl;
            printVector(buf);
            int children = 0;
            if (r->left) {
                ++children;
                q.push_back(r->left);
            }
            if (r->right) {
                ++children;
                q.push_back(r->right);
            }
            Inner(q, buf, ans);
            cout << "children: " << children << endl;
            while (children--) {
                q.pop_back();
            }
            cout << "before pop, r->data: " << r->data << endl;
            q.push_back(r);
            buf.pop_back();
            cout << "after pop r->data: " << r->data << endl;
            printVector(buf);

        }
        cout << endl;
    }
};

Node* buildtree() {
    Node *root = nullptr;
    Insert(&root, 5);
    Insert(&root, 2);
    Insert(&root, 8);
    // Insert(&root, 4);
    // Insert(&root, 1);
    // Insert(&root, 3);
    // Insert(&root, 7);
    // Insert(&root, 9);
    return root;
}

void testBSTSequences() {
    Node *root = buildtree();
    Solution sol;
    sol.BSTSequences(root);
}

int main(int argc, char *argv[]) {
    testBSTSequences();
    return 0;
}
