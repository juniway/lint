bool Tree::symmetric() {
    Node *cur = this->root;
    if (cur == nullptr || (cur->left == nullptr && cur->right == nullptr)) return true;

    queue<Node*> q;
    q.push(cur->left);
    q.push(cur->right);

    while(!q.empty()){
        Node *l = q.front();
        q.pop();
        Node *r = q.front();
        q.pop();

        if ((l == nullptr && r != nullptr) || (l != nullptr && r == nullptr) || l->item != r->item) return false;
        q.push(l->left);q.push(r->right);
        q.push(l->right);q.push(r->left);
    }

    return true;
}