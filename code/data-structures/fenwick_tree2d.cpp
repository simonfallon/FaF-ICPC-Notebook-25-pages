#include "../template.h"

struct fwtree{ // 0-indexed
  int n, m;  vector<vll> bit;
  fwtree(){}
  fwtree(int n, int m)
    : n(n), m(m), bit(n + 1, vll(m + 1, 0)){}
  ll sum(int x, int y) { // [0, x], [0, y]
    ll val = 0;
    for(int i = x + 1; i; i -= i & -i)
      for(int j = y + 1; j; j -= j & -j) 
        val += bit[i][j];
    return val;
  }
  void add(int x, int y, ll val) {
    for(int i = x + 1; i <= n; i += i & -i)
      for(int j = y + 1; j <= m; j += j & -j)
        bit[i][j] += val;
  }
};