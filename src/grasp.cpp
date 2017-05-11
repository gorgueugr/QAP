void GreedyRandomized::execute(){






}



void GreedyRandomized::step1(){
  calculatePotential();

  LRCD.clear();
  LRCF.clear();

  result = new Solution;
  result->solution.resize(problem->getSize());

  f = new bool[problem->getSize()];
  d = new bool[problem->getSize()];
  for(int i=0;i<problem->getSize();i++){
    d[i]=0;
    f[i]=0;
  }

  float minF,minD=INT_MAX;
  float maxF,maxD=0;

  for(int i=0;i<problem->getSize();i++){
    maxF = flowPotential[i]>maxF ? flowPotential[i] : maxF;
    maxD = distancePotential[i]>maxD ? distancePotential[i] : maxD;
    minF = flowPotential[i]<minF ? flowPotential[i] : minF;
    minD = distancePotential[i]<minD ? distancePotential[i] : minD;
  }

  float uF = maxF - (alfa * (maxF-minF);
  float uD = minD + (alfa * (maxD-minD);

  for(int i=0;i<problem->getSize();i++){
    flowPotential[i] < uF ? : LRCF.push_back(i);
    distancePotential[i] > uD ? : LRCD.push_back(i);
  }

 //Pick two candidates from lists
  int firstF = getRandomMax(LRCF.size());
  int secondF = getRandomMax(LRCF.size());

  while (firstF==secondF) {
    secondF = getRandomMax(LRCF.size());
  }

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
  result->solution[firstF] = firstD;
  result->solution[secondF] = secondD;

}

void greedyRandomized::step2(){
LRCD.clear();
LRCF.clear();

  for(int i=0;i<problem->getSize()-2;i++){
    float ** cost = new float*[problem->getSize()];

    for(int j=0;j<problem.>getSize();j++){
      cost[j] = new float[problem->getSize()];
    }


  }



}
