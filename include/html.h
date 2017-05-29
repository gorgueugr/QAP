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
    double d = 100*(cost-mejorCoste)/mejorCoste;
    mCoste.push_back(mejorCoste);
    desv.push_back(d);
    tiempo.push_back(t);
  }
  friend std::ostream& operator<<(std::ostream& o, const html& h);

};

std::ostream & operator<<(std::ostream & o, const html &h){
  o << "<table>" <<endl;
  o << "<tr><td colspan='2'>" << h.titulo << "</td></tr>" << endl;
  for(int i=0;i<h.coste.size();++i){
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
    o << "</tr>" << endl;
  }
  o << "</table>" << endl;
  return o;
};

#endif
