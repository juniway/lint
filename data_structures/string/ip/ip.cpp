#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

uint32_t process(const char *ipstr) {
    unsigned int ipb[4];
    char *p = (char*)ipstr;
    int dot = 0;
    int digit_cnt = 0;
    int i = 0, j = 3;
    while(*p != '\0') {
        if (!isDigit(*p)) {
            if(digit_cnt > 3) {
                cerr << "ERROR: more than 3 digits\n";
                return 0;
            }
            while(*p != '.' && *p != '\0') {
                if(*p != ' ') {
                    cerr << "ERROR: space not valid\n";
                    return 0;
                }
                p++;
                i++;
            }
            if (*p == '.') {
                ++dot;
            }
            if (dot > 3) {
                cerr << "ERROR: more than 3 dots\n";
                return 0;
            }
            sscanf(p - i, "%u", &ipb[j]);
            if (ipb[j] > 255) {
                cerr << "ERROR: number greater than 255\n";
                return 0;
            }
            i = 0, digit_cnt = 0;
            --j;
            p++;
        } else {
            digit_cnt++;
            p++;
            i++;
        }
    }
    sscanf(p - i, "%u", &ipb[j]);
    if (j > 0) {
        cerr << "ERROR: less than 3 dots\n";
        return 0;
    }
    if (dot > 3) {
        cerr << "ERROR: more than 3 dots\n";
        return 0;
    }

    return ipb[0] | ipb[1] << 8 | ipb[2] << 16 | ipb[3] << 24;
}

// test cases
void utest() {
    vector<string> vs = {
        "172.168.5.1",              // ok
        "172 .168.5.1",             // ok
        "172.168   .5.1",           // ok
        "0.128.2.1",                // ok
        "17 2.168.5.1",             // error
        "172 . 168.5 .1",           // error
        "172.168.5. 1",             // error
        "1a2.168.5.1",              // error
        "1724.168.5.1",             // error
        "172.168.5.1.9",            // error
        "277.168.5.1",              // error
        "172.168",                  // error
        "1293479",                  // error
        "-1",                       // error
    };

    int err_cnt = 0;
    for (auto &s: vs) {
        uint32_t ret = process(s.c_str());
        if(ret == 0) {
            cerr << "----: " << s << endl;
            err_cnt++;
        } else {
            cout << "++++: " << s << " | " << ret << endl;
        }
    }

    cout << "========= Total cases: " << vs.size() << " =================\n";
    cout << "========= Expected pass: " << 3 << endl;
    cout << "========= Real pass: " << vs.size() - err_cnt << " =================\n";
}

int main() {
    utest();
}
