#include "flow.hpp"

using namespace std;

// G should be an adjacency list for the directed flow network
// capacity[u][v] should 
int EdmondsKarp(vector<vector<int>>& G, vector<vector<int>>& capacity, vector<vector<int>>& flow, int s, int t) {
    int max_flow = 0;
    int n = G.size();
    vector<int> pred(n);
    vector<int> path_flow(n);

    while ( pred[t] != -1 ) {
        fill(pred.begin(), pred.end(), -1);
        fill(path_flow.begin(), path_flow.end(), numeric_limits<int>::max());
        queue<int> Q;
        Q.push(s);
        
        while ( !Q.empty() ) {
            auto u = Q.front();
            Q.pop();
            for ( auto v : G[u] ) {
                if ( pred[v] == -1 && v != s && flow[u][v] < capacity[u][v] ) {
                    pred[v] = u;
                    path_flow[v] = min(path_flow[u], capacity[u][v] - flow[u][v]);
                    Q.push(v);
                }
            }
        }
        if ( pred[t] != -1 ) {
            max_flow += path_flow[t];
            for ( auto u = t; u != s; u = pred[u] ) {
                flow[pred[u]][u] += path_flow[t];
                flow[u][pred[u]] -= path_flow[t];
            }
        }
    }
    
    return max_flow;
}