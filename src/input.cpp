#include "input.h"


Problem * Input::read()const{
  ifstream data(filename.c_str());

  if(!data){
    cout << "ERROR: abriendo el archivo" << endl;
    return 0;
  }
  Problem * p;
  p=new Problem();

  int s;
  data >> s;
  p->setSize(s);
  vector< vector<int> > d;
  vector< vector<int> > f;

  d.resize(s);
  f.resize(s);
  for(int i=0;i<s;i++){
    d[i].resize(s);
    f[i].resize(s);
  }

  for(int i=0;i<s;i++)
    for(int j=0;j<s;j++)
          data >> f[i][j];
          
  for(int i=0;i<s;i++)
    for(int j=0;j<s;j++)
      data >> d[i][j];



  p->setDistance(d);
  p->setFlow(f);
  d.clear();
  f.clear();
return p;

}
