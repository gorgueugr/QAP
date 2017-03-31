#include "genetic.h"


void Genetic::generatePopulation(){
  if(!problem)
    return;
    int size=problem->getSize();
    population.resize(numPopulation);
    for(int i=0;i<numPopulation;i++){
      population[i].solution.resize(size);
      for(int i=0;i<size;i++){
        population[i].solution[i]=i;
        random_shuffle ( population[i].solution.begin(), population[i].solution.end());
      }
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
        v.push_back(a.solution[i]); //if father1[i] and father2[i] are equal then copy it in son,

    }
                                                                          //else push it to the v vector
    random_shuffle(v.begin(),v.end()); //shuffle the vector with the numbers that do not coincide
    int c=0;
    for(int i=0;i<s;i++) //if in son [i]==-1 then get a number from v
      t->solution[i]>-1 ? : t->solution[i]=v[c],c++;

    v.clear();

    return *t;
}


Solution & Genetic::crossPMX(const Solution &a,const Solution &b){
  int s=a.solution.size();

  Solution * t=new Solution(); //Son
  t->solution.resize(s);
  vector<int> v; //vector to save the relations between parents
  v.resize(s);
  for(int i=0;i<s;i++){ //fill with -1
    t->solution[i]=-1;
    v[i]=i;
  }

    int min,max; //points to cross
    min = rand() % s; //first point
    max = rand() % (s-min) + min; //second point

    //Step 1: copy values of parent1 in the range[min,max] in the son
    for(int i=min;i<max;i++){
      t->solution[i]=a.solution[i]; //Copy in the son
      v[a.solution[i]]=b.solution[i]; //Define relation between parent 1 and 2
    }

    for(int i=0;i<min;i++){
      t->solution[i]=v[i];
    }
    for(int i=max;i<s;i++){
      t->solution[i]=v[i];
    }


    return *t;
}

int  Genetic::BinaryTournament(){
  int a = rand() % s; //first random player
  int b = rand() % s; //Second random player

  return (population[a]>population[b]) ? a : b;
}

void Genetic::Mutate(){

}

void Genetic::executeGenerational(){

  generatePopulation();

  std::vector<Solution> selection;
  selection.resize(numPopulation);
  int a,b,n;
  int iteration=0;
  int numCross=(int) crossP*(numPopulation/2);
  int contCross;
  while(iteration<maxIterations){
  contCross=0;
    for(int i=0;i<numPopulation;i++){
      a=BinaryTournament();
      if(contCross<numCross){
        b=BinaryTournament();
        selection[i]=crossPMX(population[a],population[b]);
        contCross++;
      }else{
        selection[i]=population[a];
      }
    }
    /*Mutation*/
    n=(int) mutationP*problem->getSize()*numPopulation;
    for(int i=0;i<n;i++){
      a=rand() % problem->getSize();
      c=rand() % problem->getSize();
      b=rand() % numPopulation;

      selection[b].move(a,c);
    }
    population=selection;
    for(int i=0;i<numPopulation;i++){
      population[i].cost=problem->calculateCost(population[i].solution);
    }
  }

}
