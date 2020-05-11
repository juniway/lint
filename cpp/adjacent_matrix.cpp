#include <iostream>
#include <vector>
using namespace std;

const int adjmatrix[9][9] = {
  {0,1,0,0,1,0,0,0,0},
  {1,0,1,0,0,0,0,0,0},
  {0,1,0,1,0,0,0,0,0},
  {0,0,1,0,0,1,0,0,0},
  {1,0,0,0,0,0,1,0,0},
  {0,0,0,1,0,0,0,0,1},
  {0,0,0,0,1,0,0,1,0},
  {0,0,0,0,0,0,1,0,0},
  {0,0,0,0,0,1,0,0,0}
};

struct Node {
  vector<Node*> neighbours;
  /* optional additional node information */
};

int main (int argc, char const *argv[]){
	/* initialize nodes */
	vector<Node> nodes(9);

	/* add pointers to neighbouring nodes */
	int i,j;
	for (i=0; i<9; ++i) {
		for (j=0; j<9; ++j) {
			if (adjmatrix[i][j]==0) continue;
			nodes[i].neighbours.push_back(&nodes[j]);
		}
	}

	/* print number of neighbours */
	for (i=0;i<9;++i) {
		cout << "Node " <<i<< " has " << nodes[i].neighbours.size() ;
		cout <<" outbound edges." << endl;
	}
	return 0;
}


