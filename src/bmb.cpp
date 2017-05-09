#include "bmb.h"



void bmb::execute(){
  LocalSearch * ls = new LocalSearch[maxIt];
  best.cost = INT_MAX;

  for(int i=0;i<maxIt;i++){
    ls[i].setProblem(*problem);
    ls[i].setMaxIterations(50000);
    ls[i].execute();
    best = ls[i].getActualSolution() < best ? ls[i].getActualSolution() : best;
  }

}
