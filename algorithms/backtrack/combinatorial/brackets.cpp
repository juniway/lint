#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node{
    string tmp;
    int left;
    int right;
};

void dfs(string &tmp, int left, int right, vector<string>& res) {
    if (left == 0 && right == 0) {
        res.push_back(tmp);
        return;
    }

    if (left > right) return;
    if (left > 0) {
        tmp += '(';
        dfs(tmp, left - 1, right, res);
        tmp.pop_back();
    }
    if (right > 0) {
        tmp += ')';
        dfs(tmp, left, right - 1, res);
        tmp.pop_back();
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> res;
    string tmp;
    dfs(tmp, n, n, res);
    return res;
}

void testGenerateParenthesis() {
    auto res = generateParenthesis(3);
    for (auto row : res)
        cout << row << endl;
}

int main(int argc, char *argv[]) {
    testGenerateParenthesis();
    return 0;
}
