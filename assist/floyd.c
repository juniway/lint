#include<stdio.h>
#include<stdlib.h>
#define MAX 10

void floyd(int);
int w[MAX][MAX], d[MAX][MAX][MAX];

void main()
{
int i, j,k,v;
clrscr();
printf("enter the no. of vertices\n");
scanf("%d",&v);
printf("enter the weights \n");

  for(i=1;i<=v;i++)
  {
   for(j=1;j<=v;j++)
    scanf("%d",&w[i][j]);
   }

 floyd(v);
 getch();
 }//end of main

 void floyd(int v)
 {
 int k, i,j;

  k=0;
for(i=1;i<=v;i++)
{
 for(j=1;j<=v;j++)
  d[k][i][j]=w[i][j];
 }

      for(k=1;k<=v;k++)
      {
       for(i=1;i<=v;i++)
    {
      for(j=1;j<=v;j++)
       d[k][i][j]=min(d[k-1][i][j], d[k-1][i][k]+ d[k-1][k][j]);
      }
    }

 //displayin matrix

 for(k=0;k<=v;k++)
 {
 printf(" k=%d \n",k);
   for(i=1;i<=v;i++)
   {
    printf("\n");
     for(j=1;j<=v;j++)
     printf("\t %d",d[k][i][j]);
    }
    printf("\n \n ");
  }
}
