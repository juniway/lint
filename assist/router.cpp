#include<iostream>
#include<iomanip>
#include<vector>
#include<queue>
#include<string>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<cstring>
#include<errno.h>

#include "forward.h"

#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>

// send from hosts
#define REPORT 0
#define LEAVE 1
#define SEND 2

// send from routers
#define JOIN 3
#define PRUNE 4
#define REGISTER 5
#define SSJOIN 6
#define MCAST 7

using namespace std;

const int NSET = 8;
string msgSet[NSET]={"REPORT", "LEAVE", "SEND", "JOIN", "PRUNE", "REGISTER", "SSJOIN", "MCAST"};

const int N = 6;
const int NVertex = 10;
const int INF = 99;

int source;
static int prev[N];

bool back = false;
bool nothing = false;
static int nrow_of_matrix, nrow_of_rp, nrow_of_topo;

string matrix[N][3]={{"","",""},{"","",""},{"","",""},{"","",""},{"","",""},{"","",""}}; //Initialize
int rp[N][2];
vector< vector<int> > topo;

void printpathto(int );

void dijkstra(int s, const vector< vector<int> >& tp, const int size_tp){

	int mark[N];
	int dist[N];
	int nearestUnmarkedNode = 0;

	// initialize
	for(int i=0; i<size_tp; i++){
		mark[i] = false;
		prev[i] = -1;
		dist[i] = INF;
	}
	dist[s]= 0;

    int count = 0;
    while(count<size_tp){
		int min= INF;
		for(int i=0; i<size_tp; i++){
			if((!mark[i]) && (min >= dist[i])){
				min = dist[i];
				nearestUnmarkedNode = i;
			}
		}
		mark[nearestUnmarkedNode] = true;
		for(int i=0; i<size_tp; i++){
			if((!mark[i]) && (tp[nearestUnmarkedNode][i]>0)){
				if(dist[i] > dist[nearestUnmarkedNode]+tp[nearestUnmarkedNode][i]){
					dist[i] = dist[nearestUnmarkedNode]+tp[nearestUnmarkedNode][i];
					prev[i] = nearestUnmarkedNode;
				}
			}
		}
		count++;
	}
}

void printpathto(int node){
	if(node==source)
		cout<<node;
	else if(prev[node]==-1)
		cout<<"No path from "<<source<<"to "<<node<<endl;
	else{
		printpathto(prev[node]);
		cout<<"->"<<node;
	}
}

void pushin(queue<int>& q, int dest){ // push dest into the queue
	if(dest==source)
		q.push(dest);
	else{
		pushin(q, prev[dest]);
		q.push(dest);
	}
}

int getrpId(const int& mgpid){
		// look up configrp to find the rp router id
	int rpid;
	for(int i=0; i<nrow_of_rp; ++i){
		if(rp[i][0]==mgpid){
			rpid = rp[i][1];
			break;
		}
	}
	return rpid;

}
void get_nextrouteraddr_to_dest(int& destid, string& raddr, int& rport){
	
	queue<int> pathq;
	pushin(pathq, destid);
	if(destid!=source){
		if(back == false)
			pathq.pop();// pathq stores the shortest path
						// initially source is in the front of the queue, 
						// we pop it out so we can get the nextrouterId in the front of the queue
		else
			while(pathq.size()>2)
				pathq.pop();
	}
	int nextrouterId = pathq.front();
	
	// look up configfile to find the next router addr and port number
	for(int i=0; i<nrow_of_matrix; ++i){
		if(atoi(matrix[i][0].c_str())==nextrouterId){
			raddr = matrix[i][1];
			rport = atoi(matrix[i][2].c_str());
			break;
		}
	}
}

void fwdmsg(string addrs, int portnum, string messg){
	int fwdsockfd;
	if((fwdsockfd = socket(AF_INET, SOCK_STREAM, 0))<0)
		{cout<<"create socket error!"<<endl; exit(1);}
		
	struct sockaddr_in neighborrouter_addr;
	bzero(&neighborrouter_addr, sizeof neighborrouter_addr);
	neighborrouter_addr.sin_family = AF_INET;
	neighborrouter_addr.sin_port = htons(portnum);
	neighborrouter_addr.sin_addr = *((struct in_addr*)(gethostbyname(addrs.c_str())->h_addr));

	while(1){
		if(connect(fwdsockfd, (struct sockaddr*)&neighborrouter_addr, sizeof(struct sockaddr))==-1)
			{ /* cerr<<"connection error:"<<strerror(errno)<<endl;*/ continue; }
		send(fwdsockfd, (char*)messg.c_str(), strlen(messg.c_str()), 0);
		break;
	}
	close(fwdsockfd);
}
forward ftable[N];	// create a forwarding table instance
int last=-1;

void printftable(){

	// print out the forwarding table
	cout<<"------------------------------"<<endl;
	cout<<" M Group | Next Hops | Hosts "<<endl;
	
	for(int i=0; i<=last; ++i){
		int* sm = new int[2];
		sm = ftable[i].getmginfo();
		//cout<<left<<setw(12);
		cout<<"  (";
		if(sm[0]==-1) cout<<'*';
		else cout<<sm[0];
		cout<<","<<sm[1]<<")  | ";
		
		int nhops=ftable[i].getnexthopamount(); 
		int* hopIdlist = new int[nhops];
		hopIdlist = ftable[i].gethopinfo();
		//cout<<left<<setw(20);
		int j;		
		if(nhops>0){
			for(int j=1; j<(9-nhops*(nhops+1)/2)/2+1; ++j)
				cout<<" ";
			cout<<hopIdlist[0];
		}
		else cout<<"    -    ";

		for(j=1; j<nhops; ++j){
			cout<<","<<hopIdlist[j];
		}
		if(nhops>0)
			for(j=1; j<(9-nhops*(nhops+1)/2)/2+1; ++j) cout<<" ";
		cout<<" | ";

		int nhosts=ftable[i].gethostamount();
		int* hostIdlist = new int[nhosts];
		hostIdlist = ftable[i].gethostinfo();

		if(nhosts>0 && nhosts<4){
			for(j=1; j<(5-nhosts*(nhosts+1)/2)/2+1; ++j)
				cout<<" ";
			cout<<hostIdlist[0];
		}
		if(nhosts==0) cout<<"  -  ";
		if(nhosts>=4) cout<<hostIdlist[0];
		for(j=1; j<nhosts; ++j)
			cout<<","<<hostIdlist[j];

		cout<<endl;
		delete[] sm;
		delete[] hopIdlist;
		delete[] hostIdlist;
	}
	if(last==-1)
		cout<<"    -    |     -     |   -    "<<endl;
}

