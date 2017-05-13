#include "base.h"


void base::setProblem(Problem &p){
  problem=&p;
}
void base::clearProblem(){
  problem=0;
}
Problem& base::getProblem(){
  return *problem;
}

Solution& base::getSolution(){
  return *result;
}

void base::execute(){}
