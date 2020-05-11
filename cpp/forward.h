#ifndef FORWARD_H
#define FORWARD_H
#endif

#include<vector>
using namespace std;
class forward{
	public:
		// constructors & destructors
		forward();
		~forward();
		
		// mutator functions
		void addhost(int newhost);
		void addhop(int newhop);
		void addmultig(int sId, int mgId);
		void erasehost(int hst);
		void erasenexthop(int nxhp);
		//void purge();
		
		// accessor functions
		int findbyhost(int) const;
		int findbynexthop(int) const;
		int gethostamount() const;
		int getnexthopamount() const;
		
		int* getmginfo() const;
		int* gethopinfo() const;
		int* gethostinfo() const;
		
	private:
		// data
		int multig[2];
		vector<int> nexthop;
		vector<int> hosts;
};

