
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
#include "ils.h"
#include "grasp.h"
#include "base.h"
#include <chrono>
#include <omp.h>

#include "html.h"
#include <string>


using namespace std;


int main(int argc,char *argv[]){

  if(argc<2 || argc>3){
    cout << "ERROR: Numero de parametros" << endl;
    return -1;
  }
  //cout << "DATA: " <<  argv[1] << endl;
  string f = argv[1];
  int numCasos;
  std::vector<string> ficheros;
  std::vector<int> mejorCoste;


  if(f=="all"){
  numCasos = 19;
  ficheros.resize(numCasos);
  mejorCoste.resize(numCasos);

  ficheros[0] =     "./bin/data/chr20b.dat";
  ficheros[2] =     "./bin/data/chr22a.dat";
  ficheros[1] =     "./bin/data/els19.dat";
  ficheros[3] =     "./bin/data/esc32b.dat";
  ficheros[4] =     "./bin/data/kra30b.dat";
  ficheros[5] =     "./bin/data/lipa90b.dat";
  ficheros[6] =     "./bin/data/nug25.dat";
  ficheros[7] =     "./bin/data/sko56.dat";
  ficheros[8] =     "./bin/data/sko64.dat";
  ficheros[9] =     "./bin/data/sko72.dat";
  ficheros[10] =    "./bin/data/sko100a.dat";
  ficheros[11] =    "./bin/data/sko100b.dat";
  ficheros[12] =    "./bin/data/sko100c.dat";
  ficheros[13] =    "./bin/data/sko100d.dat";
  ficheros[14] =    "./bin/data/sko100e.dat";
  ficheros[15] =    "./bin/data/tai30b.dat";
  ficheros[16] =    "./bin/data/tai50b.dat";
  ficheros[17] =    "./bin/data/tai60a.dat";
  ficheros[18] =    "./bin/data/tai256.dat";
  ficheros[19] =    "./bin/data/tho150.dat";

  mejorCoste[0] =  2298;
  mejorCoste[1] =  6156;
  mejorCoste[2] =  17212548;
  mejorCoste[3] =  168;
  mejorCoste[4] =  91420;
  mejorCoste[5] =  12490441;
  mejorCoste[6] =  3744;
  mejorCoste[7] =  34458;
  mejorCoste[8] =  48498;
  mejorCoste[9] =  66256;
  mejorCoste[10] =  152002;
  mejorCoste[11] =  153890;
  mejorCoste[12] =  147862;
  mejorCoste[13] =  149576;
  mejorCoste[14] =  149150;
  mejorCoste[15] =  637117113;
  mejorCoste[16] =  458821517;
  mejorCoste[17] =  7205962;
  mejorCoste[18] =  43849646;
  mejorCoste[19] =  7620628;


}else{
  numCasos = 1;
  ficheros.resize(numCasos);
  mejorCoste.resize(numCasos);

  ficheros[0] = argv[1];
  mejorCoste[0] =  1 ;
}
  //cout << "NumThreads: " <<  omp_get_max_threads() << endl;
  omp_set_num_threads(omp_get_max_threads());





  int Seed=123581321;
  //int actual=0;

  //srand(Seed);
  srand_sse(Seed);

  Greedy greedy;
  LocalSearch lb;
  bmb b;
  Es es;
  Ils ils;
  Ils_es ilsEs;
  grasp gr;


    html h_greedy("greedy");
    html h_lb("LocalSearch");
    html h_bmb("BMB");
    html h_es("Enfriamiento Simulado");
    html h_ils("ILS");
    html h_ilses("ILS-ES");
    html h_grasp("GRASP");


    Input in;

for(int i=0;i<numCasos;i++){

  cout << ficheros[i] << endl;

  in.setFile(ficheros[i]);

  Problem * qap=in.read();

  greedy.setProblem(*qap);
  lb.setProblem(*qap);
  gr.setProblem(*qap);
  ilsEs.setProblem(*qap);
  ils.setProblem(*qap);
  es.setProblem(*qap);
  b.setProblem(*qap);






  //Genetic gen;
  int s=qap->getSize();

  std::chrono::steady_clock::time_point begin_total = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  b.execute();
  std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
  //std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;
  Solution * sol=&b.getSolution();

  //cout << "BMB solution:" << endl;
  //for(int i=0;i<sol->solution.size();++i){
  //  cout << " "<< sol->solution[i];
  //}
  //cout << endl;
  //cout << "Coste: " << sol->cost << endl;
  h_bmb.add(ficheros[i],sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
  //cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  //cout << endl;

  std::cout << "ok" << '\n';



  es.clearInitialSolution();
  begin = std::chrono::steady_clock::now();
  es.execute();
  end= std::chrono::steady_clock::now();
  //std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;
  sol=&es.getSolution();

  //cout << "ES solution:" << endl;
  //for(int i=0;i<sol->solution.size();++i){
  //  cout << " "<< sol->solution[i];
  //}
  //cout << endl;
  //cout << "Coste: " << sol->cost << endl;
  h_es.add(ficheros[i],sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
  //cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  //cout << endl;
  std::cout << "ok2" << '\n';



    begin = std::chrono::steady_clock::now();
    ils.execute();
    end= std::chrono::steady_clock::now();
  //  std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;
    sol=&ils.getSolution();


  //  cout << "ILS solution:" << endl;
  //  for(int i=0;i<sol->solution.size();++i){
  //    cout << " "<< sol->solution[i];
  //  }
  //  cout << endl;
  //  cout << "Coste: " << sol->cost << endl;
    h_ils.add(ficheros[i],sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
  //  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  //  cout << endl;

  std::cout << "ok3" << '\n';

    begin = std::chrono::steady_clock::now();
    ilsEs.execute();
    end= std::chrono::steady_clock::now();
  //  std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;
    sol=&ilsEs.getSolution();

  //  cout << "ILS_ES solution:" << endl;
  //  for(int i=0;i<sol->solution.size();++i){
  //    cout << " "<< sol->solution[i];
  //  }
  //  cout << endl;
  //  cout << "Coste: " << sol->cost << endl;
    h_ilses.add(ficheros[i],sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
  //  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  //  cout << endl;

  std::cout << "ok4" << '\n';


    begin = std::chrono::steady_clock::now();
    gr.execute();
    end= std::chrono::steady_clock::now();
    //std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;
    sol=&gr.getSolution();

  //  cout << "GRASP solution:" << endl;
  //  for(int i=0;i<sol->solution.size();++i){
  //    cout << " "<< sol->solution[i];
  //  }
  //  cout << endl;
  //  cout << "Coste: " << sol->cost << endl;
    h_grasp.add(ficheros[i],sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
  //  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  //  cout << endl;
  std::cout << "ok5" << '\n';


  begin = std::chrono::steady_clock::now();
  greedy.execute();
  end= std::chrono::steady_clock::now();
  //std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;
  sol=&greedy.getSolution();

//  cout << "GRASP solution:" << endl;
//  for(int i=0;i<sol->solution.size();++i){
//    cout << " "<< sol->solution[i];
//  }
//  cout << endl;
//  cout << "Coste: " << sol->cost << endl;
  h_greedy.add(ficheros[i],sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
//  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
//  cout << endl;

std::cout << "ok6" << '\n';

begin = std::chrono::steady_clock::now();
lb.execute();
end= std::chrono::steady_clock::now();
//std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;
sol=&lb.getSolution();

//  cout << "GRASP solution:" << endl;
//  for(int i=0;i<sol->solution.size();++i){
//    cout << " "<< sol->solution[i];
//  }
//  cout << endl;
//  cout << "Coste: " << sol->cost << endl;
h_lb.add(ficheros[i],sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
//  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
//  cout << endl;

std::cout << "ok7" << '\n';







}
  std::cout << h_lb << '\n';
  std::cout << h_greedy << '\n';
  std::cout << h_bmb << '\n';
  std::cout << h_es << '\n';
  std::cout << h_ils << '\n';
  std::cout << h_ilses << '\n';
  std::cout << h_grasp << '\n';





  //lb.setProblem(*qap);
  //greedy.setProblem(*qap);
  //gen.setProblem(*qap);


//  cout << "Size:" << s << endl;
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
//std::chrono::steady_clock::time_point end_total = std::chrono::steady_clock::now();
//std::cout << "Time Total: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end_total - begin_total).count() /1000.0 <<std::endl;


}
