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
    #pragma omp parallel for ordered
    for(int i=0;i<numPopulation;++i){
      population[i].solution.resize(size);
      for(int j=0;j<size;++j){
        population[i].solution[j]=j;
      }
      #pragma omp ordered
      #pragma omp critical
      {
      random_shuffle(population[i].solution.begin(), population[i].solution.end(),getRandomMax);
      population[i].cost=problem->calculateCost(population[i].solution);
      }
    }

}

Solution & Genetic::crossPosition(const Solution &a,const Solution &b){
  int s=a.solution.size();
  Solution * t=new Solution(); //Son
  t->solution.resize(s);
  #pragma omp parallel for
  for(int i=0;i<s;++i) //fill with -1
    t->solution[i]=-1;

  vector<int> v; //vector to save the numbers that do not coincide

  #pragma omp parallel for ordered
    for(int i=0;i<s;++i){
      if(a.solution[i]==b.solution[i])
        t->solution[i]=b.solution[i];
      else{
        #pragma omp ordered
        v.push_back(a.solution[i]); //if father1[i] and father2[i] are equal then copy it in son
      }
    }

    if(v.size()>0){                                                  //else push it to the v vector
    random_shuffle(v.begin(),v.end(),getRandomMax); //shuffle the vector with the numbers that do not coincide
    int c=0;
    //#pragma omp parallel for
    for(int i=0;i<s;++i) //if in son [i]==-1 then get a number from v
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
  for(int i=0;i<s;++i){ //fill with i
    v[i]=i;
    m[i]=0;
  }
  t->solution=b.solution;

    //int min,max; //points to cross
    //C=A%B; == C=A-B*(A/B);
    int min = getRandomMax(s-1);
    //min = (rand() % (int)(s - 1)); //first point OLD
    int max = getRandomRange(min,s);
    //max= min+1 + (max - (s - 1 - min))*(max/d2);
    //max = min+1 + (rand() % (int)(s-1 - min) ); //second point //OLD


    //Step 1: copy values of parent1 in the range[min,max] in the son
    #pragma omp parallel for
    for(int i=min;i<max;++i){
      t->solution[i]=a.solution[i]; //Copy in the son
      m[a.solution[i]]=1; //Mark the number
      v[a.solution[i]]=b.solution[i]; //Define relation between parent 1 and 2
    }

    for(int i=0;i<min;++i)
      while(m[t->solution[i]]==1)
        t->solution[i]=v[t->solution[i]];

    for(int i=max;i<s;i++)
      while(m[t->solution[i]]==1)
        t->solution[i]=v[t->solution[i]];


    delete[] v;
    delete[] m;
    return *t;
}

int  Genetic::binaryTournament(){
  int a = getRandomMax(numPopulation);
  int b = getRandomMax(numPopulation);
  //cout <<" a: " << a <<" b: " << b << endl;
  //C=A%B; == C=A-B*(A/B);
//  a = (a-numPopulation)*(a/d1);
//  b = (b-numPopulation)*(b/d1);
  //cout <<" a: " << a <<" b: " << b << endl;

  //int a = rand() % numPopulation; //first random player
  //int b = rand() % numPopulation; //Second random player

  return (population[a].cost>population[b].cost) ? a : b;
}

void Genetic::mutate(){
  int a,b,c,n;
  n=(int) mutationP*problem->getSize()*selection.size();
  for(int i=0;i<n;++i){
    //a= getRandom() % problem->getSize();
    //c=getRandom() % problem->getSize();
    //b=getRandom() % selection.size();
    a = getRandomMax(problem->getSize()) ;
    c = getRandomMax(problem->getSize()) ;
    b = getRandomMax(selection.size()) ;

    selection[b].move(a,c);
  }
}

Solution * Genetic::bestSolution(){
  int pos=0;
  int cost=INT_MAX;
  for(int i=0;i<numPopulation;++i){
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
  for(int i=0;i<numPopulation;++i){
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
        iteration=0;
        int numCross=crossP*(numPopulation/2);
        //cout<< "numcross:" << numCross<<endl;
        int a,b;
        generations=0;
        iteration=0;

        bool * update = new bool[numPopulation];
        for(int i=0;i<numPopulation;++i){
          update[i]=false;
        }

        int contCross;
        while(iteration<maxIterations && generations<maxGenerations){
              contCross=0;

              //#pragma omp parallel for
                for(int i=0;i<numPopulation;++i){
                  //#pragma omp critical
                      a=binaryTournament();
                  if(contCross<numCross){
                      b=binaryTournament();
                      contCross++;
                    selection[i]=crossPMX(population[a],population[b]);
                    update[i]=true;
                  }else{
                    selection[i]=population[a];
                    update[i]=false;
                  }
                }

                /*Mutation*/
                mutate();

                best=*bestSolution();

                population=selection;

                //#pragma omp parallel for
                for(int i=0;i<numPopulation;++i){
                  if(update[i]){
                    population[i].cost=problem->calculateCost(population[i].solution);
                    ++iteration;
                  }
                }

                Solution * worst = worstSolution();
                worst->solution=best.solution;
                worst->cost=best.cost;
                ++generations;

              //  cout << "\e[A" << "iteration: " << iteration << " of " << maxIterations << ". Best solution cost: " << bestSolution()->cost << " worst Solution:" << worstSolution()->cost << endl;
              //  iteration++;
        }
        delete[] update;

}

void Genetic::executeGenerationalOrder(){

      //generatePopulation();

      crossP=0.7;
      mutationP=0.001;


      selection.resize(numPopulation);
      iteration=0;
      int numCross=crossP*(numPopulation/2);
      //cout<< "numcross:" << numCross<<endl;
      int a,b;
      generations=0;
      iteration=0;

      bool * update = new bool[numPopulation];
      for(int i=0;i<numPopulation;++i){
        update[i]=false;
      }

      int contCross;
      while(iteration<maxIterations && generations<maxGenerations){
            contCross=0;

            //#pragma omp parallel for
              for(int i=0;i<numPopulation;++i){
                  a=binaryTournament();
                if(contCross<numCross){

                    b=binaryTournament();
                    contCross++;

                  selection[i]=crossPosition(population[a],population[b]);
                  update[i]=true;

                }else{
                  selection[i]=population[a];
                  update[i]=false;
                }
              }

              /*Mutation*/
              mutate();

              best=*bestSolution();

              population=selection;

              //#pragma omp parallel for
              for(int i=0;i<numPopulation;++i){
                if(update[i]){
                  population[i].cost=problem->calculateCost(population[i].solution);
                  ++iteration;
                }
              }

              Solution * worst = worstSolution();
              worst->solution=best.solution;
              worst->cost=best.cost;
              ++generations;

            //  cout << "\e[A" << "iteration: " << iteration << " of " << maxIterations << ". Best solution cost: " << bestSolution()->cost << " worst Solution:" << worstSolution()->cost << endl;
            //  iteration++;
      }
      delete[] update;

}


void Genetic::executeStationaryPMX(){

        //generatePopulation();

        crossP=0.7;
        mutationP=0.001;


        selection.resize(numPopulation);
        iteration=0;
        int numCross=crossP*(numPopulation/2);
        //cout<< "numcross:" << numCross<<endl;
        int a,b;
        generations=0;
        iteration=0;

        bool * update = new bool[numPopulation];
        for(int i=0;i<numPopulation;++i){
          update[i]=false;
        }

        int contCross;
        while(iteration<maxIterations && generations<maxGenerations){
              contCross=0;

              #pragma omp parallel for
                for(int i=0;i<numPopulation;++i){
                  #pragma omp critical
                    a=binaryTournament();
                  if(contCross<numCross){
                    #pragma omp critical
                    b=binaryTournament();
                    selection[i]=crossPMX(population[a],population[b]);
                    update[i]=true;
                    contCross++;

                  }else{
                    selection[i]=population[a];
                    update[i]=false;
                  }
                }

                /*Mutation*/
                mutate();

                best=*bestSolution();

                population=selection;

                //#pragma omp parallel for
                for(int i=0;i<numPopulation;++i){
                  if(update[i]){
                    population[i].cost=problem->calculateCost(population[i].solution);
                    ++iteration;
                  }
                }

                Solution * worst = worstSolution();
                worst->solution=best.solution;
                worst->cost=best.cost;
                ++generations;

              //  cout << "\e[A" << "iteration: " << iteration << " of " << maxIterations << ". Best solution cost: " << bestSolution()->cost << " worst Solution:" << worstSolution()->cost << endl;
              //  iteration++;
        }
        delete[] update;
}
void Genetic::executeStationaryOrder(){

//  generatePopulation();

  crossP=1;
  mutationP=0.001;
  iteration=0;


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
          for(int i=0;i<selection.size();++i){
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
