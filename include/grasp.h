#ifndef GRASP_H_
#define GRASP_H_

#include <iostream>
#include <climits>
#include "solution.h"
#include "problem.h"
#include "greedy.h"
#include "random.h"

class GreedyRandomized : public Greedy{
private:
Solution * result;
float alfa;
std::vector<int> LRCF;
std::vector<int> LRCD;
float dMax;
float dMin;
bool * d;
bool * f;
public:
GreedyRandomized():alfa(0.3){};
~GreedyRandomized(){};


void execute();
};




class grasp{
private:
Solution * best;
int it;
int maxIt;

public:
grasp(){};
~grasp(){};

void execute();

};




#endif
