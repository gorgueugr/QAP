
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
  numCasos = 20;
  ficheros.resize(numCasos);
  mejorCoste.resize(numCasos);

  ficheros[0] =     "./bin/data/chr20b.dat";
  ficheros[1] =     "./bin/data/chr22a.dat";
  ficheros[2] =     "./bin/data/els19.dat";
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
  ficheros[18] =    "./bin/data/tai256c.dat";
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


    GenerationalPMX generationalPMX;
    GenerationalPOS generationalPOS;
    StationaryPMX stationaryPMX;
    StationaryPOS stationaryPOS;


    html h_greedy("GREEDY");
    html h_lb("LocalSearch");

    html h_generationalPMX("GenerationalPMX");
    html h_generationalPOS("GenerationalPOS");
    html h_stationaryPMX("stationaryPMX");
    html h_stationaryPOS("stationaryPOS");

    html h_bmb("BMB");
    html h_es("Enfriamiento Simulado");
    html h_ils("ILS");
    html h_ilses("ILS-ES");
    html h_grasp("GRASP");


    Input in;

for(int i=0;i<numCasos;i++){

  //cout << ficheros[i] << endl;

  in.setFile(ficheros[i]);
  string nombre = ficheros[i].substr(ficheros[i].find_last_of("/")+1,ficheros[i].size());

  Problem * qap=in.read();

  greedy.setProblem(*qap);
  lb.setProblem(*qap);
  gr.setProblem(*qap);
  ilsEs.setProblem(*qap);
  ils.setProblem(*qap);
  es.setProblem(*qap);
  b.setProblem(*qap);
  generationalPMX.setProblem(*qap);
  generationalPOS.setProblem(*qap);
  stationaryPMX.setProblem(*qap);
  stationaryPOS.setProblem(*qap);





  //Genetic gen;
  int s=qap->getSize();




  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  lb.execute();
  std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
  //std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;
  Solution * sol=&lb.getSolution();

  //  cout << "GRASP solution:" << endl;
  //  for(int i=0;i<sol->solution.size();++i){
  //    cout << " "<< sol->solution[i];
  //  }
  //  cout << endl;
  //  cout << "Coste: " << sol->cost << endl;
  h_lb.add(nombre,sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
  //  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  //  cout << endl;

  std::cout << "LocalSearch" << '\n';




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
    h_greedy.add(nombre,sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
  //  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  //  cout << endl;

  std::cout << "greedy" << '\n';


   begin = std::chrono::steady_clock::now();
   b.execute();
   end= std::chrono::steady_clock::now();
  //std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;
    sol=&b.getSolution();

  //cout << "BMB solution:" << endl;
  //for(int i=0;i<sol->solution.size();++i){
  //  cout << " "<< sol->solution[i];
  //}
  //cout << endl;
  //cout << "Coste: " << sol->cost << endl;
  h_bmb.add(nombre,sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
  //cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  //cout << endl;

  std::cout << "bmb" << '\n';



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
  h_es.add(nombre,sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
  //cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  //cout << endl;
  std::cout << "es" << '\n';



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
    h_ils.add(nombre,sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
  //  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  //  cout << endl;

  std::cout << "ils" << '\n';

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
    h_ilses.add(nombre,sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
  //  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  //  cout << endl;

  std::cout << "okilses" << '\n';


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
    h_grasp.add(nombre,sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
  //  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  //  cout << endl;
  std::cout << "grasp" << '\n';



  begin = std::chrono::steady_clock::now();
  generationalPMX.execute();
  end= std::chrono::steady_clock::now();
  //std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;
  sol=&generationalPMX.getSolution();

  //  cout << "GRASP solution:" << endl;
  //  for(int i=0;i<sol->solution.size();++i){
  //    cout << " "<< sol->solution[i];
  //  }
  //  cout << endl;
  //  cout << "Coste: " << sol->cost << endl;
  h_generationalPMX.add(nombre,sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
  //  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  //  cout << endl;
  std::cout << "generationalPMX" << '\n';


  begin = std::chrono::steady_clock::now();
  generationalPOS.execute();
  end= std::chrono::steady_clock::now();
  //std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;
  sol=&generationalPOS.getSolution();

  //  cout << "GRASP solution:" << endl;
  //  for(int i=0;i<sol->solution.size();++i){
  //    cout << " "<< sol->solution[i];
  //  }
  //  cout << endl;
  //  cout << "Coste: " << sol->cost << endl;
  h_generationalPOS.add(nombre,sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
  //  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  //  cout << endl;
  std::cout << "generationalPOS" << '\n';


  begin = std::chrono::steady_clock::now();
  stationaryPMX.execute();
  end= std::chrono::steady_clock::now();
  //std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;
  sol=&stationaryPMX.getSolution();

  //  cout << "GRASP solution:" << endl;
  //  for(int i=0;i<sol->solution.size();++i){
  //    cout << " "<< sol->solution[i];
  //  }
  //  cout << endl;
  //  cout << "Coste: " << sol->cost << endl;
  h_stationaryPMX.add(nombre,sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
  //  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
  //  cout << endl;
  std::cout << "stationaryPMX" << '\n';



    begin = std::chrono::steady_clock::now();
    stationaryPOS.execute();
    end= std::chrono::steady_clock::now();
    //std::cout << "Time: = " << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0 <<std::endl;
    sol=&stationaryPOS.getSolution();

    //  cout << "GRASP solution:" << endl;
    //  for(int i=0;i<sol->solution.size();++i){
    //    cout << " "<< sol->solution[i];
    //  }
    //  cout << endl;
    //  cout << "Coste: " << sol->cost << endl;
    h_stationaryPOS.add(nombre,sol->cost,mejorCoste[i],(double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() /1000.0);
    //  cout << "correct Solution: " << (int) sol->checkSolution() << endl;
    //  cout << endl;
    std::cout << "stationaryPOS" << '\n';


}

  std::cout << h_lb << '\n';
  std::cout << h_greedy << '\n';
  std::cout << h_bmb << '\n';
  std::cout << h_es << '\n';
  std::cout << h_ils << '\n';
  std::cout << h_ilses << '\n';
  std::cout << h_grasp << '\n';

  std::cout << h_generationalPMX << '\n';
  std::cout << h_generationalPOS << '\n';
  std::cout << h_stationaryPMX << '\n';
  std::cout << h_stationaryPOS << '\n';



}
