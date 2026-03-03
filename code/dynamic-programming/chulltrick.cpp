#include "../template.h"

struct line {
  ll m, b;
  ll eval(ll x) { return m * x + b; }
  ld inter(line &l) { return (ld) (b - l.b) / (l.m - m); }
};

struct cht {
  vector<line> ls; // Lines in the hull, sorted by slope
  vector<ld> ints; // Intersections of consecutive lines
  int n;
  inline bool ok(line &a, line &b, line &c) {
    return a.inter(c) > a.inter(b);
  }
  void add(line &l) { /// m1 < m2 < m3 ...
    n = sz(ls);
    if(n && ls.back().m == l.m && ls.back().b >= l.b) 
      return;
    if(n== 1 && ls.back().m == l.m && ls.back().b < l.b){
      n--; ls.pop_back();
    }
    while(n >= 2 && !ok(ls[n-2], ls[n-1], l)) {
      --n; ls.pop_back(); ints.pop_back();
    }
    ls.pb(l); n++;
    if(n >= 2) ints.pb(ls[n-2].inter(ls[n-1]));
  }
  ll get_max(ld x) {
    if(sz(ls) == 0) return LLONG_MIN;
    if(sz(ls) == 1) return ls[0].eval(x);
    int pos = lower_bound(all(ints), x) - ints.begin();
    return ls[pos].eval(x);
  }
};
