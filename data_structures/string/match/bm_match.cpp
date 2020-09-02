#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define N 256
void badCharHeuristic(string pat, int badchar[N]) {
    int i = 0;
    for (; i < N; i++) {
        badchar[i] = -1;
    }

    for(i = 0; i < pat.size(); i++)
        badchar[(int)pat[i]] = i;
}

vector<int> search(string text, string pat) {
    int m = pat.size(), n = text.size();
    int badchar[N];

    badCharHeuristic(pat, badchar);

    int i = 0;
    vector<int> res;
    while (i <= (n - m)) {
        int j = m - 1; // matching from tail

        while(j >= 0 && pat[j] == text[i + j])
            j--;

        if (j < 0) { // found a match
            res.push_back(i);
            i += (i < n - m) ? m - badchar[(int)text[i + m]] : 1;
        } else {
            i += max(1, j - badchar[(int)text[i + j]]);
        }
    }

    return res;
}

void testSearch() {
    auto res = search("ABCAABCABC", "ABC");
    for (auto x : res) cout << x << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    testSearch();
    return 0;
}
