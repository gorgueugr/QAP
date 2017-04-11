#include "genetic.h"


Genetic::Genetic(int pop,int max,float mutation,float cross){
  numPopulation=pop;
  maxIterations=max;
  mutationP=mutation;
  crossP=cross;
}

void Genetic::generatePopulation(){
  if(!problem)
    return;
    int size=problem->getSize();
    population.resize(numPopulation);
    #pragma omp parallel for
    for(int i=0;i<numPopulation;i++){
      population[i].solution.resize(size);
      for(int j=0;j<size;j++){
        population[i].solution[j]=j;
      }
      random_shuffle ( population[i].solution.begin(), population[i].solution.end());
      population[i].cost=problem->calculateCost(population[i].solution);
    }

}

Solution & Genetic::crossPosition(const Solution &a,const Solution &b){
  int s=a.solution.size();
  Solution * t=new Solution(); //Son
  t->solution.resize(s);
  for(int i=0;i<s;i++) //fill with -1
    t->solution[i]=-1;

  vector<int> v; //vector to save the numbers that do not coincide
    for(int i=0;i<s;i++){
      if(a.solution[i]==b.solution[i])
        t->solution[i]=b.solution[i];
      else
        v.push_back(a.solution[i]); //if father1[i] and father2[i] are equal then copy it in son
    }
    if(v.size()>0){                                                  //else push it to the v vector
    random_shuffle(v.begin(),v.end()); //shuffle the vector with the numbers that do not coincide
    int c=0;
    for(int i=0;i<s;i++) //if in son [i]==-1 then get a number from v
      if(t->solution[i]==-1){
        t->solution[i]=v[c];
        c++;
      }
    v.clear();
    }
    return *t;
}


Solution & Genetic::crossPMX(const Solution &a,const Solution &b){
  int s=a.solution.size();

  Solution * t=new Solution(); //Son
  t->solution.resize(s);
  int * v=new int[s]; //vector to save the relations between parents
  bool * m=new bool[s];
  #pragma omp parallel for
  for(int i=0;i<s;i++){ //fill with i
    v[i]=i;
    m[i]=0;
  }
  t->solution=b.solution;

    int min,max; //points to cross
    min = (rand() % (int)(s - 1)); //first point
    max = min+1 + (rand() % (int)(s-1 - min) ); //second point


    //Step 1: copy values of parent1 in the range[min,max] in the son

    for(int i=min;i<max;i++){
      t->solution[i]=a.solution[i]; //Copy in the son
      m[a.solution[i]]=1; //Mark the number
      v[a.solution[i]]=b.solution[i]; //Define relation between parent 1 and 2
    }

    for(int i=0;i<s;i++){
      if(i<min||i>=max){
        while(m[t->solution[i]]==1)
          t->solution[i]=v[t->solution[i]];
      }
    }


    delete v;
    delete m;
    return *t;
}

int  Genetic::binaryTournament(){
  int a = rand() % numPopulation; //first random player
  int b = rand() % numPopulation; //Second random player

  return (population[a].cost>population[b].cost) ? a : b;
}

void Genetic::mutate(){
  int a,b,c,n;
  n=(int) mutationP*problem->getSize()*selection.size();
  for(int i=0;i<n;i++){
    a=rand() % problem->getSize();
    c=rand() % problem->getSize();
    b=rand() % selection.size();

    selection[b].move(a,c);
  }
}

Solution * Genetic::bestSolution(){
  int pos=0;
  int cost=INT_MAX;
  for(int i=0;i<numPopulation;i++){
    if(population[i].cost<cost){
      pos=i;
      cost=population[i].cost;
    }
  }
  return &population[pos];
}

Solution * Genetic::worstSolution(){
  int pos=0;
  int cost=0;
  for(int i=0;i<numPopulation;i++){
    if(population[i].cost>cost){
      pos=i;
      cost=population[i].cost;
    }
  }
  return &population[pos];
}


void Genetic::executeGenerationalPMX(){

  //generatePopulation();
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
        #pragma omp parallel for
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

          #pragma omp parallel for
          for(int i=0;i<numPopulation;i++){
            population[i].cost=problem->calculateCost(population[i].solution);
          }

          Solution * worst = worstSolution();
          worst->solution=best.solution;
          worst->cost=best.cost;

      //    cout << "\e[A" << "iteration: " << iteration << " of " << maxIterations << ". Best solution cost: " << bestSolution()->cost << " worst Solution:" << worstSolution()->cost << endl;
          iteration++;
  }


}

void Genetic::executeGenerationalOrder(){

  //generatePopulation();

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

        #pragma omp parallel for
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

          #pragma omp parallel for
          for(int i=0;i<numPopulation;i++){
            population[i].cost=problem->calculateCost(population[i].solution);
          }

          Solution * worst = worstSolution();
          worst->solution=best.solution;
          worst->cost=best.cost;

        //  cout << "\e[A" << "iteration: " << iteration << " of " << maxIterations << ". Best solution cost: " << bestSolution()->cost << " worst Solution:" << worstSolution()->cost << endl;
          iteration++;
  }





}


void Genetic::executeStationaryPMX(){

  //generatePopulation();

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


          mutate();


          Solution * worst;
          for(int i=0;i<selection.size();i++){
              worst = worstSolution();
              selection[i].cost=problem->calculateCost(selection[i].solution);
              if(worst->cost > selection[i].cost ){
                worst->solution=selection[i].solution;
                worst->cost=selection[i].cost;
              }
          }


          //cout << "\e[A" << "iteration: " << iteration << " of " << maxIterations << ". Best solution cost: " << bestSolution()->cost << " worst Solution:" << worstSolution()->cost << endl;
          iteration++;
  }




}
void Genetic::executeStationaryOrder(){

//  generatePopulation();

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
          mutate();

          Solution * worst;
          for(int i=0;i<selection.size();i++){
              worst = worstSolution();
              selection[i].cost=problem->calculateCost(selection[i].solution);
              if(worst->cost > selection[i].cost ){
                worst->solution=selection[i].solution;
                worst->cost=selection[i].cost;
              }
          }


          //cout << "\e[A" << "iteration: " << iteration << " of " << maxIterations << ". Best solution cost: " << bestSolution()->cost << " worst Solution:" << worstSolution()->cost << endl;
          iteration++;
  }



}
