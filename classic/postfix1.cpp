#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isNotOperator(char c) {
  return c != '*' && c != '+' && c != '-' && c != '/' && c!= '(' && c != ')';
}

// 获取符号的优先级
int getPriority(char c) {
	int priority = -1;
	switch (c) {
    case '+':
      priority = 1;
      break;
    case '-':
      priority = 1;
      break;
    case '*':
      priority = 2;
      break;
    case '/':
      priority = 2;
      break;
    case '(':
      priority = 3;
      break;
    default:
      break;
	}
	return priority;
}

string infix2postfix(string infix) {
    string s;
    stack<char> st;
    string::const_iterator iter = infix.begin();
    for (; iter < infix.end(); iter++) {
        if(isNotOperator(*iter)) s.push_back(*iter);
        else {
            if (!st.empty()) {
                if (*iter == ')') {
                    while(!st.empty() && st.top() != '(') {
                        s.push_back(st.top());
                        st.pop();
                    }
                    if(!st.empty()) 
                        st.pop();
                    else {
                        cout << "invalid operation, matching ( is found!" << endl;
                        return "";
                    }
                } else {
                    char c = st.top();
                    if (getPriority(*iter) <= getPriority(c)) {
                        if (c == '(') {
                            st.push(*iter);
                        } else {
                            st.pop();
                            s.push_back(c);
                            st.push(*iter);
                        }
                    } else {
                        st.push(*iter);
                    }
                }
            } else {
                st.push(*iter);
            }
        }
    }

    if (iter == infix.end()) {
        while(!st.empty()) {
            s.push_back(st.top());
            st.pop();
        }
    }

    return s;
}

int domath(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return b != 0?a / b:0;
        default:
            cout << "Unsupported operation!" << endl;
            return 0;
    }
}

int infix_calc(const string& infix) {
    string::const_iterator iter = infix.begin();
    stack<char> st;
    stack<int> ns;

    while(iter != infix.end() || !st.empty()) {
        if(*iter==' ') {
            iter++;
            continue;
        }
        if (iter == infix.end()) {
            while(!st.empty()) {
                if (ns.size() < 2) {
                    cout << "error!1\n";
                }
                int a = ns.top();
                ns.pop();
                int b = ns.top();
                ns.pop();
                ns.push(domath(b, a, st.top()));
                st.pop();
            }
            // return ns.top();
            break;
        }

        if (isNotOperator(*iter)) {
            ns.push(*iter - '0');
        } else if (*iter == ')'){
            while(!st.empty() && st.top() != '(') {
                if (ns.size() < 2) {
                    cout << "error!2\n";
                }
                int a = ns.top();
                ns.pop();
                int b = ns.top();
                ns.pop();
                ns.push(domath(b, a, st.top()));
                st.pop();
            }

            if(!st.empty()) st.pop();
            else { 
                cout << "invalid expresson" << endl;
                return 0;
            }
        } else {
            while(!st.empty() && getPriority(*iter) <= getPriority(st.top()) && st.top() != '(') {
                if (ns.size() < 2) {
                    cout << "error!3\n";
                }
                int a = ns.top();
                ns.pop();
                int b = ns.top();
                ns.pop();
                ns.push(domath(b, a, st.top()));
                st.pop();
            }
            st.push(*iter);
        }
        iter++;
    }

    if(ns.size() != 1) {
        cout << ns.size() << endl;
        cout << "some error!\n";
        return -1;
    }

    return ns.top();
}

void test_data() {
    // string s1("a+b*c+(d*e+f)*g");
    // string s(")a+b");
    string ss[3] = {
        "a+b*c+(d*e+f)*g",
        ")a+b",
        "a+)b",
    };

    for (int i = 0; i < 3; i++) {
        cout << ss[i] << endl;
        cout << infix2postfix(ss[i]) << endl;
    }
}

void test_data1() {
    string ss[3] = {
        "1*2*3+ 4*5+6",      // 32
        "(7*2-4)*2",         // 20
        "1+2*3+7+(8/4)*2+1", // 19
    };
    for (int i = 0; i < 3; i++) {
        int ret = infix_calc(ss[i]);
        cout << "result: " << ret << endl;
    }
}

int main() {
	// char *s = strdup("a+b*c+(d*e+f)*g");
    // test_data();
    test_data1();
    // cout << infix_calc("(1*2-1)*2") << endl;
}
