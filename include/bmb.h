#ifndef BMB_H_
#define BMB_H_

#include <iostream>
#include <algorithm>    // std::random_shuffle
#include <cstdlib>      // std::rand, std::srand
#include <climits>
#include "solution.h"
#include "problem.h"
#include "localsearch.h"
#include "random.h"



using namespace std;

class bmb {
private:
  Problem * problem;
  Solution best;
  int maxIt;
public:
  bmb():maxIt(25){};
  ~bmb(){};
  Solution & getBestSolution(){return best;}

  void setProblem(Problem &p){problem=&p;}
  void clearProblem(){problem=0;}
  Problem& getProblem(){return *problem;}

  void execute();






};





#endif
