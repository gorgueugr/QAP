#ifndef ES_H_
#define ES_H_

#include <iostream>
#include <algorithm>    // std::random_shuffle
#include <cstdlib>      // std::rand, std::srand
#include <climits>
#include "solution.h"
#include "problem.h"
#include "localsearch.h"
#include "random.h"
#include <math.h>       /* log */

using namespace std;

class Es : public LocalSearch {
private:
  Solution  * best;
  int it;
  int maxIt;
  float beta;
  float tempActual;
  float tempInitial;
  float tempFinal;
  float u;
  int maxNeighbours;
  int maxSucces;

  float calculateNextTemp();
  float calculateInitialTemp();
  float calculateFinalTemp();
public:
  Es():u(0.3){};
  ~Es(){};

  float getTempInitial(){return tempInitial;}
  float getTempFinal(){return tempFinal;}

  Solution & getBestSolution(){return *best;}
  void execute();
  void step();


};





#endif
