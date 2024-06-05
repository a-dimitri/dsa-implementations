#ifndef FLOW_H
#define FLOW_H

#include <vector>
#include <queue>
#include <limits>

using namespace std;

int EdmondsKarp(vector<vector<int>>& G, vector<vector<int>>& capacity, vector<vector<int>>& flow, int s, int t);

#endif