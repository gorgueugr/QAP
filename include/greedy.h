#ifndef GREEDY_H_
#define GREEDY_H_

#include <vector>
#include <climits>
#include "problem.h"
#include "solution.h"
#include "base.h"

using namespace std;

class Greedy : public base{
protected:
  vector<int> distancePotential;
  vector<int> flowPotential;
  Solution sol;
  void calculateDistancePotential();
  void calculateFlowPotential();
public:
  Greedy(){};
  ~Greedy(){distancePotential.clear();flowPotential.clear();};
  void calculatePotential();
  vector<int> getDistancePotential(){return distancePotential;}
  vector<int> getFlowPotential(){return flowPotential;}
  virtual void execute();
};

#endif
