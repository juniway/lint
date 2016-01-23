// Implementation of Chaining Hash Table
#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>

using namespace std;

template <typename HashedObj>
class HashTable{

	public:
	    explicit HashTable(int size = 10);
		
		bool contains(const HashedObj& x) const;
		
		void makeEmpty();
		bool insert(const HashedObj& x);
		bool remove(const HashedObj& x);
		
	private:
		vector<list<HashedObj>> theList;  // the array of lists(Vector of linked lists)
		int currentSize; // Current $elements in the hash-table
		
		void rehash();
		int myhash(const HashedObj& x) const;
};

// hash functions for integers and string keys
int hash1(int key);
int hash1(const string& key);

template <typename HashedObj>
int HashTable<HashedObj>::myhash(const HashedObj& x) const{

	int hashVal = hash1(x);
	hashVal %= theList.size();  // this is the hashtable's current capacity (aka. "table size")
	if(hashVal < 0)
		hashVal += theList.size();
		
	return hashVal;
}

template <typename HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj& x){
	list<HashedObj>& whichList = theList[myhash(x)];
	if(find(whichList.begin(), whichList.end(), x) != whichList.end()) // check duplicate
		return false;
	whichList.push_back(x);
	
	//Rehash; see section 5.5
	if(++currentSize>theList.size())
		rehash(); // essentially resizes the hashtable if its getting crowded
		
	return true;
}

template <typename HashedObj>
void HashTable<HashedObj>::makeEmpty(){
	for(int i=0; i<theList.size(); i++)
		theList[i].clear();
}

template <typename HashedObj>
bool HashTable<HashedObj>::contains(const HashedObj& x) const{
	const list<HashedObj>& whichList = theList[myhash(x)];
    auto it = find(whichList.begin(), whichList.end(), x) ;
	return it!= whichList.end();
}

template <typename HashedObj>
bool HashTable<HashedObj>::remove (const HashedObj& x){
	list<HashedObj>& whichList = theList[myhash(x)];
	auto itr = find(whichList.begin(), whichList.end(), x);
	
	if(itr == whichList.end())
		return false;
		
		whichList.erase(itr);
		--currentSize;
		return true;
}

//Example of an Employee class

class Employee{

public:
	const string& getName() const{
		return name;
	}
	
	// all hash objects must define == and != operators
	bool operator==(const Employee& rhs) const{
		return getName() == rhs.getName();
	}
	bool operator!=(const Employee& rhs) const{
		return !(*this == rhs);
	}
	
	// additional public members not shown
	
private:
	string name;
	double salary;
	int seniority;
	
	// additional private members not shown
};

int hash1(const Employee& item){ // hash function to handle Employee object type
	return hash1(item.getName());
}

