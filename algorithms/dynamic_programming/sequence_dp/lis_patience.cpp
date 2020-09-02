#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int val;
    Node *next;
    Node(int v):val(v),next(nullptr) {}
    Node(int v, Node *nxt):val(v),next(nxt) {}
};

static bool comp(vector<Node*> a, vector<Node*> b) {
    return a.back()->val < b.back()->val;
}

vector<int> lis(vector<int>& a) {
    vector<vector<Node*>> stacks;
    stacks.push_back({new Node(a[0])});
    for (int i = 1; i < a.size(); i++) {
        int j = lower_bound(stacks.begin(), stacks.end(), vector<Node*>{new Node(a[i])}, comp) - stacks.begin();
        if (j == 0) {
            stacks[j].push_back(new Node(a[i]));
        } else {
            if (j == stacks.size()) {
                stacks.push_back({new Node(a[i], stacks.back().back())});
            } else {
                stacks[j].push_back(new Node(a[i], stacks[j - 1].back()));
            }
        }
    }

    vector<int> res;
    Node *cur = stacks.back().front();
    res.push_back(cur->val);
    cur = cur->next;
    while(cur) {
        res.insert(res.begin(), cur->val);
        cur = cur->next;
    }

    cout << "size: " << stacks.size() << endl;
    return res;
}

void testLis() {
    vector<vector<int>> a = {
        {10, 5, 8, 3, 9, 4, 12, 11},
        {5, 3, 4, 7, 1, 6},
        {3, 3, 2, 1, 5, 5, 4, 3, 7, 8},
    };

    for (auto seq : a) {
        auto res = lis(seq);
        for (auto v : res) cout << v << " "; cout << endl;
    }
}

int main(int argc, char *argv[]) {
    testLis();
    return 0;
}
