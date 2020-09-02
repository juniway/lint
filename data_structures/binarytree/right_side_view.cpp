#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include "tree.hpp"

using namespace std;

struct HashByLevelNumber {
public:
    size_t operator()(pair<Node*, int> p) const {
        return std::hash<int>()(p.second);
    }
};

struct EqualBySize {
public:
    bool operator()(pair<Node*, int> p1, pair<Node*, int> p2) const {
        return p1.second == p2.second;
    }
};

vector<int> rightSideView(Node *root) {
    if (root == nullptr) return {};
    unordered_set<pair<Node*, int>, HashByLevelNumber, EqualBySize> visited;
    stack<pair<Node*, int>> s;
    s.push(make_pair(root, 0));

    vector<int> res;
    while(!s.empty()) {
        auto nd_i = s.top();
        s.pop();
        if (visited.find(nd_i) == visited.end()) { // visit one level at one time
            visited.insert(nd_i);
            res.push_back(nd_i.first->data);
        }
        if (nd_i.first->left)
            s.push(make_pair(nd_i.first->left, nd_i.second + 1));
        if (nd_i.first->right)
            s.push(make_pair(nd_i.first->right, nd_i.second + 1));
    }

    return res;
}

void testRightSideView() {
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(5);
    root->right->right = new Node(4);

    auto res = rightSideView(root);
    for (auto x : res) cout << x << " ";
    cout << endl;

}

int main(int argc, char *argv[]) {
    testRightSideView();
    return 0;
}
