#include <iostream>
#include <string>
using namespace std;

bool oneEditAway(string first, string second) {
    int n1 = first.size(), n2 = second.size();
    if (n1 < n2) return oneEditAway(second, first);
    if (n1 == 0) return true;
    int i = 0, j = 0, cnt = 0;
    while (true) {
        while(i < n1 && j < n2 && first[i] == second[i]) i++, j++;
        if (i == n1) break;
        if (n1 == n2) {
            i++, j++;
        } else {
            i++;
        }
        cnt++;
    }
    return cnt <= 1;
}

void testOneEdit() {
    string s1 = "islander", s2 = "slander";
    cout << boolalpha << oneEditAway(s1, s2) << endl;
}

int main(int argc, char *argv[]) {
    testOneEdit();
    return 0;
}
