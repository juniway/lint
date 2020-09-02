#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int str2int(string n) {
    stringstream ss;
    ss << n;
    int num;
    ss >> num;
    return num;
}

string int2str(int n) {
    stringstream ss;
    ss << n;
    return ss.str();
}

void complexInput(string input) { // "1 + 2 * 3"
    stringstream ss(input + "+");
    vector<int> nums;
    vector<char> ops;

    int num = 0;
    char op = ' ';
    while (ss >> num && ss >> op) {
        nums.push_back(num);
        ops.push_back(op);
    }

    for (auto v : nums) cout << v << " "; cout << endl;
    for (auto c : ops) cout << c << " "; cout << endl;
}

void testConvertion() {
    cout << str2int("123") << endl;
    cout << int2str(888) << endl;
}

int main(int argc, char *argv[]) {
    testConvertion();
    complexInput("1+23*4");
    return 0;
}
