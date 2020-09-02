#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

vector<string> printKMoves(int K) {
    if (K == 0) return {"R"};

    int dirs[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}}; // "L U R D"
    int curDir = 2;
    set<pair<int, int>> blackSet;
    pair<int, int> pos = make_pair(0, 0);
    while (K > 0) {
        if (blackSet.find(pos) != blackSet.end()) {
            blackSet.insert(pos);
            curDir = (curDir + 1) % 4;
        } else {
            blackSet.erase(pos);
            curDir = (curDir + 3) % 4;
        }
        pos.first = pos.first + dirs[curDir][0];
        pos.second = pos.second + dirs[curDir][1];
        K--;
    }

    int left = pos.second, right = pos.second, top = pos.first, bottom = pos.first;
    for (auto p : blackSet) {
        left = left < p.second ? left : p.second;
        right = right > p.second ? right : p.second;
        top = top < p.first ? top : p.first;
        bottom = bottom > p.first ? bottom : p.first;
    }

    string row(right - left + 1, '_');
    vector<string> res(bottom - top + 1, row);
    for (auto p : blackSet) {
        int y = p.first, x = p.second;
        res[y - top][x - left] = 'X';
    }

    char direction[] = {'L', 'U', 'R', 'D'};
    res[pos.second - top][pos.first - left] = direction[curDir];

    return res;
}

void test() {
    auto res = printKMoves(1);
    for (auto s : res) cout << s << ", ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    test();
    return 0;
}
