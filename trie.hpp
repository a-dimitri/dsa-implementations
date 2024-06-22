#ifndef TRIE_H 
#define TRIE_H

#include <vector>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;

// When using any generic characters
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool terminal = false;
    TrieNode() {}
};

class Trie {
public:
    TrieNode* root;
    Trie() { root = new TrieNode(); };
    void insert(string word) {
        TrieNode* curr = root;
        for ( auto c :  word ) {
            if ( curr->children[c] == nullptr ) curr->children[c] = new TrieNode();
            curr = curr->children[c];
        }
        curr->terminal = true;
    }
    bool search(string word) {
        TrieNode* curr = root;
        for ( auto c : word ) {
            if ( curr->children[c] == nullptr ) return false;
            curr = curr->children[c];
        }
        return curr->terminal;
    }
    bool startsWith(string prefix) {
        TrieNode* curr = root;
        for ( auto c : prefix ) {
            if ( curr->children[c] == nullptr ) return false;
            curr = curr->children[c];
        }
        return true;
    }
};


// When only using lowercase English Letters
class TrieNodeLC {
public:
    vector<TrieNodeLC*> children;
    bool terminal = false;
    TrieNodeLC() { children.resize(26, nullptr); }
};

class TrieLC {
public:
    TrieNodeLC* root;
    TrieLC () { root = new TrieNodeLC(); };
    void insert(string word) {
        TrieNodeLC* curr = root;
        for ( char c :  word ) {
            if ( curr->children[c-'a'] == nullptr ) curr->children[c-'a'] = new TrieNodeLC();
            curr = curr->children[c-'a'];
        }
        curr->terminal = true;
    }
    bool search(string word) {
        TrieNodeLC* curr = root;
        for ( char c : word ) {
            if ( curr->children[c-'a'] == nullptr ) return false;
            curr = curr->children[c-'a'];
        }
        return curr->terminal;
    }
    bool startsWith(string prefix) {
        TrieNodeLC* curr = root;
        for ( char c : prefix ) {
            if ( curr->children[c-'a'] == nullptr ) return false;
            curr = curr->children[c-'a'];
        }
        return true;
    }
};

#endif