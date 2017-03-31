#include "genetic.h"


void Genetic::generatePopulation(){
  if(!problem)
    return;
    int size=problem->getSize();
    population.resize(numPopulation);
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
  for(int i=0;i<s;i++){ //fill with i
    v[i]=i;
  }
  t->solution=b.solution;

    int min,max; //points to cross
    min = rand() % s; //first point
    max = (rand() % (s-min)) + min; //second point
    //cout << "min/max: " << min << "/" << max << endl;
    //int z;
    //cin >> z;
    //Step 1: copy values of parent1 in the range[min,max] in the son
    for(int i=min;i<max;i++){
      t->solution[i]=a.solution[i]; //Copy in the son
      v[a.solution[i]]=b.solution[i]; //Define relation between parent 1 and 2
    }

    for(int i=0;i<min;i++){
      t->solution[i]=v[t->solution[i]];
    }
    for(int i=max;i<s;i++){
      t->solution[i]=v[t->solution[i]];
    }

    return *t;
}

int  Genetic::BinaryTournament(){
  int a = rand() % numPopulation; //first random player
  int b = rand() % numPopulation; //Second random player

  return (population[a].cost>population[b].cost) ? a : b;
}

void Genetic::Mutate(){

}

Solution & Genetic::bestSolution(){
  int pos=0;
  int cost=INT_MAX;
  for(int i=0;i<numPopulation;i++){
    if(population[i].cost<cost){
      pos=i;
      cost=population[i].cost;
    }
  }
  return population[pos];
}

void Genetic::executeGenerational(){

  generatePopulation();

  std::vector<Solution> selection;
  selection.resize(numPopulation);
  int a,b,c,n;
  int iteration=0;
  int numCross=(int) crossP*(numPopulation/2);
  cout<< "numcross:" << numCross<<endl;
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
    cout << "\e[A" << "iteration: " << iteration << " of " << maxIterations << endl;
    iteration++;
  }

}
