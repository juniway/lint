

//http://leetcode.com/2010/09/printing-binary-tree-in-level-order.html

// 用两个 queue
void printLevelOrder_twoQueues(BinaryTree *root) {
	if (!root) return;
	queue<BinaryTree*> currentLevel, nextLevel;
	currentLevel.push(root);
	while (!currentLevel.empty()) {
		BinaryTree *currNode = currentLevel.front();
		currentLevel.pop();
		if (currNode != nullptr) {
			cout << currNode->data << " ";
			nextLevel.push(currNode->left);
			nextLevel.push(currNode->right);
		}
		if (currentLevel.empty()) {
			cout << endl;
			swap(currentLevel, nextLevel);
		}
	}
}

// 用一个 queue，外加两个变量记录 queue 前后元素数量
void printLevelOrder_oneQueue(Node *root) {
	if (!root)
		return;

	queue<Node*> nodesQueue;
	int nodesInCurrentLevel = 0, nodesInNextLevel = 0;
	nodesQueue.push(root);
	++nodesInCurrentLevel;

	while (!nodesQueue.empty()) {
		Node *currNode = nodesQueue.front();
		nodesQueue.pop();
		nodesInCurrentLevel--;
		if (currNode != nullptr) {
			cout << currNode->data << " ";
			nodesQueue.push(currNode->left);
			nodesQueue.push(currNode->right);
			nodesInNextLevel += 2;
		}
		if (nodesInCurrentLevel == 0) {
			cout << endl;
			nodesInCurrentLevel = nodesInNextLevel;
			nodesInNextLevel = 0;
		}
	}
}
