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

int Problem::moveCost(const vector<int> &ant, int r, int s)
{
    int cost = 0;
    int t;
    s>r ? :t=s,s=r,r=t;
    for(int k=0;k<r;k++){
      cost +=
          flow[r][k] * (distance[ant[s]][ant[k]] - distance[ant[r]][ant[k]]) +
          flow[s][k] * (distance[ant[r]][ant[k]] - distance[ant[s]][ant[k]]) +
          flow[k][r] * (distance[ant[k]][ant[s]] - distance[ant[k]][ant[r]]) +
          flow[k][s] * (distance[ant[k]][ant[r]] - distance[ant[k]][ant[s]]);
    }
    for(int k=r+1;k<s;k++){
      cost +=
          flow[r][k] * (distance[ant[s]][ant[k]] - distance[ant[r]][ant[k]]) +
          flow[s][k] * (distance[ant[r]][ant[k]] - distance[ant[s]][ant[k]]) +
          flow[k][r] * (distance[ant[k]][ant[s]] - distance[ant[k]][ant[r]]) +
          flow[k][s] * (distance[ant[k]][ant[r]] - distance[ant[k]][ant[s]]);
    }
    for(int k=s+1;k<ant.size();k++){
      cost +=
          flow[r][k] * (distance[ant[s]][ant[k]] - distance[ant[r]][ant[k]]) +
          flow[s][k] * (distance[ant[r]][ant[k]] - distance[ant[s]][ant[k]]) +
          flow[k][r] * (distance[ant[k]][ant[s]] - distance[ant[k]][ant[r]]) +
          flow[k][s] * (distance[ant[k]][ant[r]] - distance[ant[k]][ant[s]]);
    }

    return cost;
}
