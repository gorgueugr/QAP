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
public:
  Memetic(int gen,float p){Genetic::numPopulation=10;generations=gen;percent=p;smallPopul=percent*numPopulation;}

};

class MemeticBasic : public Memetic {
public:
  MemeticBasic(int gen, float p):Memetic(gen,p){}
  void mutate() override;
};


class MemeticBest : public Memetic{
public:
  MemeticBest(int gen, float p):Memetic(gen,p){}
  void mutate() override;
  Solution ** getBestOnes();
};






#endif
