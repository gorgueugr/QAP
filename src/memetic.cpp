#include "memetic.h"

Solution * Memetic::getBestOnes(){
  int size=(int)gen.getPopulationSize()*percent;
  Solution *s=new Solution[size];
  int min=INT_MAX;
  int pos=0;
  for(int i=0;i<size;i++){
    s[i]=gen.getPopulation()[i];
    if(s[i].cost)
  }

  for(int i=size;i<gen.getPopulationSize();i++){

  }

}


void Memetic::executeGenerationalPMX(){
  gen.setProblem(*problem);
  lb.setProblem(*problem);
  gen.setNumPopulation(50);
  gen.generatePopulation();
  gen.setMaxIterations(generations);
  Solution * s;
  lb.setMaxIterations(400);
  for(int i=0;i<500;i++){
    gen.executeGenerationalPMX();
    s=gen.getPopulation();
    if(best) s=gen.getBestOnes();
    for(int j=0;j<gen.getPopulationSize()*percent;j++){
      lb.setInitialSolution(s[j]);
      lb.execute();
      s[j]=lb.getActualSolution();
      cout << "\e[A" << "iteration: " << j << endl;
    }
  }


}

void Memetic::executeGenerationalOrder(){
  gen.setProblem(*problem);
  lb.setProblem(*problem);
  gen.setNumPopulation(50);
  gen.generatePopulation();
  gen.setMaxIterations(generations);
  Solution * s;
  lb.setMaxIterations(400);
  for(int i=0;i<500;i++){
    gen.executeGenerationalOrder();
    s=gen.getPopulation();
    for(int j=0;j<(int)50*percent;j++){
      lb.setInitialSolution(s[j]);
      lb.execute();
      s[j]=lb.getActualSolution();

    }
  }


}


void Memetic::executeStationaryPMX(){
  gen.setProblem(*problem);
  lb.setProblem(*problem);
  gen.setNumPopulation(50);
  gen.generatePopulation();
  gen.setMaxIterations(generations);
  Solution * s;
  lb.setMaxIterations(400);
  for(int i=0;i<500;i++){
    gen.executeStationaryPMX();
    s=gen.getPopulation();
    for(int j=0;j<(int)50*percent;j++){
      lb.setInitialSolution(s[j]);
      lb.execute();
      s[j]=lb.getActualSolution();

    }
  }


}

void Memetic::executeStationaryOrder(){
  gen.setProblem(*problem);
  lb.setProblem(*problem);
  gen.setNumPopulation(50);
  gen.generatePopulation();
  gen.setMaxIterations(generations);
  Solution * s;
  lb.setMaxIterations(400);
  for(int i=0;i<500;i++){
    gen.executeStationaryOrder();
    s=gen.getPopulation();
    for(int j=0;j<(int)50*percent;j++){
      lb.setInitialSolution(s[j]);
      lb.execute();
      s[j]=lb.getActualSolution();

    }
  }

}
