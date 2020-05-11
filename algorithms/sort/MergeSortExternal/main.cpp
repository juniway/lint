//in main.cpp
#include "main.h"

int main(){
	//get the start time
	clock_t tStart = clock();

	//sort "data.txt" using external mergesort and the maximum number of decks in memory = 7694 and doubles
	mergesort<double> test1("data.txt", "test1results.txt", 7694);

	//print the time it took to execute
	printf("\nTime taken: %.2fs\n\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

	//get the current time
	tStart = clock();

	//sort "data.txt using mergesort in memory and strings
	mergesort<string> test2("data2.txt", "test2results.txt");

	//print the time it took to execute
	printf("\nTime taken: %.2fs\n\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

	cout << "Press ENTER to exit... " << flush;
	cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );

	return(0);
}