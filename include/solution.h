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
};

#endif
