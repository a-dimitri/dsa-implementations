#ifndef FENWICK_TREE_H
#define FENWICK_TREE_H

#include <vector>

using namespace std;

template<typename T, class BinaryOp>
class fenwick_tree {
public:
    vector<T> t;
    int n;
    BinaryOp op;
    BinaryOp inv_op;
    fenwick_tree(int n, BinaryOp op, BinaryOp inv_op) : n(n), op(op), inv_op(inv_op) {
        t.resize(n);
    }
    fenwick_tree(vector<T>& arr, BinaryOp op, BinaryOp inv_op) : fenwick_tree(arr.size(), op, inv_op) {
        for ( int i = 0; i < n; i++ ) {
            t[i] += a[i];
            int r = i | (i + 1);
            if (r < n) t[r] = op(t[r],t[i]);
        }
    }
    T query(int r) {
        T val = 0;
        for ( int i = r; i >= 0; i = (i & (i+1)) - 1 ) val = op(val, t[i]);
        return val;
    }
    T query(int l, int r) {
        return inv_op(query(r),query(l-1));
    }
    void update(int idx, T v) {
        T delta = inv_op(v, t[idx]);
        for (int i = idx; i < n; i = i | (i+1) ) t[i] = op(t[i], delta);
    }
};

template<typename T, class BinaryOp>
class fenwick_tree_2d {
public:
    vector<vector<T>> t;
    int m;
    int n;
    BinaryOp op;
    BinaryOp inv_op;
    fenwick_tree(int m, int n, BinaryOp op, BinaryOp inv_op) : m(m), n(n), op(op), inv_op(inv_op) {
        t.resize(m, vector<T>(n));
    }
    fenwick_tree(vector<vector<T>>& arr, BinaryOp op, BinaryOp inv_op) : fenwick_tree(arr.size(), arr[0].size(), op, inv_op) {
        for ( int i = 0; i < m; ++i ) 
            for ( int j = 0; j < n; ++j ) 
                update(i, j, arr[i][j]);
    }
    T query(int x, int y) {
        T val = 0;
        for ( int i = x; i >= 0; i = (i & (i+1)) - 1 ) 
            for ( int j = y; j >= 0; j = (j & (j+1)) - 1 ) 
                val = op(val, t[i][j]);
        return val;
    }
    T query(int x1, int y1, int x2, int y2) {
        return inv_op(query(x2,y2),query(x1-1,x2-1));
    }
    void update(int x, int y, T v) {
        T delta = inv_op(v, t[x][y]);
        for (int i = x; i < n; i = i | (i+1) )
            for (int j = y; j < n; j = j | (j+1) ) 
                t[i][j] = op(t[i][j], delta);
    }
};

#endif