#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <vector>
#include <iostream>

using namespace std;

class Solution{
private:
    vector<int> solution;
    int cost;
public:
  Solution():cost(0){};
  ~Solution(){solution.clear();}
  vector<int> getSolution()const{return solution;}
  void setSolution(vector<int> s){solution=s;}
  int getSize(){return solution.size();}
  int getCost(){return cost;}
  int setCost(int c){cost=c;}
};

#endif
