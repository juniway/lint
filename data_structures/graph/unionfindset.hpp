#include <vector>

using std::vector;

class UnionFindSet{
public:
    UnionFindSet(int n) {
        ranks_ = vector<int>(n + 1, 0);
        parents_ = vector<int>(n + 1, 0);
        for (int i = 0; i < parents_.size(); ++i)
            parents_[i] = i;
    }

    bool Union(int u, int v) {
        int pu = Find(u);
        int pv = Find(v);
        if (pu == pv) return false;

        if (ranks_[pv] > ranks_[pu])
            parents_[pu] = pv;
        else if (ranks_[pv] < ranks_[pu])
            parents_[pv] = pu;
        else {
            parents_[pv] = pu;
            ranks_[pv] += 1;
        }

        return true;
    }

    int Find(int u) {
        if (parents_[u] != u)
            parents_[u] = Find(parents_[u]); // path compression
        return parents_[u];
    }

private:
    vector<int> parents_;
    vector<int> ranks_;

};
