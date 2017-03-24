#ifndef GENETIC_H_
#define GENETIC_H_

#include <cstdlib>
#include <vector>
#include "problem.h"
#include "solution.h"


class Genetic{
private:
  std::vector<Solution> population;
  Problem * problem;
  int numPopulation;
public:
  Genetic();
  ~Genetic();

  void setProblem(Problem &p){problem=&p;}
  void clearProblem(){problem=0;}
  Problem& getProblem(){return *problem;}


  void setNumPopulation(int p){numPopulation=p;}

  Solution & crossPosition(const Solution &a,const Solution &b);
  Solution & crossPMX(const Solution &a,const Solution &b);
  Solution & crossOX(const Solution &a,const Solution &b);

  Solution & select();

  void generatePopulation();
  void executeGenerational();
  void executeStationary();

}




#endif
