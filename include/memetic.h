#ifndef MEMETIC_H_
#define MEMETIC_H_

#include <iostream>

#include "genetic.h"
#include "localsearch.h"


class Memetic : public GenerationalPMX{
protected:
  int generations;
  int maxGenerations;

  int smallPopul;

  float percent;
  bool best;
public:
  Memetic(int gen,float p,bool b){Genetic::numPopulation=10;generations=gen;percent=p;best=b;smallPopul=percent*numPopulation;}

};

class MemeticBasic : public Memetic {
public:
  void mutate();
};


class MemeticBest : public Memetic{
public:
  void mutate();
  Solution ** getBestOnes();
};






#endif
