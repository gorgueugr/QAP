#include "ils.h"



void Ils::execute(){
  LocalSearch l;
  l.setProblem(*problem);
  l.setMaxIterations(50000);
  l.execute();
  *result=l.getSolution();
  t = problem->getSize()/4;
  it=1;
  while(it<maxIt){
    mutate(*result);
    result->cost = problem->calculateCost(result->solution);
    l.setInitialSolution(*result);
    l.execute();
    Solution  actual = l.getSolution();
    *result = result->cost < actual.cost ? *result : actual;
    it++;
  }

}


void Ils::mutate(Solution &s){

  int i = getRandomRange(0,s.solution.size()-t);

  std::vector<int>::iterator min,max;

  min = s.solution.begin()+i;
  max = min+t;

  random_shuffle(min,max,getRandomMax);
}


void Ils_es::execute(){
  Es l;
  l.setProblem(*problem);
  l.setMaxIterations(50000);
  l.execute();
  *result=l.getSolution();
  t = problem->getSize()/4;
  it=1;
  while(it<maxIt){
    mutate(*result);
    result->cost = problem->calculateCost(result->solution);
    l.setInitialSolution(*result);
    l.execute();
    Solution  actual = l.getSolution();
    *result = result->cost < actual.cost ? *result : actual;
    it++;
  }

}
