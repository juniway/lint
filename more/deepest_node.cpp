#include<iostream>
#include<queue>

using namespace std;

struct Node{
    int data;
	Node* left, *right;
    Node(int value = -1) : data(value), left(nullptr), right(nullptr){}
};

class bst_tree{
public:
	bst_tree(){ root = nullptr; }
	void insert(int num) { 
		_insert(root, num); 
	}
	Node *get_deepest_node(Node* );
	Node *getRoot();
private:
	Node* root;
    void _insert(Node *&, int);
};

void bst_tree::_insert(Node*& q,int num){
	Node *temp = q, *prev = q;
	while(temp){
		prev = temp;
		if(num < temp->data)
			temp = temp->left;
		else
			temp = temp->right;
	}
	if(q == nullptr){
		q = new Node(num);
	}
	else{
		if(num < prev->data)
			prev->left = new Node(num);
		else
			prev->right = new Node(num);
	}
}

Node* bst_tree::get_deepest_node(Node* rt){
	if(rt == nullptr)
		return nullptr;
	queue<Node*> qnode;
	qnode.push(rt);		// push root node into the queue
	Node* tmp=nullptr;
	while(!qnode.empty()){
		tmp = qnode.front();
		qnode.pop();
		if(tmp->left) qnode.push(tmp->left);
		if(tmp->right) qnode.push(tmp->right);
	}

	return tmp;
}

Node* bst_tree::getRoot(){
    return root;
}

int main(){
	
	bst_tree bst;
	bst.insert(1);
	bst.insert(2);
	bst.insert(3);
	bst.insert(4);
    Node* tree_root = bst.getRoot();
    cout<<tree_root->data<<endl;
    Node* d = bst.get_deepest_node(tree_root);
    cout<<"the deepest node is :"<<d->data<<endl;
	return 0;

}
