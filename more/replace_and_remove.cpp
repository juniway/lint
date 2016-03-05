// <Elements of Programming Interview: The Insiders' Guide>
// 6.21
/*
	Write a function which takes as input a string s, and removes each "b"
	and replaces each "a" by "dd". Use O(1) additional storage
	--assume s is stored in an array that has enough space for the final result.
*/

#include <string>
#include <iostream>
using namespace std;	

string remove_and_replace(string s){

	int write_idx = 0, a_count = 0;

	for(const char&c : s){
		if(c != 'b')
			s[write_idx++] = c;
		if(c == 'a')
			++a_count;
	}

	// allocate space according to the number of 'a'
	s.resize(write_idx + a_count);

	// replace 'a' with 'dd'
	int cur_idx = write_idx - 1;
	write_idx = s.size() - 1;

	cout << cur_idx << endl;

	// 替换a为dd时，从字符串尾部开始
	while(cur_idx >= 0){
		if(s[cur_idx] == 'a'){
			s[write_idx--] = s[write_idx--] = 'd';

			// same as above
			// s[write_idx--] = 'd';
			// s[write_idx--] = 'd';
		}
		else{
			s[write_idx--] = s[cur_idx];
		}
		--cur_idx;
	}
	cout << s << endl;
}

int main(){
	string str("abbbckv");
	replace_and_remove(str);
}