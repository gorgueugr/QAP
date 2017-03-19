#ifndef PROBLEM_H_
#define PROBLEM_H_

#include <vector>
#include <iostream>

using namespace std;

class Problem{
  private:
    int size;
    vector< vector<int> > distance;
    vector< vector<int> > flow;
  public:
    Problem(){size=0;}
    ~Problem(){distance.clear();flow.clear();}
    int getSize() const{return size;}
    void setSize(int n){n<0 ? :size=n;}
    vector< vector<int> > getDistance() const{return distance;}
    vector< vector<int> > getFlow() const{return flow;}
    void setDistance(vector< vector<int> > d){distance=d;}
    void setFlow(vector< vector<int> > f){flow=f;}
    int atd(int a, int b)const{return distance[a][b];}
    int atf(int a, int b)const{return flow[a][b];}
    int calculateCost(const vector<int> &s)const;

};

#endif
