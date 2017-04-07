#include "memetic.h"



void Memetic::executeGenerationalPMX(){

  generatePopulation();
  crossP=0.7;
  mutationP=0.001;

  selection.resize(numPopulation);
  int iteration=0;
  int numCross=(int) crossP*(numPopulation/2);
  //cout<< "numcross:" << numCross<<endl;
  int a,b;


  int contCross;
  while(iteration<maxIterations){
        contCross=0;
          for(int i=0;i<numPopulation;i++){
              a=binaryTournament();
            if(contCross<numCross){
              b=binaryTournament();
              selection[i]=crossPMX(population[a],population[b]);
              contCross++;

            }else{
              selection[i]=population[a];
            }
          }

          /*Mutation*/
          mutate();

          best.cost=bestSolution()->cost;
          best.solution=bestSolution()->solution;

          population=selection;

          for(int i=0;i<numPopulation;i++){
            population[i].cost=problem->calculateCost(population[i].solution);
          }

          Solution * worst = worstSolution();
          worst->solution=best.solution;
          worst->cost=best.cost;
          cout << "\e[A" << "iteration: " << iteration << " of " << maxIterations << ". Best solution cost: " << bestSolution()->cost << " worst Solution:" << worstSolution()->cost << endl;


          //LocalSearch
          if(iteration%generations==0){
            int numlb=percent*numPopulation;
            lb.setProblem(*problem);
            for(int i=0;i<numlb;i++){
              lb.setInitialSolution(population[i]);
              lb.setMaxIterations(10000);
              lb.execute();
              population[i].solution=lb.getActualSolution().solution;
              population[i].cost=lb.getActualSolution().cost;

            }

          }

          cout << "\e[A" << "iteration: " << iteration << " of " << maxIterations << ". Best solution cost: " << best.cost << " worst Solution:" << worstSolution()->cost <<endl ;
          iteration++;
  }

}

void Memetic::executeGenerationalOrder(){

  generatePopulation();

  crossP=0.7;
  mutationP=0.001;


  selection.resize(numPopulation);
  int iteration=0;
  int numCross=(int) crossP*(numPopulation/2);
  //cout<< "numcross:" << numCross<<endl;
  int a,b;


  int contCross;
  while(iteration<maxIterations){
        contCross=0;
          for(int i=0;i<numPopulation;i++){
              a=binaryTournament();
            if(contCross<numCross){
              b=binaryTournament();
              selection[i]=crossPosition(population[a],population[b]);
              contCross++;

            }else{
              selection[i]=population[a];
            }
          }

          /*Mutation*/
          mutate();

          best.cost=bestSolution()->cost;
          best.solution=bestSolution()->solution;

          population=selection;

          for(int i=0;i<numPopulation;i++){
            population[i].cost=problem->calculateCost(population[i].solution);
          }

          Solution * worst = worstSolution();
          worst->solution=best.solution;
          worst->cost=best.cost;

          //LocalSearch
          if(iteration%generations==0){
            int numlb=percent*numPopulation;
            lb.setProblem(*problem);
            for(int i=0;i<numlb;i++){
              lb.setInitialSolution(population[i]);
              lb.setMaxIterations(10000);
              lb.execute();
              population[i].solution=lb.getActualSolution().solution;
              population[i].cost=lb.getActualSolution().cost;

            }

          }
          cout << "\e[A" << "iteration: " << iteration << " of " << maxIterations << ". Best solution cost: " << best.cost << " worst Solution:" << worstSolution()->cost << endl;
          iteration++;
  }

}


void Memetic::executeStationaryPMX(){

  generatePopulation();

  crossP=1;
  mutationP=0.001;


  selection.resize(2);
  int iteration=0;
  int a,b,c;


  int contCross;
  while(iteration<maxIterations){
            //Selection
              a=binaryTournament();
              b=binaryTournament();
              //Cross
              selection[0]=crossPMX(population[a],population[b]);
              selection[1]=crossPMX(population[b],population[a]);


          /*Mutation*/
          if(rand() % 1000 <1){
            a=rand() % problem->getSize();
            c=rand() % problem->getSize();
            b=rand() % selection.size();
            selection[b].move(a,c);
          }

          Solution * worst;
          for(int i=0;i<selection.size();i++){
              worst = worstSolution();
              selection[i].cost=problem->calculateCost(selection[i].solution);
              if(worst->cost > selection[i].cost ){
                worst->solution=selection[i].solution;
                worst->cost=selection[i].cost;
              }
          }

          //LocalSearch
          if(iteration%generations==0){
            int numlb=percent*numPopulation;
            lb.setProblem(*problem);
            for(int i=0;i<numlb;i++){
              lb.setInitialSolution(population[i]);
              lb.setMaxIterations(10000);
              lb.execute();
              population[i].solution=lb.getActualSolution().solution;
              population[i].cost=lb.getActualSolution().cost;

            }

          }

          cout << "\e[A" << "iteration: " << iteration << " of " << maxIterations << ". Best solution cost: " << bestSolution()->cost << " worst Solution:" << worstSolution()->cost << endl;


          iteration++;
  }
}
void Memetic::executeStationaryOrder(){

  generatePopulation();

  crossP=1;
  mutationP=0.001;


  selection.resize(2);
  int iteration=0;
  int a,b,c;


  int contCross;
  while(iteration<maxIterations){
            //Selection
              a=binaryTournament();
              b=binaryTournament();
              //Cross
              selection[0]=crossPosition(population[a],population[b]);
              selection[1]=crossPosition(population[b],population[a]);


          /*Mutation*/
          if(rand() % 1000 <1){
            a=rand() % problem->getSize();
            c=rand() % problem->getSize();
            b=rand() % selection.size();
            selection[b].move(a,c);
          }

          Solution * worst;
          for(int i=0;i<selection.size();i++){
              worst = worstSolution();
              selection[i].cost=problem->calculateCost(selection[i].solution);
              if(worst->cost > selection[i].cost ){
                worst->solution=selection[i].solution;
                worst->cost=selection[i].cost;
              }
          }

          //LocalSearch
          if(iteration%generations==0){
            int numlb=percent*numPopulation;
            lb.setProblem(*problem);
            for(int i=0;i<numlb;i++){
              lb.setInitialSolution(population[i]);
              lb.setMaxIterations(400);
              lb.execute();
              population[i].solution=lb.getActualSolution().solution;
              population[i].cost=lb.getActualSolution().cost;

            }

          }

          cout << "\e[A" << "iteration: " << iteration << " of " << maxIterations << ". Best solution cost: " << bestSolution()->cost << " worst Solution:" << worstSolution()->cost << endl;




          iteration++;
  }

}
