#include<stdio.h>
#include<vector>
#include <iostream>

using namespace std;

int main(){
	int i = 0, j = 0;

	vector< vector<int> > Array;
	vector< int > line;
	for(j = 0; j < 10; j++){
		Array.push_back(line);//Ҫ��ÿһ��vector��ʼ���������ܴ���Ԫ�ء�
		for (i = 0; i < 9; i++){
			Array[j].push_back(i);
		}
	}

	for(j = 0; j < 10; j++){
		for(i = 0; i < Array[j].size(); i++){
			cout << Array[j][i] << "  ";
		}
		cout<< endl;
	}
	return 0;
}