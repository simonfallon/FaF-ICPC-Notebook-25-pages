#include "../template.h"

#include "binpow.cpp"

inline int mul(int a, int b) { return (1LL*a*b)%mod; }

int gauss(vector<vi> &a, vi &ans) {
  int n = sz(a), m = sz(a[0]) - 1;
  vi wh(m, -1); // Where the variable is
  for(int col=0, row=0; col<m && row<n; ++col) {
    int sel = row;
    fore(i, row, n - 1)
      if(abs(a[i][col]) > abs(a[sel][col])) sel = i;
    if(abs(a[sel][col]) <= eps) continue;

    fore(i, col, m) swap (a[sel][i], a[row][i]);
    wh[col] = row;

    forn(i,n){
      if (i != row) {
        int c = mul(a[i][col], inv(a[row][col]));
        fore (j, col, m){
          int val = mul(a[row][j], c);
          a[i][j] = (mod + a[i][j] - val) % mod;
        } 
      }
    }
    ++row;
  }

  ans.assign(m, 0);
  forn(i,m){
    if(wh[i] != -1)
      ans[i] = mul(a[wh[i]][m], inv(a[wh[i]][i]));
  }
  forn(i,n){
    ll sum = 0;
    forn(j, m) sum = (sum + mul(ans[j], a[i][j]))%mod;
    if(abs(sum - a[i][m]) > eps) return 0;
  }

  // infinitas soluciones
  forn(i, m) if(wh[i] == -1) return 1e9; 
  return 1;
}
