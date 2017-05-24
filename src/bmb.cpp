#include "bmb.h"

void bmb::generateInitialsSolutions(){
    int size=problem->getSize();

    initial = new Solution[maxIt];

    #pragma omp parallel for ordered
    for(int i=0;i<maxIt;++i){
      initial[i].solution.resize(size);
      for(int j=0;j<size;++j){
        initial[i].solution[j]=j;
      }
      #pragma omp ordered
      #pragma omp critical
      {
      random_shuffle(initial[i].solution.begin(),initial[i].solution.end(),getRandomMax);
      initial[i].cost=problem->calculateCost(initial[i].solution);
      }
    }

}

void bmb::execute(){
  LocalSearch * ls = new LocalSearch[maxIt];

  generateInitialsSolutions();

  result->cost = INT_MAX;
#pragma omp parallel for
  for(int i=0;i<maxIt;i++){
    ls[i].setProblem(*problem);
    ls[i].setMaxIterations(50000);
    ls[i].setInitialSolution(initial[i]);
    ls[i].execute();
  }
  for(int i=0;i<maxIt;i++){
  *result = ls[i].getSolution() < *result ? ls[i].getSolution() : *result;
  }

}
