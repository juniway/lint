#include <iostream>
#include <cstdio>
#include <queue>
#include <stack>

using namespace std;

class Node{
public:
    int item;
    Node *left;
    Node *right;

    Node() = default;
    Node(int num, Node* left=nullptr, Node* right=nullptr) : item(num), left(left), right(right){} // constructor
    // Node(int num, Node *l = 0, Node *r = 0) : item(num), left(l), right(r) {} // constructor
};


class Tree{
public:
    Tree() { root = nullptr; }
    Tree(Node *rt) : root(rt){}
    void level();
    void in_order();
    void pre_order();
    void post_order();
    void pre_order1();
    void del_node(Node*);

    // void inorder() { inorder(root);  }
    void insert(int num){ insert(root, num); }
    Node* search(int num);
    void del(Node* &);

    int maximum(){ return maximum(root); }
    int minimum() { return minimum(root); }
    int successor(int);
    Node* successor1(int);
    Node* predecessor(int);
    Node* parent(Node*) const;
    int get_height();

    bool symmetric();
    Node *root;
private:
    Node* search(Node *m, int num);
    void insert(Node *&, int num);      // CALL BY REFERENCE.
    void inorder(Node *) const;         // in_order traversal
    void visit(Node *p) const{
        printf("%d\t", p->item);
    }
    void transplant(Node *u, Node *v){
        Node *pa = parent(u);
        if(pa == nullptr)
            root = v;
        else if (u == pa->left)
            pa->left = v;
        else pa->right = v;
    }
    int minimum(Node *);
    int maximum(Node *);
};