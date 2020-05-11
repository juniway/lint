#include<iostream>
#include<algorithm>
#include<sstream>

#include "forward.h"
using namespace std;
forward::forward(){ // constructor
	multig[0]='*';
	multig[1]='1';
	//nexthp.reserve(3);
	//hosts.reserve(3);
}
forward::~forward(){} //destructor

int forward::findbyhost(int h) const{	// is certain host in multicast group? find()
	vector<int>::const_iterator it=find(hosts.begin(), hosts.end(), h);
	if(it==hosts.end())
		return -1;
	else return std::distance(hosts.begin(), it);
	
	/*
	for(; i<hosts.size(); ++i){
		if(hosts[i]==h) return i;
		else return -1;
	}
	*/
}
int forward::findbynexthop(int hp) const{
	vector<int>::const_iterator it=find(nexthop.begin(), nexthop.end(), hp);
	if(it==nexthop.end())
		return -1;
	else return std::distance(nexthop.begin(), it);
}

int forward::gethostamount() const{	// how many members attached? getMGmemberAmount()
	return hosts.size();
}

int* forward::getmginfo() const{
	int* a= new int[2];
	a[0]=multig[0];
	a[1]=multig[1];
	return a;
}

int* forward::gethopinfo() const{
	int* temp = new int[nexthop.size()];
	for(int i=0; i<nexthop.size(); ++i)
		temp[i]=nexthop[i];
	return temp;
}

int* forward::gethostinfo() const{
	int* temp = new int[hosts.size()];
	for(int i=0; i<hosts.size(); ++i)
		temp[i]=hosts[i];
	return temp;
}

int forward::getnexthopamount() const{
	return nexthop.size();
}

void forward::addhost(int newhost){ // when a new host send REPORT to join multicast group, addhost()
	hosts.push_back(newhost);
}

void forward::addhop(int hoprouter){ // addnexthop()
	nexthop.push_back(hoprouter);
}

void forward::addmultig(int sourceId, int multicastgroupId){ // source specific?
	multig[0]=sourceId;
	multig[1]=multicastgroupId;
}
void forward::erasehost(int hst){
	vector<int>::iterator it=find(hosts.begin(), hosts.end(), hst);
	if(it!=hosts.end()){
		hosts.erase(it);
	}
	else cout<<"Fail to erase!"<<endl;
}
void forward::erasenexthop(int nxhp){
	vector<int>::iterator it=find(nexthop.begin(), nexthop.end(), nxhp);
	if(it!=nexthop.end()){
		nexthop.erase(it);
	}
	else cout<<"Fail to erase!"<<endl;
}




