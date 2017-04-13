#ifndef GENETIC_H_
#define GENETIC_H_

#include <cstdlib>
#include <climits>
#include <algorithm>    // std::random_shuffle
#include <vector>
#include "problem.h"
#include "solution.h"
#include "random.h"

class Genetic{
protected:
  std::vector<Solution> population;
  Problem * problem;
  int numPopulation;
  int maxIterations;
  float mutationP,crossP;
  Solution best;
  std::vector<Solution> selection;
public:
  Genetic(){maxIterations=50000;mutationP=0.001;crossP=0.7;};
  ~Genetic(){population.clear();};
  Genetic(int pop,int max,float mutation,float cross);

  void setMutationP(float a){mutationP=a;}
  void setCrossP(float a){crossP=a;}

  void setProblem(Problem &p){problem=&p;}
  void clearProblem(){problem=0;}
  Problem& getProblem(){return *problem;}


  void setNumPopulation(int p){numPopulation=p;}
  void setMaxIterations(int m){maxIterations=m;}


  Solution & crossPosition(const Solution &a,const Solution &b);
  Solution & crossPMX(const Solution &a,const Solution &b);
  Solution & crossOX(const Solution &a,const Solution &b);

  Solution * getPopulation(){return population.data();}
  int getPopulationSize(){return numPopulation;}

  int binaryTournament();

  void mutate();

  void generatePopulation();
  void executeGenerationalPMX();
  void executeGenerationalOrder();
  void executeStationaryPMX();
  void executeStationaryOrder();


  Solution * bestSolution();
  Solution * worstSolution();




};




#endif
