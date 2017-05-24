#ifndef ILS_H_
#define ILS_H_

#include <iostream>
#include <algorithm>    // std::random_shuffle
#include <cstdlib>      // std::rand, std::srand
#include <climits>
#include "solution.h"
#include "problem.h"
#include "localsearch.h"
#include "es.h"
#include "base.h"
#include "random.h"

using namespace std;

class Ils : public base {
protected:
  int t;
  int it;
  int maxIt;
  void mutate(Solution &s);
public:
  Ils():maxIt(25){};
  ~Ils(){};

  void execute();


};


class Ils_es : public Ils {
protected:
public:
  Ils_es(){};
  ~Ils_es(){};

  void execute();


};

#endif