int main(int argc, char *argv[]){
	system("clear");
	if(argc<5)
		{cerr<<"Usage:router <routerId> <configfile> <config-rp> <config-topo>"<<endl; exit(1);}
	
	
	int routerId, myport;
	routerId = atoi(argv[1]);
	cout<<"router "<<routerId<<endl<<endl;
	vector<int> host_id;
	vector<int> host_port;
	vector<string> host_addr;
	
	int th=-1;
	int pos = 0;
	int row = 0;
	string buff = "";
	
	// read in file "configfile" to get routers' information
	ifstream readconfig;
	readconfig.open("configfile");
	
	if(readconfig.is_open()){
		while(readconfig.good()){
			getline(readconfig, buff);
			if(readconfig.eof()) break; // prevent getting a newline at end
			for(int j =0; j<2; ++j){
				pos = buff.find(" ");
				matrix[row][j] = buff.substr(0, pos);
				buff = buff.substr(pos+1, buff.length()-pos);
			}
			matrix[row][2]=buff;
			++row;
		}
		readconfig.close();
	}
	nrow_of_matrix = row;
	for(int i = 0; i<nrow_of_matrix; ++i){
		if(atoi(matrix[i][0].c_str())==routerId)
			myport = atoi(matrix[i][2].c_str());			//get my port number
	}
	/*
	//the below code is for printing out matrix
	for(int j=0; j<nrow_of_matrix; ++j){
		for(int k=0; k<3; ++k){
			cout<<matrix[j][k]<<"  ";
		}
		cout<<endl;
	}
	*/
	
	string addr_of_otherrouter = "";
	int port_of_otherrouter = 0;

	buff="";
	row=0;
	
	/******* read in file "configrp" to get rendezvous point information
	*/
	//int rp[N][2];
	ifstream readconfigrp;
	readconfigrp.open("configrp");

	if(readconfigrp.is_open()){
		while(readconfigrp.good()){
			getline(readconfigrp, buff);
			if(readconfigrp.eof()) break; // prevent getting a newline at end
			for(int j =0; j<2; ++j){
				pos = buff.find(" ");
				rp[row][j] = atoi((buff.substr(0, pos)).c_str()); 
				buff = buff.substr(pos+1, buff.length()-pos);
			}
			rp[row][1]=atoi(buff.c_str());
			++row;
		}
		readconfigrp.close();
	}
	nrow_of_rp = row;
	
	/*
	for(int i=0; i<nrow_of_rp; ++i){
		for(int j=0; j<2; ++j)
			cout<<left<<setw(3)<<rp[i][j];
		cout<<endl;
	}
	*/
	buff="";
	
	/********* read in file "configtopo" to get topology(distance) information
	/********* need to draw a virtual graph
	*/
	
	ifstream readconfigtopo;
	readconfigtopo.open("configtopo");
	//vector< vector<int> > topo;
	int M=0;
	if(readconfigtopo.is_open()){
		int line =0;
		int t=0;
		int distance=0;
		while(readconfigtopo.good()){
			getline(readconfigtopo, buff);
			if(readconfigtopo.eof()) break; // prevent getting a newline at end
			if(line==0)
				{M=atoi(buff.c_str()); ++line;}
			else if(line>0){
				topo.push_back(vector<int>());
				for(int i =0; i<M-1; ++i){
					pos = buff.find(" ");
					distance = atoi((buff.substr(0, pos)).c_str());
					topo[t].push_back(distance);
					buff = buff.substr(pos+1, buff.length()-pos);
				}
				distance = atoi(buff.c_str());
				topo[t].push_back(distance);
				++t;
			}
		}
		readconfigtopo.close();
	}// End of reading the topo file
	
	
	// So far, we have stored the topo information int the 2-d vector
	
	/*
	// now we print it out to make sure we have stored the topo info succussfully
	vector< vector<int> >::iterator row_iter = topo.begin();
	vector< vector<int> >::iterator row_end = topo.end();
	
	for(; row_iter!=row_end; ++row_iter){
		vector<int>::iterator column_iter = row_iter->begin();
		vector<int>::iterator column_end = row_iter->end();
		for(; column_iter!=column_end; ++column_iter++){
			cout <<left << setw(3) << *column_iter;
		}
		cout<< endl;
	}
	*/

	// So far, we read all files, and thus get all the information we need
	// now we need to find a shortest path between (me .... rp-router)
	// apply dijkstra algorithm

	source = routerId;


	dijkstra(source, topo, M);
	//printpathto(0);

	/*
	// print out the shortest path between source router and rp router
	for(int i=0; i<M; ++i){
		if(i==source)
			cout<<source<<"->"<<source;
		else
			printpathto(i);
		cout<<"....."<<dist[i]<<endl;
	}

	printpathto(0);
	cout<<endl;

	/******************************************/
	/*      1. create a forwading socket	  */
	/******************************************/

	/******************************************/
	/*       2. create a listen socket		  */
	/******************************************/
	
	//now we create socket, as a router, we need to keep listening
	int yes;
	int byte;
	int listensockfd, connsockfd;
	
	// define some variables to receive in coming messages
	string msgTYPE;
	int hostId, mgroup;
	int senderhostId=-1;
	int rpId, nextrouterId, port_of_nextrouter;
	string rp_addr, addr_of_nextrouter;
	
	struct sockaddr_in myaddr, otheraddr;
	bzero(&myaddr, sizeof(myaddr));

	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(myport);
	
	if((listensockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{cerr<<"create socket error:"<<strerror(errno)<<endl; return -1;}
	setsockopt(listensockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	if(bind(listensockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1)
		{cerr<<"create socket error: "<<strerror(errno)<<endl; return -1;}
	if(listen(listensockfd, 10) == -1)
		{cerr<<"create socket error:"<<strerror(errno)<<endl; return -1;}


	int addr_len = sizeof(struct sockaddr_in);

	while(1){
		stringstream streambuf;
		char recvbuf[128]="";
		
		connsockfd = accept(listensockfd, (struct sockaddr*)&otheraddr, (socklen_t *)&addr_len);
		if(connsockfd < 0)
			{cerr<<"accept error!"<<endl; continue; }
		
		if(byte = recv(connsockfd, recvbuf, sizeof recvbuf, 0)==-1)
			{cerr<<"Fail to receive data!"<<endl; exit(EXIT_FAILURE);}
		
		//decide what message I got, REPORT, JOIN, LEAVE, PRUNE, REGISTER, SSJOIN, MCAST
		int lenn = strlen(recvbuf);
		recvbuf[lenn]='\0';
		system("clear");
		cout<<"router "<<routerId<<endl<<endl;
		cout<<"Received:"<<recvbuf<<endl;
		//cout<<"Received length:"<<lenn<<endl;

		streambuf.str("");	// clear it before use
		streambuf<<recvbuf;
		streambuf>>msgTYPE;
		
		int tindex;
		for(int i=0; i<NSET; ++i){
			if(msgTYPE==msgSet[i])
				{tindex = i; break;}
		}

		switch(tindex){
			case REPORT:{ // REPORT <hostId> <mgroup>
				stringstream tosend;
				string strtosend;
				
				int tport=0;
				string taddr="";
				streambuf>>hostId>>mgroup>>tport>>taddr;

				host_id.push_back(hostId);
				host_port.push_back(tport);
				host_addr.push_back(taddr);
				++th;
				cout<<"Received REPORT from host "<<hostId<<endl;
				/*****************************************************************/
				// according to the shortest path algoritm, 
				// we can get the next router we need to send the JOIN message
				/*****************************************************************/
				rpId=getrpId(mgroup);
				//cout<<"rpId="<<rpId<<endl;
				get_nextrouteraddr_to_dest(rpId, addr_of_nextrouter, port_of_nextrouter);

				bool foundmg=false;
				bool foundhost=false;
				int tag;
				if(last>=0){
					for(int i=0; i<=last; ++i){
						int* sm = new int[2];
						sm = ftable[i].getmginfo();
						if(sm[0]==-1 && sm[1]==mgroup){
							foundmg=true; tag=i;
							// host is already in mgroup, don't do anything
							if(ftable[i].findbyhost(hostId)>=0) {
								cout<<"The host is already in mgroup"<<endl;
								foundhost=true;
								break;
							}
						}
						delete[] sm;
					}
					
					if(foundmg && !foundhost){ // mgroup in router, but the host is not in mgroup
						ftable[tag].addhost(hostId);
						if(nothing && routerId != rpId){
							// JOIN <routerId> <rpID> <mgroup>
							tosend.str("");
							tosend<<"JOIN "<<routerId<<" "<<rpId<<" "<<mgroup;	
							strtosend=tosend.str();
							cout<<"I am not rp, send JOIN message."<<endl;
							cout<<"Send out:"<<strtosend<<endl;
							fwdmsg(addr_of_nextrouter, port_of_nextrouter, strtosend);
						}
					}
				}
				
				if(!foundmg || last ==-1){ // not found (*, mgroup) entry or no record in ftable
										   // create a new record
					cout<<"Not found host "<<hostId<<" in fowarding table"<<endl;
					++last;
					ftable[last].addmultig(-1, mgroup);
					ftable[last].addhost(hostId);
					cout<<"Create a record (*," <<mgroup<<") in forwarding table."<<endl;
					if(routerId != rpId) {// If I am not rp I will send JOIN to rp, 
										  // otherwise I will not do anything
						
						// JOIN <routerId> <rpID> <mgroup>
						tosend.str("");
						tosend<<"JOIN "<<routerId<<" "<<rpId<<" "<<mgroup;	
						strtosend=tosend.str();
						cout<<"I am not rp, send JOIN message."<<endl;
						cout<<"Send out:"<<strtosend<<endl;
						fwdmsg(addr_of_nextrouter, port_of_nextrouter, strtosend);
					}
				}
				
				printftable();
				break;
			}
			
			case LEAVE:{
				stringstream tosend;
				string strtosend;
				streambuf>>hostId>>mgroup;
				rpId=getrpId(mgroup);
				get_nextrouteraddr_to_dest(rpId, addr_of_nextrouter, port_of_nextrouter);
				
				if(last>=0){
					for(int i=0; i<=last; ++i){
						int* sm = new int[2];
						sm = ftable[i].getmginfo();
						if(sm[0]==-1 && sm[1]==mgroup){
							if(ftable[i].findbyhost(hostId)==-1)
								{cout<<"The hostId you type in is not in mgroup."<<endl; }
							
							else{ //host is in mgroup, remove it
								cout<<"Remove host "<<hostId<<" from mgroup "<<mgroup<<" successfully."<<endl;
								ftable[i].erasehost(hostId);
								
								vector<int>::iterator it_hostId = find(host_id.begin(), host_id.end(), hostId);
								int d = std::distance(host_id.begin(), it_hostId);								
								if(it_hostId!=host_id.end())
									host_id.erase(it_hostId);

								vector<int>::iterator it_port;
								vector<string>::iterator it_addr;
								it_port = host_port.begin()+d;
								it_addr = host_addr.begin()+d;
								host_port.erase(it_port);
								host_addr.erase(it_addr);
								
							}
						}
						delete[] sm;
					}
					
					/* if the router doesn't have any more members of multicast group mgroup
					 * and the router does not have any downstream routers in its forwarding table
					 * for multicast group mgroup, the router will send a PRUNE message 
					 * to the next-hop upstream node towards the rendezvous point in the multicast tree
					 */
					
					for(int i=0; i<=last; ++i){
						int* sm = new int[2];
						sm = ftable[i].getmginfo();
						if(sm[0]==-1 && sm[1]==mgroup){ //(*, mgroup)
							// after remove a host from member list
							// if has neither member nor next hop in ftable
							// send PRUNE message
							if(ftable[i].gethostamount()==0 && ftable[i].getnexthopamount()==0){
								nothing=true;
								cout<<"no any member hosts in mgroup "<<mgroup<<" attached to me"<<endl;

								if(routerId != rpId) {
									
									// PRUNE <routerId> <rpID> <mgroup>
									tosend.str("");
									tosend <<"PRUNE "<<routerId<<" "<<rpId<<" "<<mgroup;
									strtosend = tosend.str();
									cout<<"I am not rp, update my forwarding table and send PRUNE upstream"<<endl;
									cout<<"Send out:"<<strtosend<<endl;
									fwdmsg(addr_of_nextrouter, port_of_nextrouter, strtosend);
								}
							}
							break;
						}
						delete[] sm;
					}
				}
				else {cout<<"No record so far!"<<endl; printftable(); break;}
				printftable();
				break;
			}
			
			case SEND:{	// SEND <hostId> <mgroup> <data>
				stringstream tosend;
				string strtosend;
				
				string strdata;
				streambuf>>senderhostId>>mgroup; hostId=senderhostId;
				int loc = streambuf.str().find(" ", 0);
				loc = streambuf.str().find(" ", loc+1);
				loc = streambuf.str().find(" ", loc+1);
				strdata=streambuf.str().substr(loc+1, streambuf.str().length()-1);
				
				cout<<"Received SEND from host "<<senderhostId<<endl;
				rpId=getrpId(mgroup);
				get_nextrouteraddr_to_dest(rpId, addr_of_nextrouter, port_of_nextrouter);
				
				// when a router receive a SEND from user, this routerId is the srcId to send REGISTER out
				int srcId=routerId;
				bool existss=false;
				int tag1=-1;	// (*, mgroup)
				int tag2=-1;	// (srcId, mgroup)
				if(last>=0){
					for(int i=0; i<=last; ++i){

						int* sm = new int[2];
						sm = ftable[i].getmginfo();

						// if there is already a source specific entry in forwarding table
						if(sm[0]==routerId && sm[1]==mgroup){ // (srcId, mgroup) pair
							existss=true; 
							tag2=i; 
							if(ftable[i].findbyhost(senderhostId)==-1)
								ftable[i].addhost(senderhostId);
						}

						if(sm[0]==-1 && sm[1]==mgroup) // (*, mgroup) pair)
							tag1=i;
						delete[] sm;
					}
					
					if(existss){ // exist (srcId, mgroup) pair
						
						// create a MCAST messge and send it to all appropriate
						// neighbor routers as specified in its forwarding table
						// updating forwarding table, add host in if it is not in ftable already
						

						// create a MCAST message
						// MCAST <routerId> <srcID> <mgroup> <date>
						tosend.str("");
						tosend<<"MCAST "<<routerId<<" "<<srcId<<" "<<mgroup<<" "<<strdata;
						strtosend=tosend.str();
						cout<<"Already exist a source specific entry"<<endl;
						cout<<"Send out:"<<strtosend<<endl;

						// -------------- (*, mgroup) ---------------------------------
						if(tag1!=-1){
							// get these neighbor routers' Id and adderess and port number
							int nhops1=ftable[tag1].getnexthopamount();
							int *hopIdlist1 = new int[nhops1];
							hopIdlist1=ftable[tag1].gethopinfo();
						
							string* hopaddrlist1 = new string[nhops1];
							int* hopportlist1 = new int[nhops1];
						
							int nhosts1=ftable[tag1].gethostamount();
							int* hostIdlist1 = new int[nhosts1];
							hostIdlist1 = ftable[tag1].gethostinfo();

							// look up address in matrix[][]
							for(int i=0; i<nhops1; ++i){
								for(int j=0; j<nrow_of_matrix; ++j){
									if(hopIdlist1[i]==atoi(matrix[j][0].c_str())){
										hopaddrlist1[i] = matrix[j][1];
										hopportlist1[i] = atoi(matrix[j][2].c_str());
										break;
									}
								}
							}
							
							// send to all appropriate neighbor routers
							cout<<"(*,mgroup) Send to all appropriate next hop routers"<<endl;
							for(int i=0; i<nhops1; ++i){
								fwdmsg(hopaddrlist1[i], hopportlist1[i], strtosend);
							}
							
							// also sent to all attached hosts that are in mgroup except the senderhost
							cout<<"Also sent to all attached hosts that are in mgroup"<<endl;
							for(int i=0; i<nhosts1; ++i){
								if(hostIdlist1[i]!=senderhostId){
									//cout<<"Send MCAST to host "<<hostIdlist1[i]<<endl;
									fwdmsg(host_addr[i], host_port[i], strtosend);
								}
							}

							delete[] hopIdlist1;
							delete[] hopaddrlist1;
							delete[] hopportlist1;
							delete[] hostIdlist1;
							
						}// end of tag!=-1


						// -------------- (srcId, mgroup) ---------------------------------
						int nhops2 = ftable[tag2].getnexthopamount(); //cout<<"nhops="<<nhops<<endl;
						int *hopIdlist2 = new int[nhops2];
						hopIdlist2 = ftable[tag2].gethopinfo();
				
						string* hopaddrlist2 = new string[nhops2];
						int* hopportlist2 = new int[nhops2];

						int nhosts2 = ftable[tag2].gethostamount();
						int* hostIdlist2 = new int[nhosts2];
						hostIdlist2 = ftable[tag2].gethostinfo();

						// look up address in matrix[][]
						for(int i=0; i<nhops2; ++i){
							for(int j=0; j<nrow_of_matrix; ++j){
								if(hopIdlist2[i]==atoi(matrix[j][0].c_str())){
									hopaddrlist2[i] = matrix[j][1];
									hopportlist2[i] = atoi(matrix[j][2].c_str());
									break;
								}
							}
						}

						// send to all appropriate next hop routers
						cout<<"(srcId,mgroup) Send to all appropriate next hop routers"<<endl;
						for(int i=0; i<nhops2; ++i){
							if(tag1==-1){ // no (*, mgroup), then simply forward according to (*, mgroup)
								fwdmsg(hopaddrlist2[i], hopportlist2[i], strtosend);}
							
							else{ // have (*, mgroup), then only forward to hops that are not in (*, mgroup)
								if(ftable[tag1].findbynexthop(hopIdlist2[i])==-1)
									fwdmsg(hopaddrlist2[i], hopportlist2[i], strtosend);
							}

						}
						
						/*
						// also sent to all attached hosts that are in mgroup except the senderhost
						cout<<"Also sent to all attached hosts that are in mgroup"<<endl;
						cout<<"nhosts2="<<nhosts2<<endl;
						cout<<"senderhostId="<<senderhostId<<endl;
						for(int i=0; i<nhosts2; ++i){
							cout<<"hostIdlist2[i]="<<hostIdlist2[i]<<endl;
							if(hostIdlist2[i]!=senderhostId){
								
								if(tag1==-1){
									cout<<"759 send to host "<< hostIdlist2[i]<<endl;
									//fwdmsg(host_addr[i], host_port[i], strtosend);
								}
								else{
									if(ftable[tag1].findbyhost(hostIdlist2[i])==-1 && hostIdlist2[i]!=senderhostId){
										cout<<"764 send to host "<< hostIdlist2[i]<<endl;
										//fwdmsg(host_addr[i], host_port[i], strtosend);
									}
								}
							}
						}
						*/
						delete[] hopIdlist2;
						delete[] hopaddrlist2;
						delete[] hopportlist2;
						delete[] hostIdlist2;

					} // if(existss)
					
					else{ // not exist source specific entry
					      // send REGISTER toward rp
					      // forward REGISTER, will create an entry (srcId, mgroup) when receive SSJOIN
						
						cout<<"No source specific entry yet!"<<endl;
						if(routerId!=rpId){
							tosend.str("");
							tosend<<"REGISTER "<<srcId<<" "<<rpId<<" "<<mgroup<<" "<<strdata;
							strtosend=tosend.str();
							cout<<"I am not rp, I will create REGISTER"<<endl;
							cout<<"Send out:"<<strtosend<<endl;
							
							fwdmsg(addr_of_nextrouter, port_of_nextrouter, strtosend);
						}
						else{ // if I am rp, I don't need to send REGISTER and SSJOIN
							  // I will just only create a (srcId, mgroup) in my ftable
							  // then send MCAST to all appropriate neighbors(in my next hop list)
							
							cout<<"I am rp, I will create (srcId, mgroup) then send MCAST"<<endl;
							// add entry (srcId, mgroup) in ftable
							++last;
							ftable[last].addmultig(srcId, mgroup);
							ftable[last].addhost(senderhostId);
							// SSJOIN <routerd> <srcId> <mgroup>
							
							// MCAST <routerId> <srcId> <mgroup> <data>
							tosend.str("");	
							tosend<<"MCAST "<<routerId<<" "<<srcId<<" "<<mgroup<<" "<<strdata;
							strtosend=tosend.str();
							cout<<"Broadcast MCAST to nexthops and attached hosts that are in mgroup"<<endl;
							cout<<"Send out:"<<strtosend<<endl;

							// broadcast MCAST to nexthops and attached hosts that are in mgroup
							for(int i=0; i<=last; ++i){
								int* sm = new int[2];
								sm = ftable[i].getmginfo();
								if(sm[0]==-1 && sm[1]==mgroup){ // find (*, mgroup) pair
									tag1=i; // record the index
									break;
								}
								delete[] sm;
							}

							if(tag1!=-1){ // found (*, mgroup){}

								int nhops=ftable[tag1].getnexthopamount();
								int* hopIdlist = new int[nhops];
								hopIdlist = ftable[tag1].gethopinfo();

								string* hopaddrlist = new string[nhops];
								int* hopportlist = new int[nhops];

								int nhosts=ftable[tag1].gethostamount();
								int* hostIdlist = new int[nhosts];
								hostIdlist = ftable[tag1].gethostinfo();

								
								// look up hop address in matrix[][]
								for(int i=0; i<nhops; ++i){
									for(int j=0; j<nrow_of_matrix; ++j){
										if(hopIdlist[i] == atoi(matrix[j][0].c_str())){
											hopaddrlist[i] = matrix[j][1];
											hopportlist[i] = atoi(matrix[j][2].c_str());
											break;
										}
									}
								}

								// send to all appropriate next hop routers
								for(int i=0; i<nhops; ++i){
									fwdmsg(hopaddrlist[i], hopportlist[i], strtosend);
								}
								
								// if I am rp and I received a SEND, then it must come from my attached hosts
								// and under this scenario, I will not receive any REGISTER
								// so I will make sure not forward MCAST back to that host
								
								// also sent to all attached hosts that are in mgroup
								cout<<"Also sent to all attached hosts that are in mgroup"<<endl;
								
								for(int i=0; i<nhosts; ++i){
									if(hostIdlist[i]!=senderhostId){
										cout<<"Send MCAST to host "<<hostIdlist[i]<<endl;
										fwdmsg(host_addr[i], host_port[i], strtosend);
									}
								}

								delete[] hopIdlist;
								delete[] hopaddrlist;
								delete[] hopportlist;
								delete[] hostIdlist;

							}
							else cout<<"Not found (*, mgroup)"<<endl;

							// also broadcast MCAST to attached hosts taht are in mgroup
						}// if I am rp
					}//if no specific entry
				}// if(last>=0)
				
				else{ // last==-1, this means no record so far
					  // but I will only create (srcId, mgroup) when I receive SSJOIN from rp

					if(routerId!=rpId){
						tosend.str("");
						tosend<<"REGISTER "<<srcId<<" "<<rpId<<" "<<mgroup<<" "<<strdata;
						strtosend=tosend.str();
						cout<<"I am not rp, I will create REGISTER"<<endl;
						cout<<"Send out:"<<strtosend<<endl;
						
						fwdmsg(addr_of_nextrouter, port_of_nextrouter, strtosend);
					}
					else{ // if I am rp, I don't need to send REGISTER and SSJOIN
						  // I will just only create a (srcId, mgroup) in my ftable
						  // then send MCAST to all appropriate neighbors(in my next hop list)
						
						cout<<"I am rp, I will create (srcId, mgroup) then send MCAST"<<endl;

						// MCAST <routerId> <srcId> <mgroup> <data>
						tosend.str("");	
						tosend<<"MCAST "<<routerId<<" "<<srcId<<" "<<mgroup<<" "<<strdata;
						strtosend=tosend.str();
						cout<<"Broadcast MCAST to nexthops and attached hosts that are in mgroup"<<endl;
						cout<<"Send out:"<<strtosend<<endl;

						// Broadcast MCAST to nexthops and attached hosts that are in mgroup
						for(int i=0; i<=last; ++i){
							int* sm = new int[2];
							sm = ftable[i].getmginfo();
							if(sm[0]==-1 && sm[1]==mgroup){ // find (*, mgroup) pair
								tag1=i; // record the index
								break;
							}
							delete[] sm;
						}

						if(tag1!=-1){ // found (*, mgroup)
							int nhops=ftable[tag1].getnexthopamount();
							int* hopIdlist = new int[nhops];
							hopIdlist = ftable[tag1].gethopinfo();
							
							string* hopaddrlist = new string[nhops];
							int* hopportlist = new int[nhops];
														
							int nhosts=ftable[tag1].gethostamount();
							int* hostIdlist = new int[nhosts];
							hostIdlist = ftable[tag1].gethostinfo();

							// look up hop address in matrix[][]
							for(int i=0; i<nhops; ++i){
								for(int j=0; j<nrow_of_matrix; ++j){
									if(hopIdlist[i] == atoi(matrix[j][0].c_str())){
										hopaddrlist[i] = matrix[j][1];
										hopportlist[i] = atoi(matrix[j][2].c_str());
										break;
									}
								}
							}
							
							// send to all appropriate neighbor routers
							for(int i=0; i<nhops; ++i){
								fwdmsg(hopaddrlist[i], hopportlist[i], strtosend);
							}
							
							// also sent to all attached hosts that are in mgroup
							cout<<"Aalso sent MCAST to all attached hosts that are in mgroup"<<endl;
							
							for(int i=0; i<nhosts; ++i){
								if(hostIdlist[i]!=senderhostId){
									for(int j=0; j<=th; ++j){
										if(hostIdlist[i]==host_id[j])
											fwdmsg(host_addr[i], host_port[i], strtosend);
									}
								}
							}

							delete[] hopIdlist;
							delete[] hopaddrlist;
							delete[] hopportlist;
							delete[] hostIdlist;

						}
						else cout<<"Not found (*, mgroup)"<<endl;

						// also broadcast MCAST to attached hosts taht are in mgroup
					}// if I am rp

				}
				printftable();
				break;
			}
			case JOIN:{	// if receive a JOIN message,  and if I am not the rendezvous point
					    // update forwarding table to include next hop, and then forward it to rp
				stringstream tosend;
				string strtosend;
				cout<<streambuf.str()<<endl;
				int senderId;
				streambuf>>senderId>>rpId>>mgroup;

				rpId=getrpId(mgroup);
				get_nextrouteraddr_to_dest(rpId, addr_of_nextrouter, port_of_nextrouter);
				bool foundmg=false;
				
				int tag=-1;
				if(last>=0){
					for(int i = 0; i<=last; ++i){
						int* sm = new int[2];
						sm = ftable[i].getmginfo();
						if(sm[0]==-1 && mgroup ==sm[1]){ // (*, mgroup)
							ftable[i].addhop(senderId);
							foundmg=true;
							cout<<"I am in mgroup already, add the sender as a new next hop."<<endl;
							break;
						}
						delete[] sm;
					}
				}
				if(!foundmg){ // didn't found (*, mgroup) entry
					++last;
					ftable[last].addmultig(-1, mgroup);
					ftable[last].addhop(senderId);
					if(routerId!=rpId){ // if I am not rp, I wll forward JOIN
						
						// JOIN <routerId> <rpID> <mgroup>
						tosend.str("");
						tosend<<"JOIN "<<routerId<<" "<<rpId<<" "<<mgroup;
						strtosend=tosend.str();
						cout<<"I am not rp, I will forward JOIN"<<endl;
						cout<<"Send out:"<<strtosend<<endl;
						fwdmsg(addr_of_nextrouter, port_of_nextrouter, strtosend);
					}
					else{
						cout<<"I am rp, I only need to update my forwarding table"<<endl;
					}
				}
				else{ // found (*, mgroup) entry
					if(nothing){
						if(routerId!=rpId){
							tosend.str("");		// JOIN <routerId> <rpID> <mgroup>
							tosend<<"JOIN "<<routerId<<" "<<rpId<<" "<<mgroup;
							strtosend=tosend.str();
							cout<<"I am not rp, I will forward JOIN"<<endl;
							cout<<"Send out:"<<strtosend<<endl;
							fwdmsg(addr_of_nextrouter, port_of_nextrouter, strtosend);
						}
						else{
							cout<<"I am rp, I only need to update my forwarding table"<<endl;
						}
					}
				}
				printftable();
				break;
			}// end JOIN
			
			case PRUNE:{ // PRUNE <routerId> <rpId> <mgroup>
						 // when receive PRUNE, it exclude the neighbor router
						 // from which the PRUNE message was received
				stringstream tosend;
				string strtosend;
				int senderId;
				streambuf>>senderId>>rpId>>mgroup;
				
				rpId=getrpId(mgroup);
				get_nextrouteraddr_to_dest(rpId, addr_of_nextrouter, port_of_nextrouter);
				
				if(last>=0){
					for(int i=0; i<=last; ++i){
						int* sm = new int[2];
						sm = ftable[i].getmginfo();
						if(sm[0]==-1 && sm[1]==mgroup){ // (*, mgroup)
							if(ftable[i].findbynexthop(senderId)!=-1){
								ftable[i].erasenexthop(senderId); // remove the downstream hop
								nothing=true; // if I pruned one downstream hop, I set nothing=ture
								if(ftable[i].gethostamount()==0 && ftable[i].getnexthopamount()==0){
									
									// if I am not rp
									// forward this PRUNE message to rp
									if(rpId!=routerId){
										tosend.str("");	// PRUNE <routerId> <rpID> <mgroup>
										tosend<<"PRUNE "<<routerId<<" "<<rpId<<" "<<mgroup; 
										strtosend=tosend.str();
										cout<<"I am not rp, I will forward PRUNE"<<endl;
										cout<<"Send out:"<<strtosend<<endl;
										fwdmsg(addr_of_nextrouter, port_of_nextrouter, strtosend);
										break;
									}
									else{
										cout<<"I am rp, I have removed the next hop from "
												"which router PRUNE was send"<<endl;
										break;
									}
								}
							}
						}// (*, mgroup)
						delete[] sm;
					}
				}
				else {cout<<"No records in forwarding table"<<endl; break;}
				printftable();
				break;
			}

			case REGISTER:{ // REGISTER <srcId> <rpId> <mgroup> <data>
				stringstream tosend;
				string strtosend;
				int srcId;
				
				string strdata;
				streambuf>>srcId>>rpId>>mgroup;
				int loc = streambuf.str().find(" ", 0);
				loc = streambuf.str().find(" ", loc+1);
				loc = streambuf.str().find(" ", loc+1);
				loc = streambuf.str().find(" ", loc+1);
				strdata=streambuf.str().substr(loc+1, streambuf.str().length()-1);

				cout<<"Received REGISTER from source "<<srcId<<endl;
				
				rpId=getrpId(mgroup);
				if(routerId!=rpId){ // if not rp, just forward REGISTER message
					get_nextrouteraddr_to_dest(rpId, addr_of_nextrouter, port_of_nextrouter);
					tosend.str("");	// REGISTER <srcId> <rpId> <mgroup> <data>
					
					tosend<<"REGISTER "<<srcId<<" "<<rpId<<" "<<mgroup<<" "<<strdata;
					strtosend=tosend.str();
					cout<<"I am not rp, I wil forward REGISTER"<<endl;
					cout<<"Send out:"<<strtosend<<endl;

					fwdmsg(addr_of_nextrouter, port_of_nextrouter, strtosend);
				}
				else{ // I am rp, create (srcId, mgroup) entry in ftable
					  // then send SSJOIN
					  
					++last;
					ftable[last].addmultig(srcId, mgroup);

					tosend.str("");	// SSJOIN <routerId> <srcId> <mgroup>
					tosend<<"SSJOIN "<<routerId<<" "<<srcId<<" "<<mgroup; 
					strtosend=tosend.str();
					cout<<"I am rp, I will create (srcId, mgroup) entry, then send SSJOIN"<<endl;

					cout<<"Send out:"<<strtosend<<endl;
					//-------------------------------------------------------------------					
					back=true;
					source=srcId; // dest is me
					dijkstra(source, topo, M);
					get_nextrouteraddr_to_dest(routerId, addr_of_nextrouter, port_of_nextrouter);
					
					fwdmsg(addr_of_nextrouter, port_of_nextrouter, strtosend);

					source=routerId; // set source value back
					back=false;
					dijkstra(source, topo, M);
					//-------------------------------------------------------------------

					//get_nextrouteraddr_to_dest(rpId, addr_of_nextrouter, port_of_nextrouter);
					cout<<"I also need to create MCAST, and send it out along the multicast tree"<<endl;
					int tag=-1;
					for(int i=0; i<=last; ++i){
						int* sm = new int[2];
						sm = ftable[i].getmginfo();
						if(sm[0]==-1 && sm[1]==mgroup){ // find (*, mgroup) pair
							tag=i; // record the index
							break;
						}
						delete[] sm;
					}
					if(tag!=-1){// found (*, mgroup){}
						int nhops=ftable[tag].getnexthopamount();
						int* hopIdlist = new int[nhops];
						hopIdlist = ftable[tag].gethopinfo();
						
						int nhosts=ftable[tag].gethostamount();
						int* hostIdlist = new int[nhosts];
						hostIdlist = ftable[tag].gethostinfo();
						
						string* hopaddrlist = new string[nhops];
						int* hopportlist = new int[nhops];
						
						string* hostaddrlist =  new string[nhosts];
						int* hostportlist = new int[nhosts];
						
						// look up hop address in matrix[][]
						for(int i=0; i<nhops; ++i){
							for(int j=0; j<nrow_of_matrix; ++j){
								if(hopIdlist[i] == atoi(matrix[j][0].c_str())){
									hopaddrlist[i] = matrix[j][1];
									hopportlist[i] = atoi(matrix[j][2].c_str());
									break;
								}
							}
						}
						
						tosend.str("");	// MCAST <routerId> <srcId> <mgroup> <data>
						tosend<<"MCAST "<<routerId<<" "<<srcId<<" "<<mgroup<<" "<<strdata;
						strtosend=tosend.str();
						cout<<"Send out:"<<strtosend<<endl;
						
						// send to all appropriate neighbor routers
						cout<<"Send to all appropriate next hop routers"<<endl;
						for(int i=0; i<nhops; ++i){
							fwdmsg(hopaddrlist[i], hopportlist[i], strtosend);
						}
						
						// also sent to all attached hosts that are in mgroup
						cout<<"Also sent to all attached hosts that are in mgroup"<<endl;

						// Notice: if I am rp, and I received a REGISTER
						// then it must not come from my attached hosts
						// so I will braodcast MCAST to all my attached hosts that are in mgroup

						for(int i=0; i<nhosts; ++i){
							//cout<<"Send MCAST to host "<<hostIdlist[i]<<endl;
							fwdmsg(host_addr[i], host_port[i], strtosend);
						}
						
						delete[] hopIdlist;
						delete[] hostIdlist;
						delete[] hopaddrlist;
						delete[] hostaddrlist;
						delete[] hopportlist;
						delete[] hostportlist;
					}
					if(last==-1) cout<<"Multicast tree has not formed yet"<<endl;
				}// end if-else
				
				printftable();
				break;
			
			}
			
			case SSJOIN:{ // when a router receive SSJOIN, create an (srcId, mgroup) entry in ftable
				// then forward SSJOIN downstream until it reaches source router which generates REGISTER
				// only rp create SSJOIN, so rp will not itself receive SSJOIN

				stringstream tosend;
				string strtosend;
				int srcId, senderId;
				streambuf>>senderId>>srcId>>mgroup;
				cout<<"Received a SSJOIN message from router "<<senderId<<endl;
				++last;
				ftable[last].addmultig(srcId, mgroup);
				ftable[last].addhop(senderId);
				
				tosend.str("");	// SSJOIN <routerId> <srcID> <mgroup>
				tosend<<"SSJOIN "<<routerId<<" "<<srcId<<" "<<mgroup;
				strtosend=tosend.str();


				// when the source generator of REGISTER receives SSJOIN
				// it will only create an entry (srcId, mgroup), does nothing else
				//-------------------------------------------------------------------					
				if(routerId!=srcId){
					cout<<"I am neither rp nor srcId, I will forward this SSJOIN downstream to srcId"<<endl;
					cout<<"Send out:"<<strtosend<<endl;
					back=true;
					source=srcId; // dest is me
					dijkstra(source, topo, M);
					get_nextrouteraddr_to_dest(routerId, addr_of_nextrouter, port_of_nextrouter);
				
					fwdmsg(addr_of_nextrouter, port_of_nextrouter, strtosend);

					source=routerId; // set source value back
					back=false;
					dijkstra(source, topo, M);
				}
				//-------------------------------------------------------------------
				else ftable[last].addhost(hostId);
				printftable();
				break;
			}
			
			case MCAST:{ // MCAST <routerId> <srcId> <mgroup> <data>
				stringstream tosend;
				string strtosend;
				int srcId, senderId;
				string strdata;
				streambuf>>senderId>>srcId>>mgroup;
				int loc = streambuf.str().find(" ", 0);
				loc = streambuf.str().find(" ", loc+1);
				loc = streambuf.str().find(" ", loc+1);
				loc = streambuf.str().find(" ", loc+1);
				strdata=streambuf.str().substr(loc+1, streambuf.str().length()-1);

				cout<<"Received MCAST from router "<<senderId<<endl;
				//cout<<"Received data is:"<<strdata<<endl;
				// when receive MCAST
				// send it to all the appropriate neighbor routers as in ftable
				// but will not send back to which it receive MCAST from

				int tag1=-1;
				int tag2=-1;
				if(last>=0){
					for(int i=0; i<=last; ++i){
						int* sm = new int[2];
						sm = ftable[i].getmginfo();
						if(sm[0]==-1 && sm[1]==mgroup){ // find (*, mgroup) pair
							tag1=i; // record the index
						}
						if(sm[0]==srcId && sm[1]==mgroup){ // find (srcId, mgroup) pair
							tag2=i; // record the index
						}
						delete[] sm;
					}
					
					// if I received a MCAST, I must be in mgroup, either in(*, mgroup) or (srcId, mgroup)
					// otherwise, MCAST will not be send to me
					if(tag1!=-1 || tag2!=-1){// found (*, mgroup) or (srcId, mgroup) entry
						
						//------------------ form MCAST -----------------------------						
						tosend.str("");	// MCAST <routerId> <srcId> <mgroup> <data>
						tosend<<"MCAST "<<routerId<<" "<<srcId<<" "<<mgroup<<" "<<strdata;
						strtosend=tosend.str();
						
						cout<<"Send out:"<<strtosend<<endl;
						//-----------------------------------------------------------

						//------------------ (*, mgourp)-----------------------------			
						if(tag1!=-1){
							cout<<"Found (*, mgroup), I will forward MCAST"<<endl;
							// hops							
							int nhops1 = ftable[tag1].getnexthopamount();
							int* hopIdlist1 = new int[nhops1];
							hopIdlist1 = ftable[tag1].gethopinfo();

							string* hopaddrlist1 = new string[nhops1];
							int* hopportlist1 = new int[nhops1];
						
							//hosts
							int nhosts1 = ftable[tag1].gethostamount();
							int* hostIdlist1 = new int[nhosts1];
							hostIdlist1 = ftable[tag1].gethostinfo();

							// look up hop address in matrix[][], for(*, mgourp)
							for(int i=0; i<nhops1; ++i){
								for(int j=0; j<nrow_of_matrix; ++j){
									if(hopIdlist1[i] == atoi(matrix[j][0].c_str())){
										hopaddrlist1[i] = matrix[j][1];
										hopportlist1[i] = atoi(matrix[j][2].c_str());
										break;
									}
								}
							}

							cout<<"Foward MCAST to all appropriate next hop routers"<<endl;
							for(int i=0; i<nhops1; ++i){
								if(hopIdlist1[i]!=senderId)
									fwdmsg(hopaddrlist1[i], hopportlist1[i], strtosend);
							}

							cout<<"Forward MCAST to all attached hosts that are in mgroup"<<endl;
							for(int i=0; i<nhosts1; ++i){
								if(routerId!=srcId){ // if I am not srcId router
									
									//cout<<"Send MCAST to host "<<hostIdlist1[i]<<endl;
									fwdmsg(host_addr[i], host_port[i], strtosend);
								}
								else{
									if(hostIdlist1[i]!=senderhostId){
										fwdmsg(host_addr[i], host_port[i], strtosend);
									}
								}
								
							}
							
							delete[] hopIdlist1;
							delete[] hopaddrlist1;
							delete[] hopportlist1;
							delete[] hostIdlist1;

						}// end of (*, mgourp)-------------------
						else cout<<"Not found (*, mgroup)"<<endl;
						
						//------------------ (srcId, mgourp)-----------------------------
						if(tag2!=-1){ // found(srcId, mgroup)
							cout<<"Found (srcId, mgroup), I will forward MCAST"<<endl;
							int nhops2=ftable[tag2].getnexthopamount();
							int* hopIdlist2 = new int[nhops2];
							hopIdlist2 = ftable[tag2].gethopinfo();
							
							string* hopaddrlist2 = new string[nhops2];
							int* hopportlist2 = new int[nhops2];

							int nhosts2=ftable[tag2].gethostamount();
							int* hostIdlist2 = new int[nhosts2];
							hostIdlist2 = ftable[tag2].gethostinfo();
							
							// look up hop address in matrix[][], for(*, mgourp)
							for(int i=0; i<nhops2; ++i){
								for(int j=0; j<nrow_of_matrix; ++j){
									if(hopIdlist2[i] == atoi(matrix[j][0].c_str())){
										hopaddrlist2[i] = matrix[j][1];
										hopportlist2[i] = atoi(matrix[j][2].c_str());
										break;
									}
								}
							}

							cout<<"foward MCAST to all appropriate next hop routers"<<endl;
							for(int i=0; i<nhops2; ++i){
								if(hopIdlist2[i]!=senderId){
									if(tag1!=-1){
										if(ftable[tag1].findbynexthop(hopIdlist2[i])==-1)
											fwdmsg(hopaddrlist2[i], hopportlist2[i], strtosend);
									}
									else fwdmsg(hopaddrlist2[i], hopportlist2[i], strtosend);
								}
							}
							
							// forward MCAST to all attached hosts that are in mgroup
							for(int i=0; i<nhosts2; ++i){
								cout<<"Send MCAST to host "<<hostIdlist2[i]<<endl;
								if(tag1!=-1){
									if(ftable[tag1].findbyhost(hostIdlist2[i])==-1 && hostIdlist2[i]!=senderhostId)
										fwdmsg(host_addr[i], host_port[i], strtosend);
								}
								else
									fwdmsg(host_addr[i], host_port[i], strtosend);
							}
							
							delete[] hopIdlist2;
							delete[] hopportlist2;
							delete[] hopaddrlist2;
							delete[] hostIdlist2;
							
						}// found(srcId, mgroup)

						else cout<<"Not found (srcId, mgroup)"<<endl;

						/*						
						// if I am not rp, I will make sure not send MCAST back to the host that generated it
						if(routerId!=rpId){
							for(int i=0; i<nhosts; ++i){
								//cout<<"hostIdlist[i]="<<hostIdlist[i]<<endl;
								if(hostIdlist[i]!=senderhostId){
									cout<<"Send MCAST to host "<<hostIdlist[i]<<endl;
									//cout<<"address is:"<<host_addr[i]<<endl;
									//cout<<"port is:"<<host_port[i]<<endl;
									fwdmsg(host_addr[i], host_port[i], strtosend);
								}
							}
						}
						*/

					}
					
				}// end of if(last>=0)

				printftable();
				break;
			}// end of MCAST
			
			default:break;
		}// end of switch()

	}// end of while
		return 0;
}


