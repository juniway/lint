#include "tree.hpp"

Node *findKey(Node *root, int key){
    Node *cur = root;
    while(cur != nullptr) {
        if (cur->data == key) return cur;
        else if(cur->data < key) cur = cur->right;
        else cur = cur->left;
    }

    return cur;
}

Node **parent(Node **root, Node *node) {
    Node **p = root;
    while(node != (*p)->left && node != (*p)->right) {
        if ((*p)->data < node->data) {
            *p = (*p)->right;
        } else {
            *p = (*p)->left;
        }
    }

    return p;
}

Node *transplant(Node **root, Node *u, Node *v) {
    Node **p = parent(root, u);
    cout << (*p)->data << "\n";
    if (*p == nullptr) *p = v;
    else if ((*p)->left == u) {
        printf("00000000000");
        (*p)->left = v;
        printf("@@@ %d\n", (*p)->left->data);
    } else {
        printf("8888");
        (*p)->right = v;
    }
    delete u;
    u = nullptr;

    return *p;
}

void DeleteNode(Node **root, int key) {
    Node *q = findKey(*root, key);
    cout << q->data << "\n";

    if (q->left == nullptr) {
        cout << "111111\n";
        Node *p = transplant(root, q, q->right);
        cout << p->data << " ~~~~ \n";
        if (p->left != nullptr)
            cout << p->left->data << "lefttt\n";
        if(p->right != nullptr)
            cout << p->right->data << "righttt\n";
    } else if (q->right == nullptr) {
        cout << "222222\n";
        transplant(root, q, q->left);
    } else {
        Node *succ = Successor(*root, q->data);
        if (q != succ) {
            transplant(root, succ, succ->right);
            succ->right = q->right;
        }
        transplant(root, q, succ);
        succ->left = q->left;
    }

    delete q;
    q = nullptr;
}

void TestDeleteNode() {
    Node *root = nullptr;
    Insert(&root, 20);
    Insert(&root, 8);
    Insert(&root, 12);
    Insert(&root, 22);
    Insert(&root, 4);
    Insert(&root, 10);
    Insert(&root, 14);
    Insert(&root, 21);
    PrintBst(root);
    DeleteNode(&root, 21);
    PrintBst(root);
}

int main(int argc, char *argv[]) {
    TestDeleteNode();
    return 0;
}
