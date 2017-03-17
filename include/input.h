#ifndef INPUT_H__
#define INPUT_H__

#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include "problem.h"


class Input{
  private:
      string filename;
  public:
    Input(const string &file){filename=file;}
    void setFile(const string &file){filename=file;}
    string getFile()const{return filename;}
    Problem * read() const;
};

#endif
