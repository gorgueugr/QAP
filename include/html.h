#ifndef HTML_H_
#define HTML_H_


#include <string>
#include <vector>
#include <iostream>

class html{
private:
  std::string titulo;
  std::vector<string> caso;
  std::vector<int> coste;
  std::vector<int> mCoste;

  std::vector<double> desv;
  std::vector<double> tiempo;

public:
  html(string t){
    titulo = t;
  }
  ~html(){
    caso.clear();
    coste.clear();
    desv.clear();
    tiempo.clear();
  }

  void add(string c, int cost,int mejorCoste,double t){
    caso.push_back(c);
    coste.push_back(cost);
    double d = (double) 100*(cost-mejorCoste)/mejorCoste;
    mCoste.push_back(mejorCoste);
    desv.push_back(d);
    tiempo.push_back(t);
  }
  friend std::ostream& operator<<(std::ostream& o, const html& h);

};

std::ostream & operator<<(std::ostream & o, const html &h){
  o << "<table border=1 style='text-align:justify;'>" <<endl;
  o << "<tr><th colspan='5' >" << h.titulo << "</th></tr>" << endl;
  o << "<tr><th>Caso</th><th>Coste</th><th>desv</th><th>tiempo (S)</th><th>Mejor Coste</th></tr>";
  double sumDesv,sumT = 0;
  for(int i=0;i<h.coste.size();++i){
    sumDesv+=h.desv[i];
    sumT+=h.tiempo[i];
    o << "<tr>";
    o << "<td>";
      o << h.caso[i];
    o << "</td>";
    o << "<td>";
      o << h.coste[i];
    o << "</td>";
    o << "<td>";
      o << h.desv[i];
    o << "</td>";
    o << "<td>";
      o << h.tiempo[i];
    o << "</td>";
    o << "<td>";
      o << h.mCoste[i];
    o << "</td>";
    o << "</tr>" << endl;
  }
  sumDesv = sumDesv/h.coste.size();
  sumT = sumT/h.coste.size();

  o << "<tr><th colspan='2' > MEDIA</th><td>" << sumDesv << "</td><td>" << sumT <<"</td></tr>" << endl;

  o << "</table>" << endl;
  return o;
};

#endif
