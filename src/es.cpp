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
      ++it;
      neighbours++;
      double r = getRandomFloat();
      double e = exp((-tempCost)/tempActual);
      //cout << "Random/Exp" << r << " " << e <<endl;
      if(tempCost<0 || r < e ){
        accepted++;
        actual.move(a,b);
        actual.cost+=tempCost;

          if(best->cost > actual.cost)
            best = &actual;
      }
      tempActual = calculateNextTemp();
    }
    //cout << "neighbours/Accepted: " << neighbours <<" "<< accepted << endl;

}



void Es::execute(){
  if(!problem)
    return;
    if(initial.solution.size()<1)
      generateInitialSolution();

      //cout << "Cost Random:" << initial.cost << endl;
      tempInitial = calculateInitialTemp();
      tempFinal = calculateFinalTemp();
      maxNeighbours = 10*problem->getSize();
      maxSucces = 0.1 * maxNeighbours;
      maxIt = 50000;
      float m = (maxIt/maxNeighbours);
      //TODO:CHECK THIS
      beta = (tempInitial-tempFinal)/(m*tempInitial*tempFinal);
      it = 0;

      actual=initial;
      tempActual=tempInitial;
      best=&initial;
    while (it<maxIt) {
      step();
    }
    //cout << "tempInitial/tempActual/tempFinal: " << tempInitial << " " << tempActual << " " << tempFinal << endl;
    //cout << "it: " << it << endl;
}

float Es::calculateInitialTemp(){
  return (u*initial.cost)/(-log(u));
}

float Es::calculateFinalTemp(){
  return 0.001 < tempInitial ? 0.001 : tempInitial;
}

float Es::calculateNextTemp(){
  return (float) tempActual/(1+beta*tempActual);
}

float Es::calculateNextTempLineal(){
  return (float) alfa*tempActual;
}
