#include <iostream>
#include <vector>
#include <queue>
#include "../tree.hpp"

using namespace std;

//http://leetcode.com/2010/09/printing-binary-tree-in-level-order.html

// use two queues
void levelOrder1(Node *root) {
	if (!root) return;
	queue<Node*> currentLevel, nextLevel;
	currentLevel.push(root);
	while (!currentLevel.empty()) {
		Node *currNode = currentLevel.front();
		currentLevel.pop();
		if (currNode != nullptr) {
			cout << currNode->data << " ";
			nextLevel.push(currNode->left);
			nextLevel.push(currNode->right);
		}
		if (currentLevel.empty()) {
			cout << endl;
			swap(currentLevel, nextLevel);
		}
	}
}

// use an extra variable to save the next level count of nodes
void leverOrder2(Node *root) {
    queue<Node*> q;
    q.push(root);
    int cur = 1, next = 0;
    while(!q.empty()) {
        Node *tmp = q.front();
        q.pop();
        --cur;
        if (tmp != nullptr) {
            cout << tmp->data << " ";
            q.push(tmp->left);
            q.push(tmp->right);
            next += 2;
        }
        if(cur == 0) {
            cout << endl;
            cur = next;
            next = 0;;
        }
    }
}

// use an extra node to signal the end of level
vector<vector<int>> levelOrder(Node *root) {
    vector<vector<int>> res;
    vector<int> level;
    queue<Node*> q;
    Node *node = new Node(0);
    q.push(root);
    q.push(node);
    while(!q.empty()) {
        Node *p = q.front();
        q.pop();
        if (p == node) {
            res.push_back(level);
            level.clear();
            if (!q.empty()) q.push(node);
        } else {
            level.push_back(p->data);
            if (p->left != nullptr) {
                q.push(p->left);
            }
            if (p->right != nullptr) {
                q.push(p->right);
            }
        }
    }

    return res;
}

void levelOrder0(Node *root) {
    if (root == nullptr) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        while (n--) {
            Node *p = q.front();
            q.pop();
            cout << p->data << " ";
            if (p->left) q.push(p->left);
            if (p->right) q.push(p->right);
        }
        cout << endl;
    }
}

// dfs
vector<vector<int>> levelOrder7(Node *root) {
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

void printLevel(vector<vector<int>>& levels) {
    for (auto i : levels) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}

void testLevel() {
    Node *root = BuildBst(10);
    auto res = levelOrder(root);
    printLevel(res);
}

void testLevel1() {
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
    // auto res = levelOrder(root);
    // printLevel(res);
    // levelOrder0(root);
    levelOrder7(root);
}

int main(int argc, char *argv[]) {
    testLevel1();
    return 0;
}




