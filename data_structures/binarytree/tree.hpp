#include <iostream>
#include <string>
#include <queue>
#include <cstdlib>
#include <ctime>

using std::string;
using std::queue;
using std::cout;

struct Node {
    int data;
    Node *left, *right;

    Node() = default;
    Node(int data):data(data),left(nullptr),right(nullptr) {}
};

// level print
static void inline PrintBst(Node *root, string leadsymbol="") {
    queue<Node*> q;
    int cur, next = 0;
    q.push(root);
    cur = 1;

    while(!q.empty()) {
        Node *tmp = q.front();
        q.pop();
        cur--;

        if (tmp != nullptr) {
            cout << tmp->data << " ";
            q.push(tmp->left);
            q.push(tmp->right);
            next += 2;
        }

        if (cur == 0) {
            cout << "\n";
            cur = next;
            next = 0;
        }
    }
}

static inline int Height(Node *root) {
    if (root == nullptr || (root->left == nullptr && root->right == nullptr)) return 0;
    return 1 + std::max(Height(root->left), Height(root->right));
}

static inline void Insert(Node **root_ref, int key) {
    Node *cur = *root_ref;
    Node *pre = cur;
    while (cur != nullptr) {
        pre = cur;
        if (key <= cur->data) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    if((*root_ref) == nullptr) {
        *root_ref = new Node(key);
    } else {
        if (key <= pre->data) {
            pre->left = new Node(key);
        } else {
            pre->right = new Node(key);
        }
    }
}

static inline void InsertRec(Node **root_ref, int key) {
    if (*root_ref == nullptr) *root_ref = new Node(key);
    else {
        if ((*root_ref)->data > key) InsertRec(&((*root_ref)->left), key);
        else InsertRec(&((*root_ref)->right), key);
    }
}

static inline Node* BuildBst(int n) {
    Node *root = nullptr;

    srand(time(nullptr));
    for (int i = 0; i < n; i++) {
        InsertRec(&root, rand()%100);
    }

    return root;
}

Node *BuildSimpleBST();

Node* BuildSimpleBST() {
    Node *root = nullptr;
    Insert(&root, 6);
    Insert(&root, 4);
    Insert(&root, 5);
    Insert(&root, 9);
    Insert(&root, 3);
    Insert(&root, 7);
    return root;
}

Node* Successor(Node *root, int key);
