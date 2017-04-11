#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>

#include<netdb.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/select.h>
#include<sys/time.h>

#define SEND 0
#define JOIN 1
#define LEAVE 2
#define LIST 3
#define clear 4

using namespace std;
const int N = 6;
//const int port_of_me = 49999;

string types[5]={"SEND", "JOIN", "LEAVE", "LIST", "clear"};

static int receive_count =-1;
int main(int argc, char *argv[]){

	system("clear");
	srand(time(NULL));
	int port_of_me = rand()%1000+46000;
	int port_of_myrouter = 0;
	string addr_of_myrouter ="";
	
	char hname[128];
	string addr_of_me ="";
	
	//------ get host address
	gethostname(hname, sizeof(hname));
	addr_of_me = hname;
	//cout<<"addr_of_me="<<addr_of_me<<endl;
	stringstream tosend;
	string strtosend;
	
	int hostId, myrouterId, mgroup=0;
	vector<int> mgroupv;
	mgroupv.reserve(3);

	if(argc<4) {cout<<"Usage:host <hostId> <configfile> <myrouterId> <mgroupv>\n"<<endl; exit(1);}
		
	hostId = atoi(argv[1]); // cout<<"hostId="<<hostId<<endl;
	myrouterId = atoi(argv[3]);

	string buff = "";
	string matrix[N][3]={{"","",""},{"","",""},{"","",""},{"","",""},{"","",""},{"","",""}};
	int nrow_of_matrix = 0;
	int row = 0;
	size_t pos = 0;
	
	//--------- read in config file --------
	ifstream readconfig;
	readconfig.open("configfile"); //open a file
	if(readconfig.is_open()){
		while(readconfig.good()){
			getline(readconfig, buff);
			if(readconfig.eof()) break; // prevent getting a newline at end
			for(int i =0; i<2; ++i){
				pos = buff.find(" ");
				matrix[row][i] = buff.substr(0, pos);
				buff = buff.substr(pos+1, buff.length()-pos);
			}
			matrix[row][2]=buff;
			++row;
		}
		readconfig.close();
	}
	nrow_of_matrix = row;

	/*---------- print out matrix -------------------------
	for(int i=0; i<nrow_of_matrix; ++i){
		for(int j=0; j<3; ++j){
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
	*/
	
	//-------- get my router's address and port number --------
	for(int i=0; i<nrow_of_matrix; i++){
		if(atoi(matrix[i][0].c_str())==myrouterId){
			addr_of_myrouter = matrix[i][1];
			port_of_myrouter = atoi(matrix[i][2].c_str());
		}
	}
	
	if(argc==5){
		mgroupv.push_back(atoi(argv[4]));
		mgroup=atoi(argv[4]);
		// create REPORT message
		// REPORT <hostId> <mgroupv>
		tosend.str("");
		tosend<<"REPORT "<<hostId<<" "<<mgroup<<" "<<port_of_me<<" "<<addr_of_me; 
		strtosend = tosend.str();

		// create a socket to send
		int sendsockfd;
		if((sendsockfd = socket(AF_INET, SOCK_STREAM, 0))<0)
			{cout<<"create socket error!"<<endl; exit(1);}
		struct sockaddr_in myrouter_addr;
		bzero(&myrouter_addr, sizeof myrouter_addr);
		myrouter_addr.sin_family = AF_INET;
		myrouter_addr.sin_port = htons(port_of_myrouter);
		myrouter_addr.sin_addr = *((struct in_addr*)(gethostbyname(addr_of_myrouter.c_str())->h_addr)); 
		
		int rc=connect(sendsockfd, (struct sockaddr*)&myrouter_addr, sizeof(struct sockaddr));
		if(rc==0) // connect successfully
			send(sendsockfd,(char*)strtosend.c_str(), strlen(strtosend.c_str()), 0);
		close(sendsockfd);
	}
	
	fd_set fds, master;
	/*****************************************************************************/
	/***********               create a listen socket                    *********/
	/*****************************************************************************/
	
	int yes, nbytes;
	int listensockfd, connfd, maxfd;
	struct timeval tv={5,0};
	
	// define some variables to receive in coming messages
	char recvbuf[128];
	string recvbuff;
	string strdata;

	struct sockaddr_in myaddr, myrouteraddr;
	bzero(&myaddr, sizeof(myaddr));

	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(port_of_me);
	
	if((listensockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{cerr<<"create socket error:"<<strerror(errno)<<endl; return -1;}
	setsockopt(listensockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	
	//fcntl(listensockfd, F_SETFL, O_NONBLOCK);	// set listensockfd non-block
	
	if(bind(listensockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1)
		{cerr<<"create socket error: "<<strerror(errno)<<endl; return -1;}
	if(listen(listensockfd, 10) == -1)
		{cerr<<"create socket error:"<<strerror(errno)<<endl; return -1;}

	int addr_len = sizeof(struct sockaddr_in);

	/*********************\\\ End of creating listen socket ///****************************/
	/**************************************************************************************/
	
	
	/**************************************************************************************/
	/*************					create a send socket					***************/
	/**************************************************************************************/
	/**
	int sendsockfd;
	if((sendsockfd = socket(AF_INET, SOCK_STREAM, 0))<0)
		{cout<<"create socket error!"<<endl; exit(1);}
	
	struct sockaddr_in myrouter_addr;
	bzero(&myrouter_addr, sizeof myrouter_addr);
	myrouter_addr.sin_family = AF_INET;
	myrouter_addr.sin_port = htons(port_of_myrouter);
	myrouter_addr.sin_addr = *((struct in_addr*)(gethostbyname(addr_of_myrouter.c_str())->h_addr)); 
	
	//int flags = fcntl(sendsockfd, F_GETFL, 0);
	//fcntl(sendsockfd, F_SETFL, flags | O_NONBLOCK);	// set listensockfd non-block
	**/
	/**********************\\\ End of creating send socket ///*****************************/
	/**************************************************************************************/
	
	maxfd = listensockfd;
	
	while(1){	// this loop makes you can send requests multiple times

		//prompt information for the operations that user may take
		cout<<"host "<<hostId<<endl<<endl;		
		cout<<"SEND <filename> <mgroup>:"<<endl;
		cout<<"JOIN <mgroup>:"<<endl;
		cout<<"LEAVE <mgroup>: "<<endl;
		cout<<"LIST:"<<endl;
		
		string input, msgtype="";

		//int rc = connect(sendsockfd, (struct sockaddr*)&myrouter_addr, sizeof(struct sockaddr));
		//cout<<rc<<endl;
		//cerr<<strerror(errno)<<endl;
		/*
		if(rc=EINPROGRESS)
			cout<<"EINPROGRESS"<<endl;
		if(rc==EALREADY)
			cout<<"EALREADY"<<endl;
		cout<<"errno="<<errno<<endl;
		*/
		int i, ret;
		
		FD_ZERO(&master);
		FD_SET(STDIN_FILENO, &master);
		FD_SET(listensockfd, &master);
		//FD_SET(sendsockfd, &master);
		
		while(1){
			fds = master; // copy it
			//tv.tv_sec = 10;
			//tv.tv_usec = 0;
			//cout<<"i=";

			ret = select(maxfd+1, &fds, NULL, NULL, NULL);
			int error=0;
			socklen_t len;
			len=sizeof(int);
			// getsockopt(sendsockfd, SOL_SOCKET, SO_ERROR, &error, &len); 
			
			// cout<<"error="<<error<<endl;
			// cout<<"strerror(errno)="<<strerror(errno)<<endl;
			if(ret<0) {cerr<<"select error"<<endl; exit(1);}
			//else cout<<"ret="<<ret<<endl;
			for(i =0; i<=maxfd; i++){
				if(FD_ISSET(i, &fds)){
					
					if(i==listensockfd){  // listen socket
						connfd = accept(listensockfd, (struct sockaddr*)&myrouteraddr, (socklen_t *)&addr_len);
						if(connfd < 0) {cerr<<"accept error!"<<endl; continue; }
						else{
							FD_SET(connfd, &master); // add to master set
							if (connfd > maxfd) // keep track of the max
								maxfd = connfd;
						}
					}

					else if(i==connfd){ // connfd 
						
						nbytes = recv(connfd, recvbuf, sizeof recvbuf, 0);
						if(nbytes<=0){	{cerr<<"Fail to receive data!"<<endl; exit(EXIT_FAILURE);}
							if(nbytes==0)	// connection closed
								cerr<<"selectserver: socket"<<i<<"hung up"<<endl;
							else cerr<<"recv error"<<endl;
							close(i); // bye!
							FD_CLR(i, &master); // remove from master set
                        }else{  // received MCAST
								// MCAST <routerId> <srcId> <mgroup> <data>
							recvbuf[strlen(recvbuf)]='\0';
							recvbuff = recvbuf;
							int loc = recvbuff.find(" ", 0);
							loc = recvbuff.find(" ", loc+1);
							loc = recvbuff.find(" ", loc+1);
							loc = recvbuff.find(" ", loc+1);
							strdata=recvbuff.substr(loc+1, recvbuff.length()-1);
							
							cout<<"Received MCAST:"<<++receive_count<<". "<<strdata<<endl;
							close(i); // bye!
							FD_CLR(i, &master); // remove from master set
                        }
                    }/*
					else if(i==sendsockfd){	// send socket
						cout<<"I am ready"<<endl;
						send(sendsockfd, (char*)strtosend.c_str(), sizeof(strtosend.c_str()), 0);
						cout<<"finish sending"<<endl;
					}*/
					else if(i==STDIN_FILENO){ // user input
						
						getline(cin, input);
						//cout<<"input="<<input<<endl;
						pos = input.find(" ");
						if(pos!=string::npos){
							msgtype = input.substr(0, pos); 
							transform(msgtype.begin(), msgtype.end(), msgtype.begin(), ::toupper);
							input=input.substr(pos+1, input.length()-pos);
							}
						else {
							if(input!=""){
								msgtype=input;
								transform(msgtype.begin(), msgtype.end(), msgtype.begin(), ::toupper);
							}else continue;
						}
						int tindex;
						for(tindex=0; tindex<4; ++tindex){
							if(msgtype==types[tindex]) break;
						}

						string filename;
						bool wrongcommand=false;
						bool needtosend=false;
						//--------------------- for creating appropriate message ----------------
						switch(tindex){
							case JOIN:{
								//cout<<"In JOIN....."<<endl;
								mgroup = atoi(input.c_str());
								mgroupv.push_back(mgroup);
								
								// create REPORT message
								// REPORT <hostId> <mgroupv>
								tosend.str("");
								tosend<<"REPORT "<<hostId<<" "<<mgroup<<" "<<port_of_me<<" "<<addr_of_me;
								strtosend = tosend.str();
								needtosend=true;
								break;
							}
							case LEAVE:{
								mgroup = atoi(input.c_str());
								vector<int>::iterator iter = find(mgroupv.begin(), mgroupv.end(), mgroup);
								if(iter!=mgroupv.end())
									mgroupv.erase(iter);
								else cout<<"Not in mgroup yet"<<endl;
								
								// create LEAVE message
								tosend.str("");
								tosend<<"LEAVE "<<hostId<<" "<<mgroup;	// LEAVE <hostId> <mgroup>
								strtosend = tosend.str();
								needtosend=true;
								break;
							}
							
							case SEND:{
								//cout<<"In send"<<endl;
								pos = input.find(" ");
								filename = input.substr(0, pos);
								input=input.substr(pos+1, input.length() - pos);
								mgroup = atoi(input.c_str());
								//mgroupv.push_back(mgroup);
								//cout<<"file name is:"<<filename<<endl;
								string strdata = "";
								ifstream infile;
								infile.open(filename.c_str());
								if(infile.is_open()){
									while(infile.good()){
										getline(infile, strdata);
										break;
										//if(infile.eof()) 
									}
								}
								
								// create SEND message
								// SEND <hostId> <mgroupv> <data>
								tosend.str("");
								tosend<<"SEND "<<hostId<<" "<<mgroup<<" "<<strdata; 
								strtosend = tosend.str();
								needtosend=true;
								break;
							}
							
							case LIST:{
								//cout<<"In LIST........"<<endl;
								if(mgroupv.size()!=0){
									vector<int>::const_iterator iter = mgroupv.begin();
									for(; iter!=mgroupv.end(); ++iter)
										cout<<*iter<<" ";
									cout<<endl;
								}
								else cout<<"No mgroup yet!"<<endl;
								break;
							}
							
							case clear:{
								receive_count=-1;
								system("clear");
								cout<<"host "<<hostId<<endl<<endl;		
								cout<<"SEND <filename> <mgroup>:"<<endl;
								cout<<"JOIN <mgroup>:"<<endl;
								cout<<"LEAVE <mgroup>: "<<endl;
								cout<<"LIST:"<<endl;
								break;
							}
							default:{	wrongcommand=true;
										cout<<"You typed wrong message!"<<endl;
									}
						}//------end of switch()-----> end of creating appropriate messages -----------
						/**/
						
						if(needtosend && !wrongcommand){
							
							int sendsockfd;
							if((sendsockfd = socket(AF_INET, SOCK_STREAM, 0))<0)
								{cout<<"create socket error!"<<endl; exit(1);}
	
							struct sockaddr_in myrouter_addr;
							bzero(&myrouter_addr, sizeof myrouter_addr);
							myrouter_addr.sin_family = AF_INET;
							myrouter_addr.sin_port = htons(port_of_myrouter);
					myrouter_addr.sin_addr = *((struct in_addr*)(gethostbyname(addr_of_myrouter.c_str())->h_addr)); 
	
							//int flags = fcntl(sendsockfd, F_GETFL, 0);
							//fcntl(sendsockfd, F_SETFL, flags | O_NONBLOCK);	// set listensockfd non-block
							//cout<<"Send out:"<<strtosend<<endl;
							int rc=connect(sendsockfd, (struct sockaddr*)&myrouter_addr, sizeof(struct sockaddr));

							if(rc==0) {// connect successfully	
								send(sendsockfd, (char*)strtosend.c_str(), strlen(strtosend.c_str()), 0);
							}
								close(sendsockfd);
						}
					}
				}
			
			}
		}
	}
	
	close(listensockfd);
	return 0;

}

