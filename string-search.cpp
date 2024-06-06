#include "string-search.hpp"

using namespace std;

int kmp(string& s, string& t) {
    return -1;
}  

// Works as long as the string only contains ASCII characters (char values > 0)
int rk(string& s, string& t) {
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