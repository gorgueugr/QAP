#include "grasp.h"

void GreedyRandomized::execute(){

  //cout <<"ok"<<endl;
  step1();
  //cout <<"ok1"<<endl;

  step2();
  //cout <<"ok2"<<endl;

  buildSolution();
  //cout <<"ok3"<<endl;


}



void GreedyRandomized::step1(){
  calculatePotential();

  LRCD.clear();
  LRCF.clear();

  //result = new Solution;
  //result->solution.resize(problem->getSize());

  f = new bool[problem->getSize()];
  d = new bool[problem->getSize()];
  for(int i=0;i<problem->getSize();i++){
    d[i]=0;
    f[i]=0;
  }

  float minF=INT_MAX,minD=INT_MAX;
  float maxF=0,maxD=0;

  for(int i=0;i<problem->getSize();i++){
    maxF = flowPotential[i]>maxF ? flowPotential[i] : maxF;
    maxD = distancePotential[i]>maxD ? distancePotential[i] : maxD;
    minF = flowPotential[i]<minF ? flowPotential[i] : minF;
    minD = distancePotential[i]<minD ? distancePotential[i] : minD;
  }

  float uF = maxF - (alfa * (maxF-minF));
  float uD = minD + (alfa * (maxD-minD));


  //#pragma omp parallel for
  for(int i=0;i<problem->getSize();i++){
    if(flowPotential[i] >= uF)
      LRCF.push_back(i);
    if(distancePotential[i] <= uD)
      LRCD.push_back(i);
  }

 //Pick two candidates from lists
  int firstF = getRandomMax(LRCF.size());
  int secondF = getRandomMax(LRCF.size());


  while (firstF==secondF) {
    secondF = getRandomMax(LRCF.size());
  }

  //cout << LRCD.size() << endl;

  int firstD = getRandomMax(LRCD.size());
  int secondD = getRandomMax(LRCD.size());


  while (firstD==secondD) {
    secondD = getRandomMax(LRCD.size());
  }
//

  f[firstF]  = 1;
  f[secondF] = 1;
  d[firstD]  = 1;
  d[secondD] = 1;

  //result->solution[firstF] = firstD;
  //result->solution[secondF] = secondD;
  SOL.push_back(pair(firstF,firstD));
  SOL.push_back(pair(secondF,secondD));


}

void GreedyRandomized::step2(){
    for(int i=0;i<problem->getSize()-2;++i){
    calculateCandidates();
    //cout << "candidatos:" << LC.size() << endl;
    cost.clear();
    cost.resize(LC.size());
    float min = INT_MAX, max = 0;
    for(int j=0;j<LC.size();++j){

      for(int k=0;k<SOL.size();++k)
        cost[j] += problem->atf(LC[j].u,SOL[k].u) * problem->atd(LC[j].l,SOL[k].l);

        //Find the min and max cost

        min = cost[j] < min ? cost[j] : min;
        max = cost[j] > max ? cost[j] : max;
    }
    //Calculate the bound and Calculate LRC
    float u = min + (alfa * (max-min));
      LRC.clear();
    for(int j=0;j<LC.size();++j){
      if(cost[j] <= u)
        LRC.push_back(LC[j]);
    }
    //cout << "candidatos Restringidos:" << LRC.size() << endl;

    //pick a random one
    int r = getRandomMax(LRC.size());
    SOL.push_back(LRC[r]);
    f[LRC[r].u]=1;
    d[LRC[r].l]=1;

  }

}

void GreedyRandomized::calculateCandidates(){
  LC.clear();
  for(int i=0;i<problem->getSize();++i){
    if(!f[i])
    for(int j=0;j<problem->getSize();++j){
      if(!d[j])
      LC.push_back(pair(i,j));
    }
  }
}

void GreedyRandomized::buildSolution(){
  result = new Solution;
  result->solution.resize(problem->getSize());

  for(int i=0;i<problem->getSize();++i){
    result->solution[SOL[i].u]=SOL[i].l;
  }
  result->cost = problem->calculateCost(result->solution);

}


void grasp::execute(){
  best = new Solution;
  best->cost = INT_MAX;

  LocalSearch ls;
  ls.setProblem(*problem);
  ls.setMaxIterations(50000);

  GreedyRandomized gr;
  gr.setProblem(*problem);

  it=0;
  while(it<maxIt){
    gr.execute();

    Solution s=gr.getSolution();

    ls.setInitialSolution(s);
    ls.execute();

    s = ls.getActualSolution();
    *best = *best < s ? *best : s;
    ++it;
  }

}
