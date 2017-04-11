/****************************graph.cpp file***************************************/
#include<iostream>
#include "graph.h"
using namespace std;

const int INF=99;
int getMin(int a, int b){
	if(a<b)
		return a;
	else
		return b;
}
graph::graph(int n,int ** newMatrix){
    int i,j;
    matrix = newMatrix;
 nodeNumber = n;
 shortestPath = new int*[n];
    for(i = 0;i<n;i++){
  shortestPath[i] = new int[n];
  for(j = 0;j<n;j++)
  {shortestPath[i][j] = matrix[i][j];}
 }
 cout<<"the graph is like:"<<endl;
 for(i = 0;i<n;i++){
  for(j = 0;j<n;j++){
   cout<<shortestPath[i][j]<<" ";
  }
  cout<<endl;
 }
}
void floydWarshall(graph &G){
 int i,j,k,n = G.nodeNumber;
     int **temp;
 for(k = 0;k<n;k++){
 
        temp = new int*[n];
  for(i = 0;i<n;i++){
   temp[i] = new int[n];
   for(j = 0;j<n;j++){
    if(G.shortestPath[i][k]!=INF && G.shortestPath[k][j] != INF)
    temp[i][j] = getMin(G.shortestPath[i][j],G.shortestPath[i][k]+G.shortestPath[k][j]);
    else
    temp[i][j] = G.shortestPath[i][j];
   }
  }
  G.shortestPath = temp;
  cout<<"in the "<<k<<"th iteration, the result is:"<<endl;
  for(i = 0;i<n;i++){
   for(j = 0;j<n;j++){
    cout<<G.shortestPath[i][j]<<" ";
   }
   cout<<endl;
  }

 }
 for(i = 0;i<n;i++)
	delete [] temp[i];
 delete [] temp;
}
/***************************************end of graph.cpp file************************/