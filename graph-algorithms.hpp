// Useful graph algorithms, with adjacency list constructors provided

#ifndef GRAPH_ALGOS_H 
#define GRAPH_ALGOS_H

#include <vector>
#include <map>
#include <queue>
#include <limits>
#include "union-find.hpp"

using namespace std;
typedef pair<int,int> PI;

// Assumes edge list of the form [u,v] for vertices as integers from 0 to n-1
vector<vector<int>> buildGraph(int n, vector<vector<int>> edges);

// Assumes edge list of the form [u,v,w] for a directed edge from u to v with weight w
vector<vector<PI>> buildGraphWeighted(int n, vector<vector<int>> edges);

// A template recursive DFS (returns nothing)
void dfs(vector<vector<int>>& G, vector<int>& visited, int curr);

// BFS for single source shortest path in an unweighted graph (can have cycles)
// dist[x] = -1 means vertex x was not reachable from source
vector<int> bfs(vector<vector<int>>& G, int source);

// Dijkstra's single source shortest path, assumes all weights are positive
// dist[x] = numeric_limits<int>::max() means the vertex x was not reachable from source
vector<int> dijkstras(vector<vector<PI>>& G, int source);

// Floyd-Warshall
// All pairs shortest path, assumes no negative weight cycles
vector<vector<int>> FW(vector<vector<PI>>& G);

// Kruskal's algorithm for minimum spanning tree
// Takes in a list of edges in the form [u,v,w]
// returns a list of edges in the form [u,v,w] that make up the MST
vector<vector<int>> kruskals(int n, vector<vector<int>>& edges);

#endif