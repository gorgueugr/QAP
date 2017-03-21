#include "Localsearch.h"

LocalSearch::LocalSearch(){
  iteration=0;
  maxIterations=0;
}

LocalSearch::LocalSearch(Problem &p,int i){
  problem=&p;
  iteration=0;
  maxIterations=i;
  dlb.resize(problem->size());
  for(int i=0;i<problem->size())
    dlb[i]=0;
}

LocalSearch::~LocalSearch(){
  delete &initial;
  delete &actual;
  dlb.clear();
}

void LocalSearch::setInitialSolution(Solution &i){
  initial=i;
}

Solution& LocalSearch::getInitialSolution(){
  return initial;
}

void LocalSearch::generateInitialSolution(){
  if(!problem)
    return;
  initial.solution.resize(problem->getSize());
  for(int i=0;i<problem->getSize();i++)
    initial.solution[i]=i;

  random_shuffle(initial.solution.begin(),initial.solution.end(),Rand());

  initial.cost=problem->calculateCost(initial);
}

Solution& LocalSearch::getActualSolution(){
  return actual;
}

void LocalSearch::setMaxIterations(int i){
  maxIterations=i;
}
void LocalSearch::setIterations(int i){
  iteration=i;
}

void LocalSearch::step(){
    bool improve=false;
    int size=problem->getSize();
    int tempCost=0;
    for(int i=0;i<size;i++){
        if(!dlb[i]){
          improve=false;
          for(int j=0;j<size;j++){
            tempCost=problem->moveCost(actual,i,j);
              if(tempCost>actual.cost){
                actual.move(i,j);
                actual.cost=tempCost;
                dlb[i]=0;
                dlb[j]=0;
                improve=true;
              }
            }
          }
        improve ? :dlb[i]=1;
    }

}

void LocalSearch::execute(){
  if(!problem)
    return;
    if(initial.solution.size()<1)
      generateInitialSolution();
    actual=initial;
    while (iteration<maxIterations) {
      step();
      iteration++;
    }
}
