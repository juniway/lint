//get my net number.

#include<iostream>
#include<string>
#include<sstream>
#include<unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
string strset="0123456789";

int main(){
	char str[128];
	string strn;
	stringstream ss;
	//struct hostent *hent;
	gethostname(str, sizeof str);
	
	string namestr(str);
	int pos = namestr.find_first_of(strset);
	strn = namestr.substr(pos, pos+1);
	ss<<strn;
	int node;
	ss>>node;
	cout<<"node number is:"<<node<<endl;
	return 0;

}
/*
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    char hname[128];
    struct hostent *hent;
    int i;

    gethostname(hname, sizeof(hname));

    //hent = gethostent();
    hent = gethostbyname(hname);

    printf("hostname: %s/n address list: ", hent->h_name);
    for(i = 0; hent->h_addr_list[i]; i++) {
        printf("%s/t", inet_ntoa(*(struct in_addr*)(hent->h_addr_list[i])));
    }
    return 0;
}
*/