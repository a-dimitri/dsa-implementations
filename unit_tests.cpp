#include "binary-search.hpp"
#include "graph-algorithms.hpp"
#include "trie.hpp"
#include "union-find.hpp"
#include <iostream>
#include <cassert>

using namespace std;

// Sub-routine for testing binary-search
void _test_binary_search() {
    vector<int> arr = {0,1,2,3,4,6,7,8,9,10};
    assert(arr[search(arr, 0)] == 0);
    assert(arr[search(arr, 7)] == 7);
    assert(arr[search(arr, 10)] == 10);
    assert(search(arr, 5) == -1);
    assert(lower_bound(arr, -1) == -1);
    assert(arr[upper_bound(arr, -1)] == 0);
    assert(arr[lower_bound(arr, 11)] == 10);
    assert(upper_bound(arr, 11) == 10);
    assert(arr[lower_bound(arr, 5)] == 4);
    assert(arr[upper_bound(arr, 5)] == 6);
    assert(arr[lower_bound(arr, 8)] == 8);
    assert(arr[upper_bound(arr, 8)] == 8);
}

// Sub-routine for testing various graph algorithms
void _test_graph_algos() {

    // Test BFS
    auto G = buildGraph(5, {{0,1},{1,2},{2,3},{0,2},{1,4}});
    vector<int> dist = bfs(G,0);
    assert((dist == vector<int> {0,1,1,2,2}));
    dist = bfs(G,2);
    assert((dist == vector<int> {-1,-1,0,1,-1}));

    // Test Dijkstras
    auto G2 = buildGraphWeighted(5, {{0,1,3},{1,2,1},{2,3,2},{0,2,5},{1,4,7},{3,4,1}});
    int m = numeric_limits<int>::max();
    dist = dijkstras(G2,0);
    assert((dist == vector<int> {0,3,4,6,7}));
    dist = dijkstras(G2,2);
    assert((dist == vector<int> {m,m,0,2,3}));
    auto dist_FW = FW(G2);
    assert((dist_FW == vector<vector<int>> {{0,3,4,6,7},
                                            {m,0,1,3,4},
                                            {m,m,0,2,3},
                                            {m,m,m,0,1},
                                            {m,m,m,m,0}}));
    
    vector<vector<int>> edges = {{0,1,1},{1,2,2},{2,3,5},{0,2,3},{0,3,4}};
    auto T = kruskals(4, edges);
    assert( ( T == vector<vector<int>> {{0,1,1}, {1,2,2}, {0,3,4}}) );
}

// Sub-routine for testing tries
void _test_trie() {
    TrieLC T = TrieLC();
    T.insert("apple");
    assert(T.search("apple"));
    assert(!T.search("app"));
    assert(T.startsWith("app"));
    T.insert("app");
    assert(T.search("app"));

    Trie T2 = Trie();
    T2.insert("4pp|e");
    assert(T2.search("4pp|e"));
    assert(!T2.search("4pp"));
    assert(T2.startsWith("4pp"));
    T2.insert("4pp");
    assert(T2.search("4pp"));
}


void _test_union_find() {
    UnionFind UF = UnionFind(6);
    assert(UF.Find(4) == 4);
    UF.Union(0,1);
    UF.Union(2,3);
    assert(UF.Find(0) == UF.Find(1));
    assert(UF.Find(2) == UF.Find(3));
    UF.Union(1,2);
    assert(UF.Find(0) == UF.Find(3));
}

int main(int argc, char const *argv[])
{   
    cout << "--------------------------------------" << endl;
    cout << "Testing binary search..." << endl;
    _test_binary_search();
    cout << "All binary search tests passed" << endl;
    cout << "--------------------------------------" << endl;

    cout << "--------------------------------------" << endl;
    cout << "Testing trie..." << endl;
    _test_trie();
    cout << "All trie tests passed" << endl;
    cout << "--------------------------------------" << endl;

    cout << "--------------------------------------" << endl;
    cout << "Testing union find..." << endl;
    _test_union_find();
    cout << "All union find tests passed" << endl;
    cout << "--------------------------------------" << endl;

    cout << "--------------------------------------" << endl;
    cout << "Testing graph algorithms..." << endl;
    _test_graph_algos();
    cout << "All graph algorithm tests passed" << endl;
    cout << "--------------------------------------" << endl;

    return 0;
}