#ifndef LOCALSEARCH_H_
#define LOCALSEARCH_H_

#include <iostream>
#include "random.h"
#include "solution.h"
#include "problem.h"



using namespace std;

class LocalSearch{
  private:
    Solution initial;
    Solution actual;

    std::vector<bool> dlb;

    int iteration;
    int maxIterations;

    Problem * problem;
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

    void setIterations(int i);
    void setMaxIterations(int i);

    void execute();
    void step();


};

#endif
