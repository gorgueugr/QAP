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
#include "base.h"



using namespace std;

class bmb : public base {
private:
  int maxIt;
  Solution * initial;
public:
  bmb():maxIt(25){};
  ~bmb(){};

  void generateInitialsSolutions();
  void execute();






};





#endif
