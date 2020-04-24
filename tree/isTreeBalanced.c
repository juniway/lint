/*
如果我们用后序遍历的方式遍历二叉树的每一个结点，在遍历到一个结点之前我们已经遍历了它的左右子树。
只要在遍历每个结点的时候记录它的深度（某一结点的深度等于它到叶节点的路径的长度），
我们就可以一边遍历一边判断每个结点是不是平衡的。下面是这种思路的参考代码：
*/

bool IsBalanced(BinaryTreeNode* pRoot, int* pDepth) {
    if(pRoot == NULL) {
        *pDepth = 0;
        return true;
    }

    int leftDepth, rightDepth;
    if(IsBalanced(pRoot->m_pLeft, &leftDepth) && IsBalanced(pRoot->m_pRight, &rightDepth)) {
        int diff = leftDepth - rightDepth;
        if(abc(diff) <= 1) {
            *pDepth = 1 + max(leftDepth, rightDepth); // 计算当前深度
            return true;
        }
    }

    return false;
}

bool IsBalanced(BinaryTreeNode* pRoot) {
    int depth = 0;
    return IsBalanced(pRoot, &depth);
}

template<typename T>
int get_height(const shared_ptr<BinaryTree<T>> &node){
    if(node == nullptr){
        return -1;
    }

    int l_height = get_height(node->left);
    if(l_height == -2){
        return -2;  // left subtree is not balanced
    }
    int r_height = get_height(node->right);
    if(r_height == -2){
        return -2; // right subtree is not balanced
    }

    if(abs(l_height - r_height) > 1){
        return -2;  // current node is not balanced
    }

    return max(l_height, r_height) + 1;
}

template<typename T>
bool is_balanced_binary_tree(const shared_ptr<BinaryTree<T>> &node){
    return get_height(node) != -2;
}
