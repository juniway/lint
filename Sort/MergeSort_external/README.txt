The mergesort class is a template and can be declared

mergesort

<datatype>
ms("inputFileName", "outputFileName");
for internal sorting or

mergesort

<datatype>
ms("inputFileName", "outputFileName", maxDequeSize);
for external sorting, where maxDequeSize is an integer that states the largest amount of entries a deque will have in memory at one time.

The driver sorts a 100,000 list of doubles externally, and a list 50 string in main memory. No external storage library is used. All external storage is done using text files and fstream. The input files used by the driver are "data.txt" and "data2.txt". The output files are "test1results.txt" and "test2results.txt".

This program was created using Microsoft Visual Studio 2012.