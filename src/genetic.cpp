#include "genetic.h"


void Genetic::generatePopulation(){
  if(!problem)
    return;
    int size=problem->getSize();
    population.resize(numPopulation);
    for(int i=0;i<numPopulation;i++){
      population[i].solution.resize(size);
      for(int i=0;i<size;i++){
        population[i].solution[i]=i;
        random_shuffle ( population[i].solution.begin(), population[i].solution.end());
      }
      population[i].cost=problem->calculateCost(population[i].solution);
    }
}

Solution & Genetic::crossPosition(Solution &a,Solution &b){
  int s=a.solution.size();
  Solution * t=new Solution();
  t.solution.resize(s);
    for(int i=0;i<s;i++)
      a.solution[i]!=b.solution[i] ? : t.solution[i]=b.solution[i];


}
