#include <iostream>
#include <vector>
#include <map>
#include "tree.hpp"

using namespace std;

void preorder(Node *root, int level, map<int, vector<int>>& map) {
    if (root == nullptr) return;
    map[level].push_back(root->data);
    preorder(root->left, level + 1, map);
    preorder(root->right, level + 1, map);
}

// DFS: preorder + map
map<int, vector<int>> levelOrder(Node *root) {
    map<int, vector<int>> map;
    preorder(root, 0, map);
    return map;
}

// DFS: level index
vector<vector<int>> levelOrder1(Node *root) {
    vector<vector<int>> ans;
    function<void(Node*, int)> dfs = [&](Node *root, int level) {
        if (root == nullptr) return;
        if (ans.size() <= level) ans.push_back({});
        ans[level].push_back(root->data);
        dfs(root->left, level + 1);
        dfs(root->right, level + 1);
    };

    dfs(root, 0);
    return ans;
}

void testLevelOrder() {
	Node* root = nullptr;
	Insert(&root, 30);
	Insert(&root, 1);
	Insert(&root, 24);
	Insert(&root, 7);
	Insert(&root, 6);
	Insert(&root, 18);
	Insert(&root, 55);
	Insert(&root, 91);
	Insert(&root, 83);
    auto res = levelOrder(root);

    for (auto i : res) {
        for (auto j : i.second) cout << j << " ";
        cout << endl;
    }

    auto res1 = levelOrder1(root);
    for(auto row : res1) {
        for (auto col : row) cout << col << " ";
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    testLevelOrder();
    return 0;
}
