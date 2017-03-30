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


Solution & Genetic::crossOX(const Solution &a,const Solution &b){
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

    


    return *t;
}
