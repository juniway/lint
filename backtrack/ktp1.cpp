
// http://www.csegeek.com/csegeek/view/tutorials/algorithms/backtrack/backtrack_part3.php
// Backtracking

// Problem :-
// Solve the Knight's tour problem i.e find a Knight's tour on a 8 x 8 chessboard.
// A Knight's tour is a sequence of moves of Knight on a chessboard such that the knight visits every square exactly once.

// Solution :-
// A Knight is placed on the first cell of an empty chessboard and can move according to the chess rules.
// At any point on the chessboard, the knight have a maximum of 8 possible options to make a move.
// 1) Suppose, the knight is currently in cell ( x , y ) and it chooses one of the possible moves to a cell
//   (if the cell is not visited previously and the move is indeed a valid one ).
//   Then, we move the knight to that cell and check recursively whether we can find a solution from that cell.
//   If the solution exists, then that cell is marked as visited and then again
//   knight chooses one of the possible moves and follows same steps.
// 2) If the solution doesn't exits, then the knight backtracks to the previous cell ( x , y ) and
//    tries out other possible alternatives.
//    When all the cells are visited, we have found a sequence of knight moves which visits every cell
//    on the chessboard exactly once.

#include <iostream>
#include <chrono>
#define N 8
using namespace std::chrono;
using namespace std;


// defines a structure for chess moves
// each chess has 8 move directions
struct chess_moves {
   // 'x' and 'y' coordinates on chess board
   int x, y;
};

// displays the knight tour solution
void printTour(int tour[N][N]) {
   int i, j;
   for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
          cout << tour[i][j] << "\t";
      }
      cout << endl;
   }
}

// check if the next move (as per knight's constraints) is possible
bool isMovePossible(chess_moves next_pos, int tour[N][N]) {
   int i = next_pos.x;
   int j = next_pos.y;
   if ((i >= 0 && i < N) && (j >= 0 && j < N) && (tour[i][j] == 0))
      return true;
   return false;
}


// recursive function to find a knight tour
bool findTour(int tour[N][N], chess_moves move_delta[], chess_moves cur_pos, int move_count) {
   int i;
   chess_moves next_pos;
   if (move_count == N * N - 1) {
      // Knight tour is completed
      // When all cells on the chess board has been visited by knight once
      printTour(tour);
      return true;
   }

   // try out the possible moves starting from the current position
   for (i = 0; i < N; i++) {
      // get the next move
      next_pos.x = cur_pos.x + move_delta[i].x;
      next_pos.y = cur_pos.y + move_delta[i].y;

      if (isMovePossible(next_pos, tour)) {
         // if the move is possible
         // increment the move count and store it in tour matrix
         tour[next_pos.x][next_pos.y] = move_count + 1;           // Set
         if (findTour(tour, move_delta, next_pos, move_count + 1)) { // 增加一个返回值只是为了用于打印是否存在一个解。但是一旦加了返回值，就只会输出一个解。
            return true;
         } else {
            // this move was invalid, try out other possiblities
            tour[next_pos.x][next_pos.y] = 0;                     // Unset
         }
      }
   }
   return false;
}

int sol_cnt = 0;

void findTour1(int tour[N][N], chess_moves move_delta[], chess_moves cur_pos, int move_count) {
   chess_moves next_pos;
   if (move_count == N * N - 1) {
      // Knight tour is completed
      // When all cells on the chess board has been visited by knight once
      printTour(tour);
      ++sol_cnt;
      return;
   }

   // try out the possible moves starting from the current position
   for (int i = 0; i < N; i++) {
      // get the next move
      next_pos.x = cur_pos.x + move_delta[i].x;
      next_pos.y = cur_pos.y + move_delta[i].y;

      if (isMovePossible(next_pos, tour)) {
         // if the move is possible
         // increment the move count and store it in tour matrix
         tour[next_pos.x][next_pos.y] = move_count + 1;        // Set
         findTour(tour, move_delta, next_pos, move_count + 1);
         tour[next_pos.x][next_pos.y] = 0;                     // Unset
      }
   }
   // return false;
}

// wrapper function
void knightTour() {
   int tour[N][N];  // tour 用于存每个格子是第几步
   int i, j;

   // initialize tour matrix
   for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
         tour[i][j] = 0;
      }
   }

   // all possible moves that knight can take
   chess_moves move_delta[8] = { {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
                              {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

   // knight tour starts from coordinate (0,0)
   chess_moves cur_pos = {0, 0};

   // find a possible knight tour using a recursive function
   // starting from current move
   // if(findTour(tour, move_delta, cur_pos, 0) == false) {
   //    cout<<"\nKnight tour does not exist";
   // } else {
   //    cout<<"\nTour exist ...\n";
   //    // printTour(tour);
   // }

   findTour1(tour, move_delta, cur_pos, 0);
   cout << "solutions: " << sol_cnt << endl;
}

// main
int main() {

   auto t1 = high_resolution_clock::now();

   knightTour();
   auto t2 = high_resolution_clock::now();
   std::cout << "elapsed time:" << duration_cast<milliseconds>(t2 - t1).count() << "ms\n";
   cout<<endl;
   return 0;
}