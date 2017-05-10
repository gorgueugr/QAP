#include "es.h"


void Es::step(){
    int size=problem->getSize();
    int tempCost=0;
    //actual.cost=problem->calculateCost(actual.solution);
    int neighbours=0;
    int accepted=0;
    while(neighbours<maxNeighbours && accepted<maxSucces){
    int a = getRandomMax(problem->getSize());
    int b = getRandomMax(problem->getSize());
    while(b==a)
      b = getRandomMax(problem->getSize());

      tempCost=problem->moveCost(actual.solution,a,b);
      neighbours++;
      if(tempCost<0 || getRandomFloat() < exp((-tempCost)/tempActual) ){
        accepted++;
        actual.move(a,b);
        actual.cost+=tempCost;

          if(best->cost > actual.cost)
            best = &actual;
      }
      tempActual = calculateNextTemp();
    }
}



void Es::execute(){
  if(!problem)
    return;
    if(initial.solution.size()<1)
      generateInitialSolution();

      tempInitial = calculateInitialTemp();
      tempFinal = calculateFinalTemp();
      maxNeighbours = 10*initial.solution.size();
      maxSucces = 0.1 * maxNeighbours;
      maxIt = 50000;
      beta = (tempInitial-tempFinal)/(maxIt*tempInitial*tempFinal);

      actual=initial;
      tempActual=tempInitial;
      best=&initial;
    while (tempActual>=tempFinal) { //(improve || checkDlb())
      step();
    }
}

float Es::calculateInitialTemp(){
  return (u*initial.cost)/(-log(u));
}

float Es::calculateFinalTemp(){
  return 0,001 < tempInitial ? 0,001 : tempInitial;
}

float Es::calculateNextTemp(){
  return (float) tempActual/(1+beta*tempActual);
}
