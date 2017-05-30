#ifndef GENETIC_H_
#define GENETIC_H_

#include <cstdlib>
#include <climits>
#include <algorithm>    // std::random_shuffle
#include <vector>
#include "problem.h"
#include "solution.h"
#include "random.h"
#include "base.h"


class Cross{
public:
 virtual Solution & cross(const Solution &a,const Solution &b){};
};

class Genetic : public base, public Cross  {
protected:
  std::vector<Solution> population;
  std::vector<Solution> selection;

  int numPopulation;

  float mutationP,crossP;

  Solution best;

  int iteration;
  int maxIterations;

  bool * update;
public:
  Genetic(){maxIterations=50000;mutationP=0.001;crossP=0.7;numPopulation=50;};
  ~Genetic(){population.clear();};
  Genetic(int pop,int max,float mutation,float cross);

  void setMutationP(float a){mutationP=a;}
  void setCrossP(float a){crossP=a;}


  void setNumPopulation(int p){numPopulation=p;}
  void setMaxIterations(int m){maxIterations=m;}


  //Solution & crossPosition(const Solution &a,const Solution &b);
  //Solution & crossPMX(const Solution &a,const Solution &b);
  //Solution & crossOX(const Solution &a,const Solution &b);

  Solution * getPopulation(){return population.data();}
  int getPopulationSize(){return numPopulation;}

  int getIterations()const{return iteration;}

  int binaryTournament();

  virtual void mutate();

  void generatePopulation();

/*
  void executeGenerationalPMX();
  void executeGenerationalOrder();
  void executeStationaryPMX();
  void executeStationaryOrder();
*/

  Solution * bestSolution();
  Solution * worstSolution();

};


class Generational : public Genetic {
public:
  Generational(){crossP=0.7;mutationP=0.001;};
  void execute();
};

class Stationary : public Genetic {
public:
  Stationary(){crossP=1;mutationP=0.001;selection.resize(2);};
  void execute();

};


class PMX : public Cross{
public:
  Solution & cross(const Solution &a,const Solution &b);
};
class POS : public Cross{
public:
  Solution & cross(const Solution &a,const Solution &b);
};

class GenerationalPMX : public Generational , public PMX{
};

class GenerationalPOS : public Generational, public POS{
};

class StationaryPMX : public Stationary , public PMX{
};

class StationaryPOS : public Stationary, public POS{
};



#endif
