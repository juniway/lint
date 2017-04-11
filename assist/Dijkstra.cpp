#include<iostream>
#include<cstdlib>
#include<fstream>
#include<sstream>

#define INFINITY 99

using namespace std;
const int N = 20;

class Dijkstra{
    private:
        int adjMatrix[N][N];
        int predecessor[N],distance[N];
        bool mark[N]; //keep track of visited node
        int source;
        int numOfVertices;
    public:

    /*
    * Function read() reads No of vertices, Adjacency Matrix and source
    * Matrix from the user. The number of vertices must be greather than
    * zero, all members of Adjacency Matrix must be postive as distances
    * are always positive. The source vertex must also be positive from 0
    * to noOfVertices - 1
    */
        void read();
    /*
    * Function initialize initializes all the data members at the begining of
    * the execution. The distance between source to source is zero and all other
    * distances between source and vertices are infinity. The mark is initialized
    * to false and predecessor is initialized to -1
    */
        void initialize();

    /*
    * Function getClosestUnmarkedNode returns the node which is nearest from the
    * Predecessor marked node. If the node is already marked as visited, then it search
    * for another node.
    */
        int getClosestUnmarkedNode();
    /*
    * Function calculateDistance calculates the minimum distances from the source node to
    * Other node.
    */
        void calculateDistance();
    /*
    * Function output prints the result
    */
        void output();
        void printPath(int);
}; // end of class definition

void Dijkstra::read(){
	/*
	int topo[N][N] = {	{ 0,  4,  2, 99, 99, 99},
						{ 4,  0,  1,  5, 99, 99},
						{ 2,  1,  0,  8, 10, 99},
						{99,  5,  8,  0,  2,  6},
						{99, 99, 10,  2,  0,  3},
						{99, 99, 99,  6,  3,  0}};
	
	for(int i=0; i<N; ++i)
		for(int j=0; j<N; ++j)
			adjMatrix[i][j] = topo[i][j]
	*/
	
	// read a topo from file
	ifstream readintopo;
	readintopo.open("topo");
	string buff="";
	stringstream ss;
	if(readintopo.is_open()){
		int line =-1;
		//int distance=0;
		//int pos=0;
		while(readintopo.good()){
			getline(readintopo, buff);
			ss.str("");	// you have to use this to clear out the stream before you use it again
			ss<<buff;

			if(readintopo.eof()) break; // prevent getting a newline at end
			if(line==-1)
				{numOfVertices = atoi(buff.c_str()); ++line;}
			else if(line>=0){
				//cout<<"buff="<<buff<<endl;
				//cout<<"ss.str()="<<ss.str()<<endl;
				for(int i =0; i<numOfVertices; ++i){
					/*pos = buff.find(" ");
					distance = atoi((buff.substr(0, pos)).c_str());
					adjMatrix[line][i] = distance;
					buff = buff.substr(pos+1, buff.length()-pos);*/
					ss>>adjMatrix[line][i];
				}
				//distance = atoi(buff.c_str());
				//adjMatrix[line][numOfVertices -1] = distance;
				++line;
			}
		}
		cout<<"line="<<line<<endl;
		readintopo.close();
	}
	for(int i=0; i<numOfVertices; ++i){
		for(int j=0; j<numOfVertices; ++j)
			cout<<adjMatrix[i][j]<<" ";
		cout<<endl;
	}
	
	cout<<"Enter the source vertex\n";
	cout<<"It should be within the range [0, "<<numOfVertices-1<<"]."<<endl;
    cin>>source;
    while((source<0) && (source>numOfVertices-1)) {
        cout<<"Source vertex should be between 0 and"<<numOfVertices-1<<endl;
        cout<<"Enter the source vertex again\n";
        cin>>source;
    }
}

void Dijkstra::initialize(){
    for(int i=0; i<numOfVertices; i++){
        mark[i] = false;
        predecessor[i] = -1;
        distance[i] = INFINITY;
    }
    distance[source]= 0;
}

int Dijkstra::getClosestUnmarkedNode(){
    int minDistance = INFINITY;
    int closestUnmarkedNode;
    for(int i=0; i<numOfVertices; i++){
        if((!mark[i]) && (minDistance >= distance[i])){
            minDistance = distance[i];
            closestUnmarkedNode = i;
        }
    }
    return closestUnmarkedNode;
}

void Dijkstra::calculateDistance(){
    initialize();
    int minDistance = INFINITY;
    int closestUnmarkedNode;
    int count = 0;
    while(count < numOfVertices){
        closestUnmarkedNode = getClosestUnmarkedNode();
        mark[closestUnmarkedNode] = true;
        for(int i=0; i<numOfVertices; i++){
            if((!mark[i]) && (adjMatrix[closestUnmarkedNode][i]>0)){
                if(distance[i] > distance[closestUnmarkedNode]+adjMatrix[closestUnmarkedNode][i]){
                    distance[i] = distance[closestUnmarkedNode]+adjMatrix[closestUnmarkedNode][i];
                    predecessor[i] = closestUnmarkedNode;
                }
            }
        }
        count++;
    }
}

void Dijkstra::printPath(int node){
    if(node == source)
        cout<<(char)(node + 97);
    else if(predecessor[node] == -1)
        cout<<"No path from "<<source<<"to "<<(char)(node + 97)<<endl;
    else{
        printPath(predecessor[node]);
        cout<<"->"<<(char) (node + 97);
    }
}

void Dijkstra::output(){
    for(int i=0; i<numOfVertices; i++){
        if(i == source)
            cout<<(char)(source + 97)<<"->"<<(char)(source + 97);
        else
            printPath(i);
        cout<<"......"<<distance[i]<<endl;
    }
}

int main(){
    Dijkstra G;
    G.read();
    G.calculateDistance();
    G.output();
    return 0;
}

