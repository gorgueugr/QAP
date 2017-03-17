#include <vector>
#include <iostream>

using namespace std;

class Solution{
private:
    vector<int> solution;
    int cost;
public:
  Solution():cost(0){};
  ~Solution(){Solution.clear();}
  vector<int> getSolution()const{return solution;}
  void setSolution(vector<int> s){solution=s;}
  int getSize(){return solution.size();}
  int getCost(){return cost;}
  int setCost(int c){cost=c;}
}
