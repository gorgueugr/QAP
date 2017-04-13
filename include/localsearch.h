#ifndef LOCALSEARCH_H_
#define LOCALSEARCH_H_

#include <iostream>
#include <algorithm>    // std::random_shuffle
#include <cstdlib>      // std::rand, std::srand
#include "solution.h"
#include "problem.h"
#include "random.h"


using namespace std;

class LocalSearch{
  private:
    Solution initial;
    Solution actual;

    std::vector<bool> dlb;

    int iteration;
    int maxIterations;

    Problem * problem;

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

    Solution& getActualSolution();

    void setProblem(Problem &p){problem=&p;}
    void clearProblem(){problem=0;}
    Problem& getProblem(){return *problem;}

    int getIterations()const;

    void setIterations(int i);
    void setMaxIterations(int i);

    void execute();
    void step();


};

#endif
