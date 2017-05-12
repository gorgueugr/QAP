#ifndef GRASP_H_
#define GRASP_H_

#include <iostream>
#include <climits>
#include "solution.h"
#include "problem.h"
#include "greedy.h"
#include "localsearch.h"

#include "random.h"


class GreedyRandomized : public Greedy{
private:
  struct pair{
    int u;
    int l;
    pair(int a, int b){
      u=a;
      l=b;
    };
  };

Solution * result;
float alfa;
std::vector<int> LRCF;
std::vector<int> LRCD;
std::vector<pair > SOL;
std::vector<pair > LC;
std::vector<pair > LRC;
std::vector<float> cost;

float dMax;
float dMin;
bool * d;
bool * f;
public:
GreedyRandomized():alfa(0.3){};
~GreedyRandomized(){};

Solution & getSolution(){return *result;}

void buildSolution();
void step1();
void step2();
void calculateCandidates();

void execute();
};




class grasp{
private:
Solution * best;
int it;
int maxIt;

Problem *problem;
public:

grasp():maxIt(25){};
~grasp(){};

void setProblem(Problem &p){problem=&p;}
void clearProblem(){problem=0;}
Problem& getProblem(){return *problem;}

void execute();
Solution & getBestSolution(){return *best;}


};




#endif
