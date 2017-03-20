#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <vector>
#include <iostream>

using namespace std;

struct Solution{
    vector<int> solution;
    int cost;
  Solution():cost(0){};
  ~Solution(){solution.clear();}
  Solution& operator=(const Solution &s){
    if(this!=&s){
        solution.resize(s.solution.size());
        for(int i=0;i<s.solution.size();i++)
          solution[i]=s.solution[i];
        cost=s.cost;
    }
    return *this;
  }
};

#endif
