#include <stdio.h>
//#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

#define SIZE 40 //设置世界大小
//#define NUMLIFE 3
//#define NUMNOCHANGE 2
#define ALIVE 1
#define DEAD 0

int state(int* a, int i, int j, int numLife, int numNoChange)
{
	int sum=*(a+(i-1)*SIZE+(j-1))+*(a+(i-1)*SIZE+(j))+*(a+(i-1)*SIZE+(j+1))
		+*(a+(i)*SIZE+(j-1))+*(a+(i)*SIZE+(j+1))
		+*(a+(i+1)*SIZE+(j-1))+*(a+(i+1)*SIZE+(j))+*(a+(i+1)*SIZE+(j+1));
	if(sum==numLife)
		return ALIVE;
	else if(sum==numNoChange)
		return *(a+(i)*SIZE+(j));
	else
		return DEAD;
}

int main(int argc, char* argv[])
{
	//运行时传递两个参数，分别是让细胞活的邻居个数(eg. 3)以及让细胞状态不变的邻居个数(eg. 2)
	int NUMLIFE=atoi(argv[1]);
	int NUMNOCHANGE=atoi(argv[2]);

	int a[SIZE][SIZE];
	int b[SIZE][SIZE];
	srand(time(0)); //必须要用这个

	//随机设置初始状态，生死各半
	for(int i=0;i<SIZE;i++)
		for(int j=0;j<SIZE;j++)
			a[i][j]=0;

	for(int i=1;i<SIZE-1;i++)
		for(int j=1;j<SIZE-1;j++)
			a[i][j]=rand()%2;

	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}

	for(int i=1; i<=200; i++)
	{
		int count=0;

		for(int i=1;i<SIZE-1;i++)
			for(int j=1;j<SIZE-1;j++)
				b[i][j]=state(&a[0][0], i, j, NUMLIFE, NUMNOCHANGE);

		for(int i=1;i<SIZE-1;i++)
			for(int j=1;j<SIZE-1;j++)
			{
				a[i][j]=b[i][j];
				count+=a[i][j];
			}

		system("clear");
		cout<<"第"<<i<<"步后，还有"<<count<<"个存活，如下"<<endl;

		for(int i=0;i<SIZE;i++)
		{
			for(int j=0;j<SIZE;j++)
			{
				if(a[i][j]==0)
					cout<<"  ";
				else
					cout<<"o ";
			}
			cout<<endl;
		}
		cout<<endl;
		system("sleep 0.2");

	}

//	system("pause");
	return 0;
}
