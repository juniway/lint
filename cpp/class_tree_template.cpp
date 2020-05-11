#include<iostream>
using namespace std;


template <typename T>
class BinarySearchTree{
public:
    BinarySearchTree(){ rootNode = nullptr;};
    BinarySearchTree(int size);

    void insert(T);
    void search(T);
private:
    struct Node{
        T data;
        Node *leftchild, *rightchild;
    };

    Node *rootNode;
    int mSize;
};

template<typename T = int>
BinarySearchTree<T>::BinarySearchTree(int size){
    rootNode = nullptr;

    Node* cur = nullptr;
    for(int i = 0; i < size -1; ++i){
        Node* p = new Node;
        p->data = 0;
        p->next = nullptr;
        if(rootNode == nullptr){
            rootNode = p;
        }
        else{
            cur->next = p;
        }
        cur = p;
    }
}

template<typename T>
void BinarySearchTree<T>::insert(T newNum){
    Node *newNode = new Node;

    newNode->data = newNum;
    newNode->leftchild = newNode->rightchild = nullptr;

    Node *prev = nullptr;
    if(rootNode == nullptr)
        rootNode = newNode;
    else{
        Node *current =  rootNode;

        while(current){
            prev = current;
            if(newNode -> data <= current -> data)
                current = current -> leftchild;
            else
                current = current -> rightchild;
        }

        if(newNode -> data <= prev->data)
            prev -> leftchild = newNode;
        else
            prev -> rightchild = newNode;
    }
}

template< typename T>
void BinarySearchTree<T>::search(T toFindNum){
    Node *current = rootNode;

    bool rootflag = false;
    if(current->data == toFindNum){
        rootflag = true;
        cout<<"Found the element, it is root."<<endl;
    }
    else{
        while(current && current->data != toFindNum){
            //parent = current;
            if(current->data >= toFindNum)
                current = current->leftchild;
            else
                current = current->rightchild;
        }
        if(current && !rootflag)
            cout<<"Found the element!"<<endl;
        else
            cout<<"Couldn't find the element"<<endl;
    }
}

int main(){
    BinarySearchTree<int> b;
    b.insert(7);
    b.search(7);

    BinarySearchTree<char> c;
    c.insert('k');
    c.search('v');

    return 0;
}