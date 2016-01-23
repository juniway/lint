[Leetcode 111] Minimum Depth of Binary Tree
Given a binary tree, find its minimum depth.
The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

算法1: 直观的递归解法，分别求左右子树的最小深度，然后返回左右子树的最小深度中较小者+1
class Solution {
public:
    int minDepth(TreeNode *root) {
        if(root == nullptr)return 0;
        int minleft = minDepth(root->left);
        int minright = minDepth(root->right);
        if(minleft == 0)
            return minright + 1;
        else if(minright == 0)
            return minleft + 1;
        else return min(minleft, minright) + 1;
    }
};

算法2：层序遍历二叉树，找到最先遍历到的叶子的层数就是树的最小高度

class Solution {
public:
    int minDepth(TreeNode *root) {
         //层序遍历，碰到第一个叶子节点就停止,nullptr作为每一层节点的分割标志
        if(root == nullptr)return 0;
        int res = 0;
        queue<TreeNode*> Q;
        Q.push(root);
        Q.push(nullptr);
        while(Q.empty() == false){
            TreeNode *p = Q.front();
            Q.pop();
            if(p != nullptr){
                if(p->left) Q.push(p->left);
                if(p->right) Q.push(p->right);
                if(p->left == nullptr && p->right == nullptr){
                    res++;
                    break;
                }
            }
            else{
                res++;
                if(Q.empty() == false) Q.push(nullptr);
            }
        }
        return res;
    }
};