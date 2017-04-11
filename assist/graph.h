/************************graph.h file*********************************************/
class graph{
	friend void floydWarshall(graph &);
	public:
		graph(int,int**);
	private:
		int nodeNumber;
		int **matrix;
		int **shortestPath;
};
/**************************end of graph.h file***********************************/