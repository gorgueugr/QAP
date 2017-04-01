#ifndef GENETIC_H_
#define GENETIC_H_

#include <cstdlib>
#include <climits>
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
  Solution best;
public:
  Genetic(){maxIterations=50000;mutationP=0.001;crossP=1;};
  ~Genetic(){population.clear();};

  void setProblem(Problem &p){problem=&p;}
  void clearProblem(){problem=0;}
  Problem& getProblem(){return *problem;}


  void setNumPopulation(int p){numPopulation=p;update_sol=new bool[p];}

  Solution & crossPosition(const Solution &a,const Solution &b);
  Solution & crossPMX(const Solution &a,const Solution &b);
  Solution & crossOX(const Solution &a,const Solution &b);


  int BinaryTournament();

  void Mutate();

  void generatePopulation();
  void executeGenerational();
  void executeStationary();

  Solution & bestSolution();
  Solution & worstSolution();




};




#endif
