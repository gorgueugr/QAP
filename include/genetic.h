#ifndef GENETIC_H_
#define GENETIC_H_

#include <cstdlib>
#include <algorithm>    // std::random_shuffle
#include <vector>
#include "problem.h"
#include "solution.h"


class Genetic{
private:
  std::vector<Solution> population;
  Problem * problem;
  int numPopulation;
  bool * update_sol;
  int maxIterations;
  float mutationP,crossP;
public:
  Genetic(){maxIterations=50000;mutationP=0.001;crossP=0.7;};
  ~Genetic();

  void setProblem(Problem &p){problem=&p;}
  void clearProblem(){problem=0;}
  Problem& getProblem(){return *problem;}


  void setNumPopulation(int p){numPopulation=p;update_sol=new bool[p];for(int i=0;i<p;i++)update_sol[i]=0}

  Solution & crossPosition(const Solution &a,const Solution &b);
  Solution & crossPMX(const Solution &a,const Solution &b);
  Solution & crossOX(const Solution &a,const Solution &b);

  int BinaryTournament();

  void generatePopulation();
  void executeGenerational();
  void executeStationary();

};




#endif
