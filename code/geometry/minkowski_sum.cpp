#include "../template.h"

#include "point.cpp"

struct mink_sum{
  vector<pt> p;
  mink_sum(){}
  mink_sum(vector<pt>& p1, vector<pt>& p2, bool inter=0){
    if(inter) for(auto& [x, y] : p2) x = -x, y = -y;
    p.reserve(sz(p1) + sz(p2));
    reorder(p1),  reorder(p2);
    forn(i, 2) p1.pb(p1[i]), p2.pb(p2[i]);
    int i = 0, j = 0;
    while(i+2 < sz(p1) || j+2 < sz(p2)){
      p.pb(p1[i] + p2[j]);
      auto cro = (p1[i+1] - p1[i]) % (p2[j+1] - p2[j]);
      i += cro >= -eps;
      j += cro <= eps;
    }
  }
  void reorder(vector<pt> &pol){
    if(pol[2].side(pol[0], pol[1]) < 0) reverse(all(pol));
    int j = 0;
    forn(i, sz(pol)) 
      if(ii{pol[i].y, pol[i].x} < ii{pol[j].y, pol[j].x}) j = i;
    rotate(pol.begin(), pol.begin() + j, pol.end());
  }
  bool has(pt q){
    int cnt = 0;
    forn(i, sz(p))
      cnt += q.side(p[i], p[(i+1) % sz(p)]) >= 0;
    return cnt == sz(p);
  }
  bool intersect(pt shift = pt(0, 0)){ 
    return has(shift); 
  }
};  // Do polygons p1 and p2+shift intersect?