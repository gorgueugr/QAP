#include "greedy.h"

void Greedy::calculateDistancePotential(){
  if(!problem)
    return;

  int s=problem->getSize();
  distancePotential.resize(s);
  int sum;
  for(int i=0;i<s;++i){
    sum=0;
    for(int j=0;j<s;++j){
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
  for(int i=0;i<s;++i){
    sum=0;
    for(int j=0;j<s;++j){
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


void Greedy::execute(){
  if(!problem)
    return;
  if(distancePotential.size()==0||flowPotential.size()==0)
    calculatePotential();

    int psize=problem->getSize();
  bool * f=new bool[psize];
  bool * d=new bool[psize];
  for(int i=0;i<psize;++i){
    f[i]=0;
    d[i]=0;
  }

    sol.solution.resize(psize);
    int max,maxFlow=0;
    int min,minDistance=INT_MAX;
      for(int j=0;j<psize;++j){
        //Busqueda de maxFlow
          max=0;
          min=INT_MAX;

          for(int i=0;i<psize;++i){
            if(flowPotential[i]>=max && !f[i]){
              max=flowPotential[i];
              maxFlow=i;
            }
          }

          f[maxFlow]=1;
          //Busqueda de minDistance
          for(int i=0;i<psize;++i){
            if(distancePotential[i]<=min && !d[i]){
              min=distancePotential[i];
              minDistance=i;
            }
          }
          d[minDistance]=1;

          sol.solution[maxFlow]=minDistance;
      }

sol.cost=problem->calculateCost(sol.solution);

}
