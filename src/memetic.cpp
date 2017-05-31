#include "memetic.h"
#include <stdio.h>

Solution ** MemeticBest::getBestOnes(){
  int size=smallPopul;
  Solution **s = new  Solution*[size];
  int min=INT_MAX;
  int pos=0;
  //copia de los k primeros elementos, guardamos el menor y su posición
  for(int i=0;i<size;++i){
    if(update[i]){
    selection[i].cost=problem->calculateCost(selection[i].solution);
    iteration++;
    }
    update[i]=false;
    s[i]=&selection[i];
  }
  for(int i=0;i<size;++i){
    if(s[i]->cost <= min){ min = s[i]->cost; pos=i;}
  }
  //Recorrer los restantes y si son mayores qe el menor se sustituye y se busca le menor de nuevo
  for(int i=size;i<numPopulation;++i){
    if(update[i]){
    selection[i].cost=problem->calculateCost(selection[i].solution);
    iteration++;
    }
    update[i]=false;

    if(selection[i].cost >= min){
        s[pos] = &selection[i];
        min=INT_MAX;
        for(int j=0;j<size;++j){
          if(s[j]->cost <= min){ min = s[j]->cost; pos=j;}
        }
    }
  }

  return s;
}


void MemeticBasic::mutate(){

  GenerationalPMX::mutate();

    generations++;

    if(generations==maxGenerations){
      generations=0;
      //std::cout << "ok" << '\n';



      LocalSearch *l =new LocalSearch[smallPopul];

      #pragma omp parallel for
      for(int i=0;i<smallPopul;++i){
        //selection[i].cost=problem->calculateCost(selection[i].solution);
        //std::cout << "ok1" << '\n';
        if(update[i]){
          selection[i].cost=problem->calculateCost(selection[i].solution);
          iteration++;
        }
        update[i]=false;
        l[i].setProblem(*problem);
        l[i].setInitialSolution(selection[i]);
        l[i].setMaxIterations(400);
        l[i].execute();
        selection[i]=l[i].getSolution();
      }

      for(int i=0;i<smallPopul;i++){
        iteration+=l[i].getIterations();
      }
      delete[] l;
    }

}


void MemeticBest::mutate(){

  GenerationalPMX::mutate();

    generations++;
  //  std::cout << "ok2" << '\n';


    if(generations==maxGenerations){
      generations=0;


      Solution ** best = getBestOnes();


      LocalSearch *l =new LocalSearch[smallPopul];



      #pragma omp parallel for
      for(int i=0;i<smallPopul;++i){
        l[i].setProblem(*problem);
        l[i].setInitialSolution(*best[i]);
        l[i].setMaxIterations(400);
        l[i].execute();
        *best[i]=l[i].getSolution();
      }

      for(int i=0;i<smallPopul;i++){
        iteration+=l[i].getIterations();
      }
      delete[] l;
    }
}
