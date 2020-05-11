#include<iostream>
using namespace std;
typedef char VertexType;
typedef int EdgeType;
#define MAXVEX 100
#define INFINITY 65535
typedef struct{
	VertexType vexs[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;

int main(){
	MGraph *G=new MGraph;
	int i,j,k,w;
	cout<<"输入定点数和边数："<<endl;
	cin>>G->numVertexes>>G->numEdges;
	
	for(i=0;i<G->numVertexes;++i)
		cin>>G->vexs[i];
		
	for(i=0;i<G->numVertexes;++i)
		for(j=0;j<G->numVertexes;++j)
			G->arc[i][j]=INFINITY; //ÁÚ½Ó¾ØÕó³õÊ¼»¯
	
	for(k=0;k<G->numEdges;++k){
		cout<<"ÊäÈë±ß£¨vi,vj£©ÉÏµÄÏÂ±êi¡¢ÏÂ±êjºÍÈ¨Öµw:"<<endl;
		cin>>i>>j;
		G->arc[i][j]=w;
		G->arc[j][i]=G->arc[i][j];//ÓÉÓÚÊÇÎÞÏòÍ¼£¬¾ØÕó¶Ô³Æ
	}
	
	for(i=0;i<G->numVertexes;++i)
		for(j=0;j<G->numVertexes;++j)
			cout<<G->arc[i][j];
	return 0;
}


