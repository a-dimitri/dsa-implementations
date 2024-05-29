#include "trie.hpp"

using namespace std;

// When using any generic characters
TrieNode::TrieNode() {
    terminal = false;
}

Trie::Trie() { 
    root = new TrieNode(); 
}

void Trie::insert(string word) {
    TrieNode* curr = root;
    for ( auto c :  word ) {
        if ( curr->children[c] == nullptr ) curr->children[c] = new TrieNode();
        curr = curr->children[c];
    }
    curr->terminal = true;
    
}

bool Trie::search(string word) {
    TrieNode* curr = root;
    for ( auto c : word ) {
        if ( curr->children[c] == nullptr ) return false;
        curr = curr->children[c];
    }
    return curr->terminal;
}

bool Trie::startsWith(string prefix) {
    TrieNode* curr = root;
    for ( auto c : prefix ) {
        if ( curr->children[c] == nullptr ) return false;
        curr = curr->children[c];
    }
    return true;
}

// When only using lowercase English Letters
TrieNodeLC::TrieNodeLC() { 
    children.resize(26,nullptr); 
    terminal = false;
}

TrieLC::TrieLC () { 
    root = new TrieNodeLC(); 
}

void TrieLC::insert(string word) {
    TrieNodeLC* curr = root;
    for ( char c :  word ) {
        if ( curr->children[c-'a'] == nullptr ) curr->children[c-'a'] = new TrieNodeLC();
        curr = curr->children[c-'a'];
    }
    curr->terminal = true;
}

bool TrieLC::search(string word) {
    TrieNodeLC* curr = root;
    for ( char c : word ) {
        if ( curr->children[c-'a'] == nullptr ) return false;
        curr = curr->children[c-'a'];
    }
    return curr->terminal;
}

bool TrieLC::startsWith(string prefix) {
    TrieNodeLC* curr = root;
    for ( char c : prefix ) {
        if ( curr->children[c-'a'] == nullptr ) return false;
        curr = curr->children[c-'a'];
    }
    return true;
}