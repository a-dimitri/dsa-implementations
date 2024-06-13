#ifndef STRING_SEARCH_H
#define STRING_SEARCH_H

#include <string>
#include <vector>
#include <limits>

using namespace std;

// Returns index of the first match of t in s, returns -1 if no match
int knuth_morris_pratt(string& s, string& t);

// Returns index of the first match of t in s, returns -1 if no match
int rabin_karp(string& s, string& t);

bool _match(string& s, string& t, int i);

#endif