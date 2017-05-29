#ifndef LOCALSEARCH_H_
#define LOCALSEARCH_H_

#include <iostream>
#include <algorithm>    // std::random_shuffle
#include <cstdlib>      // std::rand, std::srand
#include "solution.h"
#include "problem.h"
#include "random.h"
#include "base.h"


using namespace std;

class LocalSearch : public base {
protected:
    Solution initial;
    Solution actual;

    std::vector<bool> dlb;

    int iteration;
    int maxIterations;

    bool improve;

    void startDlb();
    bool checkDlb();
  public:
    LocalSearch();
    LocalSearch(Problem &p,int i);
    ~LocalSearch();

    void setInitialSolution(Solution &i);
    Solution& getInitialSolution();
    void generateInitialSolution();
    void clearInitialSolution(){initial.solution.resize(0);};

    Solution& getActualSolution();

    int getIterations() const {return iteration;}

    void setIterations(int i);
    void setMaxIterations(int i);

  void execute();
  virtual  void step();


};

#endif
