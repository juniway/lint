[LeetCode 104] Maximum Depth of Binary Tree
Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

class Solution {
public:
    int maxDepth(TreeNode *root) {
        if(root == nullptrptr)return 0;
        int maxleft = maxDepth(root->left);
        int maxright = maxDepth(root->right);
        if(maxleft == 0)
            return maxright + 1;
        else if(maxright == 0)
            return maxleft + 1;
        else return max(maxleft, maxright) + 1;
    }
};


class Solution {
public:
    int maxDepth(TreeNode *root) {
        //层序遍历计算树的层数即可,nullptr作为每一层节点的分割标志
        if(root == nullptr)return 0;
        int res = 0;
        queue<TreeNode*> Q;
        Q.push(root);
        Q.push(nullptr);
        while(Q.empty() == false){
            TreeNode *p = Q.front();
            Q.pop();
            if(p != nullptr){
                if(p->left)Q.push(p->left);
                if(p->right)Q.push(p->right);
            }
            else{
                res++;
                if(Q.empty() == false)Q.push(nullptr);
            }
        }
        return res;
    }
};