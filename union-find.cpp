#include "union-find.hpp"

using namespace std;

UnionFind::UnionFind(int n) {
    set.resize(n);
    rank.resize(n,0);
    for ( int i = 0; i < n; ++i ) set[i] = i;
}

int UnionFind::Find(int x) {
    if ( set[x] == x ) return x;
    set[x] = Find(set[x]);
    return set[x];
}

void UnionFind::Union(int x, int y) {
    int x_set = Find(x);
    int y_set = Find(y);
    if ( rank[x_set] > rank[y_set] ) set[y_set] = x_set;
    else if ( rank[y_set] > rank[x_set] ) set[x_set] = y_set;
    else {
        set[x_set] = y_set;
        rank[y_set]++;
    }
}