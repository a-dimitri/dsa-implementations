#ifndef SEG_TREE_H 
#define SEG_TREE_H

#include <vector>

using namespace std;

// A basic Sum Segment Tree that supports updates in O(logn) time, and querying sums in any interval in O(logn) time
// class segment_tree {
// public:
//     vector<int> t;
//     int n;
//     segment_tree(int n);
//     segment_tree(vector<int>& arr);
//     void build(vector<int>& arr, int v, int tl, int tr);
//     void update(int v, int tl, int tr, int index, int val);
//     int query(int v, int tl, int tr, int l, int r);
// };

template <typename T, class BinaryOp>
class segment_tree {
public:
    vector<T> t;
    int n;
    BinaryOp op;
    segment_tree(int n, BinaryOp op) {
        n = n;
        t.resize(4*n);
        op = op;
    }
    segment_tree(vector<T>& arr, BinaryOp op) {
        int n = arr.size();
        t.resize(4*n);
        op = op;
        build(arr,0,0,n-1);
    }
    void build(vector<T>& arr, int v, int tl, int tr) {
        if ( tl == tr ) t[v] = arr[tl];
        else {
            int tm = (tl+tr)/2;
            build(arr, 2*v+1, tl, tm);
            build(arr, 2*v+2, tm+1, tr);
            t[v] = op(t[2*v+1],t[2*v+2]);
        }
    }
    void update(int v, int tl, int tr, int index, T val){
        if ( tl == tr ) t[v] = val;
        else {
            int tm = (tl + tr)/2;
            if ( index <= tm ) update(2*v+1, tl, tm, index, val);
            else update(2*v+2, tm+1, tr, index, val);
            t[v] = op(t[2*v+1],t[2*v+2]);
        }
    }
    T query(int v, int tl, int tr, int l, int r) {
        if ( l > r ) return 0;
        if ( tl == l && tr == r ) return t[v];
        int tm = (tl+tr)/2;
        return op(query(2*v+1, tl, tm, l, min(tm, r)),query(2*v+2, tm+1, tr, max(l, tm+1), r));
    }
};

#endif