#ifndef MEMETIC_H_
#define MEMETIC_H_

#include <iostream>

#include "genetic.h"
#include "localsearch.h"


class Memetic: protected Genetic {
private:
  int generations;
  float percent;
  LocalSearch lb;
public:

  Memetic(){};
  ~Memetic(){};
  Memetic(int gen,float p){generations=gen;percent=p;}


  void executeGenerationalPMX();
  void executeGenerationalOrder();
  void executeStationaryPMX();
  void executeStationaryOrder();



    void setMutationP(float a){mutationP=a;}
    void setCrossP(float a){crossP=a;}

    void setProblem(Problem &p){problem=&p;}
    void clearProblem(){problem=0;}
    Problem& getProblem(){return *problem;}


    void setNumPopulation(int p){numPopulation=p;}

    Solution * bestSolution(){return bestSolution();}




};















#endif
