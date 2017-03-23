
#include <iostream>
#include <vector>
#include "input.h"
#include "solution.h"
#include "greedy.h"
#include "localsearch.h"



using namespace std;

int main(int argc,char *argv[]){

  if(argc<2 || argc>3){
    cout << "ERROR: Numero de parametros" << endl;
    return -1;
  }

  int Seed=123581321;


  Input i(argv[1]);
  Problem * qap=i.read();
  Greedy greedy;
  LocalSearch lb;
  lb.setProblem(*qap);
  greedy.setProblem(*qap);


  int s=qap->getSize();
  cout << "Size:" << s << endl;
  /*
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
      cout << " " << qap->atd(i,j);
    }
    cout << endl;
  }
  */
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

lb.setMaxIterations(500);
cout << "ok" << endl;
lb.execute();
sol=&lb.getActualSolution();


cout << "LocalSearch solution:" << endl;
  for(int i=0;i<sol->solution.size();i++){
    cout << " "<< sol->solution[i];
  }
  cout << endl;
  cout << "Coste: " << sol->cost << endl;



}
