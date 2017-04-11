#include <iostream>
#include <cstdio>
using namespace std;

class Node{
public:
	int item;
	Node *left;
	Node *right;
	
	Node(int num, Node *l = 0, Node*r = 0):item(num), left(l), right(r){} // constructor
};


class Tree{


// public methods
public:
	Tree() { root = NULL; }
	
	void inorder() { inorder(root);	}
	void insert(int num){ insert(root, num); }
	Node* search(int num){ return search(root, num); }
	void del(Node* &);
	Node* parent(Node* node) const{ // return node's parent
		Node *temp = root;
		while(temp->left!=node  &&  temp->right!=node) {
			if(node->item < temp->item) // binary search
				temp = temp->left;
			else
				temp = temp->right;
		}
		return temp;
	}
	int maximum(){ return maximum(root); }
	int minimum() { return minimum(root); }
	int successor(int);

private:
	Node *root;
	
	// private methods
	Node* search(Node *m, int num);
	void insert(Node *&, int num);		// CALL BY REFERENCE.
	void inorder(Node *) const;			// in_order traversal
	void visit(Node *p) const{
		printf("%d\t", p->item);
	}
	void transplant(Node *u, Node *v){
		Node *pa = parent(u);
		if(pa == 0)
			root = v;
		else if (u == pa->left)
			pa->left = v;
		else pa->right = v;
	}
	int minimum(Node *);
	int maximum(Node *);
};

int Tree::successor(int num) {
	Node *temp = search(num);
	if(temp->right) {
		return minimum(temp->right);
	}
	else{
		Node *y = parent(temp);
		while(y!=0  &&  temp == y->right) {
			temp = y;
			y = parent(temp);
		}
	return y->item;
	}
}

void Tree::inorder(Node *q) const {
	if(q!=NULL) {
		inorder(q->left);
		printf("%d  ", q->item);
		inorder(q->right);
	}
}


void Tree::insert(Node *&q, int num) {
	Node *temp = q, *prev = q;
	while(temp != NULL) {
		prev = temp;
		if(num < temp->item)
			temp = temp->left;
		else
			temp = temp->right;
	}

	if(!q) { q = new Node(num); }
	else{
		if(num < prev->item)
			prev->left = new Node(num);
		else
			prev->right = new Node(num);
	}
}


Node* Tree::search(Node *q, int num){
	while(q->item != num  &&  q!=0) {
		if(num < q->item)
			q = q->left;
		else
			q = q->right;
	}

	return q;
}


void Tree::del(Node* &q){

	if(!q->left)
		transplant(q, q->right);
	else if(!q->right)
		transplant(q, q->left);
	else{
		Node *succ = search( minimum(q->right) );
		if(parent(succ) != q) {
			transplant(succ, succ->right);
			succ->right = q->right;
		}
		transplant(q, succ);
		succ->left = q->left;     //transplant doesn't take care of left and right subtrees. It just establishes link with parent of one node to another.
	}
	delete q; q = 0;

}

int Tree::maximum(Node *node) {
	Node *temp = node;
	while(temp->right!=0) {
		temp = temp->right;
	}
	return temp->item;
}

int Tree::minimum(Node *node) {
	Node *temp = node;
	while(temp->left != 0) {
		temp = temp->left;
	}
	return temp->item;
}

// test program
int main(){
    
	Tree bst;
	bst.insert(1);
	bst.insert(2);
	bst.insert(3);
	bst.insert(4);
    bst.inorder();

	return 0;

}