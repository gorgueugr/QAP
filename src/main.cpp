
#include <iostream>
#include <vector>
#include "input.h"
#include "greedy.h"
#include "solution.h"


using namespace std;

int main(int argc,char *argv[]){

  if(argc<2 || argc>3){
    cout << "ERROR: Numero de parametros" << endl;
    return -1;
  }

  int Seed=12358132134;

  Input i(argv[1]);
  Problem * qap=i.read();
  Greedy greedy;
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
cout << "Greedy solution:" << endl;
Solution * sol=&greedy.getSolution();
  for(int i=0;i<sol->solution.size();i++){
    cout << " "<< sol->solution[i];
  }
  cout << endl;
  cout << "Coste: " << sol->cost << endl;



}
