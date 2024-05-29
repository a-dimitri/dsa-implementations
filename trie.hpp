#ifndef TRIE_H 
#define TRIE_H

#include <vector>
#include <map>

using namespace std;

// When using any generic characters
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool terminal;
    TrieNode();
};

class Trie {
public:
    TrieNode* root;
    Trie();
    void insert(string word);
    bool search(string word);
    bool startsWith(string word);
};


// When only using lowercase English Letters
class TrieNodeLC {
public:
    vector<TrieNodeLC*> children;
    bool terminal = false;
    TrieNodeLC();
};

class TrieLC {
public:
    TrieNodeLC* root;
    TrieLC ();
    void insert(string word);
    bool search(string word);
    bool startsWith(string word);
};

#endif