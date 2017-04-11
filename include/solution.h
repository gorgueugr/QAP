#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <vector>

using namespace std;

struct Solution{
    vector<int> solution;
    int cost;
  Solution():cost(0){};
  ~Solution(){solution.clear();}
  bool operator<(const Solution &n) const
    {
        return cost < n.cost;
    };
  Solution& operator=(const Solution &s){
    if(this!=&s){
        solution.resize(s.solution.size());
        #pragma omp parallel for
        for(int i=0;i<s.solution.size();i++)
          solution[i]=s.solution[i];
        cost=s.cost;
    }
    return *this;
  }
  void move(int r,int s){
    int t=solution[r];
    solution[r]=solution[s];
    solution[s]=t;
  }

};

#endif
