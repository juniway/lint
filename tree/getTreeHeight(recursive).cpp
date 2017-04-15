#include<iostream>

struct tree{
    int data;
	struct tree *left, *right;
};

void insert(tree*& root, int num){
	tree *newNode = (tree *)malloc(sizeof(struct tree)); // tree* root = new root
	newNode->data = num;
	newNode->left = newNode->right = nullptr;
    
    tree *prev = root;
    tree *cur = root;

	while(cur!=nullptr){
		prev = cur;
		if(num <= root -> data)
			cur = cur -> left;
		else
			cur = cur -> right;
	}
    if(root==nullptr) // if the input tree is empty, create a new tree
		root=newNode;
    else{
    	if(num <= prev->data)
    		prev->left = newNode;
    	else
    		prev->right = newNode;
    }
}

int getHeightOfTree(tree* root){
	if (root == nullptr) 
		return 0;

	int leftHeight = getHeightOfTree(root->left);
	int rightHeight = getHeightOfTree(root->right);

	return 1 + std::max(leftHeight, rightHeight);
}

int main(){
	tree* root = nullptr;

	insert(root, 2);
	insert(root, 1);
	insert(root, 3);
	insert(root, 7);
	insert(root, 6);
	insert(root, 21);
	insert(root, 55);
	insert(root, 91);
	insert(root, 83);

	int height = getHeightOfTree(root);
	std::cout<<"the height of the tree is: "<<height<<std::endl;
	return 0;
}