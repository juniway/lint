template <class T> class BinaryTree; // 加一个前置声明

template <class T>
class BinaryTreeNode {
friend class BinaryTree<T>; /* 消除该句后可通过编译 */
private:
    T data;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;
};
template <class T>
class BinaryTree {
private:
    BinaryTreeNode<T> *root;
};
