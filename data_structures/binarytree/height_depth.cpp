#include <iostream>
#include <queue>
#include <stack>
#include "tree.hpp"

using namespace std;

/*
 * Find height without recursion:
 * We can use level order traversal to find height without recursion.
 * The idea is to traverse level by level. Whenever move down to a level,
 * increment height by 1 (height is initialized as 0). Count number of
 * nodes at each level, stop traversing when count of nodes at next level
 * is 0.
 */

// Method detail
/*
 * Create a queue.
 * Push root into the queue.
 * height = 0

 * loop
     	nodeCount = size of queue

 		// If number of nodes at this level is 0, return height
 		if nodeCount is 0
 			return Height;
 		else
 			increase Height;

 		// Remove nodes of this level and add nodes of next level
 		while(queue.empty()==false)
 			pop node from queue
			push its children to queue
			decrease nodeCount
		// At this point, queue has nodes of next level
*/

// Implementation


// recursive
int height(Node* root){
	if (!root)
		return 0;

	int leftHeight = height(root -> left);
	int rightHeight = height(root -> right);

	return 1 + std::max(leftHeight, rightHeight);
}

// iterative
int getHeight(Node *root){
	if(root == nullptr)
		return 0;

	queue<Node*> qnode;
	qnode.push(root);

	int height = 0;
	while(true){
		int nodeCount = qnode.size();
		if(nodeCount == 0)
			return height;
		height++;

		// dequeue all nodes of current level and enqueue all node of next level
		while(nodeCount > 0){
			Node *tmp = qnode.front();
			qnode.pop();
			if(tmp->left)
				qnode.push(tmp -> left);
			if(tmp->right)
				qnode.push(tmp -> right);
			nodeCount--;
		}
	}
	return height;
}


// iterative
int getHeight2(Node* root) {
    if (root == nullptr)
        return -1;

    queue<Node*> q;
    q.push(root);
    int height = -1;

    while (!q.empty()) {
        int size = q.size();
        height++;
        while (size > 0) {
            Node *treeNode = q.front();
            q.pop();
            if (treeNode->left != nullptr)
                q.push(treeNode->left);

            if (treeNode->right != nullptr)
                q.push(treeNode->right);
            size--;
        }
    }
    return height;
}

// bfs
int getHeight0(Node *root) {
    if (root == nullptr || (root->left == nullptr || root->right == nullptr)) return 0;

    queue<Node*> q;
    q.push(root);
    int h = -1;
    while(!q.empty()) {
        int n = q.size();
        while (n--) {
            Node *p = q.front();
            q.pop();
            if (p->left != nullptr) q.push(p->left);
            if (p->right != nullptr) q.push(p->right);
        }
        h++;
    }

    return h;
}

// dfs: preorder
int getHeight1(Node *root) {
    if (root == nullptr) return -1;
    if (root->left == nullptr || root->right == nullptr) return 0;
    int maxH = INT_MIN;
    stack<pair<Node*, int>> s;
    s.push(make_pair(root, 0));
    while(!s.empty()) {
        auto p = s.top();
        s.pop();
        maxH = max(maxH, p.second);
        if (p.first->right != nullptr) s.push(make_pair(p.first->right, p.second+1));
        if (p.first->left != nullptr) s.push(make_pair(p.first->left, p.second+1));
    }

    return maxH;
}

// DFS, inorder
int getHeight3(Node *root) {
    if(root == nullptr) return -1;
    if (root->left == nullptr || root->right == nullptr) return 0;
    int maxH = INT_MIN, deep = -1;
    stack<pair<Node*, int>> s;
    while(!s.empty() || root != nullptr) {
        if (root != nullptr) {
            s.push(make_pair(root, ++deep));
            root = root->left;
        } else {
            auto p = s.top();
            s.pop();
            deep = p.second;
            maxH = max(maxH, deep);
            root = p.first->right;
        }
    }

    return maxH;
}

void testGetHeight() {
	Node* root = nullptr;
	Insert(&root, 6);
	Insert(&root, 9);
	Insert(&root, 4);
	Insert(&root, 3);
	Insert(&root, 5);
	Insert(&root, 1);
	Insert(&root, 7);
	Insert(&root, 11);

	int ht = height(root);
	std::cout<<"the height of the tree is: "<< ht <<std::endl;
	ht = getHeight2(root);
	std::cout<<"the height of the tree is: "<< ht <<std::endl;

	ht = getHeight0(root);
	std::cout<<"the height of the tree is: "<< ht <<std::endl;
	ht = getHeight1(root);
	std::cout<<"the height of the tree is: "<< ht <<std::endl;
	ht = getHeight3(root);
	std::cout<<"the height of the tree is: "<< ht <<std::endl;

}

int main(){
    testGetHeight();
	return 0;
}
