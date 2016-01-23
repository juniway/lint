	

/*

  Filename: knightour.cpp
  Author  : Piyush Kumar

  To Compile: use g++ knightour.cpp -O3 -o knight
  To Run    : ./knight
 
  The purpose of this program is to demonstrate some simple C++ features.
  (Copy constructor, operator overloading <<, friend function) 
  It also shows how to implement simple backtracking/recursive solutions.

  Written for : OOP in C++ Class, COP 3330, FSU. 

  Our problem:  From an arbitrary starting position, find a knight's tour for
  a given size grid. 
 
  What is a knight tour? (From wikipedia)

  A knight's tour of a chessboard (or any other grid) is a sequence of moves 
  (i.e., a tour) by a knight chess piece (which may only make moves which 
  simultaneously shift one square along one axis and two along the other) 
  such that each square of the board is visited exactly once 
  (i.e., a Hamiltonian path).

  The output is a solution for the knights tour  problem in a sxs chessboard. 
  If you find any bugs, please let me know.
  
  Note: For the 8x8 board, and with first piece at location (7,0), 
  it takes about 5 minutes on my home machine (Pentium 4 2.99Ghz).

  Beware: If you are looking for an efficient knightour solver, this solution
  is going to disappoint you. You should try using an explicit stack and less
  space for a more efficient solution.
  
*/

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

const int move[8][2]={1,2, 2,1, 2,-1, 1,-2, -1,-2, -2,-1, -2,1, -1,2};

class tour {
	vector< vector< int > > board;
	int sx, sy, size;
		
public:
	bool findtour(tour& , int );
	
        // Constructor	
	tour(int s = 5, int startx = 0, int starty = 0)
		:sx(startx), sy(starty), size(s)
	{
		// Get the board to size x size
		board.resize(size);
		for(int i = 0; i < size; ++i)
			board[i].resize(size);

		// Fill the board with -1s
		for(int i = 0; i < size; ++i)
		  for(int j = 0; j < size; ++j) 
			board[i][j] = -1;

		// Move 0
		board[sx][sy] = 0;

		// Solve the problem
		if(!findtour(*this, 0)) 
		  cout << "No solutions found\n";
	}		
	
        // Copy constructor
	tour(const tour& T): sx(T.sx), sy(T.sy), size(T.size){
		this->board.resize(size);
		for(int i = 0; i < size; ++i)
			board[i].resize(size);

		// Copy the board
		for(int i = 0; i < size; ++i)
		  for(int j = 0; j < size; ++j)	
		    board[i][j] = T.board[i][j];
	}
	
        // Function to output class to ostream
        friend std::ostream& operator<<
	  ( std::ostream& os, const tour& T );
};

// Implementation of the overloaded << which is a friend of tour...
std::ostream& operator<<( std::ostream& os, const tour& T ){
  os << endl;
  int size = T.size;

  os << " +"; for(int i = 0; i < size*5-1; ++i) os << "-";
  os << "+\n";

  for(int i = 0; i < size; ++i){ 
    os << " | "; 
    for(int j = 0; j < size; ++j)
      os <<  setw(2) << T.board[i][j] << " | ";
    os << endl;

    os << " +"; for(int i = 0; i < size*5-1; ++i) os << "-";
    os << "+\n";

  }


  return os;
}

// A recursive function to find the knight tour.
bool tour::findtour(tour& T, int imove){
        if(imove == (size*size - 1)) return true;

        // make a move
	int cx = T.sx;
	int cy = T.sy;
        int cs = T.size;

        for ( int i = 0; i < 8; ++i){
	  int tcx = cx + move[i][0];
	  int tcy = cy + move[i][1];
	  if (
		  // Is this a valid move? 
                  (tcx >= 0) &&  (tcy >= 0)  &&  (tcx < cs) &&  (tcy < cs) &&
		  // Has this place been visited yet?
                  (T.board[tcx][tcy] == -1)
             ){
		tour temp(T);
		temp.board[tcx][tcy] = imove+1;
		temp.sx = tcx;
		temp.sy = tcy;
		if(findtour(temp, imove+1)) {
		  cout << "Solution found\n";
		  cout << temp << endl;
		  exit(1);
		}
   	  } // legal move?
        } // for
		
        return false;
}


int main(void){
	tour T;
	return 0;
}
