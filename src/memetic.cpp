#include "memetic.h"
#include <stdio.h>

Solution ** Memetic::getBestOnes(){
  int size=(int)gen.getPopulationSize()*percent;
  Solution **s = new  Solution*[size];
  int min=INT_MAX;
  int pos=0;
  //copia de los k primeros elementos, guardamos el menor y su posición
  for(int i=0;i<size;i++){
    s[i]=&gen.getPopulation()[i];
    if(s[i]->cost <= min){ min = s[i]->cost; pos=i;}
  }
  //Recorrer los restantes y si son mayores qe el menor se sustituye y se busca le menor de nuevo
  for(int i=size;i<gen.getPopulationSize();i++){
    if(gen.getPopulation()[i].cost >= min){
        s[pos] = &gen.getPopulation()[i];
        min=INT_MAX;
        for(int j=0;j<size;j++){
          if(s[j]->cost <= min){ min = s[j]->cost; pos=j;}
        }
    }
  }

  return s;
}

Solution ** Memetic::getPopulation(){
  int size=(int)gen.getPopulationSize()*percent;
  Solution **s = new  Solution*[size];
  #pragma omp parallel for
  for(int i=0;i<size;i++){
    s[i]=&gen.getPopulation()[i];
  }
  return s;
}


void Memetic::executeGenerationalPMX(){
  gen.setProblem(*problem);
  gen.setNumPopulation(50);
  gen.generatePopulation();
  gen.setMaxIterations(generations);
  int size=gen.getPopulationSize()*percent;
  Solution ** s;
  LocalSearch * l = new LocalSearch[size];
  #pragma omp parallel for
  for(int j=0;j<size;j++){
    l[j].setMaxIterations(400);
    l[j].setProblem(*problem);
  }
  for(int i=0;i<5000;i++){
    gen.executeGenerationalPMX();
    if(best) s=getBestOnes();
    else s=getPopulation();
   #pragma omp parallel for
    for(int j=0;j<size;j++){
      l[j].setInitialSolution(*s[j]);
      l[j].execute();
      (*s[j])=l[j].getActualSolution();
    }
    delete[] s;
  }
  delete[] l;
}

void Memetic::executeGenerationalOrder(){
  gen.setProblem(*problem);
  gen.setNumPopulation(50);
  gen.generatePopulation();
  gen.setMaxIterations(generations);
  int size=gen.getPopulationSize()*percent;
  Solution ** s;
  LocalSearch * l = new LocalSearch[size];
  #pragma omp parallel for
  for(int j=0;j<size;j++){
    l[j].setMaxIterations(400);
    l[j].setProblem(*problem);
  }
  for(int i=0;i<5000;i++){
    gen.executeGenerationalOrder();
    if(best) s=getBestOnes();
    else s=getPopulation();
   #pragma omp parallel for
    for(int j=0;j<size;j++){
      l[j].setInitialSolution(*s[j]);
      l[j].execute();
      (*s[j])=l[j].getActualSolution();
    }
    delete[] s;
  }
  delete[] l;
}


void Memetic::executeStationaryPMX(){
  gen.setProblem(*problem);
  gen.setNumPopulation(50);
  gen.generatePopulation();
  gen.setMaxIterations(generations);
  int size=gen.getPopulationSize()*percent;
  Solution ** s;
  LocalSearch * l = new LocalSearch[size];
  #pragma omp parallel for
  for(int j=0;j<size;j++){
    l[j].setMaxIterations(400);
    l[j].setProblem(*problem);
  }
  for(int i=0;i<5000;i++){
    gen.executeStationaryPMX();
    if(best) s=getBestOnes();
    else s=getPopulation();
   #pragma omp parallel for
    for(int j=0;j<size;j++){
      l[j].setInitialSolution(*s[j]);
      l[j].execute();
      (*s[j])=l[j].getActualSolution();
    }
    delete[] s;
  }
  delete[] l;
}

void Memetic::executeStationaryOrder(){
  gen.setProblem(*problem);
  gen.setNumPopulation(50);
  gen.generatePopulation();
  gen.setMaxIterations(generations);
  int size=gen.getPopulationSize()*percent;
  Solution ** s;
  LocalSearch * l = new LocalSearch[size];
  #pragma omp parallel for
  for(int j=0;j<size;j++){
    l[j].setMaxIterations(400);
    l[j].setProblem(*problem);
  }
  for(int i=0;i<5000;i++){
    gen.executeStationaryOrder();
    if(best) s=getBestOnes();
    else s=getPopulation();
   #pragma omp parallel for
    for(int j=0;j<size;j++){
      l[j].setInitialSolution(*s[j]);
      l[j].execute();
      (*s[j])=l[j].getActualSolution();
    }
    delete[] s;
  }
  delete[] l;
}
