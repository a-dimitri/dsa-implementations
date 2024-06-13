// Useful graph algorithms, with adjacency list constructors provided

#ifndef GRAPH_ALGOS_H 
#define GRAPH_ALGOS_H

#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
#include "union-find.hpp"

using namespace std;
typedef pair<int,int> PI;

// Assumes edge list of the form [u,v] for vertices as integers from 0 to n-1
vector<vector<int>> buildGraph(int n, vector<vector<int>>& edges);

// Assumes edge list of the form [u,v,w] for a directed edge from u to v with weight w
vector<vector<PI>> buildGraphWeighted(int n, vector<vector<int>>& edges);

// A template recursive DFS (returns nothing)
void dfs(vector<vector<int>>& G, vector<int>& visited, int curr);

// BFS for single source shortest path in an unweighted graph (can have cycles)
// dist[x] = -1 means vertex x was not reachable from source
vector<int> bfs(vector<vector<int>>& G, int source);

// Dijkstra's single source shortest path, assumes all weights are positive
// dist[x] = numeric_limits<int>::max() means the vertex x was not reachable from source
vector<int> dijkstra(vector<vector<PI>>& G, int source);

// Bellman-Ford single source shortest path, weights can be negative but no negative cycles
// dist[x] = numeric_limits<int>::max() means the vertex x was not reachable from source
vector<int> bellman_ford(vector<vector<PI>>& G, vector<vector<int>>& edges, int source);

// Floyd-Warshall
// All pairs shortest path, assumes no negative weight cycles
vector<vector<int>> floyd_warshall(vector<vector<PI>>& G);

// Topological sorting using Kahn's algorithm
// If the graph contains a cycle, an empty vector will be returned
vector<int> topsort(vector<vector<int>>& G);

// Kruskal's algorithm for minimum spanning tree
// Takes in a list of edges in the form [u,v,w]
// returns a list of edges in the form [u,v,w] that make up the MST
vector<vector<int>> kruskals(int n, vector<vector<int>>& edges);

#endif