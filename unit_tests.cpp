#include "binary-search.hpp"
#include "graph-algorithms.hpp"
#include "trie.hpp"
#include "union-find.hpp"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

// Sub-routine for testing binary-search
void _test_binary_search() {
    cout << "--------------------------------------" << endl;
    cout << "Testing binary search..." << endl;
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
    cout << "All binary search tests passed" << endl;
    cout << "--------------------------------------" << endl;
}

// Sub-routine for testing various graph algorithms
void _test_graph_algos() {
    cout << "--------------------------------------" << endl;
    cout << "Testing graph algorithms..." << endl;
    // Test BFS
    vector<vector<int>> edges = {{0,1},{1,2},{2,3},{0,2},{1,4}};
    auto G = buildGraph(5, edges);
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

    // Test Kahn's (topological sort)
    vector<int> order = topsort(G);
    for ( auto e : edges ) assert(find(order.begin(),order.end(),e[0]) - find(order.begin(), order.end(), e[1]) < 0);
    auto G3 = buildGraph(5, {{0,1},{1,2},{2,3},{0,2},{1,4},{3,1}});
    assert(topsort(G3) == vector<int>());
    
    // Test Kruskals
    vector<vector<int>> E = {{0,1,1},{1,2,2},{2,3,5},{0,2,3},{0,3,4}};
    auto T = kruskals(4, E);
    assert( ( T == vector<vector<int>> {{0,1,1}, {1,2,2}, {0,3,4}}) );
    cout << "All graph algorithm tests passed" << endl;
    cout << "--------------------------------------" << endl;
}

// Sub-routine for testing tries
void _test_trie() {
    cout << "--------------------------------------" << endl;
    cout << "Testing trie..." << endl;
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
    cout << "All trie tests passed" << endl;
    cout << "--------------------------------------" << endl;
}


void _test_union_find() {
    cout << "--------------------------------------" << endl;
    cout << "Testing union find..." << endl;
    UnionFind UF = UnionFind(6);
    assert(UF.Find(4) == 4);
    UF.Union(0,1);
    UF.Union(2,3);
    assert(UF.Find(0) == UF.Find(1));
    assert(UF.Find(2) == UF.Find(3));
    UF.Union(1,2);
    assert(UF.Find(0) == UF.Find(3));
    cout << "All union find tests passed" << endl;
    cout << "--------------------------------------" << endl;
}

void _print_usage() {
    cout << "To run all tests, use [-a | --all]" << endl;
    cout << "To see a full list of valid commands, use [-h | --help]" << endl;
};

void _print_help() {
    cout << "Here is a list of all valid commands to run tests for individual modules: " << endl;
    cout << "    [-a | --all]                 Tests all modules" << endl;
    cout << "    [-bs | --binary_search]      Tests the binary search module" << endl;
    cout << "    [-t | --trie]                Tests the trie module" << endl;
    cout << "    [-uf | --union_find]         Tests the union find module" << endl;
    cout << "    [-g | --graph_algorithms]    Tests the graph algorithms module" << endl;
};

int main(int argc, char const *argv[])
{   
    using namespace std::literals;
    bool bs = false, t = false, uf = false, g = false;
    if ( argc == 1 ) _print_usage();
    else if ( argv[1] == "-h"sv || argv[1] == "--help"sv ) _print_help();
    else if ( argv[1] == "-a"sv || argv[1] == "--all"sv) bs = t = uf = g = true;
    else { 
        for ( int x = 1; x < argc; ++x ) {
            if ( argv[x] == "-bs"sv | argv[x] == "--binary_search"sv ) bs = true;
            else if ( argv[x] == "-t"sv | argv[x] == "--trie"sv ) t = true;
            else if ( argv[x] == "-uf"sv | argv[x] == "--union_find"sv ) uf = true;
            else if ( argv[x] == "-g"sv | argv[x] == "--graph_algorithms"sv ) g = true;
        }
    }
    if ( bs || t || uf || g ) cout << "--------------------------------------" << endl;
    if ( bs ) _test_binary_search();
    if ( t ) _test_trie();
    if ( uf ) _test_union_find();
    if ( g ) _test_graph_algos();
    if ( bs || t || uf || g ) cout << "--------------------------------------" << endl;
    return 0;
}