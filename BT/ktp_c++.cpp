
// Warnsdorff's algorithm is a heuristic method in order to solve the knight's tour. 
// It is determined by the rule of choosing the square among those that are immediately 
// accessible by the knight which would give the fewest possible knight's moves following the move to that square.

// In graph-theoretic terms, each move is made to the adjacent vertex with the least degree. 
// This algorithm may also more generally be applicable to any graph. 
// The knight's tour is a special case.

// Warnsdorff’s algorithm will suffice for any initial position of the knight on the board. 
// All the possible squares that are within reach in one move from this position are spotted, 
// and the number of moves that the knight would be able to make from each of these squares is calculated. 
// Then, the algorithm dictates that the knight move to the square that has the least number of 
// possible following moves. The process is then repeated until each square has been visited.

#include <iostream>
#include <iomanip>
#include <array>
#include <string>
#include <tuple>
#include <algorithm>
using namespace std;
 
template<int N = 8>
class Board 
{
public:
    array<pair<int, int>, 8> moves;
    array<array<int, N>, N> data;
 
    Board() 
    {
        moves[0] = make_pair(2, 1);
        moves[1] = make_pair(1, 2);
        moves[2] = make_pair(-1, 2);
        moves[3] = make_pair(-2, 1);
        moves[4] = make_pair(-2, -1);
        moves[5] = make_pair(-1, -2);
        moves[6] = make_pair(1, -2);
        moves[7] = make_pair(2, -1);
    }
    
    bool isMoveOK(int x2, int y2) const{
        if(x2 < 0 || x2 >= N || y2 < 0 || y2 >= N || data[y2][x2] != 0)
            return false;
        return true;
    }

    array<int, 8> sortMoves(int x, int y) const 
    {
        array<tuple<int, int>, 8> counts;
        for(int i = 0; i < 8; ++i) 
        {
            int dx = get<0>(moves[i]);
            int dy = get<1>(moves[i]);
 
            int c = 0;
            for(int j = 0; j < 8; ++j) 
            {
                int x2 = x + dx + get<0>(moves[j]);
                int y2 = y + dy + get<1>(moves[j]);
 
                // if (x2 < 0 || x2 >= N || y2 < 0 || y2 >= N)
                //     continue;
                // if(data[y2][x2] != 0)
                //     continue;
                if(!isMoveOK(x2, y2))
                    continue; 
                c++;
            }
 
            counts[i] = make_tuple(c, i);
        }
 
        // Shuffle to randomly break ties
        random_shuffle(counts.begin(), counts.end());
 
        // Lexicographic sort
        sort(counts.begin(), counts.end());
 
        array<int, 8> out;
        for(int i = 0; i < 8; ++i)
            out[i] = get<1>(counts[i]);
        return out;
    }
 
    void solve(string start) 
    {
        for(int v = 0; v < N; ++v)
            for(int u = 0; u < N; ++u)
                data[v][u] = 0;
 
        int x0 = start[0] - 'a';
        int y0 = N - (start[1] - '0');
        data[y0][x0] = 1;
 
        array<tuple<int, int, int, array<int, 8>>, N*N> order;
        order[0] = make_tuple(x0, y0, 0, sortMoves(x0, y0));
 
        int n = 0;
        while(n < N*N-1) 
        {
            int x = get<0>(order[n]);
            int y = get<1>(order[n]);
 
            bool ok = false;
            for(int i = get<2>(order[n]); i < 8; ++i) 
            {
                int dx = moves[get<3>(order[n])[i]].first;
                int dy = moves[get<3>(order[n])[i]].second;
 
                if(x+dx < 0 || x+dx >= N || y+dy < 0 || y+dy >= N)
                    continue;
                if(data[y + dy][x + dx] != 0) 
                    continue;
 
                ++n;
                get<2>(order[n]) = i + 1;
                data[y+dy][x+dx] = n + 1;
                order[n] = make_tuple(x+dx, y+dy, 0, sortMoves(x+dx, y+dy));
                ok = true;
                break;
            }
 
            if(!ok) // Failed. Backtrack.
            {
                data[y][x] = 0;
                --n;
            }
        }
    }
 
    template<int NN>
    friend ostream& operator<<(ostream &out, const Board<NN> &b);
};
 
template<int N>
ostream& operator<<(ostream &out, const Board<N> &b) 
{
    for (int v = 0; v < N; ++v) 
    {
        for (int u = 0; u < N; ++u) 
        {
            if (u != 0) out << ",";
            out << setw(3) << b.data[v][u];
        }
        out << endl;
    }
    return out;
}
 
int main() 
{
    Board<5> b1;
    b1.solve("c3");
    cout << b1 << endl;
 
    Board<8> b2;
    b2.solve("b5");
    cout << b2 << endl;
 
    Board<31> b3; // Max size for <1000 squares
    b3.solve("a1");
    cout << b3 << endl;
    return 0;
}

// Outputs:
// 23, 16, 11,  6, 21
// 10,  5, 22, 17, 12
// 15, 24,  1, 20,  7
// 4,  9, 18, 13,  2
// 25, 14,  3,  8, 19

// 63, 20,  3, 24, 59, 36,  5, 26
// 2, 23, 64, 37,  4, 25, 58, 35
// 19, 62, 21, 50, 55, 60, 27,  6
// 22,  1, 54, 61, 38, 45, 34, 57
// 53, 18, 49, 44, 51, 56,  7, 28
// 12, 15, 52, 39, 46, 31, 42, 33
// 17, 48, 13, 10, 43, 40, 29,  8
// 14, 11, 16, 47, 30,  9, 32, 41