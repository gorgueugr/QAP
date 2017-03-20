#ifndef LOCALSEARCH_H_
#define LOCALSEARCH_H_

#include <iostream>

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
    ~LocalSearch();

    void setInitialSolution(Solution &i);
    Solution& getInitialSolution();

    Solution& getActualSolution();

    void setProblem(Problem &p){problem=&p;}
    void clearProblem(){problem=0;}
    Problem& getProblem(){return *problem;}

    void execute();


}
