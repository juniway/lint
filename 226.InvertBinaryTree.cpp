[LeetCode 226] Invert Binary Tree
invert a binary tree.
     4
   /   \
  2     7
 / \   / \
1   3 6   9
to
     4
   /   \
  7     2
 / \   / \
9   6 3   1
Trivia:
This problem was inspired by this original tweet by Max Howell:
Google: 90% of our engineers use the software you wrote (Homebrew), but you can’t invert a binary tree on a whiteboard so fuck off.

非递归算法：
1、交换根节点的左右子节点
2、交换第二层每个节点的左右子节点
....
这个与二叉树层次遍历类似，代码如下:
涉及到层次遍历一般都要考虑到用queue去保存当前层节点
涉及到深度优先遍历一般都要考虑到用stack去保存节点信息

TreeNode* invertTree2(TreeNode* root) {
    queue<TreeNode*> tree_queue;
    if (root == nullptr)
        return root;
    tree_queue.push(root);
    while(tree_queue.size() > 0){
        TreeNode * pNode = tree_queue.front();
        tree_queue.pop();
        TreeNode * tmp = pNode->left;
        pNode->left = pNode->right;
        pNode->right = tmp;
        if (pNode->left != nullptr)
            tree_queue.push(pNode->left);
        if (pNode->right != nullptr)
            tree_queue.push(pNode->right);
    }
    return root;
}
while(!q.empty()){
	Node* pNode = q.front();
	q.pop();
	Node* tmp = pNode->left;

	pNode->left = pNode->right;
	pNode->right = tmp;
	if(pNode->left != nullptr)
		q.push(pNode->left);
	if(pNode->right != nullptr)
		q.push(pNode->right);
}
return root;

Node* invertTree(Node* root){
	if(root == nullptr) return root;
	Node* tmp = root->left;
	root->left = invertTree(root->right);
	root->right = invertTree(tmp);
	return root;
}

递归算法：
1、交换根节点的左右子树。
2、对左右子树分别执行递归反转 。
代码如下：
TreeNode* invertTree(TreeNode* root) {
    if(root == nullptr) return nullptr;
	TreeNode * tmpNode = root->left;
	root->left = invertTree(root->right);
	root->right = invertTree(tmpNode);
	return root;
}