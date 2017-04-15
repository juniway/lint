[BackTracking Problem] Maze
// http://www.geeksforgeeks.org/backttracking-set-2-rat-in-a-maze/
We have discussed Backtracking and Knight’s tour problem in Set 1. 
Let us discuss Rat in a Maze as another example problem that can be solved using Backtracking.

A Maze is given as N*N binary matrix of blocks where source block is the upper left most block 
i.e., maze[0][0] and destination block is lower rightmost block i.e., maze[N-1][N-1]. 
A rat starts from source and has to reach destination. The rat can move only in two directions: forward and down.
In the maze matrix, 0 means the block is dead end and 1 means the block can be used in the path from source to destination. 
Note that this is a simple version of the typical Maze problem. For example, a more complex version can be that the rat can move in 4 directions and a more complex version can be with limited number of moves.

Following is an example maze.

Very well explained but it will fail for the case in which rat has to travel left or up and then the normal path 
ex 
1 1 1 0 0
0 0 1 0 0
0 1 1 0 0 
0 1 0 0 0
0 1 1 1 1
please take a closer look at the problem statement. It is clearly mentioned that the rat can only move forward (or right) and down.

#include <stdio.h>
// Maze size
#define N 4 
 
bool solve(int maze[N][N], int x, int y, int sol[N][N]);
 
/* A utility function to print solution matrix sol[N][N] */
void printSolution(int sol[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf(" %d ", sol[i][j]);
        printf("\n");
    }
}
 
/* A utility function to check if x,y is valid index for N*N maze */
bool isSafe(int maze[N][N], int x, int y)
{
    // if (x,y outside maze) return false
    if(x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1)
        return true;
 
    return false;
}
 
/* This function solves the Maze problem using Backtracking.  It mainly uses
solve() to solve the problem. It returns false if no path is possible,
otherwise return true and prints the path in the form of 1s. Please note that
there may be more than one solutions, this function prints one of the feasible
solutions.*/
bool solveMaze(int maze[N][N])
{
    int sol[N][N] = {
    	{0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
 
    if(solve(maze, 0, 0, sol) == false)
    {
        printf("Solution doesn't exist");
        return false;
    }
 
    printSolution(sol);
    return true;
}
 
/* A recursive utility function to solve Maze problem */
bool solve(int maze[N][N], int x, int y, int sol[N][N])
{
    // if (x,y is goal) return true
    if(x == N-1 && y == N-1)
    {
        sol[x][y] = 1;
        return true;
    }
 
    // Check if maze[x][y] is valid
    if(isSafe(maze, x, y) == true)
    {
        // mark x,y as part of solution path
        sol[x][y] = 1;
 
        /* Move forward in x direction */
        if (solve(maze, x+1, y, sol) == true)
            return true;
 
        /* If moving in x direction doesn't give solution then
           Move down in y direction  */
        if (solve(maze, x, y+1, sol) == true)
            return true;
 
        /* If none of the above movements work then BACKTRACK: 
            unmark x,y as part of solution path */
        sol[x][y] = 0;
        return false;
    }   
 
    return false;
}
 
// driver program to test above function
int main()
{
    int maze[N][N]  =  {
    	{1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };
 
    solveMaze(maze);
    getchar();
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define N 4
int solve_me(int row_arr[],int col_arr[],int index,int i,int j,int maze[N][N])
{
	if(i>=N||j>=N)
	return 0;
	if(i==N-1 && j==N-1 && maze[i][j]==1)
	{
		row_arr[index]=i;
		col_arr[index]=j;
  	return 1;
	}
	if(maze[i][j]==0)
	return 0;
	
  row_arr[index]=i;
	col_arr[index]=j;
 	if(solve_me(row_arr,col_arr,index+1,i+1,j,maze))
	return 1;
	else
	return solve_me(row_arr,col_arr,index+1,i,j+1,maze);
}

int main()
{
    int maze[N][N]  =  { {1, 0, 0, 0},
        				 {1, 1, 0, 1},
        				 {0, 1, 0, 0},
        				 {1, 1, 1, 1}
    };
 	int row_arr[2*N], i, j, col_arr[2*N];
	int a= solve_me(row_arr, col_arr, 0, 0, 0, maze);
   		if(a!=1)
   		{	
   			cout<<"No Possible Path"<<endl;
   		}
   		else
   		{
   			for(i=0;i<N;i++)
   			for(j=0;j<N;j++)
   			{
   				maze[i][j]=0;
   			}
   			for(i=0;i<2*N-1;i++)
   			maze[row_arr[i]][col_arr[i]]=1;
   			for(i=0;i<N;i++)
   			{
   				for(j=0;j<N;j++)
   				cout<<maze[i][j]<<" ";
   				cout<<endl;
   			}
   		}
    return 0;
}