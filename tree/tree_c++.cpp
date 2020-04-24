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

    Node(int num) : item(num), left(nullptr), right(nullptr) {} // constructor
    // Node(int num, Node *l = 0, Node *r = 0) : item(num), left(l), right(r) {} // constructor
};

// Basic operations
// 1. traversal: inorder, preorder, postorder
// 2. insert
// 3. search
// 4. delete
// 5. parent node
// 6. successor node

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

Node* Tree::parent(Node* node) const { // return node's parent
    Node *tmp = root;
    while(tmp->left != node && tmp->right != node) { // cur is not parent
        if(node->item < tmp->item) // binary search
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }
    return tmp;
}

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


// Node* Tree::search(Node *q, int num){
//     while(q->item != num  &&  q!=0) {
//         if(num < q->item)
//             q = q->left;
//         else
//             q = q->right;
//     }
//
//     return q;
// }
//

void Tree::del(Node* &q){
    if(q->left == nullptr)
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

// use queue and cur & next
void Tree::level() {
    queue<Node*> q;
    int cur = 0, next = 0;
    q.push(this->root);
    ++cur;
    while(!q.empty()) {
        Node *tmp = q.front();
        q.pop();
        --cur;
        if (tmp != nullptr) {
            cout << tmp->item << " ";
            q.push(tmp->left);
            q.push(tmp->right);
            next += 2;
        }
        if(cur == 0) {
            cout << endl;
            cur = next;
            next = 0;
        }
    }
}

// left > root > right
// after visit root, pop and point to top() -> right
void Tree::in_order() {
    stack<Node*> s;
    Node* tmp = this->root;
    while(tmp || !s.empty()) {
        if (tmp != nullptr) {
            s.push(tmp);
            tmp = tmp->left;
        } else {
            tmp = s.top();
            cout << tmp->item << " ";
            s.pop();
            tmp = tmp->right;
        }
    }
    cout << endl;
}

// root > left > right
// if left null, point the tmp to s.top()->right
void Tree::pre_order() {
    stack<Node*> s;
    Node* tmp = this->root;
    while(tmp || !s.empty()) {
        if (tmp) {
            cout << tmp->item << " ";
            s.push(tmp);
            tmp = tmp->left;
        } else {
            tmp = s.top() -> right;
            s.pop();
        }
    }
    cout << endl;
}

// left > right > root
// record the previous visited root node
void Tree::post_order() {
    stack<Node*> s;
    Node* tmp = this->root;
    Node* lastvisitnode = nullptr;
    while(tmp || !s.empty()) {
        if(tmp) {
            s.push(tmp);
            tmp = tmp->left;
        } else {
            Node* topnode = s.top();
            if (topnode->right && lastvisitnode != topnode->right ){
                tmp = topnode->right;
            } else {
                cout << topnode->item << " ";
                lastvisitnode = s.top();
                s.pop();
            }
        }
    }
}

Node* Tree::search(int val) {
    Node* tmp = this->root;
    while(tmp){
        if(tmp->item == val) {
            return tmp;
        } else if(val < tmp->item){
            tmp = tmp->left;
        } else {
            tmp = tmp->right;
        }
    }
    return tmp;
}

Node* Tree::predecessor(int val) {
    Node *cur = this->root, *pre = nullptr;
    while(cur && cur->item != val) {
        if (cur->item > val) {
            cur = cur->left;
        } else {
            pre = cur;
            cur = cur->right;
        }
    }

    if (cur) {
        cur = cur->left;
        while(cur) {
            pre = cur;
            cur = cur->right;
        }
    }

    return pre;
}

Node* findMin(Node* node) {
    while(node->left) {
        node = node->left;
    }
    return node;
}

Node* Tree::successor1(int val) {
    Node *cur = this->root, *succ = nullptr;
    while(cur && cur->item != val) {
        if(cur->item < val) {
            cur = cur->right;
        } else {
            succ = cur;
            cur = cur->left;
        }
    }

    if(cur && cur->right) {
        succ = findMin(cur->right);
    }

    return succ;

}

int getHeightOfTree(Node* root){
    if (!root)
        return 0;
    int leftHeight = getHeightOfTree(root -> left);
    int rightHeight = getHeightOfTree(root -> right);
    // 由于根节点不为 NULL，所以高度至少是1
    return 1 + std::max(leftHeight, rightHeight);
}

int Tree::get_height() {
    if (this->root == nullptr) return 0;

    queue<Node*> q;
    q.push(this->root);
    int height = 1;
    while(true) {
        int cnt = q.size();
        if (cnt == 0) return height;
        height++;
        while (cnt > 0 ) { // drain all nodes of each level
            Node *tmp = q.front();
            q.pop();
            if (tmp->left) q.push(tmp->left);
            if (tmp->right) q.push(tmp->right);
            cnt--;
        }
    }

    cout << "height is: "<< height << endl;
    return height;
}

bool Tree::symmetric() {
    Node *cur = this->root;
    if (cur == nullptr || (cur->left == nullptr && cur->right == nullptr)) return true;

    queue<Node*> q;
    q.push(cur->left);
    q.push(cur->right);

    while(!q.empty()){
        Node *l = q.front();
        q.pop();
        Node *r = q.front();
        q.pop();

        if (l == nullptr && r == nullptr) return true;
        if ((l == nullptr && r != nullptr) || (l != nullptr && r == nullptr) || l->item != r->item) return false;
        q.push(l->left);q.push(r->right);
        q.push(l->right);q.push(r->left);
    }

    return true;
}


int maxDepth(Node * root){
  // Root being null means tree doesn't exist.
  if (root == NULL)
    return 0;

  // Get the depth of the left and right subtree
  // using recursion.
  int leftDepth = maxDepth(root->left);
  int rightDepth = maxDepth(root->right);

  // Choose the larger one and add the root to it.
  if (leftDepth > rightDepth)
    return leftDepth + 1;
  else
    return rightDepth + 1;
}

Tree* gen_trees() {
    Node *root = new Node(1);
    root->left = new Node(3);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(6);
    root->right->left = new Node(6);
    root->right->right = new Node(4);

    return new Tree(root);
}

Tree* gen_trees1() {
    Node *root = new Node(1);
    root->left = new Node(3);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(6);
    root->right->left = new Node(6);
    root->right->right = new Node(4);

    return new Tree(root);
}

bool symmetric(Node *root) {
    int flag = 0;
    queue<Node*> Q;

    if(root != NULL || (root -> left == NULL && root -> right == NULL)){
        Q.push(root);
        Q.push(root);
        while(!Q.empty()){
          // Seeing and removing the top two elements of the queue.
          Node *Left = Q.front();
          Q.pop();
          Node *Right = Q.front();
          Q.pop();
          if (Left -> left == NULL && Right -> right != NULL){
              cout<<"The binary tree is asymmetric"<<endl;
              // Setting flag to -1 if it is asymmetric.
              flag = -1;
              break;
          }
          if (Left -> left != NULL && Right -> right == NULL){
            cout<<"The binary tree is asymmetric"<<endl;
            // Setting flag to -1 if it is asymmetric.
            flag = -1;
            break;
          }
          if (Left -> right != NULL && Right -> left == NULL){
            cout<<"The binary tree is asymmetric"<<endl;
            // Setting flag to -1 if it is asymmetric.
            flag = -1;
            break;
          }
          if (Left -> right == NULL && Right -> left != NULL){
            cout<<"The binary tree is asymmetric"<<endl;
            // Setting flag to -1 if it is asymmetric.
            flag = -1;
            break;
          }
          if(Left -> item != Right -> item){
              cout<<"The binary tree is asymmetric"<<endl;
              // Setting flag to -1 if it is asymmetric.
              flag = -1;
              break;
          }
          if(Left -> left != NULL && Right -> right != NULL){
              Q.push(Left -> left);
              Q.push(Right -> right);
          }
          if(Left -> right != NULL && Right -> left != NULL){
              Q.push(Left -> right);
              Q.push(Right -> left);
          }
        }
      }

      if(flag == 0){
          return true;
      }

      return false;
}

// test program
int main(){

    Tree bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(14);
    bst.insert(12);
    bst.insert(1);
    bst.insert(7);
    bst.insert(6);
    bst.insert(16);
    int val = 12;
    Node *p = bst.predecessor(val);
    // bst.inorder();

    bst.level();
    cout << "predecessor of " << val << " is " << p->item << endl;
    Node *p1 = bst.successor1(val);
    cout << "successor of " << val << " is " << p1->item << endl;

    // bst.pre_order();
    // bst.pre_order1();
    // bst.post_order();

    // cout << "height => : " << getTreeHeight_Iterative(bst.root) << endl;

    Tree *tr = gen_trees();
    cout << boolalpha << tr->symmetric() << endl;
    cout << boolalpha << symmetric(tr->root) << endl;

    // Tree *tr1 = gen_trees1();
    // cout << boolalpha << tr1->symmetric() << endl;
    // cout << boolalpha << symmetric(tr1->root) << endl;

    return 0;

}