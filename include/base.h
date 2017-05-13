#ifndef BASE_H_
#define BASE_H_

#include <climits>
#include "solution.h"
#include "problem.h"


class base{
protected:
  Problem *problem;
  Solution *result;
public:
  base(){
    result = new Solution;
    result->cost = INT_MAX;
  }
  ~base(){}


  void setProblem(Problem &p);
  void clearProblem();
  Problem& getProblem();

  Solution& getSolution();

  virtual void execute();

};





#endif
