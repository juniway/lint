// http://hihocoder.com/discuss/question/2533
Description
In the city, there is a one-way straight highway starts from the northern end, traverses the whole city southward, 
and finishes at the southern end. Due to some financial difficulties, there is only one lane on this highway, 
which means that overtaking other cars in front is impossible.
The highway is quite busy. Lots of different cars are running on it every day. For each car, 
it is running on the highway at the point which X km far from the northern end in Minute 0, 
and will leave at the point which Y km far from the northern end. Each car also has a speed limit L km/min. 
During the whole trip on the highway, each car should run as fast as possible without exceeding its speed limit 
or overtaking other cars in front. In addition, no two or more cars will be at the same point at Minute 0. 
Cars can be regarded as points and the distance between two cars can be infinitely small.
Given the information of N cars, please calculate the leaving time for each car.

Input
The first line contains one integer N. 2 <= N <= 1000.
Then follows N line. Each line contains three integers X, Y and L, showing the information of this car. 0 <= X < Y <= 1000000, 0 < L <= 10.
Output
Output N real numbers, one per line -- the leaving time (in minute) of each car, preserving the input order of cars. 
Your answers should be rounded to 2 digits after the decimal point and the output must contain exactly 2 digits after the decimal point.

Sample Input
3
3 5 1
1 4 2
0 8 3
Sample Output

2.00
1.50
3.00

#include <vector>
#include <list>
#include <algorithm>
#include <stdio.h>
using namespace std;
struct Node {
   double start;
   double end;
   double vmax;
   double t;
};

Node nodes[1000];
int Comp(Node * a, Node * b) {
   return a->start > b->start;
}
int Comp1(Node * a, Node * b) {
   return a->end < b->end;
}
double max(double a, double b) {
   if(a > b) return a;
   return b;
}
vector<Node *> startnodes;
vector<Node *> endnodes;
void read() {
   int num;
   scanf("%d", &num);
   int s;
   int e;
   int v;
   for(int i = 0; i < num; i++) {
       scanf("%d %d %d", &s, &e, &v);
       nodes[i].start = s;
       nodes[i].end = e;
       nodes[i].vmax = v;
       nodes[i].t = 0;
       startnodes.push_back(&nodes[i]);
       endnodes.push_back(&nodes[i]);
   }
   sort(startnodes.begin(), startnodes.end(), Comp);
   sort(endnodes.begin(), endnodes.end(), Comp1);
}
void solve() {
    for(int j = 0; j < endnodes.size(); j++) {
        double y = endnodes[j]->end;
        double tmax = 0;
        for(int i = 0; i < startnodes.size(); i++) {
            Node * node = startnodes[i];
            if(y <= node->end && node->start < y) {
                if(tmax == 0) {
                    node->t = node->t + (y - node->start) / node->vmax;
                    tmax = node->t;
                } else {
                    node->t = max(node->t + (y - node->start) / node->vmax, tmax);
                    tmax = node->t;
                }
                //更新起点
                node->start = y;
            }
        }
    }

}
void printfln() {
    for(int i = 0; i < startnodes.size(); i++) {
         printf("%.2f\n", nodes[i].t);
    }
}
int main(int argc, char* argv[])
{   read();
    solve();
    printfln();
    return 0;
}