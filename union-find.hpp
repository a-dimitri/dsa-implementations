#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>

using namespace std;

// For integers from 0 to n-1
class UnionFind {
public:
    vector<int> set;
    vector<int> rank;

    UnionFind(int n);
    int Find(int x);
    void Union(int x, int y);
};

#endif