#include "greedy.h"

void Greedy::calculateDistancePotential(){
  if(!problem)
    return;

  int s=problem->getSize();
  distancePotential.resize(s);
  int sum;
  for(int i=0;i<s;i++){
    sum=0;
    for(int j=0;j<s;j++){
      sum+=problem->atd(i,j);
    }
    distancePotential[i]=sum;
  }
}

void Greedy::calculateFlowPotential(){
  if(!problem)
    return;

  int s=problem->getSize();
  flowPotential.resize(s);

  int sum;
  for(int i=0;i<s;i++){
    sum=0;
    for(int j=0;j<s;j++){
      sum+=problem->atf(i,j);
    }
    flowPotential[i]=sum;
  }

}

void Greedy::calculatePotential(){
  if(!problem)
    return;
  calculateDistancePotential();
  calculateFlowPotential();
}
