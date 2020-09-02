#include <iostream>
#include <queue>

using namespace std;

struct Node{
    Node *left, *right;
    int data;
    Node(int data) : data(data){
        left = nullptr;
        right = nullptr;
    }
};

Node* convert(int a[], int low, int high) {
    if (low > high) return nullptr;
    int mid = low + (high - low)/2;
    Node *root = new Node(a[mid]);
    root->left = convert(a, low, mid - 1);
    root->right = convert(a, mid+1, high);

    return root;
}

void PrintLevel(Node *root) {
    if (root == nullptr) return;
    queue<Node*> q;
    int current, next = 0;

    q.push(root);
    current = 1;

    while(!q.empty()) {
        Node *tmp = q.front();
        q.pop();
        current--;
        cout << tmp->data << " ";
        if(tmp->left != nullptr)q.push(tmp->left);
        if(tmp->right != nullptr) q.push(tmp->right);
        next +=2;

        if (current == 0) {
            cout << "\n";
            current = next;
            next = 0;
        }
    }
    cout << "\n";
}

void ConvertArray2BstMinHeight(int a[], int n) {
    Node *root = convert(a, 0, n-1);
    PrintLevel(root);
}

void testConvert() {
    int a[] = {2,3,6,7,8,9,12,15,16,18,20};
    ConvertArray2BstMinHeight(a, 10);
}

int main(int argc, char *argv[]) {
    testConvert();
    return 0;
}
