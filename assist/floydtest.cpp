
/********************************test.cpp file**************************************/
#include<iostream>
#include "graph.h"
using namespace std;

extern const int INF=99;
int main(){
	int i,j,**M1;
	int tempM[5][5] = {	{  0,   3,   8, INF,  -4},
						{INF,   0, INF,   1,   7},
						{INF,   4,   0, INF, INF},
						{  2, INF,  -5,   0, INF},
						{INF, INF, INF,   6,   0}};

	M1 = new int*[5];
	for(i = 0;i<5;i++){
		M1[i] = new int[5];
		for(j = 0;j<5;j++){
			M1[i][j] = tempM[i][j];
		}
	}
	graph G1(5,M1);
	floydWarshall(G1);
	return 0;
}
/**************************************end of test.cpp****************************/