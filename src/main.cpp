
#include <iostream>
#include <vector>
#include <cstdlib>      // std::rand, std::srand
#include "input.h"
#include "solution.h"
#include "greedy.h"
#include "localsearch.h"
#include "bmb.h"
#include "genetic.h"
#include "memetic.h"
#include "es.h"
#include <chrono>
#include <omp.h>


using namespace std;


int main(int argc,char *argv[]){

  if(argc<2 || argc>3){
    cout << "ERROR: Numero de parametros" << endl;
    return -1;
  }
  cout << "DATA: " <<  argv[1] << endl;

  cout << "NumThreads: " <<  omp_get_max_threads() << endl;
  omp_set_num_threads(omp_get_max_threads());



  int Seed=123581321;
  //int actual=0;

  //srand(Seed);
  srand_sse(Seed);


  Input i(argv[1]);
  Problem * qap=i.read();
  //Greedy greedy;
  //LocalSearch lb;
  //Genetic gen;
  bmb b;
  b.setProblem(*qap);
  Es es;
  es.setProblem(*qap);

  //lb.setProblem(*qap);
  //greedy.setProblem(*qap);
  //gen.setProblem(*qap);

  int s=qap->getSize();

  cout << "Size:" << s << endl;
/*  1
  cout << "Distance:" << endl;
  for(int i=0;i<s;++i){
    for (int j=0;j<s;j++) {
      cout << " " << qap->atd(i,j) ;
    }
    cout << endl;
  }
  cout << "Flow:" << endl;
  for(int i=0;i<s;++i){
    for (int j=0;j<s;j++){
      cout << " " << qap->atf(i,j);
    }
    cout << endl;
  }
  */

//Ejecucion greedy
  //greedy.calculatePotential();
  std::chrono::steady_clock::time_point begin_total = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  b.execute();
  std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
  std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;
  Solution * sol=&b.getBestSolution();

cout << "BMB solution:" << endl;
  for(int i=0;i<sol->solution.size();++i){
    cout << " "<< sol->solution[i];
  }
  cout << endl;
  cout << "Coste: " << sol->cost << endl;
  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  cout << endl;



  begin = std::chrono::steady_clock::now();
  es.execute();
  end= std::chrono::steady_clock::now();
  std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;
  sol=&es.getBestSolution();

cout << "ES solution:" << endl;
  for(int i=0;i<sol->solution.size();++i){
    cout << " "<< sol->solution[i];
  }
  cout << endl;
  cout << "Coste: " << sol->cost << endl;
  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  cout << endl;

/*
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  greedy.execute();
  std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
  std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;

  //___________________//





  //cout <<"Distance size:" <<d.size() << endl;
  Solution * sol=&greedy.getSolution();

cout << "Greedy solution:" << endl;
  for(int i=0;i<sol->solution.size();++i){
    cout << " "<< sol->solution[i];
  }
  cout << endl;
  cout << "Coste: " << sol->cost << endl;
  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  cout << endl;


lb.setMaxIterations(50000);
begin = std::chrono::steady_clock::now();
  lb.execute();
end= std::chrono::steady_clock::now();
std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;


sol=&lb.getActualSolution();
Solution ran=lb.getInitialSolution();
ran.cost = qap->calculateCost(ran.solution);
cout << "Random solution cost: " << ran.cost << endl;
cout << "LocalSearch initializated with random solution :" << endl;
  for(int i=0;i<sol->solution.size();++i){
    cout << " "<< sol->solution[i];
  }
  cout << endl;
  cout << "Cost: " << sol->cost << endl;
cout << "iterations: " << lb.getIterations() << endl;
cout << "correct Solution: " << sol->checkSolution() << endl;
cout << endl;




  lb.setInitialSolution(greedy.getSolution());

  begin = std::chrono::steady_clock::now();

  lb.execute();
  end= std::chrono::steady_clock::now();
  std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;

  sol=&lb.getActualSolution();

  cout << "LocalSearch initializated with greedy solution :" << endl;
    for(int i=0;i<sol->solution.size();++i){
      cout << " "<< sol->solution[i];
    }
    cout << endl;
    cout << "Cost: " << sol->cost << endl;
    cout << "iterations: " << lb.getIterations() << endl;
    cout << "correct Solution: " << sol->checkSolution() << endl;
    cout << endl;



gen.setNumPopulation(50);
gen.setMaxGenerations(INT_MAX);
gen.setMaxIterations(50000);

cout << endl;
gen.generatePopulation();

//cout << "ok"<<endl;

begin = std::chrono::steady_clock::now();

gen.executeGenerationalPMX();
end= std::chrono::steady_clock::now();
std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;

sol=gen.bestSolution();
Solution genPMX=*sol;

cout << "GenerationalPMX:" << endl;
  for(int i=0;i<sol->solution.size();++i){
    cout << " "<< sol->solution[i];
  }
  cout << endl;
  cout << "Cost: " << sol->cost << endl;
  cout << "Generations: " << gen.getGenerations() << endl;
  cout << "correct Solution: " << sol->checkSolution() << endl;

  //cout << "iterations: " << lb.getIterations() << endl;

  cout << endl;
  gen.generatePopulation();

  begin = std::chrono::steady_clock::now();


  gen.executeGenerationalOrder();

  end= std::chrono::steady_clock::now();
  std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;

  sol=gen.bestSolution();
  Solution genOrder=*sol;
  cout << "GenerationalPosition:" << endl;
    for(int i=0;i<sol->solution.size();++i){
      cout << " "<< sol->solution[i];
    }
    cout << endl;
    cout << "Cost: " << sol->cost << endl;
    cout << "Generations: " << gen.getGenerations() << endl;
    cout << "correct Solution: " << sol->checkSolution() << endl;

    //cout << "iterations: " << lb.getIterations() << endl;

    cout << endl;
    gen.generatePopulation();

    begin = std::chrono::steady_clock::now();


    gen.executeStationaryPMX();

    end = std::chrono::steady_clock::now();
    std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;


    sol=gen.bestSolution();
    cout << "StationaryPMX:" << endl;
      for(int i=0;i<sol->solution.size();++i){
        cout << " "<< sol->solution[i];
      }
      cout << endl;
      cout << "Cost: " << sol->cost << endl;
      cout << "correct Solution: " << sol->checkSolution() << endl;

      //cout << "iterations: " << lb.getIterations() << endl;

      cout << endl;
      gen.generatePopulation();

      begin = std::chrono::steady_clock::now();


      gen.executeStationaryOrder();

      end= std::chrono::steady_clock::now();
      std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;


      sol=gen.bestSolution();

      cout << "StationaryPos:" << endl;
        for(int i=0;i<sol->solution.size();++i){
          cout << " "<< sol->solution[i];
        }
        cout << endl;
        cout << "Cost: " << sol->cost << endl;
        cout << "correct Solution: " << sol->checkSolution() << endl;

        //cout << "iterations: " << lb.getIterations() << endl;

        cout << endl;

Memetic m1(10,0.1,false);
m1.setProblem(*qap);

begin = std::chrono::steady_clock::now();

if(genOrder.cost>genPMX.cost){
  m1.executeGenerationalOrder();

}
else{
  m1.executeGenerationalPMX();
}

end= std::chrono::steady_clock::now();
std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;


sol=m1.bestSolution();
cout << "MEMETIC 10 0.1 false:" << endl;
  for(int i=0;i<sol->solution.size();++i){
    cout << " "<< sol->solution[i];
  }
  cout << endl;
  cout << "Cost: " << sol->cost << endl;
  cout << "correct Solution: " << sol->checkSolution() << endl;
  //cout << "iterations: " << lb.getIterations() << endl;

  cout << endl;

/*
  begin = std::chrono::steady_clock::now();


  m1.executeGenerationalOrder();

  end= std::chrono::steady_clock::now();
  std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;



  sol=m1.bestSolution();
  cout << "MEMETIC GenerationalOrder:" << endl;
    for(int i=0;i<sol->solution.size();++i){
      cout << " "<< sol->solution[i];
    }
    cout << endl;
    cout << "Cost: " << sol->cost << endl;
    //cout << "iterations: " << lb.getIterations() << endl;

    cout << endl;

    begin = std::chrono::steady_clock::now();


    m1.executeStationaryPMX();

    end= std::chrono::steady_clock::now();
    std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;



    sol=m1.bestSolution();
    cout << "MEMETIC extacionaryPMX:" << endl;
      for(int i=0;i<sol->solution.size();++i){
        cout << " "<< sol->solution[i];
      }
      cout << endl;
      cout << "Cost: " << sol->cost << endl;
      //cout << "iterations: " << lb.getIterations() << endl;

      cout << endl;

      begin = std::chrono::steady_clock::now();


      m1.executeStationaryOrder();

      end= std::chrono::steady_clock::now();
      std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;



      sol=m1.bestSolution();
      cout << "MEMETIC extacionaryOrder:" << endl;
        for(int i=0;i<sol->solution.size();++i){
          cout << " "<< sol->solution[i];
        }
        cout << endl;
        cout << "Cost: " << sol->cost << endl;
        //cout << "iterations: " << lb.getIterations() << endl;

        cout << endl;
*/
//Segundo memetico
/*

Memetic m2(10,0.1,true);
m2.setProblem(*qap);

begin = std::chrono::steady_clock::now();

if(genOrder.cost>genPMX.cost)
m2.executeGenerationalOrder();
else
m2.executeGenerationalPMX();

end= std::chrono::steady_clock::now();
std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;



sol=m2.bestSolution();
cout << "MEMETIC 10 0,1 true:" << endl;
  for(int i=0;i<sol->solution.size();++i){
    cout << " "<< sol->solution[i];
  }
  cout << endl;
  cout << "Cost: " << sol->cost << endl;
  cout << "correct Solution: " << sol->checkSolution() << endl;
  //cout << "iterations: " << lb.getIterations() << endl;

  cout << endl;*//*

  begin = std::chrono::steady_clock::now();


  m2.executeGenerationalOrder();

  end= std::chrono::steady_clock::now();
  std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;



  sol=m2.bestSolution();
  cout << "MEMETIC GenerationalOrder:" << endl;
    for(int i=0;i<sol->solution.size();++i){
      cout << " "<< sol->solution[i];
    }
    cout << endl;
    cout << "Cost: " << sol->cost << endl;
    //cout << "iterations: " << lb.getIterations() << endl;

    cout << endl;

    begin = std::chrono::steady_clock::now();


    m2.executeStationaryPMX();

    end= std::chrono::steady_clock::now();
    std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;



    sol=m2.bestSolution();
    cout << "MEMETIC extacionaryPMX:" << endl;
      for(int i=0;i<sol->solution.size();++i){
        cout << " "<< sol->solution[i];
      }
      cout << endl;
      cout << "Cost: " << sol->cost << endl;
      //cout << "iterations: " << lb.getIterations() << endl;

      cout << endl;

      begin = std::chrono::steady_clock::now();


      m2.executeStationaryOrder();

      end= std::chrono::steady_clock::now();
      std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;


      sol=m2.bestSolution();
      cout << "MEMETIC extacionaryOrder:" << endl;
        for(int i=0;i<sol->solution.size();++i){
          cout << " "<< sol->solution[i];
        }
        cout << endl;
        cout << "Cost: " << sol->cost << endl;
        //cout << "iterations: " << lb.getIterations() << endl;

        cout << endl;
*/
/*
    //Tercero
    Memetic m3(10,1,false);
    m3.setProblem(*qap);


    begin = std::chrono::steady_clock::now();

    if(genOrder.cost>genPMX.cost)
    m3.executeGenerationalOrder();
    else
    m3.executeGenerationalPMX();


    end= std::chrono::steady_clock::now();
    std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;


    sol=m3.bestSolution();
    cout << "MEMETIC 10 1 false:" << endl;
      for(int i=0;i<sol->solution.size();++i){
        cout << " "<< sol->solution[i];
      }
      cout << endl;
      cout << "Cost: " << sol->cost << endl;
      cout << "correct Solution: " << sol->checkSolution() << endl;

      //cout << "iterations: " << lb.getIterations() << endl;

      cout << endl;*/
      /*
      begin = std::chrono::steady_clock::now();


      m3.executeGenerationalOrder();

      end= std::chrono::steady_clock::now();
      std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;



      sol=m3.bestSolution();
      cout << "MEMETIC GenerationalOrder:" << endl;
        for(int i=0;i<sol->solution.size();++i){
          cout << " "<< sol->solution[i];
        }
        cout << endl;
        cout << "Cost: " << sol->cost << endl;
        //cout << "iterations: " << lb.getIterations() << endl;

        cout << endl;

        begin = std::chrono::steady_clock::now();


        m3.executeStationaryPMX();

        end= std::chrono::steady_clock::now();
        std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;



        sol=m3.bestSolution();
        cout << "MEMETIC extacionaryPMX:" << endl;
          for(int i=0;i<sol->solution.size();++i){
            cout << " "<< sol->solution[i];
          }
          cout << endl;
          cout << "Cost: " << sol->cost << endl;
          //cout << "iterations: " << lb.getIterations() << endl;

          cout << endl;

          begin = std::chrono::steady_clock::now();


          m3.executeStationaryOrder();

          end= std::chrono::steady_clock::now();
          std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;


          sol=m3.bestSolution();
          cout << "MEMETIC extacionaryOrder:" << endl;
            for(int i=0;i<sol->solution.size();++i){
              cout << " "<< sol->solution[i];
            }
            cout << endl;
            cout << "Cost: " << sol->cost << endl;
            //cout << "iterations: " << lb.getIterations() << endl;

            cout << endl;


*/
/*
cout << "Testing calculateCost() function with nug12.dat optimal solution: 578 " << endl;
//12,7,9,3,4,8,11,1,5,6,10,2
Solution optimal;
optimal.solution.resize(qap->getSize());
optimal.solution[0]=11;
optimal.solution[1]=6;
optimal.solution[2]=8;
optimal.solution[3]=2;
optimal.solution[4]=3;
optimal.solution[5]=7;
optimal.solution[6]=10;
optimal.solution[7]=0;
optimal.solution[8]=4;
optimal.solution[9]=5;
optimal.solution[10]=9;
optimal.solution[11]=1;


optimal.cost = qap->calculateCost(optimal.solution);

cout << "Optimal cost:" << optimal.cost <<endl;

cout << "Move cost: 0 6 " << qap->moveCost(optimal.solution,0,6) << endl;

optimal.move(0,6);
optimal.cost=qap->calculateCost(optimal.solution);

cout << "Optimal cost moved:" << optimal.cost <<endl;
*/
std::chrono::steady_clock::time_point end_total = std::chrono::steady_clock::now();
std::cout << "Time Total: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end_total - begin_total).count() /1000.0 <<std::endl;


}
