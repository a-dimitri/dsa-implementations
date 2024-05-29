// Binary search implementations

#include "binary-search.hpp"

using namespace std;

// Exact match binary search
// Assumes arr sorted in ascending order
int search(vector<int>& arr, int x) {
    int l = 0;
    int r = arr.size()-1;
    while ( l <= r ) {
        int m = l + (r-l)/2;
        if ( arr[m] == x ) return m;
        if ( arr[m] < x ) l = m+1;
        else r = m-1;
    }
    return -1;
}

// Finds largest element <= x
int lower_bound(vector<int>& arr, int x) {
    int l = 0;
    int r = arr.size()-1;
    if ( arr[l] > x ) return -1;
    while ( l <= r ) {
        int m = l + (r-l)/2;
        if ( arr[m] == x ) return m;
        if ( arr[m] < x ) l = m+1;
        else r = m-1;
    }
    return r;
}

// Finds smallest element >= x
int upper_bound(vector<int>& arr, int x) {
    int l = 0;
    int r = arr.size()-1;
    if ( arr[r] < x ) return r+1;
    while ( l <= r ) {
        int m = l + (r-l)/2;
        if ( arr[m] == x ) return m;
        if ( arr[m] < x ) l = m+1;
        else r = m-1;
    }
    return l;
}