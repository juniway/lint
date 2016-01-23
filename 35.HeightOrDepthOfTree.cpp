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

#include<iostream>
#include<queue>

using namespace std;

struct tree{
	int data;
	struct tree *left, *right;
};
void insert(tree*& root, int num){
    tree* newNode = (tree*)malloc(sizeof(struct tree)); // tree* root = new root
	newNode -> data = num;
	newNode -> left = newNode ->right = nullptr;
    
    tree *prev = root, *cur = root;

	while(cur!=nullptr){
		prev = cur;
		if(num <= root -> data)
			cur = cur -> left;
		else
			cur = cur -> right;
	}
    if(root==nullptr)
		root=newNode;
    else{
    	if(num <= prev->data)
    		prev->left = newNode;
    	else
    		prev->right = newNode;
    }
}

int getHeightOfTree_Recursive(tree* root){
	if (!root) 
		return 0;

	int leftHeight = getHeightOfTree(root -> left);
	int rightHeight = getHeightOfTree(root -> right);

	return 1 + std::max(leftHeight, rightHeight);
}


int getTreeHeight_Iterative(tree *root){
	if(root == nullptr)
		return 0;

	queue<tree*> qnode;
	qnode.push(root);

	int height = 0;
	while(true){
		int nodeCount = qnode.size();
		if(nodeCount == 0)
			return height;
		height++;

		// dequeue all nodes of current level and enqueue all node of next level
		while(nodeCount > 0){
			tree *tmp = qnode.front();
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



int main(){
	tree* root = nullptr;

	insert(root, 30);
	insert(root, 1);
	insert(root, 24);
	insert(root, 7);
	insert(root, 6);
	insert(root, 18);
	insert(root, 55);
	insert(root, 91);
	insert(root, 83);

	int height = getTreeHeight_Iterative(root);
	std::cout<<"the height of the tree is: "<<height<<std::endl;
	return 0;
}