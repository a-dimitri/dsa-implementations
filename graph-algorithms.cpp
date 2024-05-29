// Useful graph algorithms, with adjacency list constructors provided
#include "graph-algorithms.hpp"

using namespace std;
typedef pair<int,int> PI;

// Assumes edge list of the form [u,v] for vertices as integers from 0 to n-1
vector<vector<int>> buildGraph(int n, vector<vector<int>> edges) {
    vector<vector<int>> G(n);
    for ( auto e : edges ) G[e[0]].push_back(e[1]);
    return G;
}

// Assumes edge list of the form [u,v,w] for a directed edge from u to v with weight w
vector<vector<PI>> buildGraphWeighted(int n, vector<vector<int>> edges) {
    vector<vector<PI>> G(n);
    for ( auto e : edges ) G[e[0]].push_back({e[1],e[2]});
    return G;
}

// A template recursive DFS (returns nothing)
void dfs(vector<vector<int>>& G, vector<int>& visited, int curr) {
    if ( visited[curr] ) return;
    visited[curr] = 1;
    for ( auto v : G[curr] ) {
        dfs(G, visited, v);
    }
    return;
}

// BFS for single source shortest path in an unweighted graph (can have cycles)
// dist[x] = -1 means vertex x was not reachable from source
vector<int> bfs(vector<vector<int>>& G, int source) {
    int n = G.size();
    vector<int> dist(n,-1);
    queue<int> Q;
    Q.push(source);
    dist[source] = 0;
    while ( !Q.empty() ) {
        auto u = Q.front();
        Q.pop();
        for ( auto v : G[u] ) {
            if ( dist[v] == -1 ) {
                dist[v] = dist[u] + 1;
                Q.push(v);
            }
        }
    }
    return dist;
}

// Dijkstra's single source shortest path, assumes all weights are positive
// dist[x] = numeric_limits<int>::max() means the vertex x was not reachable from source
vector<int> dijkstras(vector<vector<PI>>& G, int source) {
    int n = G.size();
    vector<int> dist(n,numeric_limits<int>::max());
    dist[source] = 0;
    priority_queue<PI, vector<PI>, greater<PI>> Q;
    Q.push({dist[source], source});
    while ( !Q.empty() ) {
        auto [d, u] = Q.top();
        Q.pop();
        if ( d != dist[u] ) continue;
        for ( auto [v, l] : G[u] ) {
            if ( dist[u] + l < dist[v] ) {
                dist[v] = dist[u] + l;
                Q.push({dist[v],v});
            }
        }
    }
    return dist;
}

// Floyd-Warshall
// All pairs shortest path, assumes no negative weight cycles
vector<vector<int>> FW(vector<vector<PI>>& G) {
    int n = G.size();
    vector<vector<vector<int>>> DP(n+1, vector<vector<int>>(n, vector<int>(n, numeric_limits<int>::max())));
    for ( int u = 0; u < n; ++u ) {
        for ( auto [v, w] : G[u] ) {
            DP[0][u][v] = w;
        }
        DP[0][u][u] = 0;
    }

    for ( int k = 1; k <= n; ++k) {
        for ( int u = 0; u < n; ++u ) {
            for ( int v = 0; v < n; ++v ) {
                DP[k][u][v] = min(static_cast<long long>(DP[k-1][u][v]), static_cast<long long>(DP[k-1][u][k-1]) + static_cast<long long>(DP[k-1][k-1][v]));
            }
        }
    }
    return DP[n];
}

// Kruskal's algorithm for minimum spanning tree
// Takes in a list of edges in the form [u,v,w]
// returns a list of edges in the form [u,v,w] that make up the MST
vector<vector<int>> kruskals(int n, vector<vector<int>>& edges) {
    sort(edges.begin(), edges.end(), [](vector<int>& e1, vector<int>& e2) {return e2[2] > e1[2];} );
    UnionFind UF(n);
    int count = 0;
    vector<vector<int>> T;
    for ( auto e : edges ) {
        if ( UF.Find(e[0]) != UF.Find(e[1]) ) {
            UF.Union(e[0], e[1]);
            T.push_back(e);
            count++;
        }
        if ( count == n-1 ) break;
    }
    return T;
}