#include <iostream>
#include <vector>
#include <string>
using namespace std;

// substring
uint32_t ip2Int(string ip) {
    int n = ip.size(), j = 0, i = 0, dot = 0;
    uint32_t res = 0;
    while (i < n) {
        while (i < n && ip[i] != '.') {
            if (!isdigit(ip[i])) return 0;
            i++;
        }
        dot++;

        string tmp = ip.substr(j, i - j);
        if (tmp.size() > 1 && tmp[0] == '0') return 0;
        int num = stoi(tmp);
        if (num < 0 || num > 255) return 0;
        res = (res << 8) | (num & 0xFF);
        j = i + 1;
        i++;
    }

    if (dot != 4) return 0;

    return res;
}

// one pass
uint32_t convertIp2Int(string ip) {
    int i = 0, j = 0, dot = 0;
    int res = 0;
    while (i < ip.size()) {
        int tmp = 0;
        while(i < ip.size() && ip[i] != '.') {
            if (!isdigit(ip[i])) return 0;
            tmp = tmp * 10 + ip[i] - '0';
            i++;
        }
        dot++;
        int cnt = i - j;
        if (cnt > 3 || cnt <= 0) return 0;
        if (tmp < 0 || tmp > 255) return 0;
        res = res << 8 | (tmp & 0xFF);

        i++;
        j = i;
    }

    if (dot != 4) return 0;
    return res;
}


uint32_t ipv4ToUint32(string ip) {
    uint8_t ipbytes[4];
    int ret = sscanf(ip.c_str(), "%hhu.%hhu.%hhu.%hhu", &ipbytes[3], &ipbytes[2], &ipbytes[1], &ipbytes[0]);
    if (ret != 4) return 0;
    return ipbytes[0] | ipbytes[1] << 8 | ipbytes[2] << 16 | ipbytes[3] << 24;
}

void testIp2Int() {
    vector<string> cases = {
        "192.168.21.133",
        "127.0.0.1",
        "0.128.2.1",
        // invalid
        ".1.2.3.4"
        "1.2.$3.4"
        "172 .168.5.1",
        "172.168 .5.1",
        "17 2.168.5.1",
        "172.168",
        "172.0.2.1.3",
        "1293479",
        "-1",
        "1a2.168.5.1",
        "172.168.5.01"
    };

    for (auto s : cases) {
        cout << ip2Int(s) << endl;
        // cout << ipv4ToUint32(s) << endl;
    }

    cout << ipv4ToUint32("1.1.1.01") << endl;
}

int main(int argc, char *argv[]) {
    testIp2Int();
    return 0;
}
