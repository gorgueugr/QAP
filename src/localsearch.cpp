#include "localsearch.h"

LocalSearch::LocalSearch(){
  iteration=0;
  maxIterations=50000;
  improve=true;
}

LocalSearch::LocalSearch(Problem &p,int i){
  improve=true;
  problem=&p;
  iteration=0;
  maxIterations=i;
  dlb.resize(problem->getSize());
  for(int i=0;i<problem->getSize();++i)
    dlb[i]=0;
}

LocalSearch::~LocalSearch(){
  initial.solution.clear();
  actual.solution.clear();
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
  #pragma omp parallel for
  for(int i=0;i<problem->getSize();++i)
    initial.solution[i]=i;

  random_shuffle ( initial.solution.begin(), initial.solution.end(),getRandomMax);

  initial.cost=problem->calculateCost(initial.solution);
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

void LocalSearch::startDlb(){
  dlb.resize(problem->getSize());
  for(int i=0;i<problem->getSize();++i)
    dlb[i]=0;
}

void LocalSearch::step(){
    int size=problem->getSize();
    int tempCost=0;
    //actual.cost=problem->calculateCost(actual.solution);
    for(int i=0;i<size;++i){
        if(!dlb[i]){
          improve=false;
          for(int j=0;j<size;j++){
            tempCost=problem->moveCost(actual.solution,i,j);
            ++iteration;
              if(0>tempCost){
                actual.move(i,j);
                actual.cost+=tempCost;
                dlb[i]=0;
                dlb[j]=0;
                improve=true;
              }
            }
            improve ? :dlb[i]=1;
          }
    }
}

bool LocalSearch::checkDlb(){
  bool ok=0;
  for(int i=0;i<dlb.size();++i){
    if(!dlb[i])
      ok=1;
  }
  return ok;
}

void LocalSearch::execute(){
  if(!problem)
    return;
    startDlb();
    if(initial.solution.size()<1)
      generateInitialSolution();
      
      improve=true;
      iteration=0;
      actual=initial;
    while (iteration<maxIterations && improve) { //(improve || checkDlb())
      step();
      //++iteration;
    }
    *result = actual;
    initial.solution.resize(0);

}
