#ifndef BIN_SEARCH_H
#define BIN_SEARCH_H

// Binary search implementations

#include <vector>
#include <iostream>

using namespace std;

int search(vector<int>& arr, int x);
int lower_bound(vector<int>& arr, int x);
int upper_bound(vector<int>& arr, int x);

#endif