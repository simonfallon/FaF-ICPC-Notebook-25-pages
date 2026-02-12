#include "../template.h"

struct fwtree{ // 0-indexed
  int n;  vll bit;
  fwtree(int n): n(n), bit(n + 1){}
  ll rsq(int r){ // [0, r]
    ll sum = 0;
    for(++r; r; r -= r & -r) sum += bit[r];
    return sum;
  }
  ll rsq(int l, int r){
    return rsq(r) - (l == 0 ? 0 : rsq(l - 1));
  }
  void upd(int r, ll val){
    for(++r; r <= n; r += r & -r) bit[r] += val;
  }
};