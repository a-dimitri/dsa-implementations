#ifndef SEG_TREE_H 
#define SEG_TREE_H

#include <vector>

using namespace std;

template <typename T>
struct Max {
    T operator()(T a, T b) {
        return max(a,b);
    }
};

// template <typename T>
// struct Min {
//     T operator()(T a, T b) {
//         return min(a,b);
//     }
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