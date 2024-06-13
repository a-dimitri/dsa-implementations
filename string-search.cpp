#include "string-search.hpp"

using namespace std;

int knuth_morris_pratt(string& s, string& t) {
    int n = s.size();
    int m = t.size();
    
    // Compute the failure function of t
    vector<int> F(m);
    int curr_len = 0;
    int i = 1;
    while ( i < m ) {
        if ( t[i] == t[curr_len] ) {
            curr_len++;
            F[i] = curr_len;
            i++;
        } else if ( curr_len != 0 ) curr_len = F[curr_len];
        else F[i++] = 0;
    }

    // Search for a match
    int j = i = 0;
    while ( n - i >= m - j ) {
        if ( s[i] == t[j] ) {
            i++;
            j++;
            if ( j == m ) return i-j;
        } else if ( j == 0 ) i++;
        else j = F[j-1];
    }
    return -1;
}  

// Works as long as the string only contains ASCII characters (char values > 0)
int rabin_karp(string& s, string& t) {
    int n = s.size();
    int m = t.size();
    if ( m > n ) return -1;

    const int p = 16909313; // A large prime that is small enough for p*d to fit in an int without overflow
    const int d = numeric_limits<char>::max();

    // Get the hash value for string t and the first s characters of string s
    int ht = 0;
    int hs = 0;
    int dmp = 1;
    for ( int i = 0; i < m; ++i ) {
        ht = ((ht*d)%p + static_cast<int>(t[i]))%p;
        hs = ((hs*d)%p + static_cast<int>(s[i]))%p;
        dmp = (dmp*d)%p;
    }

    // If there is a match already, we can return 0
    if ( hs == ht ) if ( _match(s,t,0) ) return 0;

    for ( int i = 1; i <= n-m; ++i ) {
        hs = ((hs*d)%p - (dmp*s[i-1])%p + static_cast<int>(s[i+m-1]) + p)%p;
        if ( hs == ht ) if ( _match(s,t,i) ) return i;
    }

    return -1;
    
}

bool _match(string& s, string& t, int i) {
    for ( int j = 0; j < t.size(); ++j ) if ( t[j] != s[i+j] ) return false;
    return true;
}