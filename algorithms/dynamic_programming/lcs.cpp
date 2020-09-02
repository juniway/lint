// Problem
// Find the longest common subsequence of two strings s and t
// https://www.ics.uci.edu/~eppstein/161/960229.html
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::max;

// full match, is p a subsequence of t?
bool lcs(string p, string t) {
    int i = 0, j = 0;
    while (j < t.size()) {
        if (p[i] == t[j++] && ++i == p.size())
            return true;
    }
    return false;
}

// the longest common subsequence between s and t
int lcs(string p, string t, int i, int j) {
    int n1 = p.size(), n2 = t.size();
    if (i == n1 || j == n2) return 0;
    if (s[i] == t[j]) return 1 + lcsRec(p, t, i + 1, j + 1);
    else return max(lcsRec(p, t, i + 1, j), lcsRec(p, t, i, j + 1));
}


// memoization
int lcs(string A, string B, int i, int j, vector<vector<int>>& L) {
    if (L[i][j] < 0) {
        if (i == A.size() || j == B.size()) L[i][j] = 0;
        else if (A[i] == B[j]) L[i][j] =  1 + lcs(A, B, i+1, j+1, L);
        else L[i][j] = max (lcs(A, B, i+1, j, L), lcs(A, B, i, j+1, L));
    }

    return L[i][j];
}

// tabulation (dynamic programming)
int lcs_tab(string A, string B) {
    int n1 = A.size(), n2 = B.size();
    vector<vector<int>> L (n1 + 1, vector<int>(n2 + 1, -1));
    for(int i = n1; i >= 0; i--) {
        for (int j = n2; j >= 0; j--) {
            if (i == A.size() || j == B.size()) L[i][j] = 0;
            else if (A[i] == B[j]) L[i][j] = 1 + L[i+1][j+1];
            else L[i][j] = max(L[i+1][j], L[i][j+1]);
        }
    }

    int i = 0, j = 0;
    string res;
    while(i < A.size() && j < B.size()) {
        if (A[i] == B[j]) {
            res.push_back(A[i]);
            i++, j++;
        } else if (L[i+1][j] > L[i][j+1]) i++;
        else j++;
    }

    std::cout <<  res << "\n";
    return L[0][0];
}

// 1d array
int lcs1d(string A, string B) {
    vector<int> L (B.size() + 1, -1);
    for(int i = A.size(); i >=0; i--) {
        for (int j = B.size(); j >= 0; j--) {
            if (i == A.size() || j == B.size()) L[j] = 0;
            else if (A[i] == B[j]) L[j] = 1 + L[j+1];
            else L[j] = max(L[j], L[j+1]);
        }
    }

    int i = 0, j = 0;
    string res;
    while(i < A.size() && j < B.size()) {
        if (A[i] == B[j]) {
            res.push_back(A[i]);
            i++, j++;
        } else if (L[j] > L[j+1]) i++;
        else j++;
    }

    std::cout <<  res << "\n";
    return L[0];
}

// test
int lcs(string A, string B) {
    vector<vector<int>> L(A.size() + 1, vector<int>(B.size() + 1, -1));
    return lcsMemo(A, B, 0, 0, L);
}


int main(int argc, char *argv[]) {
    // std::cout << std::boolalpha << lcs("nematode knowledge", "nano") << "\n";
    // std::cout << std::boolalpha << lcs("nematode knowledge", "sss") << "\n";
    // std::cout << lcs_length1("nematode knowledge", "empty bottle") << "\n";
    // std::cout << lcs_length2("nematode knowledge", "empty bottle") << "\n";
    lcs_memo("abce", "xbe");
    lcs_tab("abce", "xbe");
    lcs_tab1("abce", "xbe");

    return 0;
}
