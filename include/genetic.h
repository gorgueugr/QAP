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

/*
class Cross{
public:
 virtual Solution & cross(const Solution &a,const Solution &b);
};*/

class Genetic : public base {
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
  Genetic(){maxIterations=50000;numPopulation=50;};
  ~Genetic(){population.clear();};

  void setMutationP(float a){mutationP=a;}
  void setCrossP(float a){crossP=a;}


  void setNumPopulation(int p){numPopulation=p;}
  void setMaxIterations(int m){maxIterations=m;}

  Solution * getPopulation(){return population.data();}
  int getPopulationSize(){return numPopulation;}

  int getIterations()const{return iteration;}

  int binaryTournament();

  virtual void mutate();

  virtual Solution & cross(const Solution &a,const Solution &b){};

  void generatePopulation();

  Solution * bestSolution();
  Solution * worstSolution();

};


class PMX : virtual public Genetic{
public:
  Solution & cross(const Solution &a,const Solution &b) override;
};
class POS : virtual public Genetic{
public:
  Solution & cross(const Solution &a,const Solution &b) override;
};


class Generational :virtual public Genetic {
public:
  Generational(){crossP=0.7;mutationP=0.001;};
  void execute() override;
};

class Stationary :virtual public Genetic {
public:
  Stationary(){crossP=1;mutationP=0.001;selection.resize(2);};
  void execute() override;
};


class GenerationalPMX : public PMX, public Generational {
};

class GenerationalPOS : public POS, public Generational {
};

class StationaryPMX : public POS, public Stationary{
};

class StationaryPOS :  public POS, public Stationary{
};



#endif
