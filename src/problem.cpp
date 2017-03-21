#include "problem.h"

int Problem::calculateCost(const vector<int> &s)const{
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

int Problem::moveCost(vector<int> &s, int r, int s)
{
    int cost = 0;
    s>r ? :int t=s,s=r,r=t;
    for(int k=0;k<r;k++){
      cost +=
          flow_[r][k] * (distance[s[s]][s[k]] - distance[s[r]][s[k]]) +
          flow_[s][k] * (distance[s[r]][s[k]] - distance[s[s]][s[k]]) +
          flow_[k][r] * (distance[s[k]][s[s]] - distance[s[k]][s[r]]) +
          flow_[k][s] * (distance[s[k]][s[r]] - distance[s[k]][s[s]]);
    }
    for(int k=r+1;k<s;k++){
      cost +=
          flow_[r][k] * (distance[s[s]][s[k]] - distance[s[r]][s[k]]) +
          flow_[s][k] * (distance[s[r]][s[k]] - distance[s[s]][s[k]]) +
          flow_[k][r] * (distance[s[k]][s[s]] - distance[s[k]][s[r]]) +
          flow_[k][s] * (distance[s[k]][s[r]] - distance[s[k]][s[s]]);
    }
    for(int k=s+1;k<s.solution.size();k++){
      cost +=
          flow_[r][k] * (distance[s[s]][s[k]] - distance[s[r]][s[k]]) +
          flow_[s][k] * (distance[s[r]][s[k]] - distance[s[s]][s[k]]) +
          flow_[k][r] * (distance[s[k]][s[s]] - distance[s[k]][s[r]]) +
          flow_[k][s] * (distance[s[k]][s[r]] - distance[s[k]][s[s]]);
    }

    return cost;
}
