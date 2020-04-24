#include <iostream>
#include <stack>

using namespace std;

bool isNotOperator(char c) {
  return c != '*' && c != '+' && c!= '(' && c != ')';
}

//获取符号的优先级
int getPriority(char c) {
	int priority = -1;
	switch (c) {
    case '+':
      priority = 1;
      break;
    case '*':
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

int main() {
	char *s = "a+b*c+(d*e+f)*g";
	stack<char> stk;

	while (*s != '\0' || !stk.empty()) {
		char current = *s;
		// 如果字符串完毕，只有栈里面有元素，那么就全部弹出并输出
		if (current == '\0') {  
			while (!stk.empty()) {  
				cout << stk.top();
				stk.pop();
			}
			break;
		}

		// 说明不是操作符,直接输出
		if (isNotOperator(current)) {
			cout << current;
		} else if (current == ')') {
			//1.弹出元素并输出直到'('
			while(stk.top() != '(') {
				cout << stk.top();
				stk.pop();
			}
			//2.将"("也出栈
			stk.pop();
		} else {
			// 下面是普通操作符的情况
			// 1.弹出栈元素直到发现优先级更低的元素
			while(!stk.empty() && getPriority(current) <= getPriority(stk.top()) && stk.top() != '(') {
				cout << stk.top();
				stk.pop();
			}
			//将本操作符入栈
			stk.push(current);
		}
		s++;
	}
	cout << endl;
	return 0;
}
