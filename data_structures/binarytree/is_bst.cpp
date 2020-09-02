#include <cstdlib>
#include <ctime>
#include <array>
#include "tree.hpp"

void InsertRand(Node **root, int key) {
    if (*root == nullptr)
        *root = new Node(key);
    else {
        Node *cur = *root;
        while (cur != nullptr) {
            int x = rand()%2;
            // cout << "x: " << x << "\n";
            if (x == 0) {
                // cout << "111: " << cur->data << "\n";
                if (cur->left != nullptr)
                    cur = cur->left;
                else {
                    cur->left= new Node(key);
                    break;
                }
            } else {
                // cout << "222" << "\n";
                if (cur->right != nullptr)
                    cur = cur->right;
                else {
                    cur->right = new Node(key);
                    break;
                }
            }
        }
    }
}

bool isBst(Node *root) {
    if (root == nullptr) return true;
    else if (root->left == nullptr && root->right == nullptr) {
        return true;
    } else if (root->left == nullptr && root->right != nullptr && root->right->data >= root->data) {
        return isBst(root->right);
    } else if (root->right == nullptr && root->left != nullptr && root->left->data <= root->data) {
        return isBst(root->left);
    } else if (root->left != nullptr && root->right != nullptr && 
        root->left->data <= root->data && root->right->data >= root->data){
        return isBst(root->left) && isBst(root->right);
    } else {
        return false;
    }
}

int findMinValue(Node *root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root->data;
}

bool isBst1(Node *root) {
    if (root == nullptr ) return true;
    if (root->left != nullptr && findMinValue(root->left) > root->data) 
        return false;
    if (root->right != nullptr && findMinValue(root->right) < root->data)
        return false;
    if (!isBst1(root->left) || !isBst1(root->right))
        return false;
    return true;
}

bool isBSTUtil(Node *root, int min, int max) {
    if (root == nullptr) return true;
    if (root->data < min || root->data > max)  return false;
    return isBSTUtil(root->left, min, root->data) && isBSTUtil(root->right, root->data+1, max);
}

bool isBst2(Node *root) {
    return (isBSTUtil(root, INT_MIN, INT_MAX));
}


Node* BuildTreeRand() {
    Node *root = nullptr;
    constexpr int n = 10;
    std::array<int, n> a = {7, 11, 2, 4, 8, 3, 9, 1, 13, 5};
    for (auto i : a ) {
        InsertRand(&root, i);
    }
    PrintBst(root);

    return root;
}

Node* BuildTree() {
    Node *root = nullptr;
    constexpr int n = 10;
    std::array<int, n> a = {7, 11, 2, 9, 19, 1, 6, 7, 4, 5};
    for (auto i : a ) {
        Insert(&root, i);
    }
    PrintBst(root);

    return root;
}

Node *BuildTreeHuge() {
    srand(time(nullptr));
    Node *root = nullptr;
    constexpr int n = 100*100;
    
    for (int i = 0; i < n; i++) {
        Insert(&root, rand()%1000);
    }
    return root;
}

void TestInsertRand() {
    srand(time(nullptr));
    Node *root = nullptr;
    constexpr int n = 10;
    std::array<int, n> a = {7, 11, 2, 4, 8, 3, 9, 1, 13, 5};
    for (auto i : a ) {
        InsertRand(&root, i);
    }
    PrintBst(root);
}

void TestIsBst() {
    srand(time(nullptr));

    Node *tree1 = BuildTreeRand();
    Node *tree2 = BuildTree();
    cout << std::boolalpha << isBst(tree1) << "\n";
    cout << std::boolalpha << isBst(tree2) << "\n";
}

void TestIsBstTime() {
    Node *tree = BuildTreeHuge();
    auto t1 = std::chrono::high_resolution_clock::now();
    bool res = isBst(tree);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = t2 - t1;
    std::cout << "isBst() took " << ms.count() << " ms\n";
    cout << std::boolalpha << res << "\n";
}

void TestIsBstTime1() {
    Node *tree = BuildTreeHuge();
    auto t1 = std::chrono::high_resolution_clock::now();
    bool res = isBst1(tree);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = t2 - t1;
    std::cout << "isBst() took " << ms.count() << " ms\n";
    cout << std::boolalpha << res << "\n";
}

void TestIsBstTime2() {
    Node *tree = BuildTreeHuge();
    auto t1 = std::chrono::high_resolution_clock::now();
    bool res = isBst2(tree);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = t2 - t1;
    std::cout << "isBst() took " << ms.count() << " ms\n";
    cout << std::boolalpha << res << "\n";
}

int main(int argc, char *argv[]) {
    // TestInsertRand();
    // TestIsBst();
    TestIsBstTime();
    TestIsBstTime1();
    TestIsBstTime2();
    return 0;
}

