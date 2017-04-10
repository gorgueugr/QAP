#include "memetic.h"

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
  for(int i=0;i<size;i++){
    s[i]=&gen.getPopulation()[i];
  }
  return s;
}


void Memetic::executeGenerationalPMX(){
  gen.setProblem(*problem);
  lb.setProblem(*problem);
  gen.setNumPopulation(50);
  gen.generatePopulation();
  gen.setMaxIterations(generations);
  Solution ** s;
  lb.setMaxIterations(400);
  for(int i=0;i<5000;i++){
    gen.executeGenerationalPMX();
    if(best) s=getBestOnes();
    else s=getPopulation();
    for(int j=0;j<gen.getPopulationSize()*percent;j++){
      lb.setInitialSolution(*s[j]);
      lb.execute();
      (*s[j])=lb.getActualSolution();
      //cout << "\e[A" << "iteration: " << j << endl;
    }
    delete s;
  }


}

void Memetic::executeGenerationalOrder(){
  gen.setProblem(*problem);
  lb.setProblem(*problem);
  gen.setNumPopulation(50);
  gen.generatePopulation();
  gen.setMaxIterations(generations);
  Solution ** s;
  lb.setMaxIterations(400);
  for(int i=0;i<5000;i++){
    gen.executeGenerationalOrder();
    if(best) s=getBestOnes();
    else s=getPopulation();
    for(int j=0;j<gen.getPopulationSize()*percent;j++){
      lb.setInitialSolution(*s[j]);
      lb.execute();
      (*s[j])=lb.getActualSolution();
      //cout << "\e[A" << "iteration: " << j << endl;
    }
    delete s;

  }


}


void Memetic::executeStationaryPMX(){
  gen.setProblem(*problem);
  lb.setProblem(*problem);
  gen.setNumPopulation(50);
  gen.generatePopulation();
  gen.setMaxIterations(generations);
  Solution ** s;
  lb.setMaxIterations(400);
  for(int i=0;i<5000;i++){
    gen.executeStationaryPMX();
    if(best) s=getBestOnes();
    else s=getPopulation();
    for(int j=0;j<gen.getPopulationSize()*percent;j++){
      lb.setInitialSolution(*s[j]);
      lb.execute();
      (*s[j])=lb.getActualSolution();
      //cout << "\e[A" << "iteration: " << j << endl;
    }
    delete s;

  }



}

void Memetic::executeStationaryOrder(){
  gen.setProblem(*problem);
  lb.setProblem(*problem);
  gen.setNumPopulation(50);
  gen.generatePopulation();
  gen.setMaxIterations(generations);
  Solution ** s;
  lb.setMaxIterations(400);
  for(int i=0;i<5000;i++){
    gen.executeStationaryOrder();
    if(best) s=getBestOnes();
    else s=getPopulation();
    for(int j=0;j<gen.getPopulationSize()*percent;j++){
      lb.setInitialSolution(*s[j]);
      lb.execute();
      (*s[j])=lb.getActualSolution();
      //cout << "\e[A" << "iteration: " << j << endl;
    }
    delete s;

  }
}
