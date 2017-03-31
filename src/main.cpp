
#include <iostream>
#include <vector>
#include <cstdlib>      // std::rand, std::srand
#include "input.h"
#include "solution.h"
#include "greedy.h"
#include "localsearch.h"
#include "genetic.h"



using namespace std;

int main(int argc,char *argv[]){

  if(argc<2 || argc>3){
    cout << "ERROR: Numero de parametros" << endl;
    return -1;
  }

  int Seed=123581321;

  srand(Seed);

  Input i(argv[1]);
  Problem * qap=i.read();
  Greedy greedy;
  LocalSearch lb;
  Genetic gen;
  lb.setProblem(*qap);
  greedy.setProblem(*qap);
  gen.setProblem(*qap);

  int s=qap->getSize();

  cout << "Size:" << s << endl;

  cout << "Distance:" << endl;
  for(int i=0;i<s;i++){
    for (int j=0;j<s;j++) {
      cout << " " << qap->atd(i,j) ;
    }
    cout << endl;
  }
  cout << "Flow:" << endl;
  for(int i=0;i<s;i++){
    for (int j=0;j<s;j++){
      cout << " " << qap->atf(i,j);
    }
    cout << endl;
  }

//Ejecucion greedy
  //greedy.calculatePotential();
  greedy.execute();
  //___________________//

  //cout <<"Distance size:" <<d.size() << endl;
  Solution * sol=&greedy.getSolution();

cout << "Greedy solution:" << endl;
  for(int i=0;i<sol->solution.size();i++){
    cout << " "<< sol->solution[i];
  }
  cout << endl;
  cout << "Coste: " << sol->cost << endl;

lb.setMaxIterations(10000);
lb.execute();
sol=&lb.getActualSolution();
Solution ran=lb.getInitialSolution();
ran.cost = qap->calculateCost(ran.solution);
cout << "Random solution cost: " << ran.cost << endl;
cout << "LocalSearch initializated with random solution :" << endl;
  for(int i=0;i<sol->solution.size();i++){
    cout << " "<< sol->solution[i];
  }
  cout << endl;
  cout << "Cost: " << sol->cost << endl;
cout << "iterations: " << lb.getIterations() << endl;

  lb.setInitialSolution(greedy.getSolution());
  lb.execute();
  sol=&lb.getActualSolution();

  cout << "LocalSearch initializated with greedy solution :" << endl;
    for(int i=0;i<sol->solution.size();i++){
      cout << " "<< sol->solution[i];
    }
    cout << endl;
    cout << "Cost: " << sol->cost << endl;
    cout << "iterations: " << lb.getIterations() << endl;

gen.setNumPopulation(50);
gen.executeGenerational();
sol=&gen.bestSolution();
cout << "Generational:" << endl;
  for(int i=0;i<sol->solution.size();i++){
    cout << " "<< sol->solution[i];
  }
  cout << endl;
  cout << "Cost: " << sol->cost << endl;
  //cout << "iterations: " << lb.getIterations() << endl;



/*
cout << "Testing calculateCost() function with nug12.dat optimal solution: 578 " << endl;
//12,7,9,3,4,8,11,1,5,6,10,2
Solution optimal;
optimal.solution.resize(qap->getSize());
optimal.solution[0]=11;
optimal.solution[1]=6;
optimal.solution[2]=8;
optimal.solution[3]=2;
optimal.solution[4]=3;
optimal.solution[5]=7;
optimal.solution[6]=10;
optimal.solution[7]=0;
optimal.solution[8]=4;
optimal.solution[9]=5;
optimal.solution[10]=9;
optimal.solution[11]=1;


optimal.cost = qap->calculateCost(optimal.solution);

cout << "Optimal cost:" << optimal.cost <<endl;

cout << "Move cost: 0 6 " << qap->moveCost(optimal.solution,0,6) << endl;

optimal.move(0,6);
optimal.cost=qap->calculateCost(optimal.solution);

cout << "Optimal cost moved:" << optimal.cost <<endl;
*/


}
