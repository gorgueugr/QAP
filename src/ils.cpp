#include "ils.h"



void Ils::execute(){
  LocalSearch l;
  l.setProblem(*problem);
  l.setMaxIterations(50000);
  l.execute();
  best = new Solution;
  *best=l.getActualSolution();
  t = problem->getSize()/4;
  it=1;
  while(it<maxIt){
    mutate(*best);
    best->cost = problem->calculateCost(best->solution);
    l.setInitialSolution(*best);
    l.execute();
    Solution  actual = l.getActualSolution();
    *best = best->cost < actual.cost ? *best : actual;
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
  //l.setMaxIterations(50000);
  l.execute();
  best = new Solution;
  *best=l.getBestSolution();
  t = problem->getSize()/4;
  it=1;
  while(it<maxIt){
    mutate(*best);
    best->cost = problem->calculateCost(best->solution);
    l.setInitialSolution(*best);
    l.execute();
    Solution  actual = l.getBestSolution();
    *best = best->cost < actual.cost ? *best : actual;
    it++;
  }

}
