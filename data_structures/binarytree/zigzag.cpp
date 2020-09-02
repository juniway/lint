#include <iostream>
#include <vector>
#include <queue>
#include "tree.hpp"

using namespace std;

vector<vector<int>> zigzagLevelOrder(Node *root) {
    vector<vector<int>> ans;
    function<void(Node*, int)> dfs = [&](Node *root, int level) {
        if (root == nullptr) return;
        if (ans.size() <= level) ans.push_back({});
        ans[level].push_back(root->data);
        dfs(root->left, level + 1);
        dfs(root->right, level + 1);
    };

    dfs(root, 0);
    for (int i = 1; i < ans.size(); i += 2) {
        reverse(ans[i].begin(), ans[i].end());
    }
    return ans;
}

vector<vector<int>> zigzagLevelOrder1(Node *root) {
    if (root == nullptr) return {};
    vector<vector<int>> ans;
    queue<Node*> q;
    q.push(root);
    bool change = true;
    while(!q.empty()) {
        vector<int> levelNodes;
        int n = q.size();
        while (n--) {
            Node *p = q.front();
            q.pop();
            if(change) {
                levelNodes.push_back(p->data);
            } else {
                levelNodes.insert(levelNodes.begin(), p->data);
            }
            if (p->left) q.push(p->left);
            if (p->right) q.push(p->right);
        }
        ans.push_back(levelNodes);
        change = !change;
    }
    return ans;
}

void testZigZag() {
    Node *root = nullptr;
    Insert(&root, 6);
    Insert(&root, 9);
    Insert(&root, 5);
    Insert(&root, 4);
    Insert(&root, 8);
    Insert(&root, 11);
    Insert(&root, 3);

    auto ans = zigzagLevelOrder1(root);
    for (auto x : ans) {
        for (auto y : x) cout << y << " ";
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    testZigZag();
    return 0;
}
