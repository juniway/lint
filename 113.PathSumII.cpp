[LeetCode 113] Path Sum II
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.'

For example:
Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
return
[
   [5, 4, 11, 2],
   [5, 8, 4, 5]
]

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode *root, int sum) {
        vector<int> path;
        vector<vector<int>> res;
        finaPathSum(root, sum, path, res);
        return res;
    }

    void finaPathSum(TreeNode *root, int sum, vector<int> &path, vector<vector<int>> &res) {
        if(root == nullptr) return;
        sum -= root->val;
        path.push_back(root->val);

        if(root->left == nullptr && root->right == nullptr) {
            if(sum == 0) res.push_back(path);
        }
        else {
            if(root->left != nullptr) finaPathSum(root->left, sum, path, res);
            if(root->right != nullptr) finaPathSum(root->right, sum, path, res);
        }

        path.pop_back();
    }
};



