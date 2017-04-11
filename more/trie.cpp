// https://github.com/calmhandtitan/algorepo/blob/master/stringTheory/trie.cpp
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
using namespace std;

struct node{
	int prefix_count;
	bool isEnd;
	struct node *child[26];
}*root;

class Trie{
public:
	void init(){
	//	root = (node*)malloc(sizeof(node));
		root = new node();
		root->isEnd = false;
		root->prefix_count = 0;
	}

	void insert(string word){
		node *current = root;
		current->prefix_count++;
		
		for(int i = 0 ; i < word.length(); ++i){
			int letter = (int)word[i] - (int)'a';	//extrct first character of word
			if(current->child[letter] == nullptr)
				current->child[letter] = new node();

			current->child[letter]->prefix_count++;
			current = current->child[letter];		
		}
		current->isEnd = true;
	}

	bool search(string word){
		node *current = root;
		for(int i = 0 ; i < word.length(); ++i){
			int letter = (int)word[i] - (int)'a';
			if(current->child[letter] == nullptr)
				return false;		//not found
			current = current->child[letter];
		}
		return current->isEnd;
	}

	int words_with_prefix(string prefix){
		node *current = root;
		for(int i = 0; i < prefix.length() ; ++i){
			int letter = (int)prefix[i] - (int)'a';
			if(current->child[letter] == nullptr)
				return 0;
			else
				current = current->child[letter];
		}
		return current->prefix_count;
	}
private:
    Node* root;
};



int main(){
	init();
	string s = "chandan";
	insert(s);
	s = "mittal";
	insert(s);
	s = "chirag";
	insert(s);
	s = "shashank";
	insert(s);
	s = "abhinav";
	insert(s);
	s = "arun";
	insert(s);
	s = "abhishek";
	insert(s);
	
	if(search("chandan"))
		printf("found chandan\n");
	if(search("arun"))
		printf("found arun\n");
	if(search("abhi"))
		printf("found abhi\n");
	else
		printf("not found abhi\n");
	
	printf("no of words with prefix abhi are %d\n",words_with_prefix("abhi"));
	printf("no of words with prefix ch are %d\n",words_with_prefix("ch"));
	printf("no of words with prefix k are %d\n ",words_with_prefix("k"));

	return 0;
}