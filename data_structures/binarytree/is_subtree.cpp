// Check If a Binary Tree is a Subtree of Another Binary Tree

class Solution {
public:
    bool isSubtree(TreeNode* t1, TreeNode* t2) {
        if (t2 == nullptr) return true;
        if (t1 == nullptr) return false;
        return identical(t1, t2) || isSubtree(t1->left, t2) || isSubtree(t1->right, t2);
    }

    bool identical(TreeNode* t1, TreeNode *t2) {
        if (t1 == nullptr && t2 == nullptr) return true;
        if (t1 == nullptr || t2 == nullptr) return false;
        return t1->val == t2->val && 
            identical(t1->left, t2->left) && identical(t1->right, t2->right);
    }
};

//http://blog.csdn.net/anzhsoft/article/details/17633087
// https://discuss.leetcode.com/topic/18/check-if-a-binary-tree-is-a-subtree-of-another-binary-tree/2
