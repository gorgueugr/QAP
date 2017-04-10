#ifndef MEMETIC_H_
#define MEMETIC_H_

#include <iostream>

#include "genetic.h"
#include "localsearch.h"


class Memetic: protected Genetic {
private:
  int generations;
  float percent;
  bool best;
  LocalSearch lb;
  Genetic gen;
  Problem * problem;
  Solution ** getBestOnes();
  Solution ** getPopulation();
public:

  Memetic(){};
  ~Memetic(){};
  Memetic(int gen,float p,bool b){generations=gen;percent=p;best=b;}


  void executeGenerationalPMX();
  void executeGenerationalOrder();
  void executeStationaryPMX();
  void executeStationaryOrder();

  void setBest(bool b){best=b;}
  void setPercent(float p){percent=p;}
  void setGenerations(int g){generations=g;}

    void setProblem(Problem &p){problem=&p;}
    void clearProblem(){problem=0;}
    Problem& getProblem(){return *problem;}


    void setNumPopulation(int p){gen.setNumPopulation(p);}

    Solution * bestSolution(){return gen.bestSolution();}




};















#endif
