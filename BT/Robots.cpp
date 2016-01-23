// http://www.csegeek.com/csegeek/view/tutorials/algorithms/backtrack/backtrack_part1.php

Backtracking

Problem :- 
Given a maze in the form of a matrix of size n x n. A robot is placed at cell ( 0, 0 ).
Print all possible paths that robot can take to reach the last cell ( n-1, n-1 ) of the maze.
Constraint :- Robot can move rightwards ( R ) or downwards ( D ).
Consider the maze of size 3 x 3 as shown below :-
X X X         Robot is placed at ( 0, 0 )
X X X
X X X
Possible paths that robot can take are :-
X X X        X X X        X X X        X X X        X X X         X X X
X X X        X X X        X X X        X X X        X X X         X X X
X X X        X X X        X X X        X X X        X X X         X X X
DDRR        DRDR        DRRD        RDDR       RDRD         RRDD 

Solution :- 
At any point ( cell ) in the maze, robot can move horizontally ( right cell ) or vertically ( down cell ).
1 ) Suppose the robot chooses the horizontal move, we will move to the right cell and again choose one of the possible moves ( horizontal or vertical ) and repeat these steps till we reach the last cell. If at any cell, a valid movement is not possible then we backtrack and choose other alternative move.
2 ) Same steps are followed if the robot chooses the vertical move.
We try out the horizontal and vertical alternatives at every cell to find out all possible paths that the robot can take to reach the final cell in the maze. See the implementation below.

#include<iostream>
#include<string>
using namespace std;

/* print all the paths robot can take to reach cell(n-1,n-1)
   from cell(0), given a maze in the form of a matrix of size nxn
   and the robot can move only 'Right' and 'Down'
   (r_idx,c_idx) -> starting point of robot      
*/
void printRobotPaths(string path,int row,int col,int r_idx,int c_idx) {
   if ((r_idx == row-1) && (c_idx == col-1)) {
      cout<<path<<endl;
      return;
   }
   if (r_idx == row-1) {
      printRobotPaths(path+'D',row,col,r_idx,c_idx+1);
      return;
   }
   if (c_idx == col-1) {
      printRobotPaths(path+'R',row,col,r_idx+1,c_idx);
      return;
   }
   printRobotPaths(path+'D',row,col,r_idx,c_idx+1);
   printRobotPaths(path+'R',row,col,r_idx+1,c_idx);
}

// main
int main() {
   // dimensions of the maze is row x col
   int row = 3, col = 3;
   string path;
   cout<<"\nAll possible paths :-\n";
   printRobotPaths(path,row,col,0,0);
   cout<<endl;
   return 0;
}