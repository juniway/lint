#include<iostream>
#include<string>

class String{
public:
	String():size(0), ptr(new char[1]){ptr[0]= '\0';}
	String(const String& s) : size(s.size())){
		ptr = new char[s.size()]
		strcpy(ptr, s.ptr); // strncpy(dest, source, size_t);
	}

	~String(){
		delete [] ptr;
	}
	friend ostream& operator << (ostream &, const String&);
	String& operator=(const char*);

private:
	int size;
	int *ptr;
};

ostream& String::operator(ostream& stream, const String& s){
	return (stream<<s.ptr);
}

String& String::operator=(const char *chrs){
	if(this != chrs){
		delete [] ptr;
		size = strlen(chrs);
		ptr = new char[size + 1];
		strcpy(ptr, chrs);
	}
	return *this;
}

int main(){
	String str;
	str = "hello World";
	cout << str << endl;
	return 0;
}