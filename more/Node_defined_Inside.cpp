#include<iostream>
using namespace std;


template <typename T>
class BinarySearchTree{
    public:
        BinarySearchTree(){ rootNode = nullptr;}; // constructor
		~BinarySearchTree(){ }; // constructor
        void insert(T);
        void search(T);
    private:
        struct Node{
            Node *leftchild, *rightchild;
            T data;
        } *rootNode;
};

template<typename T>
void BinarySearchTree<T>::insert(T newNum){
    cout<<"Insert: "<<newNum<<endl;
    Node *newNode = new Node;

    newNode->data = newNum;
    newNode->leftchild = newNode->rightchild = nullptr;

    Node *prev = nullptr;
    if(rootNode == nullptr)
        rootNode = newNode;
    else{
        Node *current =  rootNode;

        while(current != nullptr){
            prev = current;
            if(newNode->data <= current->data)
                current = current->leftchild;
            else
                current = current->rightchild;
        }

        if(newNode->data <= prev->data)
            prev->leftchild = newNode;
        else
            prev->rightchild = newNode;
    }
}

template< typename T>
void BinarySearchTree<T>::search(T toFindNum){
    Node *current = rootNode;
//  Node *parent = rootNode;
    bool rootflag = false;
    if(current->data == toFindNum){
        rootflag = true;
        cout<<"Found the element, it is root."<<endl;
    }
    else{
        while(current != nullptr && current->data != toFindNum){
            //parent = current;
            if(current->data >= toFindNum)
                current = current->leftchild;
            else
                current = current->rightchild;
        }
        if(current!=nullptr && !rootflag)
            cout<<"Found the element!"<<endl;
        else
            cout<<"Couldn't find the element"<<endl;
    }
}

int main(){
    BinarySearchTree<int> b;
    b.insert(30);
    b.insert(1);
    b.insert(24);
    b.insert(7);

    b.search(24);

    BinarySearchTree<char> c;
    c.insert('k');
    c.search('v');

    return 0;
}