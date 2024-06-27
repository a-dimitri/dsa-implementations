#ifndef FENWICK_TREE_H
#define FENWICK_TREE_H

#include <vector>

using namespace std;

template<typename T, class BinaryOp, class InvOp>
class fenwick_tree {
public:
    vector<T> t;
    int n;
    BinaryOp op;
    InvOp inv_op;
    T id;
    fenwick_tree(int n, BinaryOp op, InvOp inv_op, T id) : n(n), op(op), inv_op(inv_op), id(id) {
        t.resize(n, id);
    }
    fenwick_tree(vector<T>& arr, BinaryOp op, InvOp inv_op, T id) : fenwick_tree(arr.size(), op, inv_op, id) {
        for ( int i = 0; i < n; i++ ) {
            t[i] = op(t[i],arr[i]);
            int r = i | (i + 1);
            if (r < n) t[r] = op(t[r],t[i]);
        }
    }
    T query(int r) {
        T val = id;
        for ( int i = r; i >= 0; i = (i & (i+1)) - 1 ) val = op(val, t[i]);
        return val;
    }
    T query(int l, int r) {
        return inv_op(query(r),query(l-1));
    }
    void update(int idx, T delta) {
        for (int i = idx; i < n; i = i | (i+1) ) t[i] = op(t[i], delta);
    }
    void set(int idx, T v) {
        T delta = inv_op(v, query(idx,idx));
        update(idx,delta);
    }
};

template<typename T, class BinaryOp, class InvOp>
class fenwick_tree_2d {
public:
    vector<vector<T>> t;
    int m;
    int n;
    BinaryOp op;
    InvOp inv_op;
    T id;
    fenwick_tree_2d(int m, int n, BinaryOp op, InvOp inv_op, T id) : m(m), n(n), op(op), inv_op(inv_op), id(id) {
        t.resize(m, vector<T>(n, id));
    }
    fenwick_tree_2d(vector<vector<T>>& arr, BinaryOp op, InvOp inv_op, T id) : fenwick_tree_2d(arr.size(), arr[0].size(), op, inv_op, id) {
        for ( int i = 0; i < m; i++ ) {
            for ( int j = 0; j < n; ++j ) {
                t[i][j] = op(t[i][j],arr[i][j]);
                int r = i | (i + 1);
                int c = j | (j + 1);
                if (r < m) t[r][j] = op(t[r][j],t[i][j]);
                if (c < n) t[i][c] = op(t[i][c],t[i][j]);
                if (r < m && c < n) t[r][c] = inv_op(t[r][c],t[i][j]);
            }
        }
    }
    T query(int x, int y) {
        T val = id;
        for ( int i = x; i >= 0; i = (i & (i+1)) - 1 ) 
            for ( int j = y; j >= 0; j = (j & (j+1)) - 1 ) 
                val = op(val, t[i][j]);
        return val;
    }
    T query(int x1, int y1, int x2, int y2) {
        return op(inv_op(inv_op(query(x2,y2),query(x2,y1-1)),query(x1-1,y2)),query(x1-1,y1-1));
    }
    void update(int x, int y, T delta) {
        for (int i = x; i < m; i = i | (i+1) )
            for (int j = y; j < n; j = j | (j+1) )
                t[i][j] = op(t[i][j], delta);
    }
    void set(int x, int y, T v) {
        T delta = inv_op(v, query(x,y,x,y));
        update(x,y,delta);
    }
};

#endif