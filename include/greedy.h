#ifndef GREEDY_H_
#define GREEDY_H_

#include <vector>
#include "problem.h"
#include "solution.h"


using namespace std;

class Greedy{
private:
  vector<int> distancePotential;
  vector<int> flowPotential;
  Solution sol;
  Problem * problem;
  void calculateDistancePotential();
  void calculateFlowPotential();
public:
  Greedy():problem(0){};
  ~Greedy(){distancePotential.clear();flowPotential.clear();};
  void setProblem(Problem &p){problem=&p;}
  void clearProblem(){problem=0;}
  Problem getProblem(){return *problem;}
  void calculatePotential();
  vector<int> getDistancePotential(){return distancePotential;}
  vector<int> getFlowPotential(){return flowPotential;}
  void execute();
};

#endif
