#include "genetic.h"




void Genetic::generatePopulation(){
  if(!problem)
    return;
    int size=problem->getSize();
    population.resize(numPopulation);

    //#pragma omp parallel for ordered
    for(int i=0;i<numPopulation;++i){
      population[i].solution.resize(size);
      for(int j=0;j<size;++j){
        population[i].solution[j]=j;
      }
      //#pragma omp ordered
      //#pragma omp critical
      //{
      random_shuffle(population[i].solution.begin(), population[i].solution.end(),getRandomMax);
      population[i].cost=problem->calculateCost(population[i].solution);
      //}
    }

}

Solution & POS::cross(const Solution &a,const Solution &b){
  int s=a.solution.size();
  Solution * t=new Solution; //Son
  t->solution.resize(s);
  //#pragma omp parallel for
  for(int i=0;i<s;++i) //fill with -1
    t->solution[i]=-1;

  vector<int> v; //vector to save the numbers that do not coincide

  //#pragma omp parallel for ordered
    for(int i=0;i<s;++i){
      if(a.solution[i]==b.solution[i])
        t->solution[i]=b.solution[i];
      else{
        //#pragma omp ordered
        //#pragma omp critical
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


Solution & PMX::cross(const Solution &a,const Solution &b){
  int s=a.solution.size();

  Solution * t=new Solution; //Son
  t->solution.resize(s);
  int * v=new int[s]; //vector to save the relations between parents
  bool * m=new bool[s];
  //#pragma omp parallel for
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
    //#pragma omp parallel for
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
  while (a==b) {
    b = getRandomMax(numPopulation);
  }


  return (population[a].cost<population[b].cost) ? a : b;
}

void Genetic::mutate(){
  int a,b,c,n;
  n=(int) mutationP*problem->getSize()*selection.size();
  for(int i=0;i<n;++i){
    a = getRandomMax(problem->getSize()) ;
    c = getRandomMax(problem->getSize()) ;
    b = getRandomMax(selection.size()) ;
    //selection[b].cost+=problem->moveCost(selection[b].solution,a,c);
    selection[b].move(a,c);
    update[b]=true;
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


void Generational::execute(){

        generatePopulation();

        selection.resize(numPopulation);
        //std::cout << numPopulation << '\n';

        //std::cout << "ok1" << '\n';

        update = new bool[numPopulation];

        int numCross=crossP*(numPopulation/2);
        //cout<< "numcross:" << numCross<<endl;
        int a,b;
        iteration=0;

        int contCross;
        while(iteration<maxIterations){
              contCross=0;

                for(int i=0;i<numPopulation;++i){
                    a=binaryTournament();
                  if(contCross<numCross){
                      b=binaryTournament();
                        //std::cout << "ok2" << '\n';
                        selection[i]=cross(population[a],population[b]);
                        //std::cout << "ok2.2" << '\n';

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


              //  cout << "\e[A" << "iteration: " << iteration << " of " << maxIterations << ". Best solution cost: " << bestSolution()->cost << " worst Solution:" << worstSolution()->cost << endl;
              //  iteration++;
        }
        delete[] update;
        *result = *bestSolution();
}

void Stationary::execute(){


  generatePopulation();


    iteration=0;
    update = new bool[numPopulation];

    int a,b,c;


    while(iteration<maxIterations){
              //Selection
                a=binaryTournament();
                b=binaryTournament();
                         //Cross
                selection[0]=cross(population[a],population[b]);
                selection[1]=cross(population[b],population[a]);


            /*Mutation*/
            mutate();

            Solution * worst;
            for(int i=0;i<selection.size();++i){
                worst = worstSolution();
                selection[i].cost=problem->calculateCost(selection[i].solution);
                iteration++;
                if(worst->cost > selection[i].cost ){
                  worst->solution=selection[i].solution;
                  worst->cost=selection[i].cost;
                }
            }

            //cout << "\e[A" << "iteration: " << iteration << " of " << maxIterations << ". Best solution cost: " << bestSolution()->cost << " worst Solution:" << worstSolution()->cost << endl;
    }
    *result = *bestSolution();

}
