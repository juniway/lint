#include<iostream>
#include<queue>
using namespace std;

template <typename T>
struct Node{
	Node<T> *leftchild, *rightchild;
	T data;
};

template <typename T>
class BinarySearchTree{
public:
    BinarySearchTree():rootNode(nullptr){ }
    void insert(T);
	void search(T);
    Node<T>* get_deepest_node(Node<T>* );
private:


	Node<T> *rootNode;
};

template<typename T>
void BinarySearchTree<T>::insert(T newNum){
	cout<<"Insert: "<<newNum<<endl;
	Node<T> *newNode = new Node<T>;

	newNode->data = newNum;
	newNode->leftchild = newNode->rightchild = nullptr;

	Node<T> * prev = nullptr;
	if(rootNode == nullptr)
		rootNode = newNode;
	else{
		Node<T> *current =  rootNode;

		while(current){
			prev = current;
			if(newNode->data <= current->data)
				current = current->leftchild;
			else
				current = current->rightchild;
		}

		if(newNode-> data <= prev->data)
			prev->leftchild = newNode;
		else
			prev->rightchild = newNode;
	}
}

template< typename T>
void BinarySearchTree<T>::search(T toFindNum){
	Node<T> *current = rootNode;
//	Node *parent = rootNode;
	bool rootflag = false;
	if(current->data == toFindNum){
		rootflag = true;
		cout<<"Found the element, it is root."<<endl;
	}
    else{
    	while(current && current -> data != toFindNum){
    		//parent = current;
    		if(current -> data >= toFindNum)
    			current = current -> leftchild;
    		else
    			current = current -> rightchild;
    	}
    	if(current && !rootflag)
    		cout<<"Found the element!"<<endl;
        else
            cout<<"Couldn't find the element"<<endl;
    }
}

template<typename T>
Node<T>* BinarySearchTree<T>::get_deepest_node(Node<T>* root){
    if(root==nullptr)
        return nullptr;
    queue<Node<T>*> qnode;
    qnode.push(root);
    
    Node<T>* current;
    while(!qnode.empty()){
        current = qnode.front();
        qnode.pop();
        if(current->left) qnode.push(current->left);
        if(current->right) qnode.push(current->right);
    }
    return current;
}

int main(){
	BinarySearchTree<int> b;
	b.insert(7);
    b.insert(5);
    b.insert(11);
	b.search(10);

	BinarySearchTree<char> c;
	c.insert('k');
	c.search('v');

	return 0;
}