#include "problem.h"

int Problem::calculateCost(const vector<int> &s)const{
  // Calculate cost
    int cost = 0;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            cost += flow[i][j] *  distance[s[i]][s[j]];
        }
    }
    return cost;
}
